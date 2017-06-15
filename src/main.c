/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:33:58 by aradiuk           #+#    #+#             */
/*   Updated: 2017/06/07 13:33:59 by aradiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
//#include "../includes/parser.h"
//#define PRINT
#ifdef PRINT
void	print_scene(t_main *main)
{
	printf("<scene width=%d height=%d objects=%d lights=%d>\n", main->scene.wid, main->scene.hei, main->scene.objs, main->scene.lights);
	printf("<camera>\n");
	printf("\t<position>x = %f, y = %f, z = %f</position>\n", main->cam.ray.pos.x, main->cam.ray.pos.y, main->cam.ray.pos.z);
	printf("\t<rotation>x = %f, y = %f, z = %f</rotation>\n", main->cam.rot.x, main->cam.rot.y, main->cam.rot.z);
	printf("\t<fov>fov = %d</fov>\n", main->cam.fov);
	printf("</camera>\n");
	int i = -1;
	while (++i < main->scene.lights)
	{
		printf("<light>\n");
		printf("\t<position>x = %f, y = %f, z = %f</position>\n", main->light[i].ray.pos.x, main->light[i].ray.pos.y, main->light[i].ray.pos.z);
		printf("\t<direction>x = %f, y = %f, z = %f</direction>\n", main->light[i].ray.dir.x, main->light[i].ray.dir.y, main->light[i].ray.dir.z);
		printf("\t<color>x = %f, y = %f, z = %f</color>\n", main->light[i].color.x, main->light[i].color.y, main->light[i].color.z);
		printf("</light>\n");
	}
	i = -1;
	while (++i < main->scene.objs)
	{
		printf("<object type=\"%s\">\n", main->obj[i].type);
		if (ft_strcmp(main->obj[i].type, "plane") == 0)
		{
			printf("\t<position>x = %f, y = %f, z = %f</position>\n", ((t_plane *)main->obj[i].data)->pos.x, ((t_plane *)main->obj[i].data)->pos.y, ((t_plane *)main->obj[i].data)->pos.z);
			printf("\t<normal>x = %f, y = %f, z = %f</normal>\n", ((t_plane *)main->obj[i].data)->normal.x, ((t_plane *)main->obj[i].data)->normal.y, ((t_plane *)main->obj[i].data)->normal.z);
			printf("\t<color>x = %f, y = %f, z = %f</color>\n", ((t_plane *)main->obj[i].data)->mat.color.x, ((t_plane *)main->obj[i].data)->mat.color.y, ((t_plane *)main->obj[i].data)->mat.color.z);
			printf("\t<diffuse>%f</diffuse>\n", ((t_plane *)main->obj[i].data)->mat.diff);
			printf("\t<specular>%f</specular>\n", ((t_plane *)main->obj[i].data)->mat.spec);
			printf("\t<reflecion>%f</reflection>\n", ((t_plane *)main->obj[i].data)->mat.reflect);
		}
		else if (ft_strcmp(main->obj[i].type, "sphere") == 0)
		{
			printf("\t<position>x = %f, y = %f, z = %f</position>\n", ((t_sphere *)main->obj[i].data)->pos.x, ((t_sphere *)main->obj[i].data)->pos.y, ((t_sphere *)main->obj[i].data)->pos.z);
			printf("\t<radius>%f</radius>\n",((t_sphere *)main->obj[i].data)->rad);
			printf("\t<color>x = %f, y = %f, z = %f</color>\n", ((t_sphere *)main->obj[i].data)->mat.color.x, ((t_sphere *)main->obj[i].data)->mat.color.y, ((t_sphere *)main->obj[i].data)->mat.color.z);
			printf("\t<diffuse>%f</diffuse>\n", ((t_sphere *)main->obj[i].data)->mat.diff);
			printf("\t<specular>%f</specular>\n", ((t_sphere *)main->obj[i].data)->mat.spec);
			printf("\t<reflecion>%f</reflection>\n", ((t_sphere *)main->obj[i].data)->mat.reflect);
		}
		else if (ft_strcmp(main->obj[i].type, "cylinder") == 0)
		{
			printf("\t<position1>x = %f, y = %f, z = %f</position1>\n", ((t_cyl *)main->obj[i].data)->p1.x, ((t_cyl *)main->obj[i].data)->p1.y, ((t_cyl *)main->obj[i].data)->p1.z);
			printf("\t<position2>x = %f, y = %f, z = %f</position2>\n", ((t_cyl *)main->obj[i].data)->p2.x, ((t_cyl *)main->obj[i].data)->p2.y, ((t_cyl *)main->obj[i].data)->p2.z);
			printf("\t<axis>x = %f, y = %f, z = %f</axis>\n", ((t_cyl *)main->obj[i].data)->axis.x, ((t_cyl *)main->obj[i].data)->axis.y, ((t_cyl *)main->obj[i].data)->axis.z);
			printf("\t<radius>%f</radius>\n",((t_cyl *)main->obj[i].data)->rad);
			printf("\t<cut>%d</cut>\n",((t_cyl *)main->obj[i].data)->cut);
			printf("\t<color>x = %f, y = %f, z = %f</color>\n", ((t_cyl *)main->obj[i].data)->mat.color.x, ((t_cyl *)main->obj[i].data)->mat.color.y, ((t_cyl *)main->obj[i].data)->mat.color.z);
			printf("\t<diffuse>%f</diffuse>\n", ((t_cyl *)main->obj[i].data)->mat.diff);
			printf("\t<specular>%f</specular>\n", ((t_cyl *)main->obj[i].data)->mat.spec);
			printf("\t<reflecion>%f</reflection>\n", ((t_cyl *)main->obj[i].data)->mat.reflect);
		}
		else if (ft_strcmp(main->obj[i].type, "cone") == 0)
		{
			printf("\t<position1>x = %f, y = %f, z = %f</position1>\n", ((t_cone *)main->obj[i].data)->p1.x, ((t_cone *)main->obj[i].data)->p1.y, ((t_cone *)main->obj[i].data)->p1.z);
			printf("\t<position2>x = %f, y = %f, z = %f</position2>\n", ((t_cone *)main->obj[i].data)->p2.x, ((t_cone *)main->obj[i].data)->p2.y, ((t_cone *)main->obj[i].data)->p2.z);
			printf("\t<axis>x = %f, y = %f, z = %f</axis>\n", ((t_cone *)main->obj[i].data)->axis.x, ((t_cone *)main->obj[i].data)->axis.y, ((t_cone *)main->obj[i].data)->axis.z);
			printf("\t<radius1>%f</radius1>\n",((t_cone *)main->obj[i].data)->r1);
			printf("\t<radius2>%f</radius2>\n",((t_cone *)main->obj[i].data)->r2);
			printf("\t<angle>%f</angle>\n",((t_cone *)main->obj[i].data)->angle);
			printf("\t<cut>%d</cut>\n",((t_cone *)main->obj[i].data)->cut);
			printf("\t<color>x = %f, y = %f, z = %f</color>\n", ((t_cone *)main->obj[i].data)->mat.color.x, ((t_cone *)main->obj[i].data)->mat.color.y, ((t_cone *)main->obj[i].data)->mat.color.z);
			printf("\t<diffuse>%f</diffuse>\n", ((t_cone *)main->obj[i].data)->mat.diff);
			printf("\t<specular>%f</specular>\n", ((t_cone *)main->obj[i].data)->mat.spec);
			printf("\t<reflecion>%f</reflection>\n", ((t_cone *)main->obj[i].data)->mat.reflect);
		}
		printf("</object>\n");
	}
}
#endif
void	scene_line(int fd, t_main *main)
{
	char 	*tmp;
	char	*str;

	get_next_line(fd, &str);
	tmp = ft_strstr(str, "width=");
	main->scene.wid = tmp == 0 ? WIDTH : ft_atoi(tmp + ft_strlen("width="));
	tmp = ft_strstr(str, "height=");
	main->scene.hei = tmp == 0 ? HEIGHT : ft_atoi(tmp + ft_strlen("height="));
	tmp = ft_strstr(str, "objects=");
	main->scene.objs = tmp == 0 ? OBJECTS : ft_atoi(tmp + ft_strlen("objects="));
	tmp = ft_strstr(str, "lights=");
	main->scene.lights = tmp == 0 ? LIGHTS : ft_atoi(tmp + ft_strlen("lights="));
	free(str);
}

void	set_flag(char *str, t_main *main, int set_rem)
{
	while (ft_isspace(*str) == 1)
		str++;
	if (set_rem == 1)
	{
		main->flag.cam = ft_strcmp(str, "<camera>") == 0 ? 1 : 0;
		main->flag.light = ft_strcmp(str, "<light>") == 0 ? 1 : 0;
		main->flag.obj = ft_strstr(str, "<object") != 0 ? 1 : 0;
	}
	else if (set_rem == 2)
	{
		main->flag.cam = ft_strcmp(str, "</camera>") == 0 ? 0 : main->flag.cam;
		main->flag.light = ft_strcmp(str, "</light>") == 0 ? 0 : main->flag.light;
		main->flag.obj = ft_strcmp(str, "</object>") == 0 ? 0 : main->flag.obj;
		main->obj_i += ft_strcmp(str, "</object>") == 0 ? 1 : 0;
		main->light_i += ft_strcmp(str, "</light>") == 0 ? 1 : 0;
	}
}

void	default_values(t_main *main)
{
	main->light = (t_light *)malloc(sizeof(t_light) * main->scene.lights);
	main->obj = (t_obj *)malloc(sizeof(t_obj) * main->scene.objs);
	main->obj_i = 0;
	main->light_i = 0;
	main->flag.cam = 0;
	main->flag.light = 0;
	main->flag.obj = 0;
	main->cam.ray.pos.x = 0;
	main->cam.ray.pos.y = 0;
	main->cam.ray.pos.z = 0;
	main->cam.rot.x = 0;
	main->cam.rot.y = 0;
	main->cam.rot.z = 0;
	main->cam.fov = 45;
}

void	read_file(int fd, t_main *main)
{
	char	*str;

	scene_line(fd, main);
	default_values(main);
	while (get_next_line(fd, &str))
	{
		//line_validation
		if (ft_strcmp(str, "</scene") == 0)
			break ;
		if (main->flag.cam == 0 && main->flag.light == 0 && main->flag.obj == 0)
			set_flag(str, main, 1);
		else if (main->flag.cam == 1 || main->flag.light == 1 || main->flag.obj == 1)
			set_flag(str, main, 2);
		if (main->obj_i == main->scene.objs)
		{
			free(str);
			return ;
		}
		if (main->flag.cam == 1)
			cam_light_obj_line(str, main, 1);
		else if (main->flag.light == 1)
			cam_light_obj_line(str, main, 2);
		else if (main->flag.obj == 1)
			cam_light_obj_line(str, main, 3);
		free(str);
	}
}

int main(int argc, char **argv)
{
	int fd;
	t_main	main;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	read_file(fd, &main);
//	scene_initialise(&main);
#ifdef PRINT
	print_scene(&main);
#endif
	mlx_initialise(&main);
	return (0);
}


//int 	main(int argc, char **argv)
//{
//	t_main	main;
//
//	if (argc != 1)
//		return (1);
//	//read_input(&main);
//	scene_initialise(&main);
//	mlx_initialise(&main);
//}