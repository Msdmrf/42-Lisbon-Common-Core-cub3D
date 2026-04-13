#include "../inc/cub3d.h"

static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int	parse_rgb_value(char *str, int *val)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (ft_putendl_fd("Error\nEmpty color component.", 2), 0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i])
		return (ft_putendl_fd("Error\nInvalid color component.", 2), 0);
	*val = ft_atoi(str);
	if (*val < 0 || *val > 255)
		return (ft_putendl_fd("Error\nColor value out of [0,255].", 2), 0);
	return (1);
}

static int	parse_rgb(char *str, t_rgb *color)
{
	char	**parts;
	int		ok;

	parts = ft_split(str, ',');
	if (!parts)
		return (ft_putendl_fd("Error\nOut of memory.", 2), 0);
	ok = 0;
	if (parts[0] && parts[1] && parts[2] && !parts[3])
	{
		if (parse_rgb_value(parts[0], &color->r)
			&& parse_rgb_value(parts[1], &color->g)
			&& parse_rgb_value(parts[2], &color->b))
			ok = 1;
	}
	else
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Color needs exactly 3 components (R,G,B).", 2);
	}
	free_parts(parts);
	return (ok);
}

int	parse_floor_color(t_game *game, char *line)
{
	if (game->floor.r >= 0)
		return (ft_putendl_fd("Error\nDuplicate floor color (F).", 2), 0);
	line++;
	while (*line == ' ' || *line == '\t')
		line++;
	return (parse_rgb(line, &game->floor));
}

int	parse_ceil_color(t_game *game, char *line)
{
	if (game->ceiling.r >= 0)
		return (ft_putendl_fd("Error\nDuplicate ceiling color (C).", 2), 0);
	line++;
	while (*line == ' ' || *line == '\t')
		line++;
	return (parse_rgb(line, &game->ceiling));
}
