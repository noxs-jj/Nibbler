/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:11 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/04 19:04:02 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/event.class.hpp"

Event::Event( void ) {}
Event::Event( Event const & src ) { static_cast<void>(src); }
Event & Event::operator=( Event const & rhs ) { static_cast<void>(rhs); return *this; }
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
	for (int y = 0; y < this->_winy; ++y) {
		for (int x = 0; x < this->_winx; ++x) {
			if (this->_map_info[y][x] > 0)
				this->_map_info[y][x] -= dec;
		}
	}
}

void	Event::inc_map( void ) {
	for (int y = 0; y < this->_winy; ++y) {
		for (int x = 0; x < this->_winx; ++x) {
			if (this->_map_info[y][x] > 0)
				this->_map_info[y][x] += 1;
		}
	}
}

void	Event::pro_spawn_obstacle( int rock )
{
	int 	x;
	int 	y;

	x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
	y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	while (rock > 0) {
		while (this->_map[y][x] != ' ') {
			x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
			y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
		}
		this->_map[y][x] = WALL;
		rock--;
	}
}

void	Event::pro_get_special( void ) {
	int i = rand() % 50;

	if (i >= 20 && i <= 30) {	// bonus
		this->_score += 100;
		this->_special = 0;
	}
	else if ((i % 2) == 0) {	// malus
		this->_score = ((this->_score - 100 >= 100) ? (this->_score - 100) : 0);
		this->_eat += 1;
		this->_special = 0;
	}
	else {	// malus
		this->_eat += 2;
		pro_spawn_obstacle(2);
		this->_special = 0;
	}
}

