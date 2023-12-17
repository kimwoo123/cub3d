/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:40:27 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/17 10:31:20 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw(t_ray *r, t_img *img, int x)
{
	int	color;
	int	y;

	y = r->draw_start;
	while (y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos & (TEXHEIGHT - 1);
		r->tex_pos += r->step;
		if (r->side == 0)
		{
			if (r->raydir_x >= 0)
				color = img->texture[1][TEXHEIGHT * r->tex_y + r->tex_x];
			else
				color = img->texture[0][TEXHEIGHT * r->tex_y + r->tex_x];
		}
		else if (r->side == 1)
		{
			if (r->raydir_y >= 0)
				color = img->texture[3][TEXHEIGHT * r->tex_y + r->tex_x];
			else
				color = img->texture[2][TEXHEIGHT * r->tex_y + r->tex_x];
		}
		img->data[SCREENWIDTH * y + x] = color;
		y++;
	}
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREENWIDTH)
	{
		init_ray(&game->r, &game->p, x);
		step_sidedist(&game->r, &game->p);
		dda(game);
		perpwalldist_line_height(&game->r, &game->p);
		texture(&game->r, &game->p);
		draw(&game->r, &game->img, x);
		x++;
	}
}
