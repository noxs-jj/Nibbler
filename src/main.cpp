/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/31 15:25:06 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"
#include "../includes/event.class.hpp"


int main(int ac, char **av)
{
	// t_data 				*d;
	Event				event;

	// if ((d = static_cast<t_data *>(std::malloc(sizeof(t_data)))) == NULL)
	// {
	// 	std::cerr << "t_data malloc error" << std::endl; 
	// 	exit(EXIT_FAILURE);
	// }
	event.init(ac, av);
	event.run();
	event.close_all();
	return (EXIT_SUCCESS);
}
