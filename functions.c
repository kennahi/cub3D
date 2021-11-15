/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:52:02 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/06 14:51:49 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub3d *cub)
{
	cub->path.no = NULL;
	cub->path.so = NULL;
	cub->path.we = NULL;
	cub->path.ea = NULL;
	cub->path.s = NULL;
	cub->map = NULL;
	cub->parse.x = 0;
	cub->parse.spawn = 0;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->image = NULL;
	cub->rep.res = 0;
	cub->rep.no = 0;
	cub->rep.so = 0;
	cub->rep.we = 0;
	cub->rep.ea = 0;
	cub->rep.s = 0;
	cub->rep.f = 0;
	cub->rep.c = 0;
	cub->sprite_num = 0;
	cub->sprite_n = 0;
}

void	checker(char **s, t_cub3d *cub, int i)
{
	int	j;

	while (s[i])
	{
		j = 0;
		if (s[i][0] == '-')
			error_free("Error\nNegative number\n", cub, s);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				error_free("Error\nAnother char found\n", cub, s);
			j++;
		}
		i++;
	}
}

void	fc_checker(t_parse *parse, t_cub3d *cub)
{
	int	comma;
	int	i;

	i = 0;
	comma = 0;
	if (parse->splitted[2])
		error_free("Error\nAnother arg after color\n", cub, parse->splitted);
	while (parse->splitted[1][i])
	{
		if (parse->splitted[1][i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		error_free("Error\nWrong format of rgb\n", cub, parse->splitted);
}

void	range(t_rgb *rgb, t_cub3d *cub)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0
		|| rgb->b > 255 || rgb->b < 0)
		error_msg_free("Error\nThe number is incorrect\n", cub);
}

void	spritesort(t_cub3d *cub)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < cub->sprite_num - 1)
	{
		j = 0;
		while (j < cub->sprite_num - i - 1)
		{
			if (cub->sprite[j].dist < cub->sprite[j + 1].dist)
			{
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
