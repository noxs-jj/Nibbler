/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 19:28:45 by vjacquie          #+#    #+#             */
/*   Updated: 2015/03/25 19:35:03 by vjacquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.class.hpp"

Game::Game( void ) {}

Game::Game( Game const & src ) { *this = src; }

Game & Game::operator=( Game const & rhs ) {
	if (this != &rhs)
	{

	}
	return (*this);
}
Game::~Game( void ) {}

int		Game::check_move(t_data *d)
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

void	Game::dec_map(t_data *d, int dec)
{
	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] > 0)
				d->map_info[y][x] -= dec;
		}
	}
}

void	Game::inc_map(t_data *d)
{
	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] > 0)
				d->map_info[y][x] += 1;
		}
	}
}

void	Game::move(t_data *d)
{
	int 	movx = 0;
	int 	movy = 0;

	if (check_move(d) < 0)
	{
		d->game = false;
		return ;
	}

	if (d->eat > 0)
		inc_map(d);
	if (d->dir == 1)
		movy = -1;
	else if (d->dir == 2)
		movy = 1;
	else if (d->dir == 3)
		movx = -1;
	else if (d->dir == 4)
		movx = 1;
	d->map_info[d->posy + movy][d->posx + movx] = d->map_info[d->posy][d->posx] + 1;
	dec_map(d, 1);
	if (d->eat > 0)
		d->eat--;
	d->after_head = d->head;
	d->head[0] = QUEUE;
	d->posy += movy;
	d->posx += movx;
	d->head = &(d->map[d->posy][d->posx]);
	if (d->head[0] == FRUIT)
		d->eat++;
	d->head[0] = HEAD;
	d->queue[0] = ' ';
	d->queue = d->before_queue;

	for (int y = 0; y < d->winy; ++y)
	{
		for (int x = 0; x < d->winx; ++x)
		{
			if (d->map_info[y][x] == 2)
			{
				d->before_queue = &(d->map[y][x]);
				return ;
			}
		}
	}
}

void	Game::change_dir(t_data *d) {
	if (d->key == NULL || (*d->key)->size() == 0)
		return ;
	// move(d); // REMOVE
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



void	Game::run(t_data *d)
{
	d->game = true;
	while (d->game == true)
	{
		change_dir(d);
		move(d);
		d->graphic->render_scene();
		if (d->key == NULL || (*d->key)->size() == 0)
			d->key = d->graphic->get_touch_list();
		usleep(d->speed);
	}
}
