#ifndef CIRCLE_H_
#define CIRCLE_H_
 
#include <iostream>
#include "API.h"
class api;
class	circle : public API
{
	public:
		virtual void		init(void); //construct
		virtual void		close(void); //destruct
		virtual void		render_scene(char **);
		virtual t_list_key	get_touch_list(void);

};
 
typedef circle *(*maker_circle)();

#endif
