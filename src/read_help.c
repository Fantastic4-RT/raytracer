/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 16:03:15 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/18 16:03:16 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_arr_tmp(char **arr, char *tmp)
{
	if (arr[0])
		free(arr[0]);
	if (arr[1])
		free(arr[1]);
	if (arr[2])
		free(arr[2]);
	free(arr);
	free(tmp);
}

t_vec3	vec3_fill_atoi(char **arr)
{
	if (!arr[0] || !arr[1] || !arr[2])
		error(10);
	return (vec3_create(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2])));
}

void	scene_line(int fd, t_main *main)
{
	char	*tmp;
	char	*str;

	get_next_line(fd, &str);
	ft_strstr(str, "<scene") == 0 ? error(4) : 0;
	tmp = ft_strstr(str, "width=");
	main->scene.wid = tmp == 0 ? WIDTH : ft_atoi(tmp + ft_strlen("width="));
	tmp = ft_strstr(str, "height=");
	main->scene.hei = tmp == 0 ? HEIGHT : ft_atoi(tmp + ft_strlen("height="));
	tmp = ft_strstr(str, "objects=");
	main->scene.objs = tmp == 0 ? OBJECTS :
					ft_atoi(tmp + ft_strlen("objects="));
	tmp = ft_strstr(str, "lights=");
	main->scene.lights = tmp == 0 ? LIGHTS :
					ft_atoi(tmp + ft_strlen("lights="));
	tmp = ft_strstr(str, "aa=");
	main->scene.a_a = tmp == 0 ? 0 : ft_atoi(tmp + ft_strlen("aa="));
	tmp = ft_strstr(str, "eff=");
	main->scene.eff = tmp == 0 ? 0 : ft_atoi(tmp + ft_strlen("eff="));
	tmp = ft_strstr(str, "ambient=");
	main->scene.amb = tmp == 0 ? AMBIENT : ft_atof(tmp + ft_strlen("ambient="));
	main->scene.objs == 0 ? error(4) : 0;
	main->scene.lights == 0 ? error(5) : 0;
	free(str);
}

void	set_flag(char *str, t_main *main, int set_rem)
{
	while (ft_isspace(*str) == 1)
		str++;
	if (set_rem == 1)
	{
		main->flag.cam = ft_strcmp(str, "<camera>") == 0 ? 1 : 0;
		main->flag.lgh = ft_strcmp(str, "<light>") == 0 ? 1 : 0;
		main->flag.obj = ft_strstr(str, "<object") != 0 ? 1 : 0;
		if (main->light_i == main->scene.lights && ft_strcmp(str,
															"<light>") == 0)
			error(3);
	}
	else if (set_rem == 2)
	{
		main->flag.cam = ft_strcmp(str, "</camera>") == 0 ? 0 : main->flag.cam;
		main->flag.lgh = ft_strcmp(str, "</light>") == 0 ? 0 : main->flag.lgh;
		main->flag.obj = ft_strcmp(str, "</object>") == 0 ? 0 : main->flag.obj;
		main->obj_i += ft_strcmp(str, "</object>") == 0 ? 1 : 0;
		main->light_i += ft_strcmp(str, "</light>") == 0 ? 1 : 0;
	}
	main->obj_i > main->scene.objs ? error(6) : 0;
	main->light_i > main->scene.lights ? error(7) : 0;
}

void	read_file(int fd, t_main *main)
{
	char	*str;

	scene_line(fd, main);
	default_values(main);
	while (get_next_line(fd, &str))
	{
		if (ft_strstr(str, "/scene") != 0 || main->obj_i >= main->scene.objs)
			break ;
		if (main->flag.cam == 0 && main->flag.lgh == 0 && main->flag.obj == 0)
			set_flag(str, main, 1);
		else if (main->flag.cam == 1 || main->flag.lgh == 1 ||
				main->flag.obj == 1)
			set_flag(str, main, 2);
		if (main->flag.cam == 1)
			cam_light_obj_line(str, main, 1);
		else if (main->flag.lgh == 1)
			cam_light_obj_line(str, main, 2);
		else if (main->flag.obj == 1)
			cam_light_obj_line(str, main, 3);
		free(str);
	}
	if (ft_strstr(str, "/scene") != 0 || main->obj_i >= main->scene.objs)
		free(str);
	last_check(str, main);
}
