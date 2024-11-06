/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/05 18:38:34 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:33:37 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void ft_free_str_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}


int ft_str_array_len(char **array)
{
    int len = 0;
    while (array[len])
        len++;
    return len;
}

static void parse_color(char *line, t_color *color, t_data *data)
{
    char    **rgb_values;
    char    *trimmed_line;

    trimmed_line = ft_strtrim(line, " \n");
    rgb_values = ft_split(trimmed_line, ',');
    free(trimmed_line);
    if (!rgb_values || ft_str_array_len(rgb_values) != 3)
    {
        fprintf(stderr, "Error\nInvalid color format.\n");
        terminate(data);
    }
    color->r = ft_atoi(rgb_values[0]);
    color->g = ft_atoi(rgb_values[1]);
    color->b = ft_atoi(rgb_values[2]);
    ft_free_str_array(rgb_values);
    // Validate RGB values are in the range [0, 255]
    if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
    {
        fprintf(stderr, "Error\nColor values must be in range 0-255.\n");
        terminate(data);
    }
}

void parse_map(char *map_file, t_data *data)
{
    int     fd;
    char    *line;
    int     in_map = 0;
    t_list  *map_lines = NULL;

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error\nFailed to open map file.\n");
        terminate(data);
    }

    while ((line = get_next_line(fd)))
    {
        // Remove the newline character at the end
        line[strcspn(line, "\n")] = '\0';

        // Skip empty lines before the map starts
        if (line[0] == '\0')
        {
            free(line);
            continue;
        }

        if (ft_strncmp(line, "NO ", 3) == 0)
            data->north_texture_path = ft_strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0)
            data->south_texture_path = ft_strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0)
            data->west_texture_path = ft_strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0)
            data->east_texture_path = ft_strdup(line + 3);
        else if (ft_strncmp(line, "F ", 2) == 0)
            parse_color(line + 1, &data->floor_color, data);
        else if (ft_strncmp(line, "C ", 2) == 0)
            parse_color(line + 1, &data->ceiling_color, data);
        else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
        {
            in_map = 1;
            ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
        }
        else if (in_map)
        {
            // Invalid line encountered after map has started
            fprintf(stderr, "Error\nInvalid line in map file: %s\n", line);
            free(line);
            terminate(data);
        }
        else
        {
            // Invalid line encountered before map has started
            fprintf(stderr, "Error\nInvalid line in map file: %s\n", line);
            free(line);
            terminate(data);
        }
        free(line);
    }
    close(fd);

    if (!map_lines)
    {
        fprintf(stderr, "Error\nMap data is missing.\n");
        terminate(data);
    }

    // Convert the list of map lines to a 2D array
    data->map_height = ft_lstsize(map_lines);
    data->map = ft_calloc(data->map_height + 1, sizeof(char *));
    if (!data->map)
    {
        fprintf(stderr, "Error\nMemory allocation failed.\n");
        terminate(data);
    }
    int i = 0;
    t_list *current = map_lines;
    while (current)
    {
        data->map[i++] = ft_strdup(current->content);
        free(current->content);
        t_list *temp = current;
        current = current->next;
        free(temp);
    }
    data->map[i] = NULL;

    // Calculate map width (maximum line length)
    data->map_width = 0;
    for (int j = 0; data->map[j]; j++)
    {
        size_t line_length = ft_strlen(data->map[j]);
        if (line_length > data->map_width)
            data->map_width = line_length;
    }

    // Print the map for debugging
    print_map(data->map);

    // Validate the map
    validate_map(data);
}
