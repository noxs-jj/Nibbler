#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/28 21:14:09 by jmoiroux          #+#    #+#              #
#    Updated: 2015/03/28 21:14:10 by jmoiroux         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
#
#
# LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L $(SFML)/lib -Wl,-rpath=$(SFML)/lib -Wl,-rpath-link=$(SFML)/lib

CLANG = clang++

NAME = lib_sfml_2d.so

SFML = ~/.brew/Cellar/sfml/2.2

GL = -framework opengl -L $(SFML)/lib -Wl,-rpath,$(SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

# GL = -framework opengl -L ~/.brew/Cellar/sfml/2.2/lib -lsfml-graphics -lsfml-window -lsfml-system



CFLAGS = -Wall -Werror -Wextra

LIB_FLAG = -shared -fPIC

SFML_FLAGS = -I ~/.brew/Cellar/sfml/2.2/include

HEADER = lib_sfml.class.hpp

SRC =	../Api.class.cpp \
		lib_sfml.class.cpp			

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	$(CLANG) $(CFLAGS) $(SFML_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(LIB_FLAG) $(SFML_FLAGS) -o $(NAME) $(OBJ) $(GL)

run:
	$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
