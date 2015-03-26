// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   opengl_sdl_2D.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/26 10:58:51 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/26 10:58:52 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "opengl_2D.class.hpp"

// START #############################################
Graphic	*g_currentInstance;

void				drawCallback() { // glutDisplayFunc(drawCallback)
	g_currentInstance->show_scene();
}

void				callAddKey(int keyInput) {
	g_currentInstance->addKey(keyInput);
}

void				Graphic::render_scene( void ) { // from main graphic->rander_scene
	this->show_scene();
}

void				Graphic::setCurrentInstance( void ) {
	g_currentInstance = this;
}
// END ###############################################

void  				keyboard(unsigned char touche, int x, int y)
{
	(void)x;
	(void)y;
	if ( touche == 'q' || touche == 27 )
		exit(0);
	else if (touche == 'a')
	{
		std::cout << "LEFT: " << touche << std::endl;
		callAddKey(68);
	}
	else if (touche == 'd')
	{
		std::cout << "RIGHT: " << touche << std::endl;
		callAddKey(67);
	}
	else if (touche == 'w')
	{
		std::cout << "UP: " << touche << std::endl;
		callAddKey(65);
	}
	else if (touche == 's')
	{
		std::cout << "DOWN: " << touche << std::endl;
		callAddKey(66);
	}
	else
	{
		std::cout << "touche: " << touche << std::endl;
	}
}

void				Graphic::show_scene( void ) { // render map
	int x = 0;
	int y = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScalef(SCALE_GL, SCALE_GL, SCALE_GL);

	draw_border();
	while (y < this->mapYsize)
	{
		x = 0;
		while(x < this->mapXsize)
		{
			if (QUEUE  == this->map[y][x])
				draw_queue(x, y);
			if (HEAD == this->map[y][x])
				draw_head(x, y);
			else if (FRUIT == this->map[y][x])
				draw_fruit(x, y);
			x++;
		}
		y++;
	}
	glFlush();
	glLoadIdentity();
	std::cout << "show_scene" << std::endl;
	while (42)
		;
	//glutLeaveMainLoop ();
	//usleep(3000000);
}

void				Graphic::init( int ac, char **av, int x, int y, char *title, char **map ) {
	this->setCurrentInstance();
	this->winx = x * X_MULTI;
	this->winy = y * Y_MULTI;
	this->mapXsize = x;
	this->mapYsize = y;
	this->map = map;
	//###############################
	// int i = 0;
	// y = 0;
	// while (y < 10)
	// {
	// 	i = 0;
	// 	while (i < 10)
	// 	{
	// 		std::cout << map[y][i];
	// 		i++;
	// 	}
	// 	std::cout << std::endl;
	// 	y++;
	// }
	// std::cout << std::endl;
	//###############################
	if (SDL_init( SDL_INIT_VIDEO ) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: SDL_init" << std::endl;
		throw std::exception();
	}
	else {
		this->window = SDL_CreateWindow( static_cast<const char *>(title),
										STARTX, STARTY,
										x * X_MULTI, y * Y_MULTI,
										SDL_WINDOW_SHOWN );
		if ( NULL == this->window ) {
			std::cerr << "Window could not be created! SDL_Error: SDL_CreateWindow" << std::endl;
		}
		// Get windows surface
		this->screenSurface = SDL_GetWindowSurface( this->window );

		// fill surface white
		SDL_FillRect( this->screenSurface, NULL,
			SDL_MapRGB( this->screenSurface->format, 0xFF, 0xFF, 0xFF ) );

		// update surface
		SDL_UpdateWindowSurface ( this->window );
	}

}

void				Graphic::draw_head( float case_x, float case_y ) { // draw on case of smake head
	glBegin(GL_QUADS);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// LEFT BOTTOM
	glEnd();
}


void				Graphic::draw_fruit( float case_x, float case_y ) { // draw on case of FRUIT
	glBegin(GL_QUADS);
		glColor3ub(FRUIT_R, FRUIT_G, FRUIT_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_queue( float case_x, float case_y ) { // draw on case of snake queue
	glBegin(GL_QUADS);
		glColor3ub(QUEUE_R, QUEUE_G, QUEUE_B);
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// LEFT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI + Y_MULTI);	// RIGHT TOP
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI + X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(-(this->winx / 2) + case_x * X_MULTI, -(this->winy / 2) + case_y * Y_MULTI);	// LEFT BOTTOM
	glEnd();
}

void				Graphic::draw_border( void ) { // color all map same color
	glBegin(GL_QUADS);
		glColor3ub(WALL_R, WALL_G, WALL_B);
		glVertex2i(-1, 1);	// LEFT TOP
		glVertex2i(1, 1);	// RIGHT TOP
		glVertex2i(1, -1);	// RIGHT BOTTOM
		glVertex2i(-1, -1);	// LEFT BOTTOM
	glEnd();
}

void				Graphic::addKey(int keyInput) {
	if (true == empty)
	{
		this->key_list = new std::vector<int>;
		this->key_list->push_back(keyInput);
		this->empty = false;
	}
	else
		this->key_list->push_back(keyInput);
}

std::vector<int>	**Graphic::get_touch_list( void ) { // get list key
	return (&(this->key_list));
}

Graphic &	Graphic::operator=(Graphic const & rhs) {
	if (this != &rhs)
	{
		this->winx = rhs.winx;
		this->winy = rhs.winy;
		this->key_list = rhs.key_list;
	}
	return *this;
}

void				Graphic::close( void ) {
	//Destroy window
    SDL_DestroyWindow( this->window );

    //Quit SDL subsystems
    SDL_Quit();
}

Graphic::Graphic( Graphic const & rhs ) {
	*this = rhs;
}

Graphic::Graphic( void ) : winx(0), winy(0), mapXsize(0), mapYsize(0),
map(NULL), key_list(NULL), empty(true), window(NULL), screenSurface(NULL) { //construct
}

Graphic::~Graphic( void ) {	// destruct
	this->key_list->clear();
}
