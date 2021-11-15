/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:56:15 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 16:54:10 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	error_msg_free(char *s, t_cub3d *cub)
{
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->image);
	if (cub->parse.x > 0)
		ft_free(cub->map);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_free(char *s, t_cub3d *cub, char **tofree)
{
	ft_free(tofree);
	free(cub->parse.line);
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
	free(cub->image);
	ft_putstr_fd(s, 2);
	exit(1);
}

void	error_msg(char *s)
{
	ft_putstr_fd(s, 2);
	exit(1);
}

void	exist(t_cub3d *cub)
{
	if (cub->rep.res == 0)
		error_msg_free("ERROR\nResolution not found", cub);
	else if (cub->rep.no == 0 || cub->rep.so == 0 || cub->rep.ea == 0
		|| cub->rep.we == 0 || cub->rep.s == 0)
		error_msg_free("ERROR\nRequired Path not found", cub);
	else if (cub->rep.f == 0)
		error_msg_free("ERROR\nFloor color not found", cub);
	else if (cub->rep.c == 0)
		error_msg_free("ERROR\nCeiling color not found", cub);
	if (cub->parse.x == 0)
	{
		cub->map = (char **)malloc(2 * sizeof(char *));
		cub->map[0] = ft_strdup(cub->parse.line);
		cub->map[1] = NULL;
	}
	else
		push(cub);
}
