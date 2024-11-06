/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:14 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:43:09 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_data *data = (t_data *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_ESCAPE)
            terminate(data);
        else if (keydata.key == MLX_KEY_W)
        {
            // Move forward
            if (data->map[(int)(data->player.y)][(int)(data->player.x + data->player.dir_x * data->player.move_speed)] == '0')
                data->player.x += data->player.dir_x * data->player.move_speed;
            if (data->map[(int)(data->player.y + data->player.dir_y * data->player.move_speed)][(int)(data->player.x)] == '0')
                data->player.y += data->player.dir_y * data->player.move_speed;
        }
        else if (keydata.key == MLX_KEY_S)
        {
            // Move backward
            if (data->map[(int)(data->player.y)][(int)(data->player.x - data->player.dir_x * data->player.move_speed)] == '0')
                data->player.x -= data->player.dir_x * data->player.move_speed;
            if (data->map[(int)(data->player.y - data->player.dir_y * data->player.move_speed)][(int)(data->player.x)] == '0')
                data->player.y -= data->player.dir_y * data->player.move_speed;
        }
        else if (keydata.key == MLX_KEY_A)
        {
            // Strafe left
            double perp_dir_x = -data->player.dir_y;
            double perp_dir_y = data->player.dir_x;
            if (data->map[(int)(data->player.y)][(int)(data->player.x + perp_dir_x * data->player.move_speed)] == '0')
                data->player.x += perp_dir_x * data->player.move_speed;
            if (data->map[(int)(data->player.y + perp_dir_y * data->player.move_speed)][(int)(data->player.x)] == '0')
                data->player.y += perp_dir_y * data->player.move_speed;
        }
        else if (keydata.key == MLX_KEY_D)
        {
            // Strafe right
            double perp_dir_x = data->player.dir_y;
            double perp_dir_y = -data->player.dir_x;
            if (data->map[(int)(data->player.y)][(int)(data->player.x + perp_dir_x * data->player.move_speed)] == '0')
                data->player.x += perp_dir_x * data->player.move_speed;
            if (data->map[(int)(data->player.y + perp_dir_y * data->player.move_speed)][(int)(data->player.x)] == '0')
                data->player.y += perp_dir_y * data->player.move_speed;
        }
        else if (keydata.key == MLX_KEY_LEFT)
        {
            // Rotate left
            double old_dir_x = data->player.dir_x;
            data->player.dir_x = data->player.dir_x * cos(data->player.rot_speed) - data->player.dir_y * sin(data->player.rot_speed);
            data->player.dir_y = old_dir_x * sin(data->player.rot_speed) + data->player.dir_y * cos(data->player.rot_speed);
            double old_plane_x = data->player.plane_x;
            data->player.plane_x = data->player.plane_x * cos(data->player.rot_speed) - data->player.plane_y * sin(data->player.rot_speed);
            data->player.plane_y = old_plane_x * sin(data->player.rot_speed) + data->player.plane_y * cos(data->player.rot_speed);
        }
        else if (keydata.key == MLX_KEY_RIGHT)
        {
            // Rotate right
            double old_dir_x = data->player.dir_x;
            data->player.dir_x = data->player.dir_x * cos(-data->player.rot_speed) - data->player.dir_y * sin(-data->player.rot_speed);
            data->player.dir_y = old_dir_x * sin(-data->player.rot_speed) + data->player.dir_y * cos(-data->player.rot_speed);
            double old_plane_x = data->player.plane_x;
            data->player.plane_x = data->player.plane_x * cos(-data->player.rot_speed) - data->player.plane_y * sin(-data->player.rot_speed);
            data->player.plane_y = old_plane_x * sin(-data->player.rot_speed) + data->player.plane_y * cos(-data->player.rot_speed);
        }
    }
}

void loop_hook(void *param)
{
    t_data *data = (t_data *)param;
    render(data);
}

void hook_functions(t_data *data)
{
    mlx_key_hook(data->mlx, &key_hook, data);
    mlx_loop_hook(data->mlx, &loop_hook, data);
}
