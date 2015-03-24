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

void				opengl_2D::close( void ) {}

std::vector<int>	opengl_2D::get_touch_list( void ) {}

void				opengl_2D::render_scene( char **map ) { // render map
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
			else if (map[i][0] == RUIT)
				this->draw_fruit(i, y);
			else if (map[i][0] == HEAD)
				this->draw_head(i, y);
			i++;
		}
		y++;
	}
}

void	opengl_2D::draw_head( int case_x, int case_y ) { // draw on case of smake head
	glBegin(GL_QUAD);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	opengl_2D::draw_fruit( int case_x, int case_y ) { // draw on case of FRUIT
	glBegin(GL_QUAD);
		glColor3ub(HEAD_R, HEAD_G, HEAD_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI);	// RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	opengl_2D::draw_queue( int case_x, int case_y ) { // draw on case of snake queue
	glBegin(GL_QUAD);
		glColor3ub(QUEUE_R, QUEUE_G, QUEUE_B);
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI);						// LEFT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI);			// RIGHT TOP
		glVertex2f(case_x * X_MULTI + X_MULTI, case_y * Y_MULTI + Y_MULTI); // RIGHT BOTTOM
		glVertex2f(case_x * X_MULTI, case_y * Y_MULTI + Y_MULTI);			// LEFT BOTTOM
	glEnd();
}

void	opengl_2D::draw_border( void ) { // color all map same color
	glBegin(GL_QUAD);
		glColor3ub(WALL_R, WALL_G, WALL_B);
		glVertex2f(0, 0);
		glVertex2f(0, this->winy);
		glVertex2f(this->winx, 0);
		glVertex2f(this->x, this->y);
	glEnd();
}

void	opengl_2D::init( int ac, char **av, int x, int y, char *title ) {
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
	this->wuny = x * Y_MULTI;
}

opengl_2D & opengl_2D::operator=(opengl_2D const & rhs) {
	if (this != &rhs)
	{
		this->mlx = rhs.mlx;
	}
	return *this;
}

void	opengl_2D::opengl_2D( opengl_2D const & src ) {
	*this = src;
}

opengl_2D::opengl_2D( void ) {}	//construct

opengl_2D::~opengl_2D( void ) {	// destruct
	std::free(this->img_data);
}
