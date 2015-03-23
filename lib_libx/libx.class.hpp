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
	void	*mlx;
	void	*win;
	void	*img_new;
	char	*img_data;
	int		winx;
	int		winy;
	int		red;
	int		green;
	int		blue;
	int		endian;
	int		line_size;
	int		bit_pixel;

	lib_libx( int x, int y, char *title );
	lib_libx( lib_libx const & src );
	lib_libx & operator=( lib_libx const & rhs );
	~lib_libx( void );
};

#endif
