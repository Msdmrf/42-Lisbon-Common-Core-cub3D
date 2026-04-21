#include "../inc/cub3d.h"

static int	get_tex_id(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (tex_no);
	if (ft_strncmp(line, "SO", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (tex_so);
	if (ft_strncmp(line, "WE", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (tex_we);
	if (ft_strncmp(line, "EA", 2) == 0
		&& (line[2] == ' ' || line[2] == '\t'))
		return (tex_ea);
	return (-1);
}

static int	parse_texture(t_game *game, char *line, int id)
{
	char	*path;
	int		len;

	if (game->tex[id].path)
		return (ft_putendl_fd("Error\nDuplicate texture identifier.", 2), 0);
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Empty texture path.", 2);
		return (0);
	}
	path = ft_strdup(line);
	if (!path)
		return (ft_putendl_fd("Error\nOut of memory.", 2), 0);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	if (len > 1 && path[len - 2] == '\r')
		path[len - 2] = '\0';
	game->tex[id].path = path;
	return (1);
}

static int	parse_element_line(t_game *game, char *line)
{
	int	tex_id;

	while (*line == ' ' || *line == '\t')
		line++;
	tex_id = get_tex_id(line);
	if (tex_id >= 0)
		return (parse_texture(game, line, tex_id));
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_floor_color(game, line));
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
		return (parse_ceil_color(game, line));
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Unknown element identifier.", 2);
	return (0);
}

int	parse_header(t_game *game, char **lines, int map_start)
{
	int		i;
	char	*ptr;

	i = 0;
	while (i < map_start)
	{
		ptr = lines[i];
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*ptr != '\0' && !parse_element_line(game, lines[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_all_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < tex_count)
	{
		if (!game->tex[i].path)
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("Missing texture path.", 2);
			return (0);
		}
		i++;
	}
	if (game->floor.r < 0 || game->ceiling.r < 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Missing floor or ceiling color.", 2);
		return (0);
	}
	return (1);
}
