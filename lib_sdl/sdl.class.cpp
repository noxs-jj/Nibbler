// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sdl.class.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/27 12:41:33 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/27 12:41:33 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "sdl.class.hpp"

extern "C"	Api		*newObject( void ) {
	return (new Graphic());
}

void  				Graphic::keyboard( void ) {
	while (SDL_PollEvent(&this->event)) {
		if (this->event.type == SDL_KEYDOWN) {
			switch((this->event).key.keysym.sym) {
				case SDLK_ESCAPE:	this->addKey(ECHAP); break;
				case SDLK_q:		this->addKey(ECHAP); break;
				case SDLK_DOWN:		this->addKey(DOWN); break;
				case SDLK_s:		this->addKey(DOWN); break;
				case SDLK_UP:		this->addKey(UP); break;
				case SDLK_w:		this->addKey(UP); break;
				case SDLK_RIGHT:	this->addKey(RIGHT); break;
				case SDLK_d:		this->addKey(RIGHT); break;
				case SDLK_LEFT:		this->addKey(LEFT); break;
				case SDLK_a:		this->addKey(LEFT); break;
				case SDLK_SPACE:	this->addKey(SPACE); break;
				case SDLK_p:		this->addKey(SPACE); break;
				case SDLK_1:		this->addKey(ONE); break;
				case SDLK_2:		this->addKey(TWO); break;
				case SDLK_3:		this->addKey(THREE); break;
				default: break;
			}
		}
	}
}

void				Graphic::render_scene( void ) { // render map
	int x = 0;
	int y = 0;

	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear( this->renderer );
	this->keyboard();
	this->keyboard();
	while (y < this->mapYsize) {
		x = 0;
		while (x < this->mapXsize) {
			switch (this->map[y][x]) {
				case WALL:		SDL_SetRenderDrawColor(this->renderer, WALL_R, WALL_G, WALL_B, 255); break;
				case QUEUE:		SDL_SetRenderDrawColor(this->renderer, QUEUE_R, QUEUE_G, QUEUE_B, 255); break;
				case HEAD:		SDL_SetRenderDrawColor(this->renderer, HEAD_R, HEAD_G, HEAD_B, 255); break;
				case FRUIT:		SDL_SetRenderDrawColor(this->renderer, FRUIT_R, FRUIT_G, FRUIT_B, 255); break;
				case SPECIAL:	SDL_SetRenderDrawColor(this->renderer, SPECIAL_R, SPECIAL_G, SPECIAL_B, 255); break;
				default:		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); break;
			}
			this->draw_spot(x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent( this->renderer );
}

void				Graphic::init( int ac, char **av, int x, int y, char *title, char **map ) {
	if ( -1 == SDL_Init(SDL_INIT_EVERYTHING) ) {
		std::cout << "Failed to initialize SDL : " << SDL_GetError();
		throw std::exception();
	}
	this->window = 		SDL_CreateWindow(title,
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										x * X_MULTI,
										y * Y_MULTI,
										SDL_WINDOW_OPENGL |
										SDL_WINDOW_INPUT_GRABBED |
										SDL_WINDOW_SHOWN);
	if ( NULL == this->window ) {
		std::cout << "Failed to create window : " << SDL_GetError();
		throw std::exception();
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if ( NULL == this->renderer ) {
		std::cout << "Failed to create renderer : " << SDL_GetError();
		throw std::exception();
	}
	SDL_RenderSetLogicalSize( this->renderer, x * X_MULTI, y * Y_MULTI );
	static_cast<void>(ac);
	static_cast<void>(av);
	this->winx = 		x * X_MULTI;
	this->winy = 		y * Y_MULTI;
	this->mapXsize = 	x;
	this->mapYsize = 	y;
	this->map = 		map;
	this->key_list = 	new std::vector<int>;
}

void				Graphic::close( void ) {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void				Graphic::draw_spot( float case_x, float case_y ) {
	SDL_Rect rectangle;

	rectangle.x = case_x * X_MULTI;
	rectangle.y = case_y * Y_MULTI;
	rectangle.w = X_MULTI;
	rectangle.h = Y_MULTI;
	SDL_RenderFillRect(this->renderer, &rectangle);
}

Graphic &			Graphic::operator=(Graphic const & rhs) {
	if (this != &rhs) {
		this->winx = rhs.winx;
		this->winy = rhs.winy;
		this->key_list = rhs.key_list;
	}
	return *this;
}

Graphic::Graphic( void ) : winx(0), winy(0), mapXsize(0), mapYsize(0),
							map(NULL), key_list(NULL), empty(true) {}

void				Graphic::addKey(int keyInput) { this->key_list->push_back(keyInput);}
std::vector<int>	**Graphic::get_touch_list( void ) { return (&(this->key_list)); }
Graphic::Graphic( Graphic const & rhs ) { *this = rhs; }
Graphic::~Graphic( void ) { this->key_list->clear(); }
