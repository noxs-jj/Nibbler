/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:21:21 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/24 18:23:39 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_HPP
# define GRAPHIC_HPP

# include "../includes/api.class.hpp"
# include <ncurses.h>

# define TIME_USLEEP 1000	// test value

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

// Api					*newObject( void );

class Graphic : public Api{
private:
	WINDOW				*_window;
	int					_speed;
	int					_x;
	int					_y;
	char				*_name;
	std::vector<int> 	*_key;
	
public:
	Graphic( void );
	Graphic( Graphic const & src );
	Graphic & operator=( Graphic const & rhs );
	~Graphic( void );

	char				*getName( void ) const;
	WINDOW				*getWindow( void ) const;
	int					getSpeed( void ) const;
	int					getX( void ) const;
	int					getY( void ) const;
	std::vector<int>	*getKey( void ) const;
	void				keyboard( void );

	void				init( int ac, char** av, int x, int y, char *title );
	void				close( void );
	void				render_scene( char **map );
	std::vector<int>	*get_touch_list( void );

	// void				delObject( Api *del );
	// void				echo( void );
protected:

};


#endif