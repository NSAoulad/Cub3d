/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:39:04 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:39:23 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t rgb_to_hex(t_color color)
{
    return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 0xFF);
}

uint32_t get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
        return 0;
    int pixel_index = (y * texture->width + x) * 4;
    uint8_t *pixel = &texture->pixels[pixel_index];
    uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
    return color;
}

void render(t_data *data)
{
    memset(data->image->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));

    uint32_t floor_color = rgb_to_hex(data->floor_color);
    uint32_t ceiling_color = rgb_to_hex(data->ceiling_color);

    // Draw floor and ceiling
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        uint32_t color = (y < WINDOW_HEIGHT / 2) ? ceiling_color : floor_color;
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            mlx_put_pixel(data->image, x, y, color);
        }
    }

    // Raycasting and texture rendering
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Calculate ray position and direction
        double camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        double ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
        double ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;

        // Map position
        int map_x = (int)data->player.x;
        int map_y = (int)data->player.y;

        // Length of ray from current position to next x or y-side
        double side_dist_x;
        double side_dist_y;

        // Length of ray from one x or y-side to next x or y-side
        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        // Direction to step in x and y (either +1 or -1)
        int step_x;
        int step_y;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?

        // Calculate step and initial sideDist
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (data->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (data->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
        }

        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square in x or y direction
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0; // 0 for x-side
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1; // 1 for y-side
            }
            // Check if ray has hit a wall
            if (data->map[map_y][map_x] == '1')
                hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0)
            perp_wall_dist = (map_x - data->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - data->player.y + (1 - step_y) / 2) / ray_dir_y;

        // Calculate height of line to draw on screen
        int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;

        // Choose texture based on wall hit direction
        mlx_texture_t *texture;
        if (side == 0)
        {
            if (ray_dir_x > 0)
                texture = data->texture_west;
            else
                texture = data->texture_east;
        }
        else
        {
            if (ray_dir_y > 0)
                texture = data->texture_north;
            else
                texture = data->texture_south;
        }

        // Calculate value of wallX (exact position where wall was hit)
        double wall_x; // X coordinate on the wall
        if (side == 0)
            wall_x = data->player.y + perp_wall_dist * ray_dir_y;
        else
            wall_x = data->player.x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        // x coordinate on the texture
        int tex_x = (int)(wall_x * (double)texture->width);
        if (side == 0 && ray_dir_x > 0)
            tex_x = texture->width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = texture->width - tex_x - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texture->height / line_height;
        // Starting texture coordinate
        double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

        for (int y = draw_start; y < draw_end; y++)
        {
            // Cast the texture coordinate to integer, and mask with texture height
            int tex_y = (int)tex_pos & (texture->height - 1);
            tex_pos += step;
            // Get the color from the texture pixel
            uint32_t color = get_texture_pixel(texture, tex_x, tex_y);
            // Apply shading if desired
            if (side == 1)
                color = (color >> 1) & 0x7F7F7F7F;
            // Draw the pixel
            mlx_put_pixel(data->image, x, y, color);
        }
    }
}
