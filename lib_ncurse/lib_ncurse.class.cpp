/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/04 19:09:08 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_ncurse.class.hpp"

extern "C"	Api		*newObject( void ) {
	return (new Graphic());
}

Graphic::Graphic( void ) :	_window(NULL),
							_key(NULL) {}

Graphic::Graphic( Graphic const & src ) {
	*this = src;
}

Graphic & Graphic::operator=( Graphic const & rhs ) {
	if (this != &rhs) {
		this->_name = rhs.getName();
		this->_window = rhs.getWindow();
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_key = rhs.getKey();
		this->_map = rhs.getMap();
	}
	return (*this);
}

Graphic::~Graphic( void ) {}

void	Graphic::init( int ac, char** av, int x, int y, char *title, char **map ) {
	this->_x = x;
	this->_y = y;
	this->_name = title;
	this->_map = map;
	this->_key = new std::vector<int>;
	static_cast<void>(ac);
	static_cast<void>(av);
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		// wall
	init_pair(2, COLOR_GREEN, COLOR_BLACK);		// snake
	init_pair(3, COLOR_CYAN, COLOR_BLACK);		// fruit
	init_pair(4, COLOR_RED, COLOR_BLACK);		// special
	this->_window = newwin(this->_y, this->_x, 0, 0);
	if (this->_window == NULL)
		throw std::exception();
	wbkgd(this->_window, COLOR_PAIR(0));
	cbreak();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	keypad(this->_window, true);
	wrefresh(this->_window);
}

void	Graphic::close( void ) {
	refresh();
	wrefresh(this->_window);
	delwin(this->_window);
	endwin();
}

void	Graphic::keyboard( void ) {
	int			key;
	int			touch = 1;

	wtimeout(this->_window, 1);
	while (touch == 1) {
		key = wgetch(this->_window);
		switch(key) {
			case KEY_DOWN: this->_key->push_back(DOWN) ; break;
			case 's': this->_key->push_back(DOWN); break;
			case KEY_UP: this->_key->push_back(UP); break;
			case 'w': this->_key->push_back(UP); break;
			case KEY_LEFT: this->_key->push_back(LEFT); break;
			case 'a': this->_key->push_back(LEFT); break;
			case KEY_RIGHT: this->_key->push_back(RIGHT); break;
			case 'd': this->_key->push_back(RIGHT); break;
			case 27: this->_key->push_back(27); break;
			case ONE: this->_key->push_back(ONE); break;
			case TWO: this->_key->push_back(TWO); break;
			case THREE: this->_key->push_back(THREE); break;
			case SPACE: this->_key->push_back(SPACE); break;
			default: break;
		}
		break ;
	}
}

void	Graphic::render_scene( void ) {
	int	x;
	int	y;
	int	state = 1;

	keyboard();
	werase(this->_window);
	wattron(this->_window, COLOR_PAIR(1));
	for (y = 0; y < this->_y; y++) {
		for (x = 0; x < this->_x; x++) {
			if (state != 1 && this->_map[y][x] == WALL) {
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(1));
				state = 1;
			}
			else if (state != 3 && this->_map[y][x] == FRUIT) {
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(3));
				state = 3;
			}
			else if (state != 2 && (this->_map[y][x] == QUEUE || this->_map[y][x] == HEAD)) {
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(2));
				state = 2;
			}
			else if (state != 4 && this->_map[y][x] == SPECIAL){
				wattroff(this->_window, COLOR_PAIR(state));
				wattron(this->_window, COLOR_PAIR(4));
				state = 4;
			}
			mvwprintw(this->_window, y, x, "%c", this->_map[y][x]);
		}
	}
	wrefresh(this->_window);
}

std::vector<int> **Graphic::get_touch_list( void ) { return (&this->_key); }

char				*Graphic::getName( void ) const { return (this->_name); }

WINDOW				*Graphic::getWindow( void ) const { return (this->_window); }

int					Graphic::getX( void ) const { return (this->_x); }

int					Graphic::getY( void ) const { return (this->_y); }

std::vector<int>	*Graphic::getKey( void ) const {return (this->_key); }

char				**Graphic::getMap( void ) const {return (this->_map); }
