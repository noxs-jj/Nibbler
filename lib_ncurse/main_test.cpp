#include <iostream>
#include <dlfcn.h>
// #include "lib_ncurse.class.hpp"
#include "../includes/api.class.hpp"
// class Graphic;

using namespace std;

int	main(int ac, char **av)
{
	void		*hndl;
 	Api			*(*create)();
 	Api			*graphic;

 	char *str;		// delete
 	str = (char *)std::malloc(sizeof(char) * 5);
 	std::strcpy(str, "Test");
    // Ouverture de la librairie

    static_cast<void>(ac);
    static_cast<void>(av);

    hndl = dlopen("lib_ncurse.so", RTLD_LAZY | RTLD_LOCAL);
    if (hndl == NULL)
    {
		cerr << "dlopen : "<< dlerror() << endl; 
		exit(EXIT_FAILURE);
    }
 

    // Chargement du créateur

	if ((create = reinterpret_cast<Api *(*)()>(dlsym(hndl, "newObject"))) == NULL)
	{
		cerr << "dlsym : " << dlerror() << endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "bla" << std::endl;
	graphic = create();
	std::cout << "bla1" << std::endl;
	graphic->init(ac, av, 80, 80, str);
	std::cout << "bla2" << std::endl;
	graphic->delObject();
	std::cout << "bla3" << std::endl;
    dlclose(hndl);
    return (EXIT_SUCCESS);
}