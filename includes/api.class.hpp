// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   api.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/23 16:00:39 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/23 16:00:40 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef API_CLASS_HPP
# define API_CLASS_HPP

# include <stdexcept>
# include <vector>
# include <string>
# include <iostream>
# include <strings.h>

class	api
{
	public:
		// virtual void				init( int x, int y, char *name ) = 0; //construct
		virtual void				init( void ) = 0; //construct
		virtual void				close( void ) = 0; //destruct
		virtual void				render_scene( char **map ) = 0;
		virtual std::vector<int>	get_touch_list( void ) = 0;
		///////////////////// cette version pour OpenGL
		virtual void	init( int ac, char** av, int x, int y, char *title ) = 0;
		virtual void	close( void ) = 0;
		virtual void	render_scene( char **map ) = 0;
		virtual std::vector<int>	get_touch_list( void ) = 0;
};

#endif
