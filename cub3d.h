/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennahi <kennahi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:35:06 by kennahi           #+#    #+#             */
/*   Updated: 2021/05/06 14:51:46 by kennahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "getnextline/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include "math.h"

typedef struct s_resolution
{
	int		h;
	int		w;
}				t_res;

typedef struct s_mlx
{
	void	*p;
	void	*w;
}				t_mlx;

typedef struct s_fd
{
	int		file;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
}				t_fd;

typedef struct s_repetition
{
	int		res;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		s;
	int		f;
	int		c;
}				t_rep;

typedef struct s_path
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
}				t_path;

typedef struct s_parse
{
	int		r;
	char	*line;
	char	**splitted;
	char	**splitted2;
	char	**splitted3;
	char	**colors;
	int		x;
	int		y;
	int		spawn;
	int		rgb;
}				t_parse;

typedef struct s_img
{
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;
	void	*xpm;
}				t_img;

typedef struct s_bmp
{
	int		pad;
	int		filesize;
	int		fd;
	int		i;
}				t_bmp;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
	int		order;
}				t_sprite;

typedef struct s_cub3d
{
	t_res		res;
	t_rep		rep;
	t_mlx		mlx;
	t_path		path;
	t_rgb		f;
	t_rgb		c;
	t_parse		parse;
	t_img		img;
	t_bmp		bmp;
	t_fd		fd;
	t_img		txt[5];
	t_sprite	*sprite;

	char		*image;
	int			color;
	int			ac;
	int			bmp_pos;
	int			abrv;
	int			keyboard[300];
	char		**map;
	char		**tmp;
	int			ray;
	int			mapx;
	int			mapy;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		olddirx;
	double		oldplanex;
	double		rotatespeed;
	double		movespeed;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			texwidth;
	int			texheight;
	double		wallx;
	int			tex_x;
	int			tex_y;
	double		step;
	double		texpos;
	int			sprite_num;
	int			sprite_n;
	double		*sprite_buf;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidth;
	int			drawstarty;
	int			drawstartx;
	int			drawendy;
	int			drawendx;
	int			spriteline;
	int			d;
}				t_cub3d;

void	resolution(t_cub3d *cub);
void	identifier(t_cub3d *cub);
void	path(char **path, t_cub3d *cub, int *fd, int *rep);
void	fcc(t_cub3d *cub);
void	fc_color(t_cub3d *cub, t_rgb *fc, int *rep);
void	ft_free(char **arr);
void	error_free(char *s, t_cub3d *cub, char **tofree);
void	error_msg_free(char *s, t_cub3d *cub);
void	error_msg(char *s);
void	exist(t_cub3d *cub);
void	checker(char **s, t_cub3d *cub, int i);
void	fc_checker(t_parse *parse, t_cub3d *cub);
void	range(t_rgb *rgb, t_cub3d *cub);
void	push(t_cub3d *cub);
void	map(t_cub3d *cub);
void	init(t_cub3d *cub);
void	first_line(t_cub3d *cub);
void	zero(t_cub3d *cub);
void	space(t_cub3d *cub);
void	spawning(t_cub3d *cub);
void	spawning_we(t_cub3d *cub);
void	spawning_ns(t_cub3d *cub);
int		character(t_cub3d *cub);
void	extension_error(char *av, char *ext, int *fd);
void	map_errors(t_cub3d *cub);
void	last_line(t_cub3d *cub);
void	map_check_next(t_cub3d *cub, int i);
void	spriteposition(t_cub3d *cub, int i);
void	spritesort(t_cub3d *cub);
void	spritedistance(t_cub3d *cub);
void	sprite(t_cub3d *cub);
void	spriterendering(t_cub3d *cub);
void	sprite_image(t_cub3d *cub);
void	texture(t_cub3d *cub);
void	free_path(t_cub3d *cub);
void	texture(t_cub3d *cub);
void	calculate(t_cub3d *cub);
void	sidedistance(t_cub3d *cub);
void	hit(t_cub3d *cub);
void	wall(t_cub3d *cub);
void	rendering(t_cub3d *cub);
int		create_rgb(t_rgb *rgb);
void	wallrendering(t_cub3d *cub);
int		key_pressed(int key, t_cub3d *cub);
int		key_released(int key, t_cub3d *cub);
int		key_close(t_cub3d *cub);
void	moves_up_down(t_cub3d *cub);
void	movesides(t_cub3d *cub);
void	look(t_cub3d *cub);
void	if_sprite(t_cub3d *cub);
void	bmp(t_cub3d *cub, int ac, char **av);
void	bmp_save(t_cub3d *cub);
void	bmp_filling(t_cub3d *cub, t_rgb *fc);

#endif