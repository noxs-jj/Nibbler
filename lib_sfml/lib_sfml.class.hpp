/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_sfml.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 15:07:26 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/04 14:54:40 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_SFML_CLASS_HPP
# define LIB_SFML_CLASS_HPP


# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "../includes/api.class.hpp"

#include <vector>

class api;

typedef struct		s_key
{
	int				key;
	struct s_key	*next;
}					t_key;

class Graphic : public Api {
private:
	sf::RenderWindow	*_window;
	int					_x;
	int					_y;
	char				*_name;
	std::vector<int> 	*_key;
	char				**_map;
	sf::CircleShape		*_queue;
	sf::CircleShape		*_head;
	sf::CircleShape		*_fruit;
	sf::CircleShape		*_special;
	sf::CircleShape		*_wall;

	sf::Event 			*_event;
	
public:
	Graphic( void );
	Graphic( Graphic const & src );
	Graphic & operator=( Graphic const & rhs );
	~Graphic( void );

	char				*getName( void ) const;
	sf::RenderWindow	*getWindow( void ) const;
	int					getX( void ) const;
	int					getY( void ) const;
	std::vector<int>	*getKey( void ) const;
	char				**getMap( void ) const;
	void				keyboard( void );

	void				init( int ac, char** av, int x, int y, char *title, char **map );
	void				close( void );
	void				render_scene( void );
	std::vector<int>	**get_touch_list( void );

	// void				delObject( Api *del );
	// void				echo( void );
protected:

};


#endif
