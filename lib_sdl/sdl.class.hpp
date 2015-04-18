// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sdl.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/27 12:41:44 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/27 12:41:45 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SDL_CLASS_HPP
# define SDL_CLASS_HPP
# include "../includes/api.class.hpp"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <string>
# include <SDL.h>
# include <openGL/gl.h>
# include <openGL/glu.h>

# define STARTX		100
# define STARTY		100
# define X_MULTI	10.0f		//(x * 10) * number case width
# define Y_MULTI	10.0f		//(y * 10) * number case height
# define LINE_WIDTH	1.0f
# define POINT_SIZE	2.0f
# define SCALE_GL	0.01f

# define WALL_R		255
# define WALL_G		255
# define WALL_B		255

# define QUEUE_R	0
# define QUEUE_G	255
# define QUEUE_B	0

# define HEAD_R		255
# define HEAD_G		0
# define HEAD_B		0

# define FRUIT_R	0
# define FRUIT_G	0
# define FRUIT_B	255

# define SPECIAL_R	255
# define SPECIAL_G	255
# define SPECIAL_B	0

class 					Api;

class	Graphic : public Api {
public:
	int					winx;
	int					winy;
	int 				mapXsize;
	int 				mapYsize;
	char **				map;
	std::vector<int> *	key_list;
	bool				empty;
	bool				run;
	SDL_Event 			event;
	SDL_Window *		window;
	SDL_Renderer *		renderer;

	Graphic( void );
	virtual ~Graphic( void );

	void				addKey(int keyInput);
	void				init( int ac, char** av, int x, int y, char *title, char **map );
	void				close( void );
	void				render_scene( void );
	void				show_scene( void );
	std::vector<int>	**get_touch_list( void );
	void  				keyboard( void );
	void				draw_spot( float case_x, float case_y );

private:
	Graphic	& 			operator=( Graphic const & rhs );
	Graphic( Graphic const & rhs );
};

#endif