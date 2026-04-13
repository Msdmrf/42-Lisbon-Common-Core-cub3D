#include "../inc/cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_putendl_fd("Error\nMLX init failed.", 2), 0);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, WINDOW_TITLE);
	if (!game->win)
		return (ft_putendl_fd("Error\nWindow creation failed.", 2), 0);
	return (1);
}

static int	init_img(t_game *game)
{
	game->img.ptr = mlx_new_image(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE);
	if (!game->img.ptr)
		return (ft_putendl_fd("Error\nImage creation failed.", 2), 0);
	game->img.data = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	return (1);
}

int	init_window(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	if (!init_img(game))
		return (0);
	return (1);
}

int	close_game(t_game *game)
{
	exit_game(game, 0);
	return (0);
}
