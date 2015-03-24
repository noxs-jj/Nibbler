// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   opengl_2D.class.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/24 10:09:47 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/24 10:09:50 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../includes/api.class.hpp"

#ifndef OPENGL_2D_CLASS_HPP
# define OPENGL_2D_CLASS_HPP

# define STARTX		100
# define STARTY		10
# define X_MULTI	15		//(x * 15) * number case width
# define Y_MULTI	15		//(y * 15) * number case height
# define LINE_WIDTH	2.0f
# define POINT_SIZE	3.0f

# define WALL_R		200
# define WALL_G		250
# define WALL_B		230

# define QUEUE_R	14
# define QUEUE_G	24
# define QUEUE_B	34

# define HEAD_R		120
# define HEAD_G		163
# define HEAD_B		110

//OpenGL
# ifdef linux //sudo apt-get install freeglut3 freeglut3-dev
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <GL/glut.h>
# endif
# ifdef __APPLE__
#	include <openGL/gl.h>
#	include <openGL/glu.h>
#	include <glut/glut.h>
# endif
# ifdef __WIN32__
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <windows.h>
# endif

class 	Api;

void  	keyboard(unsigned char touche, int x, int y);

class	Graphic : public Api {
public:
	int					winx;
	int					winy;
	std::vector<int>	*key_list;
	bool				empty;

	void				addKey(int keyInput);

	Graphic( void );
	~Graphic( void );
	void				init( int ac, char** av, int x, int y, char *title );
	void				close( void );
	void				render_scene( char **map );
	std::vector<int>	*get_touch_list( void );

private:
	Graphic	& 			operator=( Graphic const & rhs );
	Graphic( Graphic const & rhs );
	void				draw_border( void );
	void				draw_queue( int case_x, int case_y );
	void				draw_head( int case_x, int case_y );
	void				draw_fruit( int case_x, int case_y );
};

#endif
