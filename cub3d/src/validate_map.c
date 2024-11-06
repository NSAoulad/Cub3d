/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_map.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:54 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:31:36 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void set_player(t_data *data, int x, int y, char dir)
{
    data->player.x = x + 0.5;
    data->player.y = y + 0.5;
    if (dir == 'N')
    {
        data->player.dir_x = 0;
        data->player.dir_y = -1;
        data->player.plane_x = 0.66;
        data->player.plane_y = 0;
    }
    else if (dir == 'S')
    {
        data->player.dir_x = 0;
        data->player.dir_y = 1;
        data->player.plane_x = -0.66;
        data->player.plane_y = 0;
    }
    else if (dir == 'E')
    {
        data->player.dir_x = 1;
        data->player.dir_y = 0;
        data->player.plane_x = 0;
        data->player.plane_y = 0.66;
    }
    else if (dir == 'W')
    {
        data->player.dir_x = -1;
        data->player.dir_y = 0;
        data->player.plane_x = 0;
        data->player.plane_y = -0.66;
    }
    data->map[y][x] = '0'; // Replace the player's starting position with empty space
}

void validate_map(t_data *data)
{
    int player_count = 0;

    for (size_t y = 0; data->map[y]; y++)
    {
        for (size_t x = 0; data->map[y][x]; x++)
        {
            char c = data->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                set_player(data, x, y, c);
                player_count++;
            }
            else if (c != '0' && c != '1' && c != ' ')
            {
                fprintf(stderr, "Error\nInvalid character '%c' in map.\n", c);
                terminate(data);
            }
            // Check for walls around the map
            if (c == '0')
            {
                // Boundary checks
                if (y == 0 || x == 0 || y == data->map_height - 1 || x == ft_strlen(data->map[y]) - 1)
                {
                    fprintf(stderr, "Error\nMap is not closed/surrounded by walls.\n");
                    terminate(data);
                }
                if (data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' ' ||
                    data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ')
                {
                    fprintf(stderr, "Error\nMap is not closed/surrounded by walls.\n");
                    terminate(data);
                }
            }
        }
    }

    if (player_count != 1)
    {
        fprintf(stderr, "Error\nThere must be exactly one player starting position.\n");
        terminate(data);
    }
}
