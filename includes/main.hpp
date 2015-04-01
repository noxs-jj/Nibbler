/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:21:21 by vjacquie          #+#    #+#             */
/*   Updated: 2015/04/01 13:03:47 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

# include <unistd.h>
# include <iostream>
# include <dlfcn.h>
# include <stdlib.h>
# include <time.h>
# include <stdlib.h>
# include <random>
# include <string.h>
# include "../includes/api.class.hpp"

# define PARAM "./nibbler [xPOSX] [yPOSY] [-level | -pro] <lib>"

# define MAP_WIDTH 40
# define MAP_HEIGHT 40
# define BASIC_SPEED 100000
# define SPECIAL_TIME 40

# define UP     65
# define DOWN   66
# define LEFT   68
# define RIGHT  67
# define ECHAP  27
# define ONE	49
# define TWO	50
# define THREE	51

# define START_X (MAP_WIDTH / 2)
# define START_Y (MAP_HEIGHT / 2)

# define WALL '#'
# define HEAD '*'
# define QUEUE 'o'
# define FRUIT '@'
# define SPECIAL '?'

class 					Event;

typedef struct			s_data
{
	int					ac;
	char				**av;
}						t_data;

#endif
