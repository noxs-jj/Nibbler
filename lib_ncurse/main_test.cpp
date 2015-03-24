#include <iostream>
#include <dlfcn.h>
#include "lib_ncurse.class.hpp"
// #include "../includes/api.class.hpp"
// class Graphic;

using namespace std;

int	main(int ac, char **av)
{
	void		*hndl;
 	Graphic		*(*create)();
 	Graphic		*graphic;

 	// char *str;		// delete
 	// str = (char *)std::malloc(sizeof(char) * 5);
 	// std::strcpy(str, "Test");

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

	if ((create = dynamic_cast<Graphic *(*)()>(dlsym(hndl, "newObject"))) == NULL)
	{
		cerr << "dlsym : " << dlerror() << endl;
		exit(EXIT_FAILURE);
	}

	graphic = create();
	graphic->delObject();
    dlclose(hndl);
    return (EXIT_SUCCESS);
}