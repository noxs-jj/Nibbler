/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:11 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/31 15:17:31 by vjacquie         ###   ########.fr       */
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


int		Event::check_move(t_data *d) {
	int 	movx = 0;
	int 	movy = 0;

	if (d->dir == 1)
		movy = -1;
	else if (d->dir == 2)
		movy = 1;
	else if (d->dir == 3)
		movx = -1;
	else if (d->dir == 4)
		movx = 1;

	if (d->map[d->posy + movy][d->posx + movx] == WALL
		|| d->map[d->posy + movy][d->posx + movx] == QUEUE)
		return (-1);
	return (0);
}

void	Event::dec_map(t_data *d, int dec) {
	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] > 0)
				d->map_info[y][x] -= dec;
		}
	}
}

void	Event::inc_map(t_data *d) {
	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] > 0)
				d->map_info[y][x] += 1;
		}
	}
}

void	Event::move(t_data *d) {
	int 	movx = 0;
	int 	movy = 0;

	if (check_move(d) < 0)
	{
		d->game = false;
		return ;
	}

	if (d->eat > 0)
		inc_map(d);
	if (d->dir == 1)
		movy = -1;
	else if (d->dir == 2)
		movy = 1;
	else if (d->dir == 3)
		movx = -1;
	else if (d->dir == 4)
		movx = 1;
	d->map_info[d->posy + movy][d->posx + movx] = d->map_info[d->posy][d->posx] + 1;
	dec_map(d, 1);
	if (d->eat > 0)
		d->eat--;
	d->after_head = d->head;
	d->head[0] = QUEUE;
	d->posy += movy;
	d->posx += movx;
	d->head = &(d->map[d->posy][d->posx]);
	if (d->head[0] == FRUIT)
	{
		d->fruit = false;
		d->eat++;
	}
	d->head[0] = HEAD;
	d->queue[0] = ' ';
	d->queue = d->before_queue;

	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] == 2)
			{
				d->before_queue = &(d->map[y][x]);
				return ;
			}
		}
	}
}

void	Event::change_dir(t_data *d) {
	while (d->key != NULL && (*d->key)->size() != 0)
	{
		if ((*d->key)->front() == (UP) && d->posy - 1 >= 0 && d->dir != 2)
			d->dir = 1;
		else if ((*d->key)->front() == (DOWN) && d->posy + 1 < MAP_HEIGHT && d->dir != 1)
			d->dir = 2;
		else if ((*d->key)->front() == (LEFT) && d->posx - 1 >= 0 && d->dir != 4)
			d->dir = 3;
		else if ((*d->key)->front() == (RIGHT) && d->posx + 1 < MAP_WIDTH && d->dir != 3)
			d->dir = 4;
		else if ((*d->key)->front() == (ECHAP))
			d->game = false;
		(*d->key)->erase((*d->key)->begin());
	}
	return ;
}



void	Event::run(t_data *d) {
	
	d->game = true;
	srand(time(NULL));
	while (d->game == true)
	{
		change_dir(d);
		if (d->game == false)
			return ;
		move(d);
		if (d->fruit == false)
			add_fruit(d);
		d->graphic->render_scene();
		if (d->key == NULL || (*d->key)->size() == 0)
			d->key = d->graphic->get_touch_list();
		usleep(d->speed);
	}
}

void	Event::add_fruit(t_data *d) {
	int		x;
	int		y;

	x = (rand() + d->posx / d->posy * d->dir) % d->winx;
	y = (rand() + d->posy / d->posx * d->dir) % d->winy;
	while (d->map[y][x] != ' ')
	{
		x = (rand() + d->posx / d->posy * d->dir) % d->winx;
		y = (rand() + d->posy / d->posx * d->dir) % d->winy;
	}
	d->map[y][x] = FRUIT;
	d->fruit = true;
}

int 	Event::parse_option(t_data *d, int ac, char **av)
{
	int tmp = 0;
	int i = 1;
	int lib = 0;

	while (i < ac)
	{
		if (av[i][0] == 'x' && strlen(&av[i][1]) >= 2 && strlen(&av[i][1]) <= 5 && isdigit(av[i][1]))
		{
			tmp = atoi(&av[i][1]);
			if (tmp >= 10 && tmp <= 80)
				d->winx = tmp;
		}
		else if (av[i][0] == 'y' && strlen(&av[i][1]) >= 2 && strlen(&av[i][1]) <= 5 && isdigit(av[i][1]))
		{
			tmp = atoi(&av[i][1]);
			if (tmp >= 10 && tmp <= 80)
				d->winy = tmp;
		}
		else if (strstr(av[i], ".so") != NULL && lib < 3)
		{
			d->lib_name[lib] = av[i];
			lib++;
		}
		i++;
	}
	if (lib <= 0)
	{
		std::cerr << "Error : Lib required" << std::endl;
		exit(EXIT_FAILURE);
	}
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
	d->winx = MAP_WIDTH;
	d->winy = MAP_HEIGHT;
	d->lib_name[0] = NULL;
	d->lib_name[1] = NULL;
	d->lib_name[2] = NULL;
	parse_option(d, ac, av);
	d->posx = d->winx / 2;
	d->posy = d->winy / 2;
	d->eat = 0;
	d->dir = 2;
	d->speed = BASIC_SPEED;
	this->open_lib(d, d->lib_name[0]);
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
