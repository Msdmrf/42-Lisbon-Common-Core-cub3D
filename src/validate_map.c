#include "../inc/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == CHAR_WALL || c == CHAR_EMPTY || c == CHAR_SPACE
		|| c == CHAR_NORTH || c == CHAR_SOUTH
		|| c == CHAR_EAST || c == CHAR_WEST);
}

static int	check_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_map_char(game->map.grid[i][j]))
			{
				ft_putendl_fd("Error", 2);
				ft_putendl_fd("Invalid character in map.", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_player_spawn(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = -1;
	while (++i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (ft_strchr("NSEW", game->map.grid[i][j]))
			{
				count++;
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				game->player.spawn_dir = game->map.grid[i][j];
				game->player.angle = convert_angle(game->player.spawn_dir);
			}
			j++;
		}
	}
	if (count != 1)
		return (ft_putendl_fd("Error\nExactly one spawn required.", 2), 0);
	return (1);
}

static int	check_map_size(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Map too small (minimum 3x3).", 2);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_map_size(game)
		|| !check_map_chars(game)
		|| !check_player_spawn(game))
		return (0);
	return (1);
}
