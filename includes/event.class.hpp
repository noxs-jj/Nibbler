/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:16 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/04 18:59:52 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include "main.hpp"

class Event {
private:
	Api					*_graphic;
	bool				_fruit;
	bool				_game;
	bool				_paused;
	char				**_map;
	char				*_after_head;
	char				*_before_queue;
	char				*_head;
	char				*_lib_name[3];
	char				*_queue;
	char 				*_spec;
	int					**_map_info;
	int					_dir; // actual direction (1 up, 2 down, 3 left, 4 right)
	int					_eat; // >= 1 if need to grow
	int					_posx;
	int					_posy;
	int					_special;
	int					_speed;
	int					_winx;
	int					_winy;
	int 				_game_mode;	// 0: normal, 2:pro
	std::vector<int>	**_key;
	t_data				*_d;
	unsigned int 		_score;
	void				*_hndl;

	Event( Event const & src );
	Event & operator=( Event const & rhs );

public:
	Event( void );
	~Event( void );

	void	init(t_data *d);
	void	open_lib(char *name);
	void	change_lib(int lib);
	void	close_all( void );
	void	init_map( void );
	int 	parse_option(int ac, char **av);

	void	run( void );

	void	pro_get_special( void );
	void	pro_spawn_obstacle( int rock );
	void	change_dir( void );
	void	move( void );
	void	inc_map( void );
	void	dec_map(int dec );
	int		check_move( void );
	void	add_fruit( void );
	void	add_special( void );
};

#endif