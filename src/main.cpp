// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 15:35:31 by jmoiroux          #+#    #+#             //
//   Updated: 2015/03/16 15:35:32 by jmoiroux         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../includes/circle.test.hpp"
#include <iostream>
#include <dlfcn.h>
 
using namespace std;
 
int main(int argc, char **argv)
{
    void *hndl;
    maker_circle pMaker;
 
    // Ouverture de la librairie
    hndl = dlopen("./libcircle.so", RTLD_LAZY);
    if(hndl == NULL)
    {
		cerr << "dlopen : "<< dlerror() << endl; 
		exit(EXIT_FAILURE);
    }
 
    // Chargement du créateur
    void *mkr = dlsym(hndl, "make_circle");
    if (mkr == NULL)
    {
		cerr << "dlsym : " << dlerror() << endl;
		exit(EXIT_FAILURE);
    }
    pMaker = (maker_circle)mkr;
 
 
    // Création, affichagedu cercle
    circle *my_circle = pMaker();
    my_circle->draw();
    dlclose(hndl);
 
    return EXIT_SUCCESS;
}