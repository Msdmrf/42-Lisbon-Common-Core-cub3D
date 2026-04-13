#include "../inc/cub3d.h"

static int	valid_cell(t_game *game, double x, double y)
{
	int	tx;
	int	ty;

	if (x < 0.0 || y < 0.0)
		return (0);
	tx = (int)(x);
	ty = (int)(y);
	if (ty >= game->map.height || tx >= game->map.width)
		return (0);
	return (game->map.grid[ty][tx] != CHAR_WALL
		&& game->map.grid[ty][tx] != CHAR_SPACE);
}

static int	can_move(t_game *game, double nx, double ny)
{
	double	r;

	r = PLAYER_RADIUS;
	return (valid_cell(game, nx - r, ny - r)
		&& valid_cell(game, nx + r, ny - r)
		&& valid_cell(game, nx - r, ny + r)
		&& valid_cell(game, nx + r, ny + r));
}

static void	rotate_player(t_game *game)
{
	if (game->keys.left)
	{
		if (game->player.spawn_dir == 'N')
			game->player.spawn_dir = 'W';
		else if (game->player.spawn_dir == 'W')
			game->player.spawn_dir = 'S';
		else if (game->player.spawn_dir == 'S')
			game->player.spawn_dir = 'E';
		else
			game->player.spawn_dir = 'N';
	}
	else if (game->keys.right)
	{
		if (game->player.spawn_dir == 'N')
			game->player.spawn_dir = 'E';
		else if (game->player.spawn_dir == 'E')
			game->player.spawn_dir = 'S';
		else if (game->player.spawn_dir == 'S')
			game->player.spawn_dir = 'W';
		else
			game->player.spawn_dir = 'N';
	}
}

static void	move_player(t_game *game)
{
	double	nx;
	double	ny;

	nx = game->player.x;
	ny = game->player.y;
	if (game->keys.w)
		ny -= MOVE_SPEED;
	if (game->keys.s)
		ny += MOVE_SPEED;
	if (game->keys.a)
		nx -= MOVE_SPEED;
	if (game->keys.d)
		nx += MOVE_SPEED;
	rotate_player(game);
	if (can_move(game, nx, game->player.y))
		game->player.x = nx;
	if (can_move(game, game->player.x, ny))
		game->player.y = ny;
}

int	game_loop(t_game *game)
{
	static int	timer;

	if (timer++ >= MOVE_TIMER)
	{
		move_player(game);
		timer = 0;
	}
	render_frame(game);
	return (0);
}
