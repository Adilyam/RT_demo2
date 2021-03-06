/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_figure.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htkachuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 20:30:39 by htkachuk          #+#    #+#             */
/*   Updated: 2018/06/04 20:30:41 by htkachuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		set_vector_dir(t_all *ev, int x, int y)
{
	ev->d.x = (double)(x - 90) / 800;
	ev->d.y = (double)y / SIZE_Y;
	ev->d.x = (2 * ev->d.x) - 1;
	ev->d.y = 1 - (2 * ev->d.y);
	ev->d.x *= tan(60);
	ev->d.y *= tan(60);
	ev->d.z = 1;
}

void		init2(t_all *ev)
{
	ev->k_iter = 1;
	ev->filter = NORMAL;
	ev->transp = 0;
	ev->reflect = 0;
	ev->coef = 0.0;
	ev->cam.o = define_vector(0, 0, 0);
	ev->cam.o_rot = define_vector(0, 0, 0);
}

void		init(t_all *ev)
{
	int j;

	j = -1;
	init2(ev);
	while (++j < ev->num_f)
	{
		ev->figure[j].specular = 500;
		ev->figure[j].centre = define_vector(0, 0, 0);
		define_color(&ev->figure[j], 255, 0, 0);
		ev->figure[j].id_figure = 0;
		ev->figure[j].max = 2;
		ev->figure[j].min = 0;
		ev->figure[j].radius = 1;
		ev->figure[j].point = define_vector(0, 1, 0);
		ev->figure[j].k = 0.9;
	}
	j = -1;
	while (++j < ev->num_l)
	{
		ev->light[j].intensity = 0.2;
		ev->light[j].position = define_vector(0, 0, 0);
		ev->light[j].type = AMBIANT;
	}
}

void		allocate_mem(t_all *ev)
{
	ev->figure = (t_figure*)malloc(sizeof(t_figure) * ev->num_f);
	ev->light = (t_light*)malloc(sizeof(t_light) * ev->num_l);
	init(ev);
}

void		normalise_obj(t_all *ev)
{
	int i;

	i = -1;
	while (++i < ev->num_f)
	{
		if (ev->figure[i].id_figure == PLANE)
			ev->figure[i].centre = normalise(ev->figure[i].centre);
		else if (ev->figure[i].id_figure == CYLINDRE ||
				ev->figure[i].id_figure == CONE ||
				ev->figure[i].id_figure == CYLINDRE_CUT ||
				ev->figure[i].id_figure == ELLIPSOID ||
				ev->figure[i].id_figure == PARABOLOID ||
				ev->figure[i].id_figure == CONE_CUT)
			ev->figure[i].point = normalise(ev->figure[i].point);
	}
}
