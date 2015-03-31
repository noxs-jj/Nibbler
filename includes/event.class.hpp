/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:16 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/31 16:28:23 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include "main.hpp"

class Event {
private:
	char				*_lib_name[3];
	Api					*_graphic;
	void				*_hndl;
	char				*_head;
	char				*_after_head;
	char				*_queue;
	char				*_before_queue;
	int					_posx;
	int					_posy;
	int					_winx;
	int					_winy;
	std::vector<int>	**_key;
	char				**_map;
	int					**_map_info;
	int					_dir; // actual direction (1 up, 2 down, 3 left, 4 right)
	int					_eat; // >= 1 if need to grow
	bool				_game;
	int					_speed;
	bool				_fruit;
	int 				_game_mode;	// 0: normal, 1:level, 2:pro
	unsigned int 		_score;
	int					_special;
	char 				*_spec;
public:
	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	~Event( void );

	void	init(int ac, char **av);
	void	open_lib(char *name);
	void	close_all( void );
	void	init_map( void );
	int 	parse_option(int ac, char **av);

	void	run( void );
	void	run_level( void );

	void	pro_get_special( void );
	void	pro_spawn_obstacle( int rock );
	void	change_dir( void );
	void	move( void );
	void	inc_map( void );
	void	dec_map(int dec );
	int		check_move( void );
	void	add_fruit( void );
	void	add_special( void );
protected:

};

#endif