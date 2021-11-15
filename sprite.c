/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:23:27 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 17:34:04 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spriteposition(t_cub3d *cub, int x)
{
	cub->sprite[cub->sprite_n].x = x + 0.5;
	cub->sprite[cub->sprite_n].y = cub->parse.y + 0.5;
	cub->sprite_n++;
	cub->parse.y++;
}

void	spritedistance(t_cub3d *cub)
{
	int		num;

	cub->sprite_n = 0;
	while (cub->sprite_n < cub->sprite_num)
	{
		num = cub->sprite_n;
		cub->sprite[cub->sprite_n].order = cub->sprite_n;
		cub->sprite[num].dist = pow(cub->posx - cub->sprite[num].x, 2)
			+ pow(cub->posy - cub->sprite[cub->sprite_n].y, 2);
		cub->sprite_n++;
	}
	spritesort(cub);
	cub->sprite_n = 0;
}

void	sprite(t_cub3d *cub)
{
	spritedistance(cub);
	cub->bmp_pos = 0;
	while (cub->sprite_n < cub->sprite_num)
	{
		cub->spritex = cub->sprite[cub->sprite_n].x - cub->posx;
		cub->spritey = cub->sprite[cub->sprite_n].y - cub->posy;
		cub->invdet = 1.0 / (cub->planex * cub->diry - cub->dirx * cub->planey);
		cub->transformx = cub->invdet * (cub->diry * cub->spritex
				- cub->dirx * cub->spritey);
		cub->transformy = cub->invdet * (-cub->planey * cub->spritex
				+ cub->planex * cub->spritey);
		cub->spritescreenx = (int)((cub->res.w / 2) * (1 + cub->transformx
					/ cub->transformy));
		cub->spriteheight = abs((int)(cub->res.h / cub->transformy));
		cub->drawstarty = -cub->spriteheight / 2 + cub->res.h / 2;
		if (cub->spriteheight < 0)
			cub->drawstarty = 0;
		cub->drawendy = cub->spriteheight / 2 + cub->res.h / 2;
		if (cub->drawendy >= cub->res.h)
			cub->drawendy = cub->res.h - 1;
		cub->spritewidth = abs((int)(cub->res.h / (cub->transformy)));
		spriterendering(cub);
		cub->sprite_n++;
	}
}

void	spriterendering(t_cub3d *cub)
{
	cub->drawstartx = -cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawstartx < 0)
		cub->drawstartx = 0;
	cub->drawendx = cub->spritewidth / 2 + cub->spritescreenx;
	if (cub->drawendx >= cub->res.w)
		cub->drawendx = cub->res.w - 1;
	while (cub->drawstartx < cub->drawendx)
	{
		cub->bmp_pos = 0;
		cub->tex_x = (int)(256 * (cub->drawstartx - (-cub->spritewidth / 2
						+ cub->spritescreenx))
				* cub->texwidth / cub->spritewidth) / 256;
		if (cub->transformy > 0 && cub->drawstartx > 0
			&& cub->drawstartx < cub->res.w
			&& cub->transformy < cub->sprite_buf[cub->drawstartx])
		{
			cub->spriteline = cub->drawstarty;
			while (cub->spriteline < cub->drawendy)
			{
				sprite_image(cub);
				cub->spriteline++;
			}
		}
		cub->drawstartx++;
	}
}

void	sprite_image(t_cub3d *cub)
{
	cub->d = (cub->spriteline) * 256 - cub->res.h * 128
		+ cub->spriteheight * 128;
	cub->tex_y = ((cub->d * cub->texheight) / cub->spriteheight) / 256;
	if (cub->txt[4].img_data[cub->tex_x + cub->tex_y * cub->txt[4].w])
	{
		cub->img.img_data[cub->spriteline * cub->res.w + cub->drawstartx]
			= cub->txt[4].img_data[cub->tex_x + cub->tex_y * cub->txt[4].w];
		if (cub->ac == 3)
		{
			cub->abrv = ((cub->drawendy - cub->bmp_pos) * cub->res.w
					+ cub->drawstartx);
			cub->image[cub->abrv * 3 + 2] = cub->txt[4].img_data[cub->tex_x
				+ cub->tex_y * cub->txt[4].w] >> 16;
			cub->image[cub->abrv * 3 + 1] = cub->txt[4].img_data[cub->tex_x
				+ cub->tex_y * cub->txt[4].w] >> 8;
			cub->image[cub->abrv * 3 + 0] = cub->txt[4].img_data[cub->tex_x
				+ cub->tex_y * cub->txt[4].w];
		}
	}
	cub->bmp_pos++;
}
