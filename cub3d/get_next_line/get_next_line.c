/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aaoulad- <aaoulad-@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 17:31:29 by aaoulad-      #+#    #+#                 */
/*   Updated: 2024/11/06 17:39:28 by aaoulad-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*extract_line(char **input_buffer)
{
	char	*line;
	char	*current_char;
	char	*line_start;
	char	*remaining_data;

	current_char = *input_buffer;
	while (*current_char && *current_char != '\n')
		current_char++;
	if (*current_char == '\0')
	{
		line = ft_strdup_g(*input_buffer);
		return (free(*input_buffer), *input_buffer = NULL, line);
	}
	line = (char *)malloc(current_char - *input_buffer + 2);
	if (!line)
		return (free(*input_buffer), *input_buffer = NULL, NULL);
	line_start = line;
	current_char = *input_buffer;
	while (*current_char && *current_char != '\n')
		*line++ = *current_char++;
	if (*current_char == '\n')
		*line++ = *current_char++;
	*line = '\0';
	remaining_data = ft_strdup_g(current_char);
	return (free(*input_buffer), *input_buffer = remaining_data, line_start);
}

char	*accumulate_data(int fd, char **input_buffer, char *read_data)
{
	int		read_bytes;
	char	*old_buffer;

	read_bytes = 1;
	while (!ft_strchr(read_data, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, read_data, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(read_data), free(*input_buffer), NULL);
		read_data[read_bytes] = '\0';
		old_buffer = *input_buffer;
		if (*input_buffer == NULL)
			*input_buffer = ft_strdup_g(read_data);
		else
			*input_buffer = ft_strjoin_g(*input_buffer, read_data);
		free(old_buffer);
		if (!*input_buffer)
			return (free(read_data), NULL);
		if (!ft_strlen(*input_buffer))
			return (free(read_data), free(*input_buffer), NULL);
	}
	return (free(read_data), *input_buffer);
}

char	*get_next_line(int fd)
{
	static char	*input_buffer;
	char		*read_data;
	char		*line;

	if (fd == -1)
	{
		free(input_buffer);
		input_buffer = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_data = malloc(BUFFER_SIZE + 1);
	if (!read_data)
		return (NULL);
	read_data[0] = '\0';
	input_buffer = accumulate_data(fd, &input_buffer, read_data);
	if (!input_buffer)
		return (NULL);
	line = extract_line(&input_buffer);
	return (line);
}
