/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:11 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/31 15:26:44 by vjacquie         ###   ########.fr       */
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


int		Event::check_move( void ) {
	int 	movx = 0;
	int 	movy = 0;

	if (this->_dir == 1)
		movy = -1;
	else if (this->_dir == 2)
		movy = 1;
	else if (this->_dir == 3)
		movx = -1;
	else if (this->_dir == 4)
		movx = 1;

	if (this->_map[this->_posy + movy][this->_posx + movx] == WALL
		|| this->_map[this->_posy + movy][this->_posx + movx] == QUEUE)
		return (-1);
	return (0);
}

void	Event::dec_map(int dec) {
	for (int y = 0; y < this->_winy; ++y)
	{
		for (int x = 0; x < this->_winx; ++x)
		{
			if (this->_map_info[y][x] > 0)
				this->_map_info[y][x] -= dec;
		}
	}
}

void	Event::inc_map( void ) {
	for (int y = 0; y < this->_winy; ++y)
	{
		for (int x = 0; x < this->_winx; ++x)
		{
			if (this->_map_info[y][x] > 0)
				this->_map_info[y][x] += 1;
		}
	}
}

void	Event::move( void ) {
	int 	movx = 0;
	int 	movy = 0;

	if (check_move() < 0)
	{
		this->_game = false;
		return ;
	}

	if (this->_eat > 0)
		inc_map();
	if (this->_dir == 1)
		movy = -1;
	else if (this->_dir == 2)
		movy = 1;
	else if (this->_dir == 3)
		movx = -1;
	else if (this->_dir == 4)
		movx = 1;
	this->_map_info[this->_posy + movy][this->_posx + movx] = this->_map_info[this->_posy][this->_posx] + 1;
	dec_map(1);
	if (this->_eat > 0)
		this->_eat--;
	this->_after_head = this->_head;
	this->_head[0] = QUEUE;
	this->_posy += movy;
	this->_posx += movx;
	this->_head = &(this->_map[this->_posy][this->_posx]);
	if (this->_head[0] == FRUIT)
	{
		this->_fruit = false;
		this->_eat++;
	}
	this->_head[0] = HEAD;
	this->_queue[0] = ' ';
	this->_queue = this->_before_queue;

	for (int y = 0; y < this->_winy; ++y)
	{
		for (int x = 0; x < this->_winx; ++x)
		{
			if (this->_map_info[y][x] == 2)
			{
				this->_before_queue = &(this->_map[y][x]);
				return ;
			}
		}
	}
}

void	Event::change_dir( void ) {
	while (this->_key != NULL && (*this->_key)->size() != 0)
	{
		if ((*this->_key)->front() == (UP) && this->_posy - 1 >= 0 && this->_dir != 2)
			this->_dir = 1;
		else if ((*this->_key)->front() == (DOWN) && this->_posy + 1 < MAP_HEIGHT && this->_dir != 1)
			this->_dir = 2;
		else if ((*this->_key)->front() == (LEFT) && this->_posx - 1 >= 0 && this->_dir != 4)
			this->_dir = 3;
		else if ((*this->_key)->front() == (RIGHT) && this->_posx + 1 < MAP_WIDTH && this->_dir != 3)
			this->_dir = 4;
		else if ((*this->_key)->front() == (ECHAP))
			this->_game = false;
		(*this->_key)->erase((*this->_key)->begin());
	}
	return ;
}



void	Event::run( void ) {
	
	this->_game = true;
	srand(time(NULL));
	while (this->_game == true)
	{
		change_dir();
		if (this->_game == false)
			return ;
		move();
		if (this->_fruit == false)
			add_fruit();
		this->_graphic->render_scene();
		if (this->_key == NULL || (*this->_key)->size() == 0)
			this->_key = this->_graphic->get_touch_list();
		usleep(this->_speed);
	}
}

