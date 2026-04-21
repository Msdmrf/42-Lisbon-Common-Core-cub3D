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
	if (game->keys.right)
		game->player.angle += ROT_SPEED;
	else if (game->keys.left)
		game->player.angle -= ROT_SPEED;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	if (game->player.angle >= 2 * M_PI)
		game->player.angle -= 2 * M_PI;
}

static void	move_player(t_game *game)
{
	double	nx;
	double	ny;
	double	move_x;
	double	move_y;

	nx = game->player.x;
	ny = game->player.y;
	move_x = 0;
	move_y = 0;
	if (game->keys.w)
	{
		move_x += cos(game->player.angle) * MOVE_SPEED;
		move_y += sin(game->player.angle) * MOVE_SPEED;
	}
	if (game->keys.s)
	{
		move_x -= cos(game->player.angle) * MOVE_SPEED;
		move_y -= sin(game->player.angle) * MOVE_SPEED;
	}
	if (game->keys.a)
	{
		move_x -= cos(game->player.angle + M_PI/2) * MOVE_SPEED;
		move_y -= sin(game->player.angle + M_PI/2) * MOVE_SPEED;
	}
	if (game->keys.d)
	{
		move_x += cos(game->player.angle + M_PI/2) * MOVE_SPEED;
		move_y += sin(game->player.angle + M_PI/2) * MOVE_SPEED;
	}
	if (can_move(game, nx + move_x, ny + move_y))
	{
		game->player.x += move_x;
		game->player.y += move_y;
	}
	else if (can_move(game, nx + move_x, ny))
		game->player.x += move_x;
	else if (can_move(game, nx, ny + move_y))
		game->player.y += move_y;
}

int	game_loop(t_game *game)
{
	static int	timer;

	rotate_player(game);
	
	if (timer++ >= MOVE_TIMER)
	{
		move_player(game);
		timer = 0;
	}
	render_frame(game);
	return (0);
}
