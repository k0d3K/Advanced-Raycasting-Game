/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguerbig <lguerbig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:40:12 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/15 19:46:15 by lguerbig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_H
# define GEO_H

typedef int __attribute__((vector_size(8), aligned(8)))		t_pointd;

typedef union u_point
{
	struct
	{
		int	x;
		int	y;
	};
	t_pointd	p;
}	t_point;

typedef float __attribute__((vector_size(8), aligned(8)))	t_vec2f;

typedef union u_vec2
{
	struct
	{
		float	x;
		float	y;
	};
	t_vec2f	v;
}	t_vec2;

typedef float __attribute__((vector_size(16), aligned(16)))	t_vec3f;

typedef union u_vec3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	t_vec3f	v;
}	t_vec3;

t_point	point(int x, int y);

t_vec2	vec2(float x, float y);
float	vec2_length(t_vec2 v);
t_vec2	vec2_normalize(t_vec2 v);
float	vec2_dot(t_vec2 v1, t_vec2 v2);
float	vec2_angle(t_vec2 v1, t_vec2 v2);

t_vec2	geo_intersection(t_vec2 p1, t_vec2 p2, t_vec2 p3, t_vec2 p4);

t_vec3	vec3(float x, float y, float z);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_dot(t_vec3 v1, t_vec3 v2);
float	vec3_angle(t_vec3 v1, t_vec3 v2);

# define PI		3.14159265359f
# define R2D	57.2957795131f		// 180 / pi
# define D2R	0.0174532925199f	// pi / 180

typedef enum e_face
{
	NORTH = 1,
	SOUTH,
	WEST,
	EAST,
	DOOR,
	EXIT
}	t_face;

typedef struct s_vec2_pair
{
	t_vec2	a;
	t_vec2	b;
}	t_vec2_pair;

#endif