/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 12:52:42 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/10 12:52:44 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	prot;

	prot.x = x;
	prot.y = y;
	prot.z = z;
	return (prot);
}

t_vec3	vec3_norm(t_vec3 vector)
{
	double	length;

	length = vec3_length(vector);
	vector.x /= length;
	vector.y /= length;
	vector.z /= length;
	return (vector);
}

t_vec3	vec3_invert(t_vec3 vector)
{
	vector.x = -vector.x;
	vector.y = -vector.y;
	vector.z = -vector.z;
	return (vector);
}

double	vec3_dp(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

int		vec3_eq(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (1);
	else
		return (0);
}
