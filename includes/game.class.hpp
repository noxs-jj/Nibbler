/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 19:28:55 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/26 12:41:32 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

# include "main.hpp"

class Game {
private:

public:
	Game( void );
	Game( Game const & src );
	Game & operator=( Game const & rhs );
	~Game( void );

	void	run(t_data *d);
	void	change_dir(t_data *d);
	void	move(t_data *d);
	void	inc_map(t_data *d);
	void	dec_map(t_data *d, int dec);
	int		check_move(t_data *d);
	void	add_fruit(t_data *d);
protected:

};

#endif