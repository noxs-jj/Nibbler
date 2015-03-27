/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:11 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/27 16:27:18 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/event.class.hpp"

Event::Event( void ) {}

Event::Event( Event const & src ) { *this = src; }

Event & Event::operator=( Event const & rhs ) {
	if (this != &rhs)
	{

	}
	return (*this);
}
Event::~Event( void ) {}

void	Event::init_map(t_data *d)
{
	d->map = static_cast<char **>(std::malloc(sizeof(char*) * MAP_HEIGHT ));
	d->map_info = static_cast<int **>(std::malloc(sizeof(int*) * MAP_HEIGHT ));
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		d->map[i] = static_cast<char *>(std::malloc(sizeof(char) * MAP_HEIGHT ));
		d->map_info[i] = static_cast<int *>(std::malloc(sizeof(int) * MAP_HEIGHT ));
		memset(d->map[i], ' ', MAP_HEIGHT);
		memset(d->map_info[i], '0', MAP_HEIGHT);
	}
	for (int y = 0; y < MAP_WIDTH; ++y)
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			if (y == 0 || y == MAP_WIDTH - 1 || i == 0 || i == MAP_HEIGHT - 1)
				d->map[y][i] = WALL;
		}
	}
	d->map[d->posy - 3][d->posx] = QUEUE;
	d->map_info[d->posy - 3][d->posx] = 1;

	d->map[d->posy - 2][d->posx] = QUEUE;
	d->map_info[d->posy - 2][d->posx] = 2;

	d->map[d->posy - 1][d->posx] = QUEUE;
	d->map_info[d->posy - 1][d->posx] = 3;

	d->map[d->posy][d->posx] = HEAD;
	d->map_info[d->posy][d->posx] = 4;

	d->head = &(d->map[d->posy][d->posx]);
	d->after_head = &(d->map[d->posy - 1][d->posx]);
	d->before_queue = &(d->map[d->posy - 2][d->posx]);
	d->queue = &(d->map[d->posy - 3][d->posx]);
}

void	Event::init(t_data *d, int ac, char **av) {
	d->key = NULL;
	d->map = NULL;
	d->fruit = false;
	d->winx = MAP_WIDTH;
	d->winy = MAP_HEIGHT;
	d->posx = d->winx / 2;
	d->posy = d->winy / 2;
	d->eat = 0;
	d->dir = 2;
	d->speed = BASIC_SPEED;
	this->open_lib(d, av[1]);
	this->init_map(d);
	d->graphic->init(ac, av, d->winx, d->winy, NULL, d->map);
}

void	Event::open_lib(t_data *d, char *name ) {
	Api					*(*create)();

	d->hndl = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
	if (d->hndl == NULL)
	{
		std::cerr << "dlopen : "<< dlerror() << std::endl; 
		exit(EXIT_FAILURE);
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(d->hndl, "newObject"))) == NULL)
	{ 
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	d->graphic = create();
}

void	Event::close_all(t_data *d) {
	d->graphic->close();
	dlclose(d->hndl);
	if (d->key != NULL)
		(*d->key)->clear();
	if (d->map != NULL)
		delete[] d->map;
	if (d->map_info != NULL)
		delete[] d->map_info;
	if (d != NULL)
		free(d);
}
