// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libx.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 15:40:57 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/16 15:40:58 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "libx.class.hpp"

lib_libx::lib_libx( lib_libx const & src ) {
	*this = src;
}

lib_libx & lib_libx::operator=(lib_libx const & rhs) {
	if (this != &rhs)
	{
		this->mlx = rhs.mlx;
		this->win = rhs.win;
		this->img_new = rhs.img_new;
		this->img_data = rhs.img_data;
		this->winx = rhs.winx;
		this->winy = rhs.winy;
		this->red = rhs.red;
		this->green = rhs.green;
		this->blue = rhs.blue;
		this->endian = rhs.endian;
		this->line_size = rhs.line_size;
		this->bit_pixel = rhs.bit_pixel;
	}
	return *this;
}

lib_libx::lib_libx( int x, int y, char *title ) :
mlx(NULL), win(NULL), img_new(NULL), img_data(NULL), winx(x * 10), winy(y * 10),
red(0), green(0), blue(0), endian(0), line_size(0), bit_pixel(0) {

	this->mlx = mlx_init();
	if (NULL == this->mlx)
		throw std::exception();

	this->win = mlx_new_window(this->mlx, this->winx, this->winy, title);
	if (NULL == this->win)
		throw std::exception();

	this->img_new = mlx_new_image(this->mlx, this->winx, this->winy);
	if (NULL == this->img_new)
		throw std::exception();

	this->img_data = mlx_get_data_addr(this->img_data, &(this->bit_pixel), &(this->line_size), &(this->endian));
	if (NULL == this->img_data)
		throw std::exception();
}

lib_libx::~lib_libx( void ) {
	std::free(this->img_data);
	std::free(this->img_new);
	std::free(this->win);
	std::free(this->mlx);
}
