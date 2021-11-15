/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 11:32:57 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/07 14:07:06 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate(t_cub3d *cub)
{
	cub->hit = 0;
	cub->img.h = 0;
	cub->bmp_pos = 0;
	cub->camerax = 2 * cub->ray / (double)cub->res.w - 1;
	cub->raydirx = cub->dirx + cub->planex * cub->camerax;
	cub->raydiry = cub->diry + cub->planey * cub->camerax;
	cub->mapx = (int)cub->posx;
	cub->mapy = (int)cub->posy;
	cub->deltadistx = sqrt(1 + pow(cub->raydiry, 2) / pow(cub->raydirx, 2));
	cub->deltadisty = sqrt(1 + pow(cub->raydirx, 2) / pow(cub->raydiry, 2));
	if (cub->raydiry == 0)
		cub->deltadistx = 0;
	else if (cub->raydirx == 0)
		cub->deltadistx = 1;
	if (cub->raydirx == 0)
		cub->deltadisty = 0;
	else if (cub->raydiry == 0)
		cub->deltadisty = 1;
}

void	sidedistance(t_cub3d *cub)
{
	if (cub->raydirx < 0)
	{
		cub->stepx = -1;
		cub->sidedistx = (cub->posx - cub->mapx) * cub->deltadistx;
	}
	else
	{
		cub->stepx = 1;
		cub->sidedistx = (cub->mapx + 1.0 - cub->posx) * cub->deltadistx;
	}
	if (cub->raydiry < 0)
	{
		cub->stepy = -1;
		cub->sidedisty = (cub->posy - cub->mapy) * cub->deltadisty;
	}
	else
	{
		cub->stepy = 1;
		cub->sidedisty = (cub->mapy + 1.0 - cub->posy) * cub->deltadisty;
	}
}

void	hit(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->sidedistx < cub->sidedisty)
		{
			cub->sidedistx += cub->deltadistx;
			cub->mapx += cub->stepx;
			cub->side = 0;
		}
		else
		{
			cub->sidedisty += cub->deltadisty;
			cub->mapy += cub->stepy;
			cub->side = 3;
		}
		if (cub->side == 0 && cub->raydirx > 0)
			cub->side = 2;
		else if (cub->side == 3 && cub->raydiry < 0)
			cub->side = 1;
		if (cub->map[cub->mapx][cub->mapy] == '1')
			cub->hit = 1;
	}
}

void	wall(t_cub3d *cub)
{
	if (cub->side == 0 || cub->side == 2)
		cub->perpwalldist = (cub->mapx - cub->posx + (1 - cub->stepx) / 2)
			/ cub->raydirx;
	else
		cub->perpwalldist = (cub->mapy - cub->posy + (1 - cub->stepy) / 2)
			/ cub->raydiry;
	cub->lineheight = (int)(cub->res.h / cub->perpwalldist);
	cub->drawstart = (-cub->lineheight / 2) + (cub->res.h / 2);
	if (cub->drawstart < 0)
		cub->drawstart = 0;
	cub->drawend = cub->lineheight / 2 + (cub->res.h / 2);
	if (cub->drawend >= cub->res.h)
		cub->drawend = cub->res.h - 1;
	if (cub->side == 0 || cub->side == 2)
		cub->wallx = cub->posy + cub->perpwalldist * cub->raydiry;
	else
		cub->wallx = cub->posx + cub->perpwalldist * cub->raydirx;
	cub->wallx -= floor((cub->wallx));
	cub->tex_x = (int)(cub->wallx * (double)(cub->texwidth));
	if (cub->side == 0 && cub->raydirx > 0)
		cub->tex_x = cub->texwidth - cub->tex_x - 1;
	if (cub->side == 1 && cub->raydiry < 0)
		cub->tex_x = cub->texwidth - cub->tex_x - 1;
	cub->step = 1.0 * cub->texheight / cub->lineheight;
}

void	rendering(t_cub3d *cub)
{
	cub->texpos = (cub->drawstart - cub->res.h / 2 + cub->lineheight / 2)
		* cub->step;
	while (cub->img.h < cub->res.h)
	{
		if (cub->img.h < cub->drawstart)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray]
				= create_rgb(&cub->c);
			bmp_filling(cub, &cub->f);
		}
		if (cub->img.h >= cub->drawstart && cub->img.h <= cub->drawend)
			wallrendering(cub);
		if (cub->img.h > cub->drawend)
		{
			cub->img.img_data[cub->img.h * cub->res.w + cub->ray]
				= create_rgb(&cub->f);
			bmp_filling(cub, &cub->c);
		}
		cub->img.h++;
	}
	if (cub->sprite_num)
		cub->sprite_buf[cub->ray] = cub->perpwalldist;
	cub->ray++;
}