void	Event::add_fruit( void ) {
	int		x;
	int		y;

	x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
	y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	while (this->_map[y][x] != ' ')
	{
		x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
		y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	}
	this->_map[y][x] = FRUIT;
	this->_fruit = true;
}

int 	Event::parse_option(int ac, char **av)
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
				this->_winx = tmp;
		}
		else if (av[i][0] == 'y' && strlen(&av[i][1]) >= 2 && strlen(&av[i][1]) <= 5 && isdigit(av[i][1]))
		{
			tmp = atoi(&av[i][1]);
			if (tmp >= 10 && tmp <= 80)
				this->_winy = tmp;
		}
		else if (strstr(av[i], ".so") != NULL && lib < 3)
		{
			this->_lib_name[lib] = av[i];
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

void	Event::init_map( void )
{
	this->_map = static_cast<char **>(std::malloc(sizeof(char*) * this->_winy ));
	this->_map_info = static_cast<int **>(std::malloc(sizeof(int*) * this->_winy ));
	for (int i = 0; i < this->_winy; ++i)
	{
		this->_map[i] = static_cast<char *>(std::malloc(sizeof(char) * this->_winx ));
		this->_map_info[i] = static_cast<int *>(std::malloc(sizeof(int) * this->_winx ));
		memset(this->_map[i], ' ', this->_winx);
		memset(this->_map_info[i], '0', this->_winx);
	}
	for (int y = 0; y < this->_winy; ++y)
	{
		for (int i = 0; i < this->_winx; ++i)
		{
			if (y == 0 || y == this->_winy - 1 || i == 0 || i == this->_winx - 1)
				this->_map[y][i] = WALL;
		}
	}
	this->_map[this->_posy - 3][this->_posx] = QUEUE;
	this->_map_info[this->_posy - 3][this->_posx] = 1;

	this->_map[this->_posy - 2][this->_posx] = QUEUE;
	this->_map_info[this->_posy - 2][this->_posx] = 2;

	this->_map[this->_posy - 1][this->_posx] = QUEUE;
	this->_map_info[this->_posy - 1][this->_posx] = 3;

	this->_map[this->_posy][this->_posx] = HEAD;
	this->_map_info[this->_posy][this->_posx] = 4;

	this->_head = &(this->_map[this->_posy][this->_posx]);
	this->_after_head = &(this->_map[this->_posy - 1][this->_posx]);
	this->_before_queue = &(this->_map[this->_posy - 2][this->_posx]);
	this->_queue = &(this->_map[this->_posy - 3][this->_posx]);
}

void	Event::init(int ac, char **av) {
	this->_key = NULL;
	this->_map = NULL;
	this->_fruit = false;
	this->_winx = MAP_WIDTH;
	this->_winy = MAP_HEIGHT;
	this->_lib_name[0] = NULL;
	this->_lib_name[1] = NULL;
	this->_lib_name[2] = NULL;
	parse_option(ac, av);
	this->_posx = this->_winx / 2;
	this->_posy = this->_winy / 2;
	this->_eat = 0;
	this->_dir = 2;
	this->_speed = BASIC_SPEED;
	this->open_lib(this->_lib_name[0]);
	this->init_map();
	this->_graphic->init(ac, av, this->_winx, this->_winy, NULL, this->_map);
}

void	Event::open_lib(char *name ) {
	Api					*(*create)();

	this->_hndl = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
	if (this->_hndl == NULL)
	{
		std::cerr << "dlopen : "<< dlerror() << std::endl; 
		exit(EXIT_FAILURE);
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(this->_hndl, "newObject"))) == NULL)
	{ 
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_graphic = create();
}

void	Event::close_all( void ) {
	this->_graphic->close();
	dlclose(this->_hndl);
	if (this->_key != NULL)
		(*this->_key)->clear();
	if (this->_map != NULL)
		delete[] this->_map;
	if (this->_map_info != NULL)
		delete[] this->_map_info;
	// if (d != NULL)
	// 	free(d);
}
