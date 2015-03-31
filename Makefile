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

example: src/main.cpp libcircle.so
	g++ -o example src/main.cpp -ldl

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
