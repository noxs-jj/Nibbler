#include <iostream>
#include <dlfcn.h>
// #include "lib_ncurse.class.hpp"
#include "../includes/api.class.hpp"
// class Graphic;

# define TEST_WALL '#'
# define TEST_HEAD '*'
# define TEST_QUEUE 'o'
# define TEST_FRUIT '@'

using namespace std;

int	main(int ac, char **av)
{
	void		*hndl;
 	Api			*(*create)();
 	Api			*graphic;
 	// char 		map[80][80];
 	char		**map;

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
	graphic = create();
	graphic->init(ac, av, 80, 80, NULL);

	map = static_cast<char **>(std::malloc(sizeof(char*) * 80 ));
	for (int i = 0; i < 80; ++i)
		map[i] = static_cast<char *>(std::malloc(sizeof(char) * 80 ));
	for (int y = 0; y < 80; ++y)
	{
		for (int i = 0; i < 80; ++i)
		{
			if (y == 1 || y == 79 || i == 1 || i == 79)
				map[y][i] = TEST_WALL;
		}
	}
	std::cout << "hey" << std::endl;
	while (1)
	{
		graphic->render_scene(map);
		// usleep(100000);
	}

	graphic->close();
    dlclose(hndl);
    return (EXIT_SUCCESS);
}