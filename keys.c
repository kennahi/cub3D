/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:15:34 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/06 12:29:13 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int key, t_cub3d *cub)
{
	cub->keyboard[key] = 1;
	return (0);
}

int	key_released(int key, t_cub3d *cub)
{
	cub->keyboard[key] = 0;
	return (0);
}

void	moves_up_down(t_cub3d *cub)
{
	if (cub->keyboard[13])
	{
		if (cub->map[(int)(cub->posx + cub->dirx * cub->movespeed)]
			[(int)(cub->posy)] == '0')
			cub->posx += cub->dirx * cub->movespeed;
		if (cub->map[(int)(cub->posx)][(int)(cub->posy + cub->diry
			* cub->movespeed)] == '0')
			cub->posy += cub->diry * cub->movespeed;
	}
	if (cub->keyboard[1])
	{
		if (cub->map[(int)(cub->posx - cub->dirx * cub->movespeed)]
			[(int)(cub->posy)] == '0')
			cub->posx -= cub->dirx * cub->movespeed;
		if (cub->map[(int)(cub->posx)][(int)(cub->posy - cub->diry *
			cub->movespeed)] == '0')
			cub->posy -= cub->diry * cub->movespeed;
	}
}

void	movesides(t_cub3d *cub)
{
	if (cub->keyboard[0])
	{
		if (cub->map[(int)(cub->posx - cub->planex * cub->movespeed)]
			[(int)(cub->posy)] == '0')
			cub->posx -= cub->planex * cub->movespeed;
		if (cub->map[(int)(cub->posx)][(int)(cub->posy - cub->planey *
			cub->movespeed)] == '0')
			cub->posy -= cub->planey * cub->movespeed;
	}
	if (cub->keyboard[2])
	{
		if (cub->map[(int)(cub->posx + cub->planex * cub->movespeed)]
			[(int)(cub->posy)] == '0')
			cub->posx += cub->planex * cub->movespeed;
		if (cub->map[(int)(cub->posx)][(int)(cub->posy + cub->planey *
			cub->movespeed)] == '0')
			cub->posy += cub->planey * cub->movespeed;
	}
}

void	look(t_cub3d *cub)
{
	cub->olddirx = cub->dirx;
	if (cub->keyboard[123])
	{
		cub->dirx = cub->dirx * cos(cub->rotatespeed) - cub->diry
			* sin(cub->rotatespeed);
		cub->diry = cub->olddirx * sin(cub->rotatespeed) + cub->diry
			* cos(cub->rotatespeed);
		cub->oldplanex = cub->planex;
		cub->planex = cub->planex * cos(cub->rotatespeed) - cub->planey
			* sin(cub->rotatespeed);
		cub->planey = cub->oldplanex * sin(cub->rotatespeed) + cub->planey
			* cos(cub->rotatespeed);
	}
	if (cub->keyboard[124])
	{
		cub->dirx = cub->dirx * cos(-cub->rotatespeed) - cub->diry
			* sin(-cub->rotatespeed);
		cub->diry = cub->olddirx * sin(-cub->rotatespeed) + cub->diry
			* cos(-cub->rotatespeed);
		cub->oldplanex = cub->planex;
		cub->planex = cub->planex * cos(-cub->rotatespeed) - cub->planey
			* sin(-cub->rotatespeed);
		cub->planey = cub->oldplanex * sin(-cub->rotatespeed) + cub->planey
			* cos(-cub->rotatespeed);
	}
}
