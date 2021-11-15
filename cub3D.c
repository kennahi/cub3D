/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:32:05 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/06 15:36:37 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub3d *cub)
{
	cub->img.img_ptr = mlx_new_image(cub->mlx.p, cub->res.w, cub->res.h);
	cub->img.img_data = (int *)mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	cub->ray = 0;
	cub->texheight = 64;
	cub->texwidth = 64;
	cub->rotatespeed = 0.03;
	cub->movespeed = 0.05;
	while (cub->ray < cub->res.w)
	{
		calculate(cub);
		sidedistance(cub);
		hit(cub);
		wall(cub);
		rendering(cub);
	}
	if (cub->sprite_num)
		sprite(cub);
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.w, cub->img.img_ptr, 0, 0);
}

int	deal_key(t_cub3d *cub)
{
	mlx_destroy_image(cub->mlx.p, cub->img.img_ptr);
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	moves_up_down(cub);
	movesides(cub);
	look(cub);
	if (cub->keyboard[53])
		key_close(cub);
	draw(cub);
	return (0);
}

void	texture(t_cub3d *cub)
{
	cub->mlx.p = mlx_init();
	cub->mlx.w = mlx_new_window(cub->mlx.p, cub->res.w, cub->res.h, "cub3D");
	cub->txt[0].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.no,
			&cub->txt[0].w, &cub->txt[0].h);
	cub->txt[0].img_data = (int *)mlx_get_data_addr(cub->txt[0].img_ptr,
			&cub->txt[0].bpp, &cub->txt[0].size_line, &cub->txt[0].endian);
	cub->txt[1].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.we,
			&cub->txt[1].w, &cub->txt[1].h);
	cub->txt[1].img_data = (int *)mlx_get_data_addr(cub->txt[1].img_ptr,
			&cub->txt[1].bpp, &cub->txt[1].size_line, &cub->txt[1].endian);
	cub->txt[2].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.so,
			&cub->txt[2].w, &cub->txt[2].h);
	cub->txt[2].img_data = (int *)mlx_get_data_addr(cub->txt[2].img_ptr,
			&cub->txt[2].bpp, &cub->txt[2].size_line, &cub->txt[2].endian);
	cub->txt[3].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.ea,
			&cub->txt[3].w, &cub->txt[3].h);
	cub->txt[3].img_data = (int *)mlx_get_data_addr(cub->txt[3].img_ptr,
			&cub->txt[3].bpp, &cub->txt[3].size_line, &cub->txt[3].endian);
	cub->txt[4].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.s,
			&cub->txt[4].w, &cub->txt[4].h);
	cub->txt[4].img_data = (int *)mlx_get_data_addr(cub->txt[4].img_ptr,
			&cub->txt[4].bpp, &cub->txt[4].size_line, &cub->txt[4].endian);
	free_path(cub);
	if (cub->ac == 3)
		cub->image = (char *)malloc(cub->res.w * cub->res.h * 3);
}

void	parsing(t_cub3d *cub)
{
	cub->parse.r = 1;
	while (cub->parse.r == 1)
	{
		cub->parse.r = get_next_line(cub->fd.file, &cub->parse.line);
		if (*cub->parse.line == 'R')
			resolution(cub);
		else if (cub->parse.line[0] == 'N' || cub->parse.line[0] == 'S'
			|| cub->parse.line[0] == 'W' || cub->parse.line[0] == 'E')
		{
			cub->parse.splitted = ft_split(cub->parse.line, ' ');
			identifier(cub);
		}
		else if (cub->parse.line[0] == 'F' || cub->parse.line[0] == 'C')
			fcc(cub);
		else if (*cub->parse.line == ' ' || *cub->parse.line == '1'
			|| *cub->parse.line == '0' || (!*cub->parse.line
				&& cub->parse.x > 0))
			map(cub);
		free(cub->parse.line);
	}
	if_sprite(cub);
	if (cub->parse.x)
		map_errors(cub);
	else
		error_msg_free("ERROR\nMap not found", cub);
}

int	main(int ac, char **av)
{
	t_cub3d	cub;

	if (ac >= 2 && ac <= 3)
	{
		cub.ac = ac;
		extension_error(av[1], ".cub", &cub.fd.file);
		init(&cub);
		parsing(&cub);
		texture(&cub);
		draw(&cub);
		bmp(&cub, ac, av);
		mlx_hook(cub.mlx.w, 2, 0, key_pressed, &cub);
		mlx_hook(cub.mlx.w, 3, 0, key_released, &cub);
		mlx_hook(cub.mlx.w, 17, 0, key_close, &cub);
		mlx_loop_hook(cub.mlx.p, deal_key, &cub);
		mlx_loop(cub.mlx.p);
	}
	else
		error_msg("Error\nInvalid params");
	return (0);
}
