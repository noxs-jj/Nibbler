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
		if (this->event.type == SDL_KEYDOWN)
		{
			switch((this->event).key.keysym.sym)
			{
				case SDLK_ESCAPE: this->addKey(ECHAP); break;
				case SDLK_q: this->addKey(ECHAP); break;
				case SDLK_DOWN: this->addKey(UP); break;
				case SDLK_s: this->addKey(UP); break;
				case SDLK_UP: this->addKey(DOWN); break;
				case SDLK_w: this->addKey(DOWN); break;
				case SDLK_RIGHT: this->addKey(RIGHT); break;
				case SDLK_d: this->addKey(RIGHT); break;
				case SDLK_LEFT: this->addKey(LEFT); break;
				case SDLK_a: this->addKey(LEFT); break;
				case SDLK_SPACE: this->addKey(SPACE); break;
				case SDLK_p: this->addKey(SPACE); break;
				case SDLK_1: this->addKey(ONE); break;
				case SDLK_2: this->addKey(TWO); break;
				case SDLK_3: this->addKey(THREE); break;

			}
		}
	}
}

void				Graphic::render_scene( void ) { // render map
		int x = 0;
		int y = 0;
		glClear(GL_COLOR_BUFFER_BIT);
		this->keyboard();
		this->keyboard();
		while (y < this->mapYsize)
		{
			x = 0;
			while(x < this->mapXsize)
			{
				if (WALL  == this->map[y][x])
					this->draw_wall(x, y);
				else if (QUEUE  == this->map[y][x])
					this->draw_queue(x, y);
				else if (HEAD == this->map[y][x])
					this->draw_head(x, y);
				else if (FRUIT == this->map[y][x])
					this->draw_fruit(x, y);
				else if (SPECIAL == this->map[y][x])
					this->draw_special(x, y);
				x++;
			}
			y++;
		}
		glFlush();
		SDL_GL_SwapWindow(this->window);
}

void				Graphic::init( int ac, char **av, int x, int y, char *title, char **map ) {
	float	scale = 0.1f;

	if (x > y)
		scale /= x;
	else
		scale /= y;
	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow(title,
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									x * X_MULTI, y * Y_MULTI,
									SDL_WINDOW_OPENGL |
									SDL_WINDOW_INPUT_GRABBED |
									SDL_WINDOW_SHOWN);
	this->opengl3_context = SDL_GL_CreateContext(this->window);
	glScalef(scale, scale, scale);
	glPointSize(POINT_SIZE);
	glLineWidth(LINE_WIDTH);
	(void)ac;
	(void)av;
	this->winx = x * X_MULTI;
	this->winy = y * Y_MULTI;
	this->mapXsize = x;
	this->mapYsize = y;
	this->map = map;
	this->key_list = new std::vector<int>;
}


void				Graphic::close( void ) {
	SDL_GL_DeleteContext(this->opengl3_context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void				Graphic::draw_head( float case_x, float case_y ) { // draw on case of smake head
	glBegin(GL_QUADS);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);			// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);			// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);						// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_special( float case_x, float case_y ) { // draw on case of FRUIT
	glBegin(GL_QUADS);
		glColor3ub(SPECIAL_R, SPECIAL_G, SPECIAL_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);			// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);			// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);						// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_fruit( float case_x, float case_y ) { // draw on case of FRUIT
	glBegin(GL_QUADS);
		glColor3ub(FRUIT_R, FRUIT_G, FRUIT_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);			// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);			// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);						// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_queue( float case_x, float case_y ) { // draw on case of snake queue
	glBegin(GL_QUADS);
		glColor3ub(QUEUE_R, QUEUE_G, QUEUE_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);			// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);			// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);						// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_wall( float case_x, float case_y ) { // draw on case of snake queue
	glBegin(GL_QUADS);
		glColor3ub(WALL_R, WALL_G, WALL_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);			// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI - Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);			// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);						// LEFT BOTTOM
	glEnd();
}

void				Graphic::addKey(int keyInput) {
	this->key_list->push_back(keyInput);
}

std::vector<int>	**Graphic::get_touch_list( void ) { return (&(this->key_list)); }

Graphic &	Graphic::operator=(Graphic const & rhs) {
	if (this != &rhs) {
		this->winx = rhs.winx;
		this->winy = rhs.winy;
		this->key_list = rhs.key_list;
	}
	return *this;
}

Graphic::Graphic( Graphic const & rhs ) {
	*this = rhs;
}

Graphic::Graphic( void ) : winx(0), winy(0), mapXsize(0), mapYsize(0),
	map(NULL), key_list(NULL), empty(true) { //construct
}

Graphic::~Graphic( void ) {	// destruct
	this->key_list->clear();
}
