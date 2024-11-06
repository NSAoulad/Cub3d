/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:39:40 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/05 18:39:42 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print_map(char **map)
{
    printf("Map:\n");
    for (int i = 0; map[i]; i++)
    {
        printf("%s\n", map[i]);
    }
}
