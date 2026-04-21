#include "../inc/cub3d.h"

static void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->floor.r = -1;
	game->ceiling.r = -1;
}

static int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, DestroyNotify, NoEventMask, close_game, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, handle_keyrelease, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Usage: ./cub3D <map.cub>", 2);
		return (1);
	}
	init_game(&game);
	if (!check_extension(argv[1]))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("File must end with .cub.", 2);
		return (1);
	}
	if (!parse_cub_file(&game, argv[1]))
		exit_game(&game, 1);
	if (!init_window(&game))
		exit_game(&game, 1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
