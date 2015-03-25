#include <iostream>
#include <dlfcn.h>
// #include "lib_ncurse.class.hpp"
#include "../includes/api.class.hpp"
// class Graphic;

#include <unistd.h>

# define TEST_WALL '#'
# define TEST_HEAD '*'
# define TEST_QUEUE 'o'
# define TEST_FRUIT '@'
# define TEST_POS_X 20
# define TEST_POS_Y 20
# define TEST_SIZE	40

# define KEY_UP		65
# define KEY_DOWN	66
# define KEY_LEFT	68
# define KEY_RIGHT	67
# define KEY_ECHAP	27

using namespace std;

void	do_move(int posx, int posy, int newx, int newy, char **map)
{
	map[posy][posx] = ' ';
	map[posy + newy][posx + newx] = TEST_HEAD;
}

void	move(std::vector<int> **key, int posx, int posy, char **map) {
	if (key == NULL || (*key)->size() == 0)
		return ;
	if ((*key)->front() == (KEY_UP) && posy - 1 >= 0)
		do_move(posx, posy, 0, -1, map);
	else if ((*key)->front() == (KEY_DOWN) && posy + 1 < TEST_SIZE)
		do_move(posx, posy, 0, 1, map);
	else if ((*key)->front() == (KEY_LEFT) && posx - 1 >= 0)
		do_move(posx, posy, -1, 0, map);
	else if ((*key)->front() == (KEY_RIGHT) && posx + 1 < TEST_SIZE)
		do_move(posx, posy, 1, 0, map);
	else if ((*key)->front() == (KEY_ECHAP))
		;
	(*key)->erase((*key)->begin());
	return ;
}

int	main(int ac, char **av)
{
	void		*hndl;
	Api			*(*create)();
	Api			*graphic;
	std::vector<int>	**key = NULL;
	char		**map = NULL;
	int posx = TEST_POS_X;
	int posy = TEST_POS_Y;

	static_cast<void>(ac);
	static_cast<void>(av);
	hndl = dlopen("lib_ncurse.so", RTLD_LAZY | RTLD_LOCAL);
	if (hndl == NULL)
	{
		cerr << "dlopen : "<< dlerror() << endl; 
		exit(EXIT_FAILURE);
	}
	if ((create = reinterpret_cast<Api* (*)()>(dlsym(hndl, "newObject"))) == NULL)
	{ 
		cerr << "dlsym : " << dlerror() << endl;
		exit(EXIT_FAILURE);
	}
	map = static_cast<char **>(std::malloc(sizeof(char*) * TEST_SIZE ));
	for (int i = 0; i < TEST_SIZE; ++i)
	{
		map[i] = static_cast<char *>(std::malloc(sizeof(char) * TEST_SIZE ));
		memset(map[i], '\0', TEST_SIZE);
	}
	for (int y = 0; y < TEST_SIZE; ++y)
	{
		for (int i = 0; i < TEST_SIZE; ++i)
		{
			if (y == 0 || y == TEST_SIZE - 1 || i == 0 || i == TEST_SIZE - 1)
				map[y][i] = TEST_WALL;
		}
	}
	map[TEST_POS_Y][TEST_POS_X] = HEAD;

	graphic = create();
	graphic->init(ac, av, TEST_SIZE, TEST_SIZE, NULL, map);

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
