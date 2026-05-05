/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:58:06 by migusant          #+#    #+#             */
/*   Updated: 2026/05/05 15:49:27 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static void	strip_line(char *line)
{
	char	*end;

	end = ft_strchr(line, '\n');
	if (end)
		*end = '\0';
	end = line + ft_strlen(line);
	while (end > line && (end[-1] == '\r' || end[-1] == ' ' || end[-1] == '\t'))
		*--end = '\0';
}

static char	**read_file_lines(char *path, int count)
{
	char	**lines;
	int		fd;
	int		i;
	char	*line;

	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(lines), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line && i < count)
	{
		strip_line(line);
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static int	find_map_start(char **lines, int count)
{
	int		i;
	int		j;
	int		has_content;

	i = 0;
	while (i < count)
	{
		j = 0;
		has_content = 0;
		while (lines[i][j] && lines[i][j] != '\n')
		{
			if (!ft_strchr("01NSEW ", lines[i][j]))
				break ;
			if (lines[i][j] != ' ')
				has_content = 1;
			j++;
		}
		if (has_content && (!lines[i][j] || lines[i][j] == '\n'))
			return (i);
		i++;
	}
	return (-1);
}

int	parse_cub_file(t_game *game, char *path)
{
	char	**lines;
	int		count;
	int		map_start;

	count = count_lines(path);
	if (count <= 0)
		return (ft_putendl_fd("Error\nCannot open or empty file.", 2), 0);
	lines = read_file_lines(path, count);
	if (!lines)
		return (ft_putendl_fd("Error\nMemory allocation failed.", 2), 0);
	map_start = find_map_start(lines, count);
	if (map_start < 0)
		return (free_lines(lines, count),
			ft_putendl_fd("Error\nNo map found in file.", 2), 0);
	if (!parse_header(game, lines, map_start)
		|| !check_all_elements(game)
		|| !parse_map(game, lines, map_start, count)
		|| !validate_map(game)
		|| !check_enclosure(game))
		return (free_lines(lines, count), 0);
	free_lines(lines, count);
	return (1);
}
