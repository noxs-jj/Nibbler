// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main_test.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/27 14:27:35 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/27 14:27:36 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
#include "../includes/api.class.hpp"
#include "sdl.class.hpp"

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
			map[i] = strncpy(map[i], "##########", 10);
		else if (i == 4)
			map[i] = strncpy(map[i], "# ooo*  @#", 10);
		else
			map[i] = strncpy(map[i], "#        #", 10);
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

	return (0);
}

/*
int	main( int argc, char *argv[ ] )
{
	(void)argc;
	(void)argv;
	SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Mon premier programme OpenGL !",NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);

    bool continuer = true;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = false;
        }

         glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
            glColor3ub(0,255,0);    glVertex2d(0,0.75);
            glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
        glEnd();

        glFlush();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}
*/