/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:37:58 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:38:43 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void terminate(t_data *data)
{
    // Free textures
    if (data->texture_north)
        mlx_delete_texture(data->texture_north);
    if (data->texture_south)
        mlx_delete_texture(data->texture_south);
    if (data->texture_west)
        mlx_delete_texture(data->texture_west);
    if (data->texture_east)
        mlx_delete_texture(data->texture_east);

    // Free texture paths
    free(data->north_texture_path);
    free(data->south_texture_path);
    free(data->west_texture_path);
    free(data->east_texture_path);

    // Free map data
    if (data->map)
    {
        for (int i = 0; data->map[i]; i++)
            free(data->map[i]);
        free(data->map);
    }

    // Delete image and terminate MLX
    if (data->image)
        mlx_delete_image(data->mlx, data->image);
    if (data->mlx)
        mlx_terminate(data->mlx);

    exit(EXIT_SUCCESS);
}

int32_t main(int32_t argc, char **argv)
{
    t_data data = {0}; // Initialize all fields to zero or NULL

    if (argc != 2)
    {
        fprintf(stderr, "Error\nInvalid number of arguments.\n");
        fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
        return (EXIT_FAILURE);
    }

    // Initialize MLX42
    data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
    if (!data.mlx)
    {
        fprintf(stderr, "Error\nMLX42 initialization failed.\n");
        return (EXIT_FAILURE);
    }

    // Create an image
    data.image = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!data.image)
    {
        fprintf(stderr, "Error\nFailed to create MLX42 image.\n");
        terminate(&data);
    }

    // Add the image to the window
    if (mlx_image_to_window(data.mlx, data.image, 0, 0) < 0)
    {
        fprintf(stderr, "Error\nFailed to put image to window.\n");
        terminate(&data);
    }

    // Parse the map file
    parse_map(argv[1], &data);

    // Load textures
    load_textures(&data);

    // Initialize game components
    init_game(&data);

    // Hook functions
    hook_functions(&data);

    // Start the MLX42 loop
    mlx_loop(data.mlx);

    // Clean up and exit
    terminate(&data);
    return (EXIT_SUCCESS);
}
