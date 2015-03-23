/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/23 17:25:15 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

lib_curse::lib_ncurse( int x, int y, std::string name ) :	_window(NULL),
															_speed(TIME_USLEEP),
															_x(x),
															_y(y),
															_key(NULL) {}

lib_curse::lib_ncurse( lib_ncurse const & src ) {
	*this = src;
}

lib_curse & lib_ncurse::operator=( lib_ncurse const & rhs ) {
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

lib_curse::~lib_ncurse( void ) {}


lib_curse::init( void ) {
	initscr();
	start_color();
	init_pair(10, COLOR_WHITE, COLOR_BLACK);	// wall
	init_pair(1, COLOR_GREEN, COLOR_BLACK);		// snake
	init_pair(11, COLOR_YELLOW, COLOR_BLACK);	// fruit
	this->window = newwin(y, x, 0, 0);
	if (this->window == NULL)
		throw std::execption;
	wbkgd(this->window, COLOR_PAIR(0));
	cbreak();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	wrefresh(this->window);
}

lib_curse::close( void ) {
	refresh();
	wrefresh(this->window);
	delwin(this->window);
	endwin();
}

void lib_curse::render_scene( char **map ) {
	
}

std::vector<int> lib_curse::get_touch_list( void ) {
	int				key_input[3];

	wtimeout(this->window, 1);
	key_input[0] = wgetch(this->window);
	if (key_input[0] == 27 && (key_input[1] = wgetch(this->window)) == 91 &&
		(key_input[2] = wgetch(this->window)) == 65)	// UP
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


std::string			getName( void ) { return (this->_name);}

WINDOW				*getWindow( void ) { return (this->_window);}

int					getSpeed( void ) { return (this->_speed);}

int					getX( void ) { return (this->_x);}

int					getY( void ) { return (this->_y);}

std::vector<int>	getKey( void ) { return (this->_key);}
