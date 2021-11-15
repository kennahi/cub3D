/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:46:02 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 17:18:47 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	last_line(t_cub3d *cub)
{
	cub->parse.y = 0;
	while (cub->map[cub->parse.x - 1][cub->parse.y])
	{
		if (cub->map[cub->parse.x - 1][cub->parse.y] > 'E' &&
				cub->map[cub->parse.x][cub->parse.y] != '1')
			error_msg_free("ERROR\nSpawning position in an invalid place", cub);
		cub->parse.y++;
	}
	cub->parse.y = 0;
	while (cub->map[cub->parse.x][cub->parse.y])
	{
		if (cub->map[cub->parse.x][cub->parse.y] != ' ' &&
				cub->map[cub->parse.x][cub->parse.y] != '1')
			error_msg_free("ERROR\nLast line invalid", cub);
		cub->parse.y++;
	}
}

void	map_errors(t_cub3d *cub)
{
	int	i;

	i = -1;
	if (!cub->parse.spawn)
		error_msg_free("ERROR\nSpawning position not found or invalid", cub);
	while (cub->map[--cub->parse.x][0] == '\0')
		cub->map[cub->parse.x] = NULL;
	last_line(cub);
	while (++i < cub->parse.x)
	{
		cub->parse.y = 0;
		while (cub->map[i][cub->parse.y])
		{
			map_check_next(cub, i);
			if (cub->map[i][cub->parse.y] == '1')
				cub->parse.y++;
			else if (cub->map[i][cub->parse.y] == '2')
				spriteposition(cub, i);
			else
				cub->parse.y++;
		}
	}
	cub->parse.x++;
}

void	first_line(t_cub3d *cub)
{
	cub->parse.y = 0;
	while (cub->map[cub->parse.x][cub->parse.y])
	{
		if (cub->map[cub->parse.x][cub->parse.y] != ' ' &&
				cub->map[cub->parse.x][cub->parse.y] != '1')
			error_msg_free("ERROR\nFirst line invalid", cub);
		cub->parse.y++;
	}
}

void	map_check_next(t_cub3d *cub, int i)
{
	if (cub->map[i][cub->parse.y] == ' ' &&
			cub->map[i + 1][cub->parse.y] == '0' &&
			cub->parse.y < (int)ft_strlen(cub->map[i + 1]))
		error_msg_free("ERROR\n0 beneath space", cub);
	else if (cub->map[i][cub->parse.y] == '0' &&
			(cub->map[i + 1][cub->parse.y] == ' ' ||
			cub->map[i + 1][cub->parse.y] == '\0'))
		error_msg_free("ERROR\nSpace or end of line beneath 0", cub);
}
