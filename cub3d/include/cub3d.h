/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:37:45 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:31:09 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "MLX42/MLX42.h"   // Include MLX42 header
#include "libft.h"         // Your libft header
#include "../get_next_line/get_next_line.h" // Your get_next_line header

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Keycodes for MLX42 (using GLFW key codes)
#define KEY_ESC    GLFW_KEY_ESCAPE
#define KEY_W      GLFW_KEY_W
#define KEY_A      GLFW_KEY_A
#define KEY_S      GLFW_KEY_S
#define KEY_D      GLFW_KEY_D
#define KEY_LEFT   GLFW_KEY_LEFT   // Left arrow key
#define KEY_RIGHT  GLFW_KEY_RIGHT  // Right arrow key

typedef struct s_color {
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double move_speed;
    double rot_speed;
}   t_player;

typedef struct s_data {
    mlx_t           *mlx;       // MLX42 instance
    mlx_image_t     *image;     // Image to render

    // Texture file paths
    char            *north_texture_path;
    char            *south_texture_path;
    char            *west_texture_path;
    char            *east_texture_path;

    // Loaded textures
    mlx_texture_t   *texture_north;
    mlx_texture_t   *texture_south;
    mlx_texture_t   *texture_west;
    mlx_texture_t   *texture_east;

    // Colors
    t_color         floor_color;
    t_color         ceiling_color;

    // Map data
    char            **map;       // 2D array representing the map
    size_t             map_width;
    size_t             map_height;

    // Player data
    t_player        player;
}   t_data;

// Function prototypes
void    init_game(t_data *data);
void    load_textures(t_data *data);
void    parse_map(char *map_file, t_data *data);
void    validate_map(t_data *data);
void    hook_functions(t_data *data);
void    render(t_data *data);
void    terminate(t_data *data);
void    key_hook(mlx_key_data_t keydata, void *param);
void    loop_hook(void *param);
uint32_t rgb_to_hex(t_color color);
uint32_t get_texture_pixel(mlx_texture_t *texture, int x, int y);
void    set_player(t_data *data, int x, int y, char dir);
void    print_map(char **map);

#endif
