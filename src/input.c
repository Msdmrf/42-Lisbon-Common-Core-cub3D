#include "../inc/cub3d.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_game(game);
	if (keysym == XK_w)
		game->keys.w = 1;
	if (keysym == XK_a)
		game->keys.a = 1;
	if (keysym == XK_s)
		game->keys.s = 1;
	if (keysym == XK_d)
		game->keys.d = 1;
	if (keysym == XK_Left)
		game->keys.left = 1;
	if (keysym == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->keys.w = 0;
	if (keysym == XK_a)
		game->keys.a = 0;
	if (keysym == XK_s)
		game->keys.s = 0;
	if (keysym == XK_d)
		game->keys.d = 0;
	if (keysym == XK_Left)
		game->keys.left = 0;
	if (keysym == XK_Right)
		game->keys.right = 0;
	return (0);
}
