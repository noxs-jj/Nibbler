/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/21 12:14:58 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 17:47:30 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.hpp"

int		check_move(t_data *d)
{
	int 	movx = 0;
	int 	movy = 0;

	if (d->dir == 1)
		movy = -1;
	else if (d->dir == 2)
		movy = 1;
	else if (d->dir == 3)
		movx = -1;
	else if (d->dir == 4)
		movx = 1;

	if (d->map[d->posy + movy][d->posx + movx] == WALL
		|| d->map[d->posy + movy][d->posx + movx] == QUEUE)
		return (-1);
	return (0);
}

void    move(t_data *d)
{
	if (check_move(d) < 0)
		;	// die







	// d->map[d->posy][d->posx] = ' ';
	d->map[d->posy + newy][d->posx + newx] = HEAD;
	d->after_head = d->head;
	d->posy += newy;
	d->posx += newx;
	d->head = &(d->map[d->posy][d->posx]);
}

void    change_dir(t_data *d) {
	if (d->key == NULL || (*d->key)->size() == 0)
		return ;
	if ((*d->key)->front() == (UP) && d->posy - 1 >= 0 && d->dir != 2)
		d->dir = 1;
	else if ((*d->key)->front() == (DOWN) && d->posy + 1 < MAP_HEIGHT && d->dir != 1)
		d->dir = 2;
	else if ((*d->key)->front() == (LEFT) && d->posx - 1 >= 0 && d->dir != 4)
		d->dir = 3;
	else if ((*d->key)->front() == (RIGHT) && d->posx + 1 < MAP_WIDTH && d->dir != 3)
		d->dir = 4;
	else if ((*d->key)->front() == (ECHAP))
		;
	(*d->key)->erase((*d->key)->begin());
	return ;
}

void	init_map(t_data *d)
{
	d->map = static_cast<char **>(std::malloc(sizeof(char*) * MAP_HEIGHT ));
	d->map_info = static_cast<int **>(std::malloc(sizeof(int*) * MAP_HEIGHT ));
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		d->map[i] = static_cast<char *>(std::malloc(sizeof(char) * MAP_HEIGHT ));
		d->map_info[i] = static_cast<int *>(std::malloc(sizeof(int) * MAP_HEIGHT ));
		memset(d->map[i], '\0', MAP_HEIGHT);
		memset(d->map_info[i], '0', MAP_HEIGHT);
	}
	for (int y = 0; y < MAP_WIDTH; ++y)
	{
		for (int i = 0; i < MAP_HEIGHT; ++i)
		{
			if (y == 0 || y == MAP_WIDTH - 1 || i == 0 || i == MAP_HEIGHT - 1)
				d->map[y][i] = WALL;
		}
	}
	d->map[d->posy - 3][d->posx] = QUEUE;
	d->map_info[d->posy - 3][d->posx] = 1;

	d->map[d->posy - 2][d->posx] = QUEUE;
	d->map_info[d->posy - 2][d->posx] = 2;

	d->map[d->posy - 1][d->posx] = QUEUE;
	d->map_info[d->posy - 1][d->posx] = 3;

	d->map[d->posy][d->posx] = HEAD;
	d->map_info[d->posy][d->posx] = 4;

	d->head = &(d->map[d->posy][d->posx]);
	d->after_head = &(d->map[d->posy - 1][d->posx]);
	d->before_queue = &(d->map[d->posy - 2][d->posx]);
	d->queue = &(d->map[d->posy - 3][d->posx]);
	// d->head[0] = FRUIT;
}

int main(int ac, char **av)
{
	void				*hndl;
	Api					*(*create)();
	Api					*graphic;
	t_data 				*d;

	static_cast<void>(ac);
	static_cast<void>(av);
	if ((d = static_cast<t_data *>(std::malloc(sizeof(t_data)))) == NULL)
	{
		std::cerr << "t_data malloc error" << std::endl; 
		exit(EXIT_FAILURE);
	}
	d->key = NULL;
	d->map = NULL;
	d->winx = MAP_WIDTH;
	d->winy = MAP_HEIGHT;
	d->posx = d->winx / 2;
	d->posy = d->winy / 2;
	d->eat = 0;
	d->dir = 2;

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
	init_map(d);
	graphic = create();
	graphic->init(ac, av, d->winx, d->winy, NULL, d->map);
	while (1)
	{
		change_dir(d);
		// move(d);
		graphic->render_scene();
		if (d->key == NULL || (*d->key)->size() == 0)
			d->key = graphic->get_touch_list();
	}

	graphic->close();
	dlclose(hndl);
	return (EXIT_SUCCESS);
}
