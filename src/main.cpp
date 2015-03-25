/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 16:57:34 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"

void    do_move(t_data *d, int newx, int newy)
{
	d->map[d->posy][d->posx] = ' ';
	d->map[d->posy + newy][d->posx + newx] = HEAD;
}

void    move(t_data *d) {
	if (d->key == NULL || (*d->key)->size() == 0)
		return ;
	if ((*d->key)->front() == (UP) && d->posy - 1 >= 0)
		do_move(d, 0, -1);
	else if ((*d->key)->front() == (DOWN) && d->posy + 1 < MAP_HEIGHT)
		do_move(d, 0, 1);
	else if ((*d->key)->front() == (LEFT) && d->posx - 1 >= 0)
		do_move(d, -1, 0);
	else if ((*d->key)->front() == (RIGHT) && d->posx + 1 < MAP_WIDTH)
		do_move(d, 1, 0);
	else if ((*d->key)->front() == (ECHAP))
		;
	(*d->key)->erase((*d->key)->begin());
	return ;
}

int main(int ac, char **av)
{
	void				*hndl;
	Api					*(*create)();
	Api					*graphic;
	t_data 				*d;

	static_cast<void>(ac);
	static_cast<void>(av);
	if ((d = static_cast<t_data *>(std::malloc(sizeof(t_data)))) == NULL)
	{
		std::cerr << "t_data malloc error" << std::endl; 
		exit(EXIT_FAILURE);
	}
	d->key = NULL;
	d->map = NULL;
	d->winx = MAP_WIDTH;
	d->winy = MAP_HEIGHT;
	d->posx = d->winx / 2;
	d->posy = d->winy / 2;
	hndl = dlopen("lib_graphic.so", RTLD_LAZY | RTLD_LOCAL);
	if (hndl == NULL)
	{
		std::cerr << "dlopen : "<< dlerror() << std::endl; 
		exit(EXIT_FAILURE);
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(hndl, "newObject"))) == NULL)
	{ 
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	d->map = static_cast<char **>(std::malloc(sizeof(char*) * MAP_HEIGHT ));
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		d->map[i] = static_cast<char *>(std::malloc(sizeof(char) * MAP_HEIGHT ));
		memset(d->map[i], '\0', MAP_HEIGHT);
	}
	for (int y = 0; y < MAP_WIDTH; ++y)
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			if (y == 0 || y == MAP_WIDTH - 1 || i == 0 || i == MAP_HEIGHT - 1)
				d->map[y][i] = WALL;
		}
	}
	d->map[d->posy][d->posx] = HEAD;

	graphic = create();
	graphic->init(ac, av, MAP_WIDTH, MAP_HEIGHT, NULL, d->map);

	while (1)
	{
		move(d);
		graphic->render_scene();
		if (d->key == NULL || (*d->key)->size() == 0)
			d->key = graphic->get_touch_list();
	}

	graphic->close();
	dlclose(hndl);
	return (EXIT_SUCCESS);
}
