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

int 	main(int argc, char **argv)
{
	t_main	main;

	if (argc != 1)
		return (1);
	//read_input(&main);
	scene_initialise(&main);
	mlx_initialise(&main);
}