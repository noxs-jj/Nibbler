/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 18:45:16 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 19:25:16 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_CLASS_HPP
# define EVENT_CLASS_HPP

# include "main.hpp"

class Event {
private:

public:
	Event( void );
	Event( Event const & src );
	Event & operator=( Event const & rhs );
	~Event( void );

	void	init(t_data *d, int ac, char **av);
	void	open_lib(t_data *d);
	void	close_all(t_data *d);
	void	init_map(t_data *d);
protected:

};

#endif