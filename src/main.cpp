/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 15:42:59 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"

void    do_move(int posx, int posy, int newx, int newy, char **map)
{
	map[posy][posx] = ' ';
	map[posy + newy][posx + newx] = HEAD;
}

void    move(std::vector<int> **key, int posx, int posy, char **map) {
	if (key == NULL || (*key)->size() == 0)
		return ;
	if ((*key)->front() == (UP) && posy - 1 >= 0)
		do_move(posx, posy, 0, -1, map);
	else if ((*key)->front() == (DOWN) && posy + 1 < MAP_HEIGHT)
		do_move(posx, posy, 0, 1, map);
	else if ((*key)->front() == (LEFT) && posx - 1 >= 0)
		do_move(posx, posy, -1, 0, map);
	else if ((*key)->front() == (RIGHT) && posx + 1 < MAP_WIDTH)
		do_move(posx, posy, 1, 0, map);
	else if ((*key)->front() == (ECHAP))
		;
	(*key)->erase((*key)->begin());
	return ;
}

int main(int ac, char **av)
{
	void				*hndl;
	Api					*(*create)();
	Api					*graphic;
	std::vector<int>	**key = NULL;
	char				**map = NULL;
	int					posx = START_X;
	int					posy = START_Y;

	static_cast<void>(ac);
	static_cast<void>(av);
	hndl = dlopen("lib_graphic.so", RTLD_LAZY | RTLD_LOCAL);
	if (hndl == NULL)
	{
		std::cerr << "dlopen : "<< dlerror() << std::endl; 
		exit(EXIT_FAILURE);
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(hndl, "newObject"))) == NULL)
	{ 
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	map = static_cast<char **>(std::malloc(sizeof(char*) * MAP_HEIGHT ));
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		map[i] = static_cast<char *>(std::malloc(sizeof(char) * MAP_HEIGHT ));
		memset(map[i], '\0', MAP_HEIGHT);
	}
	for (int y = 0; y < MAP_WIDTH; ++y)
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			if (y == 0 || y == MAP_WIDTH - 1 || i == 0 || i == MAP_HEIGHT - 1)
				map[y][i] = WALL;
		}
	}
	map[posy][posx] = HEAD;

	graphic = create();
	graphic->init(ac, av, MAP_WIDTH, MAP_HEIGHT, NULL, map);

	while (1)
	{
		move(key, posx, posy, map);
		graphic->render_scene();
		if (key == NULL || (*key)->size() == 0)
			key = graphic->get_touch_list();
	}

	graphic->close();
	dlclose(hndl);
	return (EXIT_SUCCESS);
}
