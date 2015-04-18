# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 16:39:58 by vjacquie          #+#    #+#              #
#    Updated: 2015/04/01 12:37:46 by vjacquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = g++

NAME = lib_ncurse.so

CFLAGS = -Wall -Werror -Wextra

LIB_FLAG = -shared -fPIC

NCURSE_FLAGS = -lncurses

HEADER = lib_ncurse.class.hpp

SRC =	lib_ncurse.class.cpp \
		../Api.class.cpp		

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	@$(CXX) $(CFLAGS) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(CXX) $(CFLAGS) $(NCURSE_FLAGS) $(LIB_FLAG) -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
