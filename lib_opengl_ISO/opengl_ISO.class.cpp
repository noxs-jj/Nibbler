// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   opengl_ISO.class.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 15:41:13 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/16 15:41:14 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include "opengl_2D.class.hpp"

void				Graphic::close( void ) {}

std::vector<int>	*Graphic::get_touch_list( void ) {
	return (this->key_list);
}

void				Graphic::addKey(int keyInput) {
	if (true == empty)
	{
		this->key_list = new std::vector<int>;
		this->key_list->push_back(keyInput);
		this->empty = false;
	}
	else
		this->key_list->push_back(keyInput);
}

void  				keyboard(unsigned char touche, int x, int y)
{
	(void)x;
	(void)y;
	if ( touche == 'q' || touche == 27 ) {
		;
	}
}

void	Graphic::render_scene( char **map ) { // render map
	this->ic = 0;
	while (this->ic < WIN_X)
	{
		this->camx = 2 * this->ic / static_cast<double>((WIN_X) - 1);
		this->rayposx = this->posx;
		this->rayposy = this->posy;
		this->raydirx = this->dirx + (this->planex * this->camx);
		this->raydiry = this->diry + (this->planey * this->camx);
		this->mapx = static_cast<int>(this->rayposx);
		this->mapy = static_cast<int>(this->rayposy);
		this->deltadistx = sqrt(1 + ((this->raydiry * this->raydiry) / (this->raydirx * this->raydirx)));
		this->deltadisty = sqrt(1 + ((this->raydirx * this->raydirx) / (this->raydiry * this->raydiry)));
		this->hit = 0;
		if (this->raydirx < 0)
		{
			this->stepx = -1;
			this->sidedistx = (this->rayposx - this->mapx) * this->deltadistx;
		}
		else
		{
			this->stepx = 1;
			this->sidedistx = (this->mapx + 1.0 - this->rayposx) * this->deltadistx;
		}
		if (this->raydiry < 0)
		{
			this->stepy = -1;
			this->sidedisty = (this->rayposy - this->mapy) * this->deltadisty;
		}
		else
		{
			this->stepy = 1;
			this->sidedisty = (this->mapy + 1.0 - this->rayposy) * this->deltadisty;
		}
		while (this->hit == 0)
		{
			if (this->sidedistx < this->sidedisty)
			{
				this->sidedistx = this->sidedistx + this->deltadistx;
				this->mapx = this->mapx + this->stepx;
				this->side = 0;
			}
			else
			{
				this->sidedisty = this->sidedisty + this->deltadisty;
				this->mapy = this->mapy + this->stepy;
				this->side = 1;
			}
			if (this->map[this->mapx][this->mapy] > 0)
				this->hit = 1;
		}
		if (this->side == 0)
			this->perpwalldist = fabs((this->mapx - this->rayposx + (1 - this->stepx) / 2) / this->raydirx);
		else
			this->perpwalldist = fabs((this->mapy - this->rayposy + (1 - this->stepy) / 2) / this->raydiry);
		this->lineheight = abs(WIN_Y / this->perpwalldist);
		ft_draw(d);
		this->ic = this->ic + 1;
	}
}

void	Graphic::draw_line(void)
{
	int		i;
	int		min;
	int		max;

	i = 0;
	min = (this->lineheight < 0) ? WIN_Y / 2 : (WIN_Y - this->lineheight) / 2;
	max = min + this->lineheight;
	while (i < WIN_Y)
	{
		if (i < min)
			mlx_pixel_put(this->winthis->mlx, this->winthis->win, this->ic, i, SKYCOLOR);
		else if (i < max)
			ft_draw_putpixel(d, i);
		else
			mlx_pixel_put(this->winthis->mlx, this->winthis->win, this->ic, i, FLOORCOLOR);
		i++;
	}
}

void	Graphic::init( int ac, char **av, int x, int y, char *title ) {
	glutInit(&ac, av);								// init glut
	glutInitDisplayMode(GLUT_RGB					// set color to RGB
				| GLUT_DOUBLE						// set double buffered windows
				| GLUT_DEPTH);						// Bit mask to select a window with a depth buffer.
	glutInitWindowSize(x * X_MULTI, x * Y_MULTI);	// Size of windows
	glutInitWindowPosition(STARTX, STARTY);   		// where the windos in create on Xserver/Desktop
	glutCreateWindow(title);						// Create windows with title in param char *
	glClearColor(0.5f, 0.5f, 0.5f, 1); 				//purple set background/void color
	glEnable(GL_DEPTH_TEST);
	glPointSize(POINT_SIZE);
	glLineWidth(LINE_WIDTH);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	glutSwapBuffers();
	glLoadIdentity();
	this->winx = x * X_MULTI;
	this->winy = x * Y_MULTI;
}

Graphic &	Graphic::operator=(Graphic const & rhs) {
	if (this != &rhs)
	{
		this->winx = rhs.winx;
		this->winy = rhs.winy;
		this->key_list = rhs.key_list;
	}
	return *this;
}

Graphic::Graphic( Graphic const & rhs ) {
	*this = rhs;
}

Graphic::Graphic( void ) : winx(0), winy(0), key_list(NULL), empty(true) {}	//construct

Graphic::~Graphic( void ) {	// destruct
	this->key_list->clear();
}
