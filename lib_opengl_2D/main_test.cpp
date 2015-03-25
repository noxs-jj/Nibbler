#include "../includes/api.class.hpp"
#include "opengl_2d.class.hpp"

// clear ; clang -Wall -Werror -Wextra -framework GLUT -framework OpenGL -framework Cocoa ../Api.class.cpp opengl_2D.class.cpp

// clang -Wall -Werror -Wextra -pedantic -o3 -shared -fPIC -o lib_opengl_2D.so -w -framework GLUT -framework OpenGL -framework Cocoa Api.class.cpp opengl_2D.class.cpp 

int	main(int ac, char **av)
{
	int		i = 0;
	Api		*graphic = new Graphic();
	char	**map = (char **)std::malloc(sizeof(char*) * 10);

	while ( i < 10)
	{
		map[i] = (char *)std::malloc(sizeof(char) * 10 + 1);
		if (NULL == map[i])
		{
			std::cerr << "map malloc error" << std::endl;
			return (-1);
		}
		map[i] = strncpy(map[i], "# oo * @ #", 10);
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

	return (0);
}
