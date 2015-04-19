/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_sfml.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 15:07:24 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/04 19:13:00 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_sfml.class.hpp"

extern "C"	Api		*newObject( void ) {
	return (new Graphic());
}

Graphic::Graphic( void ) :	_key(NULL) {}

Graphic::Graphic( Graphic const & src ) { *this = src; }

Graphic & Graphic::operator=( Graphic const & rhs ) {
	if (this != &rhs){
		this->_name =		rhs.getName();
		this->_window =		rhs.getWindow();
		this->_x =			rhs.getX();
		this->_y =			rhs.getY();
		this->_key =		rhs.getKey();
		this->_map =		rhs.getMap();
	}
	return (*this);
}

Graphic::~Graphic( void ) {}

void	Graphic::init( int ac, char** av, int x, int y, char *title, char **map ) {
	sf::ContextSettings settings;

	this->_x =						x;
	this->_y =						y;
	this->_name =					title;
	this->_map =					map;
	this->_key =					new std::vector<int>;
	static_cast<void>(ac);
	static_cast<void>(av);
	settings.antialiasingLevel =	8;
	this->_event = 					new sf::Event();
	sf::VideoMode 					desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i					pos((desktop.width / 2) - ((x * 10) / 2),
										(desktop.height / 2) - ((y * 10) / 2));


	// BUG A CHERCHE
	std::cerr << "sfml 1" << std::endl;
	try {
		this->_window = new sf::RenderWindow(
									sf::VideoMode(y * 10, x * 10, 32),
									title,
									sf::Style::Default,
									settings);
		this->_window->setPosition(pos);
	}
	catch (std::exception & e) {
		std::cerr << "SFML EXCEPTION --] " << e.what() << std::endl;
	}
	std::cerr << "sfml 2" << std::endl;
	// BUG A CHERCHE



	this->_queue = new sf::CircleShape(5.f);
	this->_queue->setFillColor(sf::Color::Green);
	this->_head = new sf::CircleShape(5.f);
	this->_head->setFillColor(sf::Color::Red);
	this->_fruit = new sf::CircleShape(5.f, 4);
	this->_fruit->setFillColor(sf::Color::Cyan);
	this->_special = new sf::CircleShape(5.f, 4);
	this->_special->setFillColor(sf::Color::Yellow);
	this->_wall = new sf::CircleShape(5.f);
	this->_wall->setFillColor(sf::Color::Green);
}

void	Graphic::close( void ) {
	delete this->_queue;
	delete this->_head;
	delete this->_fruit;
	delete this->_special;
	delete this->_wall;
	delete this->_event;
	delete this->_window;
}

void	Graphic::keyboard( void ) {
	while (this->_window->pollEvent(*this->_event)) {
		if (this->_event->type == sf::Event::KeyPressed) {
			switch (this->_event->key.code) {
				case sf::Keyboard::Left:	this->_key->push_back(LEFT); break;
				case sf::Keyboard::A:		this->_key->push_back(LEFT); break;
				case sf::Keyboard::Right:	this->_key->push_back(RIGHT); break;
				case sf::Keyboard::D:		this->_key->push_back(RIGHT); break;
				case sf::Keyboard::Up:		this->_key->push_back(UP); break;
				case sf::Keyboard::W:		this->_key->push_back(UP); break;
				case sf::Keyboard::Down:	this->_key->push_back(DOWN); break;
				case sf::Keyboard::S:		this->_key->push_back(DOWN); break;
				case sf::Keyboard::Escape:	this->_key->push_back(ECHAP); break;
				case sf::Keyboard::Q:		this->_key->push_back(ECHAP); break;
				case sf::Keyboard::Space: 	this->_key->push_back(SPACE); break;
				case sf::Keyboard::P:		this->_key->push_back(SPACE); break;
				case sf::Keyboard::Num1:	this->_key->push_back(ONE); break;
				case sf::Keyboard::Num2:	this->_key->push_back(TWO); break;
				case sf::Keyboard::Num3:	this->_key->push_back(THREE); break;
				default: break;
			}
		}
	}
}

void	Graphic::render_scene( void ) {
	keyboard();
	this->_window->clear(sf::Color::Black);
	for (int y = 0; y < this->_y; ++y) {
		for (int x = 0; x < this->_x; ++x) {
			switch (this->_map[y][x]) {
				case WALL: {
					this->_wall->setPosition(x * 10.f, y * 10.f);
					this->_window->draw(*this->_wall);
				} break;

				case HEAD: {
					this->_head->setPosition(x * 10.f, y * 10.f);
					this->_window->draw(*this->_head);
				} break;

				case QUEUE: {
					this->_queue->setPosition(x * 10.f, y * 10.f);
					this->_window->draw(*this->_queue);
				} break;

				case FRUIT: {
					this->_fruit->setPosition(x * 10.f, y * 10.f);
					this->_window->draw(*this->_fruit);
				} break;

				case SPECIAL: {
					this->_special->setPosition(x * 10.f, y * 10.f);
					this->_window->draw(*this->_special);
				} break;

				default: break;
			}
		}
	}
	this->_window->display();
	keyboard();
}

std::vector<int>	**Graphic::get_touch_list( void ) { return (&this->_key); }

char				*Graphic::getName( void ) const { return (this->_name); }

sf::RenderWindow	*Graphic::getWindow( void ) const { return (this->_window); }

int					Graphic::getX( void ) const { return (this->_x); }

int					Graphic::getY( void ) const { return (this->_y); }

std::vector<int>	*Graphic::getKey( void ) const {return (this->_key); }

char				**Graphic::getMap( void ) const {return (this->_map); }
