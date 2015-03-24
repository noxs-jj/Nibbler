/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/24 16:07:01 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ncurse.class.hpp"

Graphic::Graphic( void ) :	_window(NULL),
							_speed(TIME_USLEEP) {}

Graphic::Graphic( Graphic const & src ) {
	*this = src;
}

Graphic & Graphic::operator=( Graphic const & rhs ) {
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_window = rhs.getWindow();
		this->_speed = rhs.getSpeed();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_key = rhs.getKey();
	}
	return (*this);
}

Graphic::~Graphic( void ) {}

void	Graphic::init( int ac, char** av, int x, int y, char *title ) {
	std::cout << "test" << std::endl;
	this->_x = x;
	this->_y = y;
	this->_name = title;
	static_cast<void>(ac);
	static_cast<void>(av);
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		// wall
	init_pair(2, COLOR_GREEN, COLOR_BLACK);		// snake
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// fruit
	this->_window = newwin(this->_y, this->_x, 0, 0);
	if (this->_window == NULL)
		throw std::exception();
	wbkgd(this->_window, COLOR_PAIR(0));
	cbreak();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	wrefresh(this->_window);
}

void	Graphic::close( void ) {
	refresh();
	wrefresh(this->_window);
	delwin(this->_window);
	endwin();
}

void	Graphic::keyboard( void ) {
	int				key_input[3];

	wtimeout(this->_window, 1);
	key_input[0] = wgetch(this->_window);
	if (key_input[0] == 27 && (key_input[1] = wgetch(this->_window)) == 91 &&
		(key_input[2] = wgetch(this->_window)) == 65)	// UP
		this->_key.push_back(65);
	else if (key_input[0] == 27 && key_input[1] == 91 && key_input[2] == 66)
		this->_key.push_back(66);	//DOWN
	else if (key_input[0] == 27 && key_input[1] == 91 && key_input[2] == 68)
		this->_key.push_back(68);	//LEFT
	else if (key_input[0] == 27 && key_input[1] == 91 && key_input[2] == 67)
		this->_key.push_back(67);	//RIGHT
	if (key_input[0] == 27 && key_input[1] == -1)
		this->_key.push_back(27);	//ECHAP
}

void	Graphic::render_scene( char **map ) {
	int	x;
	int	y;
	int	state = 1;

	std::cout << "1111" << std::endl;
	keyboard();	// maybe put keyboard in the for ?
	std::cout << "22222" << std::endl;
	wattron(this->_window, COLOR_PAIR(1));
	for (y = 0; y < this->_y; y++)
	{
		for (x = 0; x < this->_x; x++)
		{
			if (state != 1 && map[this->_y][this->_x] == WALL)
			{
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(1));
				state = 1;
			}
			else if (state != 2 && map[this->_y][this->_x] == FRUIT)
			{
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(2));
				state = 2;
			}
			else if (state != 3 && (map[this->_y][this->_x] == QUEUE || map[this->_y][this->_x] == HEAD))
			{
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(2));
				state = 2;
			}
			mvwprintw(this->_window, y, x, "%c", map[this->_y][this->_x]);
		}
	}
}

std::vector<int> Graphic::get_touch_list( void ) { return (this->_key); }

char				*Graphic::getName( void ) const { return (this->_name); }

WINDOW				*Graphic::getWindow( void ) const { return (this->_window); }

int					Graphic::getSpeed( void ) const { return (this->_speed); }

int					Graphic::getX( void ) const { return (this->_x); }

int					Graphic::getY( void ) const { return (this->_y); }

std::vector<int>	Graphic::getKey( void ) const { return (this->_key); }

// void				Graphic::delObject( Api *del)
// {
// 	delete reinterpret_cast<Graphic*>(del);
// }

// void		Graphic::echo( void )
// {
// 	std::cout << "hey " << std::endl;
// }

extern "C"	Api				*newObject( void )
{
	return (new Graphic());
}





