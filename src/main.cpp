/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/01 13:05:08 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"
#include "../includes/event.class.hpp"


int main(int ac, char **av)
{
	t_data 				d;
	Event				event;

	d.ac = ac;
	d.av = av;
	event.init(&d);
	event.run();
	event.close_all();
	return (EXIT_SUCCESS);
}
