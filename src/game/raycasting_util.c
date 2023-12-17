/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:11:37 by seunlee2          #+#    #+#             */
/*   Updated: 2023/12/17 10:29:27 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init_ray(t_ray *r, t_player *p, int x)
{
	r->camera = 2 * x / (double)SCREENWIDTH - 1;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	r->raydir_x = p->dir_x + p->plane_x * r->camera;
	r->raydir_y = p->dir_y + p->plane_y * r->camera;
	r->deltadist_x = fabs(1 / r->raydir_x);
	r->deltadist_y = fabs(1 / r->raydir_y);
	r->perpwalldist = 0;
	r->step_x = 0;
	r->step_y = 0;
	r->hit = 0;
	r->side = 0;
	r->wall = 0;
	r->tex_x = 0;
	r->tex_y = 0;
	r->line_height = 0;
	r->draw_start = 0;
	r->draw_end = 0;
	r->step = 0;
	r->tex_pos = 0;
}

void	step_sidedist(t_ray *r, t_player *p)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (p->pos_x - r->map_x) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_x + 1.0 - p->pos_x) * r->deltadist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (p->pos_y - r->map_y) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_y + 1.0 - p->pos_y) * r->deltadist_y;
	}
}

void	dda(t_game *game)
{
	game->r.hit = 0;
	while (game->r.hit == 0)
	{
		if (game->r.sidedist_x < game->r.sidedist_y)
		{
			game->r.sidedist_x += game->r.deltadist_x;
			game->r.map_x += game->r.step_x;
			game->r.side = 0;
		}
		else
		{
			game->r.sidedist_y += game->r.deltadist_y;
			game->r.map_y += game->r.step_y;
			game->r.side = 1;
		}
		if (game->map.matrix[game->r.map_y][game->r.map_x] > 0)
			game->r.hit = 1;
	}
}

void	perpwalldist_line_height(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->perpwalldist = \
			(r->map_x - p->pos_x + (1 - r->step_x) / 2) / r->raydir_x;
	else
		r->perpwalldist = \
			(r->map_y - p->pos_y + (1 - r->step_y) / 2) / r->raydir_y;
	r->line_height = (int)(SCREENHEIGHT / r->perpwalldist);
	r->draw_start = SCREENHEIGHT / 2 - r->line_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = SCREENHEIGHT / 2 + r->line_height / 2;
	if (r->draw_end >= SCREENHEIGHT)
		r->draw_end = SCREENHEIGHT - 1;
}

void	texture(t_ray *r, t_player *p)
{
	if (r->side == 0)
		r->wall = p->pos_y + r->perpwalldist * r->raydir_y;
	else if (r->side == 1)
		r->wall = p->pos_x + r->perpwalldist * r->raydir_x;
	r->wall = r->wall - floor(r->wall);
	r->tex_x = (int)(r->wall * (double)TEXWIDTH);
	if (r->side == 0 && r->raydir_x < 0)
		r->tex_x = TEXWIDTH - r->tex_x - 1;
	else if (r->side == 1 && r->raydir_y > 0)
		r->tex_x = TEXWIDTH - r->tex_x - 1;
	r->step = 1.0 * TEXHEIGHT / r->line_height;
	r->tex_pos = \
		(r->draw_start - SCREENHEIGHT / 2 + r->line_height / 2) * r->step;
}
