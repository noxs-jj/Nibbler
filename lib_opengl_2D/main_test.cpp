#include "../includes/api.class.hpp"
#include "opengl_2D.class.hpp"

//clear ; clang++ `sdl2-config --libs` `sdl2-config --cflags` main_test.cpp opengl_sdl_2D.cpp -o test_main

// clear ; clang++ -Wall -Werror -Wextra -stdlib=libc++ `sdl2-config --libs` `sdl2-config --cflags` main_test.cpp opengl_sdl_2D.cpp ../Api.class.cpp -o test_main

// clear ; clang++ -Wall -Werror
int	main(int ac, char **av)
{
	int		i = 0;
	Api		*graphic = new Graphic();
	char	**map = (char **)std::malloc(sizeof(char*) * 10);

	(void)ac;
	(void)av;
	while ( i < 10)
	{
		map[i] = (char *)std::malloc(sizeof(char) * 10 + 1);
		if (NULL == map[i])
		{
			std::cerr << "map malloc error" << std::endl;
			return (-1);
		}

		if (i == 0 || i == 9)
		{
			map[i] = strncpy(map[i], "##########", 10);
		}
		else if (i == 4)
		{
			map[i] = strncpy(map[i], "# ooo*  @#", 10);
		}
		else
		{
			map[i] = strncpy(map[i], "#        #", 10);
		}

		i++;
	}

	if (NULL == graphic)
	{
		std::cerr << "graphic init error" << std::endl;
		return (-1);
	}

	std::cout << "Debugg 0" << std::endl;
	graphic->init(ac, av, 10, 10, "Test snake", map);
	std::cout << "Debugg 1" << std::endl;
	graphic->render_scene();
	std::cout << "Debugg 3" << std::endl;
	graphic->render_scene();
	std::cout << "Debugg 4" << std::endl;
	graphic->render_scene();
	std::cout << "Debugg 5" << std::endl;
	graphic->render_scene();
	std::cout << "Debugg 6" << std::endl;
	graphic->render_scene();


	return (0);
}
