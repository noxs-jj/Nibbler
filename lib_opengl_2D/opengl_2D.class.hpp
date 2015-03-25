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



#ifndef OPENGL_2D_CLASS_HPP
# define OPENGL_2D_CLASS_HPP

# include "../includes/api.class.hpp"
# include <time.h>
# include <unistd.h>

# define STARTX		100
# define STARTY		100
# define X_MULTI	20.0f		//(x * 15) * number case width
# define Y_MULTI	20.0f		//(y * 15) * number case height
# define LINE_WIDTH	1.0f
# define POINT_SIZE	1.0f
# define SCALE_GL	0.01f

# define WALL_R		13
# define WALL_G		13
# define WALL_B		13

# define QUEUE_R	255
# define QUEUE_G	0
# define QUEUE_B	0

# define HEAD_R		0
# define HEAD_G		0
# define HEAD_B		255

# define FRUIT_R	0
# define FRUIT_G	255
# define FRUIT_B	0

# ifdef linux //sudo apt-get install freeglut3 freeglut3-dev
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <GL/glut.h>
# endif
# ifdef __APPLE__
#	include <openGL/gl.h>
#	include <openGL/glu.h>
#	include <glut/glut.h>
//#	include "openglut.h"
# endif
# ifdef __WIN32__
#	include <GL/gl.h>
#	include <GL/glu.h>
#	include <windows.h>
# endif

class 					Api;

void  					keyboard(unsigned char touche, int x, int y);
void					drawCallback();
void					callAddKey(int keyInput);

class	Graphic : public Api {
public:
	int					winx;
	int					winy;
	int 				mapXsize;
	int 				mapYsize;
	char				**map;
	std::vector<int>	*key_list;
	bool				empty;

	void				addKey(int keyInput);

	Graphic( void );
	~Graphic( void );
	void				init( int ac, char** av, int x, int y, char *title, char **map );
	void				close( void );
	void				render_scene( void );
	void				show_scene( void );
	std::vector<int>	**get_touch_list( void );


	Graphic	& 			operator=( Graphic const & rhs );
	Graphic( Graphic const & rhs );

	void				draw_border( void );
	void				draw_queue( float case_x, float case_y );
	void				draw_head( float case_x, float case_y );
	void				draw_fruit( float case_x, float case_y );
	void				setCurrentInstance( void );

private:

};

#endif
