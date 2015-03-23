/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ncurse.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:21:21 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/23 17:18:11 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_NCURSE_HPP
# define LIB_NCURSE_HPP

# include "../includes/api.class.hpp"
# include <ncurses.h>
# include <execption>

# define TIME_USLEEP 1000	// test value

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class lib_ncurse.class {
private:
	WINDOW				*_window;
	int					_speed;
	int					_x;
	int					_y;
	const std::string	_name;
	std::vector<int> 	_key;

public:
	lib_ncurse( void );
	lib_ncurse( lib_ncurse const & src );
	lib_ncurse & operator=( lib_ncurse const & rhs );
	~lib_ncurse( void );

	std::string			getName( void );
	WINDOW				*getWindow( void );
	int					getSpeed( void );
	int					getX( void );
	int					getY( void );
	std::vector<int>	getKey( void );

protected:

};

#endif
