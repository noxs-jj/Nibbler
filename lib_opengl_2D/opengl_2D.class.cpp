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

Graphic	*g_currentInstance;

// START #############################################
extern "C" void		drawCallback() { // glutDisplayFunc(drawCallback)
	g_currentInstance->show_scene();
}

void				Graphic::render_scene( void ) { // from main graphic->rander_scene
	this->show_scene();
}

void				Graphic::setCurrentInstance( void ) {
	g_currentInstance = this;
}
// END ###############################################

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

void  				keyboard(unsigned char touche, int x, int y)
{
	(void)x;
	(void)y;
	if ( touche == 'q' || touche == 27 ) {
		;
	}
}

void				Graphic::show_scene( void ) { // render map
	std::cout << "Debugg 1.1" << std::endl;
	int i = 0;
	int y = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	this->draw_border();
	while (y < this->mapYsize)
	{
		i = 0;
		std::cout << "Debugg 1.2" << std::endl;
		while (i < this->mapXsize)
		{
			std::cout << "Debugg 1.3" << std::endl;
			if (this->map[i][0] == QUEUE)
				this->draw_queue(i, y);
			else if (this->map[i][0] == FRUIT)
				this->draw_fruit(i, y);
			else if (this->map[i][0] == HEAD)
				this->draw_head(i, y);
			i++;
		}
		y++;
	}
	std::cout << "Debugg 1.9" << std::endl;
	glFlush();
	glLoadIdentity();
	glutSwapBuffers();
	while(42)
		;
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

void	Graphic::init( int ac, char **av, int x, int y, char *title, char **map ) {
	std::cout << "Debugg 2" << std::endl;
	glutInit(&ac, av);								// init glut
	glutInitDisplayMode(GLUT_RGB					// set color to RGB
				| GLUT_DOUBLE						// set double buffered windows
				| GLUT_DEPTH);						// Bit mask to select a window with a depth buffer.
	glutInitWindowSize(x * X_MULTI, y * Y_MULTI);	// Size of windows
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
	this->winy = y * Y_MULTI;
	this->mapXsize = x;
	this->mapYsize = y;
	this->map = map;
	//glutKeyboardFunc(keyboard);					// function for keyboard event
	this->setCurrentInstance(); // assign this object to global ptr
	glutDisplayFunc(drawCallback);
	//glutTimerFunc(0, timer, 0);
	glutMainLoop();
	std::cout << "Debugg 2.1" << std::endl;
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

Graphic::Graphic( void ) : winx(0), winy(0), mapXsize(0), mapYsize(0),
map(NULL), key_list(NULL), empty(true) {
	std::cout << "Debugg -1" << std::endl;
}	//construct

Graphic::~Graphic( void ) {	// destruct
	this->key_list->clear();
}
