#include "../inc/cub3d.h"

static int	calc_map_width(char **lines, int start, int total)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = start;
	while (i < total)
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_row(char *src, int width)
{
	char	*row;
	int		len;
	int		i;

	row = (char *)malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	len = (int)ft_strlen(src);
	i = 0;
	while (i < width)
	{
		if (i < len)
			row[i] = src[i];
		else
			row[i] = CHAR_SPACE;
		i++;
	}
	row[width] = '\0';
	return (row);
}

static char	**build_map_grid(char **lines, int start, int height, int width)
{
	char	**grid;
	int		i;

	grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = pad_row(lines[start + i], width);
		if (!grid[i])
		{
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	grid[height] = NULL;
	return (grid);
}

int	parse_map(t_game *game, char **lines, int start, int total)
{
	if (total <= start)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Map section is empty.", 2);
		return (0);
	}
	game->map.height = total - start;
	game->map.width = calc_map_width(lines, start, total);
	game->map.grid = build_map_grid(lines, start, game->map.height,
			game->map.width);
	if (!game->map.grid)
		return (ft_putendl_fd("Error\nOut of memory for map.", 2), 0);
	return (1);
}
