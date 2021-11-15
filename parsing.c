/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 18:44:47 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/07 12:32:37 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resolution(t_cub3d *cub)
{
	if (cub->rep.res == 1)
		error_msg_free("ERROR\nres is repeated", cub);
	if (cub->parse.line[1] != ' ')
		error_msg_free("ERROR\nAnother char found after R", cub);
	cub->parse.splitted = ft_split(cub->parse.line, ' ');
	if (cub->parse.splitted[3] || !cub->parse.splitted[2])
		error_free("ERROR\nR must only have 2 parameters",
			cub, cub->parse.splitted);
	cub->res.w = ft_atoi(cub->parse.splitted[1]);
	checker(cub->parse.splitted, cub, 1);
	if (cub->res.w < 0)
		cub->res.w = 2560;
	if (cub->res.w > 2560)
		cub->res.w = 2560;
	cub->res.h = ft_atoi(cub->parse.splitted[2]);
	if (cub->res.h < 0)
		cub->res.h = 1440;
	if (cub->res.h > 1440)
		cub->res.h = 1440;
	ft_free(cub->parse.splitted);
	cub->rep.res = 1;
}

void	identifier(t_cub3d *cub)
{
	if (cub->parse.splitted[0][0] == 'N'
		&& cub->parse.splitted[0][1] == 'O')
		path(&cub->path.no, cub, &cub->fd.no, &cub->rep.no);
	else if (cub->parse.splitted[0][0] == 'S'
		&& cub->parse.splitted[0][1] == 'O')
		path(&cub->path.so, cub, &cub->fd.so, &cub->rep.so);
	else if (cub->parse.splitted[0][0] == 'W'
		&& cub->parse.splitted[0][1] == 'E')
		path(&cub->path.we, cub, &cub->fd.we, &cub->rep.we);
	else if (cub->parse.splitted[0][0] == 'E'
		&& cub->parse.splitted[0][1] == 'A')
		path(&cub->path.ea, cub, &cub->fd.ea, &cub->rep.ea);
	else if (cub->parse.splitted[0][0] == 'S'
		&& cub->parse.splitted[0][1] != '0')
		path(&cub->path.s, cub, &cub->fd.s, &cub->rep.s);
}

void	path(char **path, t_cub3d *cub, int *fd, int *rep)
{
	int	i;	

	i = 0;
	if (*rep == 1)
		error_msg_free("Error\nAdditional path found\n", cub);
	if (cub->parse.line[0] == 'S' && cub->parse.line[1] != 'O'
		&& cub->parse.line[2] == ' ')
		error_msg_free("Error\nInvalid identifier\n", cub);
	if (cub->parse.line[2] != ' ')
	{
		if (cub->parse.line[0] == 'S' && cub->parse.line[1] != '0')
		{
			if (cub->parse.line[1] != ' ')
				error_msg_free("Error\nInvalid identifier\n", cub);
		}
		else
			error_msg_free("Error\nInvalid identifier\n", cub);
	}
	if (cub->parse.splitted[2])
		error_free("Error\nInvalid identifier\n", cub, cub->parse.splitted);
	*path = ft_strdup(cub->parse.splitted[1]);
	ft_free(cub->parse.splitted);
	extension_error(*path, ".xpm", fd);
	*rep = 1;
}

void	fc_color(t_cub3d *cub, t_rgb *fc, int *rep)
{
	ft_free(cub->parse.splitted);
	cub->parse.rgb = 0;
	while (cub->parse.colors[cub->parse.rgb])
		cub->parse.rgb++;
	if (cub->parse.rgb != 3)
		error_free("Error\nWrong format of rgb\n", cub, cub->parse.colors);
	checker(cub->parse.colors, cub, 0);
	fc->r = ft_atoi(cub->parse.colors[0]);
	fc->g = ft_atoi(cub->parse.colors[1]);
	fc->b = ft_atoi(cub->parse.colors[2]);
	ft_free(cub->parse.colors);
	range(fc, cub);
	*rep = 1;
}

void	fcc(t_cub3d *cub)
{
	if (*cub->parse.line == 'F')
	{
		if (cub->rep.f == 1)
			error_msg_free("Error\nRepetition of F\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after F\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(cub, &cub->f, &cub->rep.f);
	}
	else if (*cub->parse.line == 'C')
	{
		if (cub->rep.c == 1)
			error_msg_free("Error\nRepetition of C\n", cub);
		if (cub->parse.line[1] != ' ')
			error_msg_free("Error\nAnother char found after C\n", cub);
		cub->parse.splitted = ft_split(cub->parse.line, ' ');
		fc_checker(&cub->parse, cub);
		cub->parse.colors = ft_split(cub->parse.splitted[1], ',');
		fc_color(cub, &cub->c, &cub->rep.c);
	}
}
