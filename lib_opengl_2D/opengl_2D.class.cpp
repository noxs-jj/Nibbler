// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   opengl_2D.class.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 15:41:13 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/16 15:41:14 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "opengl_2D.class.hpp"

//virtual void				init( int x, int y, char *name ) = 0; //construct

void				Graphic::close( void ) {}

std::vector<int>	*Graphic::get_touch_list( void ) {
	return (this->key_list);
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

void  		keyboard(unsigned char touche, int x, int y)
{
	(void)x;
	(void)y;
	if ( touche == 'q' || touche == 27 ) {
		;
	}
}

void				Graphic::render_scene( char **map ) { // render map
	int i = 0;
	int y = 0;

	this->draw_border();
	while (map[y] != '\0')
	{
		i = 0;
		while (map[i] != '\0')
		{
			if (map[i][0] == QUEUE)
				this->draw_queue(i, y);
			else if (map[i][0] == FRUIT)
				this->draw_fruit(i, y);
			else if (map[i][0] == HEAD)
				this->draw_head(i, y);
			i++;
		}
		y++;
	}
}

void	Graphic::draw_head( int case_x, int case_y ) { // draw on case of smake head
	glBegin(GL_QUADS);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	Graphic::draw_fruit( int case_x, int case_y ) { // draw on case of FRUIT
	glBegin(GL_QUADS);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	Graphic::draw_queue( int case_x, int case_y ) { // draw on case of snake queue
	glBegin(GL_QUADS);
		glColor3ub(QUEUE_R, QUEUE_G, QUEUE_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI); // RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	Graphic::draw_border( void ) { // color all map same color
	glBegin(GL_QUADS);
		glColor3ub(WALL_R, WALL_G, WALL_B);
		glVertex2f(0, 0);
		glVertex2f(0, this->winy);
		glVertex2f(this->winx, 0);
		glVertex2f(this->winx, this->winy);
	glEnd();
}

void	Graphic::init( int ac, char **av, int x, int y, char *title ) {
	glutInit(&ac, av);								// init glut
	glutInitDisplayMode(GLUT_RGB					// set color to RGB
				| GLUT_DOUBLE						// set double buffered windows
				| GLUT_DEPTH);						// Bit mask to select a window with a depth buffer.
	glutInitWindowSize(x * X_MULTI, x * Y_MULTI);	// Size of windows
	glutInitWindowPosition(STARTX, STARTY);   		// where the windos in create on Xserver/Desktop
	glutCreateWindow(title);						// Create windows with title in param char *
	glClearColor(0.5f, 0.5f, 0.5f, 1); 				//purple set background/void color
	glEnable(GL_DEPTH_TEST);
	glPointSize(POINT_SIZE);
	glLineWidth(LINE_WIDTH);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	glutSwapBuffers();
	glLoadIdentity();
	this->winx = x * X_MULTI;
	this->winy = x * Y_MULTI;
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

Graphic::Graphic( Graphic const & rhs ) {
	*this = rhs;
}

Graphic::Graphic( void ) : winx(0), winy(0), key_list(NULL), empty(true) {}	//construct

Graphic::~Graphic( void ) {	// destruct
	this->key_list->clear();
}
