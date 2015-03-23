// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libx.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/23 16:27:26 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/23 16:27:29 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef LIBX_CLASS_HPP
# define LIBX_CLASS_HPP

# include "../includes/api.class.hpp"
# include "minilibx_macos/mlx.h"

class 				api;

typedef struct		s_key {
	int				key;
	struct s_key	*next;
}					t_key;

class	lib_libx : public api {
public:
	void	*img_new;
	void	*mlx;
	void	*win;
	char	*img_data;
	int		winx;
	int		winy;
	int		red;
	int		freen;
	int		blue;
	int		endian;
	int		line_size;
	int		bit_pixel;

	lib_libx( int x, int y, std::string *title );
	lib_libx( lib_libx const &bsrc );
	lib_libx & operation=( lib_libx const &brhs );
	~lib_libx( void );
};

#endif
