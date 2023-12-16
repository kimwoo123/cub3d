/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:50:26 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/17 05:03:16 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREENHEIGHT / 2)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			game->img.data[y * SCREENWIDTH + x] = game->map.ceiling;
			game->img.data[(SCREENHEIGHT - 1 - y) * SCREENWIDTH + x] \
				= game->map.floor;
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	set_floor(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.image, 0, 0);
	key_hook(game);
	return (0);
}
