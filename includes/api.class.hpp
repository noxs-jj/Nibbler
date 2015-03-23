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

class	api
{
	public:
		virtual void				init( int x, int y, std::string name ) = 0; //construct
		virtual void				close( void ) = 0; //destruct
		virtual void				render_scene( char **map ) = 0;
		virtual std::vector<int>	get_touch_list( void ) = 0;
};
