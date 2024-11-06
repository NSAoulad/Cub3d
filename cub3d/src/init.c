/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:08 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:39:28 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_game(t_data *data)
{
    // Initialize movement and rotation speeds
    data->player.move_speed = 0.05; // Adjust as needed
    data->player.rot_speed = 0.03;  // Adjust as needed

    // Other initialization code if needed
}
