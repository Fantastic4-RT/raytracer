//
// Created by Andrew Radiuk on 6/7/17.
//

#include "rt.h"

int		cross_exit(void *a)
{
	if (a)
		exit(0);
	return (0);
}

int 	key_hook(int keycode, t_main *main)
{
	void *a;

	a = main;
	if (keycode == 53)
		exit(0);
	return (0);
}