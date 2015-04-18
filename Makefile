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

$(NAME): ncurse sdl2 sfml $(OBJ)
	@cp lib_ncurse/lib_ncurse.so .
	@cp lib_sdl/lib_sdl_2d.so .
	@cp lib_sfml/lib_sfml_2d.so .
	@$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\tBuild Bin 'nibbler' SUCCESS"
	@echo "\n\t./nibbler lib_ncurse.so lib_sdl_2d.so lib_sfml_2d.so"
	@echo "\n\t./nibbler *.so\n"

ncurse:
	@make -C lib_ncurse
	@echo "\tBuild Dynamic Lib Ncurse SUCCESS"

sdl2:
	@make -C lib_sdl
	@echo "\tBuild Dynamic Lib SDL2 SUCCESS"

sfml:
	@make -C lib_sfml
	@echo "\tBuild Dynamic Lib SFML SUCCESS"

example: src/main.cpp libcircle.so
	@g++ -o example src/main.cpp -ldl

clean:
	@make -C lib_ncurse clean
	@make -C lib_sdl clean
	@make -C lib_sfml clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C lib_ncurse fclean
	@make -C lib_sdl fclean
	@make -C lib_sfml fclean
	@rm *.so
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
