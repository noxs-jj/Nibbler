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

full: $(NAME)
	@brew update && brew install sdl && reset
	@make -C lib_sdl && echo "\t\tCompil lib_sdl_2d.so SUCCESS"
	@make -C lib_ncurse && echo "\t\tCompil lib_ncurse.so SUCCESS"
	@make -C lib_sfml && echo "\t\tCompil lib_sfml_2d.so SUCCESS"
	@export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.2/lib
	@./set_shell.sh
	@cp lib_ncurse/lib_ncurse.so .
	@cp lib_sdl/lib_sdl_2d.so .
	@cp lib_sfml/lib_sfml_2d.so .
	@echo "\n\n\t\tAll Lib_xx_.so Compil SUCCESS\n\n"

fullclean:
	@make -C lib_ncurse fclean
	@make -C lib_sdl fclean
	@make -C lib_sfml fclean
	@rm *.so
	@rm nibbler	

example: src/main.cpp libcircle.so
	g++ -o example src/main.cpp -ldl

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
