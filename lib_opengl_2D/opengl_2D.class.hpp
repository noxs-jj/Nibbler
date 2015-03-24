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

#ifndef API_CLASS_HPP
# define API_CLASS_HPP

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

class 	api;

class	opengl_2D : public api
{
public:
	int					winx;
	int					winy;
	std::vector<int>	key_list;

	opengl_2D( void );
	~opengl_2D( void );

private:
	opengl_2D	& operator=( opengl_2D const & rhs );
	opengl_2D( opengl_2D const & src );
	void		draw_border( void );
	void		draw_queue( int case_x, int case_y );
	void		draw_head( int case_x, int case_y );
};

#endif
