/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:58:28 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/05 17:26:23 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checker(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][0] == '0')
		error_msg_free("ERROR\nLine starts with 0", cub);
	if (cub->parse.x == 0)
		first_line(cub);
	cub->parse.y = 1;
	while (cub->map[cub->parse.x][cub->parse.y])
	{
		if (cub->map[cub->parse.x][cub->parse.y] == ' ')
			space(cub);
		else if (cub->map[cub->parse.x][cub->parse.y] == '1' ||
				cub->map[cub->parse.x][cub->parse.y] == 'N' ||
				cub->map[cub->parse.x][cub->parse.y] == 'S' ||
				cub->map[cub->parse.x][cub->parse.y] == 'W' ||
				cub->map[cub->parse.x][cub->parse.y] == 'E' ||
				cub->map[cub->parse.x][cub->parse.y] == '2')
			cub->parse.y++;
		else if (cub->map[cub->parse.x][cub->parse.y] == '0')
			zero(cub);
		else if (!cub->map[cub->parse.x][cub->parse.y])
			error_msg_free("ERROR\nInvalid char in map", cub);
		else
			cub->parse.y++;
	}
}

void	map(t_cub3d *cub)
{
	if (!*cub->parse.line)
		error_msg_free("ERROR\nEmpty line\n", cub);
	exist(cub);
	map_checker(cub);
	cub->parse.y = 0;
	while (cub->map[cub->parse.x][cub->parse.y])
	{
		if (cub->parse.spawn == 0 && character(cub) == 1)
			spawning(cub);
		else if (cub->map[cub->parse.x][cub->parse.y] == '2'
				&& !cub->map[cub->parse.x][cub->parse.y + 1])
			error_msg_free("ERROR\nSprite position invalid", cub);
		else if (cub->map[cub->parse.x][cub->parse.y] == '2')
			cub->sprite_num++;
		else if (cub->parse.spawn == 1 && character(cub) == 1)
			error_msg_free("ERROR\nSpawning position repeated or invalid", cub);
		else if (character(cub) == 0)
			error_msg_free("ERROR\nInvalid char in the map", cub);
		cub->parse.y++;
	}
	cub->parse.x++;
}

void	push(t_cub3d *cub)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (cub->map[count])
		count++;
	cub->tmp = malloc((count + 2) * sizeof(char *));
	while (++i < count)
		cub->tmp[i] = ft_strdup(cub->map[i]);
	ft_free(cub->map);
	cub->map = NULL;
	cub->tmp[i] = ft_strdup(cub->parse.line);
	cub->tmp[i + 1] = NULL;
	i = -1;
	cub->map = malloc((count + 2) * sizeof(char *));
	while (cub->tmp[++i])
		cub->map[i] = ft_strdup(cub->tmp[i]);
	cub->map[i] = NULL;
	ft_free(cub->tmp);
}

void	space(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y - 1] != ' '
			&& cub->map[cub->parse.x][cub->parse.y - 1] != '1')
		error_msg_free("ERROR\nInvalid char before space", cub);
	else if (cub->map[cub->parse.x][cub->parse.y + 1] != ' '
			&& cub->map[cub->parse.x][cub->parse.y + 1] != '1'
			&& cub->map[cub->parse.x][cub->parse.y + 1] != '\0')
		error_msg_free("ERROR\nInvalid char after space", cub);
	else if (cub->parse.x - 1 >= 0
		&& cub->map[cub->parse.x - 1][cub->parse.y] != ' '
			&& cub->map[cub->parse.x - 1][cub->parse.y] != '1')
	{
		if (cub->parse.y < (int)ft_strlen(cub->map[cub->parse.x - 1]))
			error_msg_free("ERROR\nInvalid char above space", cub);
	}
	cub->parse.y++;
}

void	zero(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y - 1] == ' ')
		error_msg_free("ERROR\nSpace before 0", cub);
	else if (cub->map[cub->parse.x][cub->parse.y + 1] == ' ')
		error_msg_free("ERROR\nSpace after 0", cub);
	else if (cub->map[cub->parse.x][cub->parse.y + 1] == '\0')
		error_msg_free("ERROR\n0 at the end of the line", cub);
	else if (cub->parse.x - 1 >= 0
		&& cub->map[cub->parse.x - 1][cub->parse.y] < '0')
		error_msg_free("ERROR\nSpace or empty line above 0", cub);
	cub->parse.y++;
}
