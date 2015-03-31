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

SRC_NCURSE =	lib_ncurse/lib_ncurse.class.cpp \
				Api.class.cpp

SRC_SFML = lib_sfml/lib_sfml.class.cpp \
				Api.class.cpp

SFML_FLAGS = -I ~/.brew/Cellar/sfml/2.2/include \
				-L ~/.brew/Cellar/sfml/2.2/lib \
				-lsfml-graphics -lsfml-window -lsfml-system


SO_NAME = lib_graphic.so

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp $(HEAD)
	@$(CXX) $(CFLAGS) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)
	# @$(CXX) $(CFLAGS) $(OBJ) -o $(NAME) $(GL)


ncurse:
	echo "Compil with NCurse lib .so."
	$(CXX) $(CFLAGS) -lncurses $(LIB_FLAG) -o $(SO_NAME) $(SRC_NCURSE)



sfml:
	# export LD_LIBRARY_PATH=~/.brew/Cellar/sfml/2.2/lib
	$(CXX) $(CFLAGS) $(LIB_FLAG) $(SFML_FLAGS) -o $(SO_NAME) $(SRC_SFML)



example: src/main.cpp libcircle.so
	g++ -o example src/main.cpp -ldl

libcircle.so: src/circle.test.cpp includes/circle.test.hpp
	g++ -shared -o libcircle.so src/circle.test.cpp

soclean:
	rm -f example libcircle.so

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