void	Event::move( void ) {
	int 	movx = 0;
	int 	movy = 0;

	if (check_move() < 0) {
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
	if (this->_head[0] == FRUIT) {
		if (this->_game_mode == 2)
			pro_spawn_obstacle(1);
		this->_fruit = false;
		this->_score += 10;
		this->_eat++;
	}
	else if (this->_head[0] == SPECIAL && this->_game_mode != 2) {
		this->_score += 50;
		this->_special = 0;
	}
	else if (this->_head[0] == SPECIAL && this->_game_mode == 2)
		pro_get_special();
	this->_head[0] = HEAD;
	this->_queue[0] = ' ';
	this->_queue = this->_before_queue;

	for (int y = 0; y < this->_winy; ++y) {
		for (int x = 0; x < this->_winx; ++x) {
			if (this->_map_info[y][x] == 2) {
				this->_before_queue = &(this->_map[y][x]);
				return ;
			}
		}
	}
}

void	Event::change_lib(int lib) {
	if (this->_lib_name[lib] == NULL)
		return ;
	this->_graphic->close();
	dlclose(this->_hndl);
	open_lib(this->_lib_name[lib]);
	this->_graphic->init(this->_d->ac, this->_d->av, this->_winx, this->_winy, NULL, this->_map);
	this->_graphic->render_scene();
}

void	Event::change_dir( void ) {
	int 	dir = this->_dir;

	while (this->_key != NULL && (*this->_key)->size() != 0) {
		if ((*this->_key)->front() == (UP) && this->_posy - 1 >= 0 && this->_dir != 2)
			dir = 1;
		else if ((*this->_key)->front() == (DOWN) && this->_posy + 1 < MAP_HEIGHT && this->_dir != 1)
			dir = 2;
		else if ((*this->_key)->front() == (LEFT) && this->_posx - 1 >= 0 && this->_dir != 4)
			dir = 3;
		else if ((*this->_key)->front() == (RIGHT) && this->_posx + 1 < MAP_WIDTH && this->_dir != 3)
			dir = 4;
		else if ((*this->_key)->front() == (ECHAP))
			this->_game = false;
		else if ((*this->_key)->front() == ONE)
			change_lib(0);
		else if ((*this->_key)->front() == TWO)
			change_lib(1);
		else if ((*this->_key)->front() == THREE)
			change_lib(2);
		else if ((*this->_key)->front() == SPACE && this->_paused == true)
			this->_paused = false;
		else if ((*this->_key)->front() == SPACE && this->_paused == false)
			this->_paused = true;
		(*this->_key)->erase((*this->_key)->begin());
	}
	this->_dir = dir;
	return ;
}

void	Event::run_level( void ) {}

void	Event::run( void ) {
	this->_game = true;
	srand(time(NULL));
	if (this->_game_mode == 1)
		run_level();
	else {
		while (this->_game == true) {
			change_dir();
			if (this->_game == false)
				return ;
			if (this->_paused == false) {
				move();
				if (this->_fruit == false)
					add_fruit();
				if (this->_special == 0)
					add_special();
				else {
					this->_special--;
					if (this->_special == 0)
						this->_spec[0] = ' ';
				}
			}
			this->_graphic->render_scene();
			if (this->_key == NULL || (*this->_key)->size() == 0)
				this->_key = this->_graphic->get_touch_list();
			if (this->_game_mode == 2)
				this->_speed = ((BASIC_SPEED - this->_score <= 0) ? 1 : (BASIC_SPEED - this->_score));
			usleep(this->_speed);
		}
	}
}

void	Event::add_special( void ) {
	int		x;
	int		y;

	if (((rand() + this->_posx / this->_posy * this->_dir) % 50) != 25)
		return ;
	x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
	y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	while (this->_map[y][x] != ' ') {
		x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
		y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	}
	this->_map[y][x] = SPECIAL;
	this->_spec = &(this->_map[y][x]);
	this->_special = SPECIAL_TIME;
}

void	Event::add_fruit( void ) {
	int		x;
	int		y;

	x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
	y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	while (this->_map[y][x] != ' ') {
		x = (rand() + this->_posx / this->_posy * this->_dir) % this->_winx;
		y = (rand() + this->_posy / this->_posx * this->_dir) % this->_winy;
	}
	this->_map[y][x] = FRUIT;
	this->_fruit = true;
}

int 	Event::parse_option(int ac, char **av) {
	int tmp = 0;
	int i = 1;
	int lib = 0;

	while (i < ac) {
		if (av[i][0] == 'x' && strlen(&av[i][1]) >= 2 && strlen(&av[i][1]) <= 5) {
			if (isdigit(av[i][1])) {
				tmp = atoi(&av[i][1]);
				if (tmp >= 10 && tmp <= 80)
					this->_winx = tmp;
				else {
					std::cerr << "Event::parse_option - width between 10 to 80." << std::endl;
					throw std::exception();
				}
			}
			else if (av[i][1] == '-') {
				std::cerr << "Event::parse_option - width must be positive." << std::endl;
				throw std::exception();
			}
		}
		else if (av[i][0] == 'y' && strlen(&av[i][1]) >= 2 && strlen(&av[i][1]) <= 5 ) {
			if (isdigit(av[i][1])) {
				tmp = atoi(&av[i][1]);
				if (tmp >= 10 && tmp <= 80)
					this->_winy = tmp;
				else {
					std::cerr << "Event::parse_option - height between 10 to 80." << std::endl;
					throw std::exception();
				}
			}
			else if (av[i][1] == '-') {
				std::cerr << "Event::parse_option - height must be positive." << std::endl;
				throw std::exception();
			}
		}
		else if (strstr(av[i], ".so") != NULL && lib < 3) {
			this->_lib_name[lib] = av[i];
			lib++;
		}
		else if (strstr(av[i], "-level") != NULL && lib < 3)
			this->_game_mode = 1;
		else if (strstr(av[i], "-pro") != NULL && lib < 3)
			this->_game_mode = 2;
		i++;
	}
	if (lib <= 0) {
		std::cerr << "Event::parse_option - Lib required" << std::endl;
		throw std::exception();
	}
	return (0);
}

void	Event::init_map( void ) {
	this->_map = static_cast<char **>(std::malloc(sizeof(char*) * this->_winy ));
	this->_map_info = static_cast<int **>(std::malloc(sizeof(int*) * this->_winy ));
	if (NULL == this->_map || NULL == this->_map_info) {
		std::cerr << "Event::init_map - Malloc error on _map, _map_info";
		throw std::exception();
	}
	for (int i = 0; i < this->_winy; ++i) {
		this->_map[i] = static_cast<char *>(std::malloc(sizeof(char) * this->_winx ));
		this->_map_info[i] = static_cast<int *>(std::malloc(sizeof(int) * this->_winx ));
		if (NULL == this->_map[i] || NULL == this->_map_info[i]) {
			std::cerr << "Event::init_map - Malloc error on _map[i], _map_info[i]";
			throw std::exception();
		}
		memset(this->_map[i], ' ', this->_winx);
		memset(this->_map_info[i], '0', this->_winx);
	}
	for (int y = 0; y < this->_winy; ++y) {
		for (int i = 0; i < this->_winx; ++i) {
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

void	Event::init( t_data *d ) {
	this->_d = d;
	this->_paused = false;
	this->_key = NULL;
	this->_map = NULL;
	this->_spec = NULL;
	this->_fruit = false;
	this->_special = 0;
	this->_winx = MAP_WIDTH;
	this->_winy = MAP_HEIGHT;
	this->_score = 0;
	this->_lib_name[0] = NULL;
	this->_lib_name[1] = NULL;
	this->_lib_name[2] = NULL;
	parse_option(d->ac, d->av);
	this->_posx = this->_winx / 2;
	this->_posy = this->_winy / 2;
	this->_eat = 0;
	this->_dir = 2;
	this->_speed = BASIC_SPEED;
	this->open_lib(this->_lib_name[0]);
	this->init_map();
	this->_graphic->init(d->ac, d->av, this->_winx, this->_winy, NULL, this->_map);
}

void	Event::open_lib( char *name ) {
	Api					*(*create)();

	this->_hndl = dlopen(name, RTLD_LAZY | RTLD_LOCAL);
	if (!this->_hndl) {
		std::cerr << "dlopen : "<< dlerror() << std::endl;
		throw std::exception();
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(this->_hndl, "newObject"))) == NULL) { 
		std::cerr << "dlsym : " << dlerror() << std::endl;
		throw std::exception();
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
}
