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

int 	Event::parse_option(t_data *d, int ac, char **av)
{
	int tmp = 0;

	while (1)
	{
		if (av[d->i_argv][0] == 'x' && strlen(&av[d->i_argv][1]) >= 2 && strlen(&av[d->i_argv][1]) <= 5 && isdigit(av[d->i_argv][1]))
		{
			tmp = atoi(&av[d->i_argv][1]);
			if (tmp >= 10 && tmp <= 80)

				d->winx = tmp;
			d->i_argv++;
		}
		else if (av[d->i_argv][0] == 'y' && strlen(&av[d->i_argv][1]) >= 2 && strlen(&av[d->i_argv][1]) <= 5 && isdigit(av[d->i_argv][1]))
		{
			tmp = atoi(&av[d->i_argv][1]);
			if (tmp >= 10 && tmp <= 80)
				d->winy = tmp;
			d->i_argv++;
		}
		else
			d->i_argv++;
		if (strncmp(av[d->i_argv], "lib", 3) == 0)
			break ;
	}

	(void)ac;
	(void)d;
	return (0);
}

void	Event::init_map(t_data *d)
{
	d->map = static_cast<char **>(std::malloc(sizeof(char*) * d->winy ));
	d->map_info = static_cast<int **>(std::malloc(sizeof(int*) * d->winy ));
	for (int i = 0; i < d->winy; ++i)
	{
		d->map[i] = static_cast<char *>(std::malloc(sizeof(char) * d->winx ));
		d->map_info[i] = static_cast<int *>(std::malloc(sizeof(int) * d->winx ));
		memset(d->map[i], ' ', d->winx);
		memset(d->map_info[i], '0', d->winx);
	}
	for (int y = 0; y < d->winy; ++y)
	{
		for (int i = 0; i < d->winx; ++i)
		{
			if (y == 0 || y == d->winy - 1 || i == 0 || i == d->winx - 1)
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
	d->i_argv = 1;
	d->winx = MAP_WIDTH;
	d->winy = MAP_HEIGHT;
	this->parse_option(d, ac, av);
	d->posx = d->winx / 2;
	d->posy = d->winy / 2;
	d->eat = 0;
	d->dir = 2;
	d->speed = BASIC_SPEED;
	this->open_lib(d, av[d->i_argv]);
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
