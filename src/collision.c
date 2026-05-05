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

int	can_move(t_game *game, double nx, double ny)
{
	double	r;

	r = PLAYER_RADIUS;
	return (valid_cell(game, nx - r, ny - r)
		&& valid_cell(game, nx + r, ny - r)
		&& valid_cell(game, nx - r, ny + r)
		&& valid_cell(game, nx + r, ny + r));
}
