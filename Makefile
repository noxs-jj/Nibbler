#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 15:26:25 by jmoiroux          #+#    #+#              #
#    Updated: 2015/03/16 15:26:26 by jmoiroux         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CXX = g++
CLANG = clang

NAME = nibbler

PLATFORM := $(shell uname)

CFLAGS = -Wall -Werror -Wextra -o3

LIB_FLAG = -shared -fPIC

HEAD = 	includes/main.hpp

SRC = 	src/main.cpp src/event.class.cpp

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp $(HEAD)
	@$(CXX) $(CFLAGS) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	# @$(CXX) $(CFLAGS) $(OBJ) -o $(NAME) $(GL)

full: $(NAME)
	make -C lib_ncurse && echo "Compil lib_ncurse.so"
	brew update && brew install sdl && reset
	make -C lib_sdl && echo "Compil lib_sdl_2d.so"
	make -C lib_sfml && echo "Compil lib_sfml_2d.so"
	export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.2/lib
	./set_shell.sh
	cp lib_ncurse/lib_ncurse.so .
	cp lib_sdl/lib_sdl_2d.so .
	cp lib_sfml/lib_sfml_2d.so .
	echo "All Lib_xx_.so compil"

fullclean:
	@rm -rf $(OBJ)
	rm *.so
	rm nibbler
	make -C fclean lib_ncurse
	make -C fclean lib_sdl
	make -C fclean lib_sfml

example: src/main.cpp libcircle.so
	g++ -o example src/main.cpp -ldl

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
