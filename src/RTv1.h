/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkachuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:04:30 by htkachuk          #+#    #+#             */
/*   Updated: 2018/05/04 12:04:35 by htkachuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define SIZE_X 600
# define SIZE_Y 600
# define MIN 1
# define MAX 2147483647

# include "mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	int				size_x;
	int				size_y;
	char			*str;
	void			*img;
	int				bits;
	int				size;
	int				end;
}					t_mlx;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_rgb
{
	unsigned int	b : 8;
	unsigned int	g : 8;
	unsigned int	r : 8;
	unsigned int	a : 8;
}					t_rgb;

typedef union		u_color
{
	uint32_t		color;
	t_rgb			chanels;
}					t_color;

typedef struct		s_ray
{
	t_vector		start;
	t_vector		dir;
}					t_ray;

typedef struct		s_light
{
	char			type;
	double			intensity;
	t_vector		position;
}					t_light;

typedef struct		s_figure
{
	int				id_figure;
	double			radius;
	t_vector		centre;
	t_vector		point;
	double			specular;
	t_color			color;
}					t_figure;

typedef struct		s_all
{
	t_mlx			mlx;
	int				id;
	double			x1;
	double			x2;
	t_vector		o;
	t_vector		o_rot;
	t_vector		c;
	t_vector		d;
	t_vector		l;
	t_vector		p;
	t_vector		n;
	t_vector		r;
	t_vector		v;
	t_light			*light;
	t_figure		*figure;
	double			vw;
	double			vh;
	int				d_d;
	uint32_t		color;
	t_color			color_f;
	int				num_f;
	int				num_l;
	void			(*func1)(struct	s_all *);
	void			(*func2)(struct s_all *, int, t_vector, t_vector);
}					t_all;

void				rot_figure(t_all *ev);
void				ft_create(t_all *ev);
t_vector			vector_plus_vector(t_vector a, t_vector b);
int					ft_key(int keycode, t_all *ev);
double				compute_lighting(t_all *ev, int c);
void				draw_scene(t_all *ev);
t_vector			normalise(t_vector a);
double				multy_vec(t_vector a1, t_vector a2);
double				find_len(t_vector a);
t_vector			vector_minus_vector(t_vector a, t_vector b);
t_vector			define_vector(double x, double y, double z);
t_vector			vector_div_const(t_vector a, double b);
t_vector			vector_multy_const(t_vector a, double b);
t_vector			vector_plus_const(t_vector a, double b);
t_vector			vector_minus_const(t_vector a, double b);
double				closet_interesection(t_all *ev, double *t,
	t_vector o, t_vector d);
uint32_t			multy_col(t_color col, double j);
void				parsing(char *str, t_all *ev);
void				intersect_ray_plane(t_all *ev, int i,
	t_vector o, t_vector d);
void				intersect_ray_sphere(t_all *ev, int i,
	t_vector o, t_vector d);
void				intersect_ray_cylinder(t_all *ev, int i,
	t_vector o, t_vector d);
void				intersect_ray_cone(t_all *ev, int i,
	t_vector o, t_vector d);
void				define_scene1(t_all *ev);
void				define_scene2(t_all *ev);
void				define_color(t_figure *figure, unsigned int b,
	unsigned int g, unsigned int r);
void				allocate_mem(t_all *ev, int figure, int light);
void				define_type_intens(t_light *l, char c, double i);
void				define_sph_cyl(t_figure *figure, double radius,
	int specular, int id);
void				define_scene3(t_all *ev);
void				define_scene4(t_all *ev);
void				define_scene5(t_all *ev);
int					mouse_zoom(int keycode, int x, int y, t_all *ev);

#endif
