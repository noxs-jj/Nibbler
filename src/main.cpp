/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 19:35:33 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"
#include "../includes/event.class.hpp"
#include "../includes/game.class.hpp"


int main(int ac, char **av)
{
	t_data 				*d;
	Event				event;
	Game				game;

	if ((d = static_cast<t_data *>(std::malloc(sizeof(t_data)))) == NULL)
	{
		std::cerr << "t_data malloc error" << std::endl; 
		exit(EXIT_FAILURE);
	}
	event.init(d, ac, av);
	game.run(d);
	event.close_all(d);
	return (EXIT_SUCCESS);
}
