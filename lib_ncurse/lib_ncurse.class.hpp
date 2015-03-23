/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:21:21 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/23 19:19:35 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_NCURSE_HPP
# define LIB_NCURSE_HPP

# include "../includes/api.class.hpp"
# include <ncurses.h>

# define TIME_USLEEP 1000	// test value

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class Lib_ncurse {
private:
	WINDOW				*_window;
	int					_speed;
	int					_x;
	int					_y;
	char				*_name;
	std::vector<int> 	_key;
	Lib_ncurse( void );
public:
	Lib_ncurse( int x, int y, char *name );
	Lib_ncurse( Lib_ncurse const & src );
	Lib_ncurse & operator=( Lib_ncurse const & rhs );
	~Lib_ncurse( void );

	char				*getName( void ) const;
	WINDOW				*getWindow( void ) const;
	int					getSpeed( void ) const;
	int					getX( void ) const;
	int					getY( void ) const;
	std::vector<int>	getKey( void ) const;
	void				keyboard( void );

	void				init( void );
	void				close( void );
	void				render_scene( char **map );
	std::vector<int>	get_touch_list( void );

protected:

};

#endif