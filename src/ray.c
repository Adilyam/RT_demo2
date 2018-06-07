/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkachuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:15:40 by htkachuk          #+#    #+#             */
/*   Updated: 2018/05/21 19:15:42 by htkachuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	reflect_ray(t_vector r, t_vector n)
{
	t_vector	k;
	t_vector	d_n;
	double		r_n;

	r_n = multy_vec(r, n);
	d_n = vector_multy_const(n, (2 * r_n));
	k = vector_minus_vector(d_n, r);
	k = normalise(k);
	return (k);
}

static void	figure_type(int i, t_all *ev)
{
	if (i == 0)
		ev->func2 = &intersect_ray_sphere;
	if (i == 1)
		ev->func2 = &intersect_ray_plane;
	if (i == 2)
		ev->func2 = &intersect_ray_cylinder;
	if (i == 3)
		ev->func2 = &intersect_ray_cone;
}

double		closet_interesection(t_all *ev, double *t, t_vector o, t_vector d)
{
	int		i;
	double	closet_t;

	closet_t = t[1];
	ev->id = -1;
	i = 0;
	while (i < ev->num_f)
	{
		figure_type(ev->figure[i].id_figure, ev);
		(ev->func2)(ev, i, o, d);
		if (ev->x1 >= t[0] && ev->x1 <= t[1] && ev->x1 < closet_t)
		{
			ev->id = i;
			closet_t = ev->x1;
		}
		if (ev->x2 >= t[0] && ev->x2 <= t[1] && ev->x2 < closet_t)
		{
			ev->id = i;
			closet_t = ev->x2;
		}
		i++;
	}
	return (closet_t);
}

void		rot_figure(t_all *ev)
{
	double			mat[3][3];
	t_vector		ret;

	mat[0][0] = cos(ev->o_rot.z) * cos(ev->o_rot.z);
	mat[1][0] = cos(ev->o_rot.z) * sin(ev->o_rot.x) *
	sin(ev->o_rot.y) - cos(ev->o_rot.x) * sin(ev->o_rot.z);
	mat[2][0] = cos(ev->o_rot.x) * cos(ev->o_rot.z) *
	sin(ev->o_rot.y) + sin(ev->o_rot.x) * sin(ev->o_rot.z);
	mat[0][1] = cos(ev->o_rot.y) * sin(ev->o_rot.z);
	mat[1][1] = cos(ev->o_rot.x) * cos(ev->o_rot.z) +
	sin(ev->o_rot.x) * sin(ev->o_rot.y) * sin(ev->o_rot.z);
	mat[2][1] = -cos(ev->o_rot.z) * sin(ev->o_rot.x) +
	cos(ev->o_rot.x) * sin(ev->o_rot.y) * sin(ev->o_rot.z);
	mat[0][2] = -sin(ev->o_rot.y);
	mat[1][2] = cos(ev->o_rot.y) * sin(ev->o_rot.x);
	mat[2][2] = cos(ev->o_rot.x) * cos(ev->o_rot.y);
	ret.x = (mat[0][0] * ev->d.x) + (mat[1][0] * ev->d.y)
	+ (mat[2][0] * ev->d.z);
	ret.y = (mat[0][1] * ev->d.x) + (mat[1][1] * ev->d.y)
	+ (mat[2][1] * ev->d.z);
	ret.z = (mat[0][2] * ev->d.x) + (mat[1][2] * ev->d.y)
	+ (mat[2][2] * ev->d.z);
	ev->d = ret;
}
