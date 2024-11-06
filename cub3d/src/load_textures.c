/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:39:14 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:39:26 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void load_textures(t_data *data)
{
    data->texture_north = mlx_load_png(data->north_texture_path);
    if (!data->texture_north)
    {
        fprintf(stderr, "Error\nFailed to load north texture.\n");
        terminate(data);
    }

    data->texture_south = mlx_load_png(data->south_texture_path);
    if (!data->texture_south)
    {
        fprintf(stderr, "Error\nFailed to load south texture.\n");
        terminate(data);
    }

    data->texture_west = mlx_load_png(data->west_texture_path);
    if (!data->texture_west)
    {
        fprintf(stderr, "Error\nFailed to load west texture.\n");
        terminate(data);
    }

    data->texture_east = mlx_load_png(data->east_texture_path);
    if (!data->texture_east)
    {
        fprintf(stderr, "Error\nFailed to load east texture.\n");
        terminate(data);
    }
}
