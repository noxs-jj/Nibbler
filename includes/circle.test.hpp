#ifndef CIRCLE_H_
#define CIRCLE_H_
 
#include <iostream>
#include "API.h"
class api;
class	circle : public API
{
	public:
		// virtual init (construct);
		// virtual render_scene();
		// virtual close(destruct);
		// virtual get_touch_list();
		virtual void draw();

};
 
typedef circle *(*maker_circle)();

#endif
