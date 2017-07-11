/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:57:17 by aradiuk           #+#    #+#             */
/*   Updated: 2017/04/10 13:57:18 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;
	return (result);
}

t_vec3	vec3_sub(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	result;

	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;
	return (result);
}

t_vec3	vec3_mult(t_vec3 vec, double multiplier)
{
	t_vec3	result;

	result.x = vec.x * multiplier;
	result.y = vec.y * multiplier;
	result.z = vec.z * multiplier;
	return (result);
}

double	vec3_length(t_vec3 vec)
{
	double result;

	result = sqrt(vec3_dp(vec, vec));
	return (result);
}

t_vec3	vec3_cross(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3 res;

	res = vec3_create(vec1.y * vec2.z - vec1.z * vec2.y,
					vec1.z * vec2.x - vec1.x * vec2.z,
					vec1.x * vec2.y - vec1.y * vec2.x);
	return (res);
}
