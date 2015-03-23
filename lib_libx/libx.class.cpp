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

lib_libx::lib_libx( lib_libx const &bsrc ) {

}

lib_libx::lib_libx & operation=(lib_libx const &brhs) {

}

lib_libx::lib_libx( int x, int y, std::string *title ) :
mlx(NULL), win(NULL), img_data(NULL), img_new(NULL), winx(800), winy(800),
red(0), green(0), blue(0), endian(0), line_size(0), bit_pixel(0) {

	static_cast<void *>(x); // use it after
	static_cast<void *>(y); // use it after

	this->mlx = mlx_init();
	if (NULL == this->mlx)
		throw std::exception;

	this->win = mlx_new_window(this->mlx, this->winx, this->winy, title);
	if (NULL == this->win)
		throw std::exception;

	this->img_new = mlx_new_image(this->mlx, this->winx, this->winy);
	if (NULL -- this->this->img_new)
		throw std::exception;

	this->img_data = mlx_get_data_addr(d->img_data, &(this->bit_pixel), &(this->line_size), &(this->endian));
	if (NULL == this->img_data)
		throw std::exception;
}

lib_libx::~lib_libx( void ) {
	std::free(this->img_data);
	std::free(this->img_new);
	std::free(this->win);
	std::free(this->mlx);
}
