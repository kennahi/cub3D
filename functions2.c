/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:34:55 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/06 14:51:42 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_path(t_cub3d *cub)
{
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	cub->path.s = NULL;
	cub->path.no = NULL;
	cub->path.so = NULL;
	cub->path.ea = NULL;
	cub->path.we = NULL;
}

int	create_rgb(t_rgb *rgb)
{
	int		color;

	color = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	return (color);
}

void	wallrendering(t_cub3d *cub)
{
	cub->tex_y = (int)cub->texpos;
	cub->texpos += cub->step;
	if (cub->side == 0)
		cub->color = cub->txt[2].img_data[cub->tex_x + cub->tex_y
			* cub->txt[2].w];
	else if (cub->side == 1)
		cub->color = cub->txt[3].img_data[cub->tex_x + cub->tex_y
			* cub->txt[3].w];
	else if (cub->side == 2)
		cub->color = cub->txt[0].img_data[cub->tex_x + cub->tex_y
			* cub->txt[0].w];
	else if (cub->side == 3)
		cub->color = cub->txt[1].img_data[cub->tex_x + cub->tex_y
			* cub->txt[1].w];
	cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->color;
	if (cub->ac == 3)
	{
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			*3 + 2] = cub->color >> 16;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			*3 + 1] = cub->color >> 8;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			*3 + 0] = cub->color;
		cub->bmp_pos++;
	}
}

int	key_close(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	ft_putstr_fd("END OF GAME!\n", 2);
	exit(0);
	return (0);
}

void	if_sprite(t_cub3d *cub)
{
	cub->parse.line = NULL;
	if (cub->sprite_num)
	{
		cub->sprite_buf = (double *)malloc((cub->res.w + 1) * sizeof(double));
		cub->sprite = malloc((cub->sprite_num + 1) * sizeof(t_sprite));
	}
}
