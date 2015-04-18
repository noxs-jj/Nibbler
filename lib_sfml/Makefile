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
# CREATE 	tar -jcf graphics_libs.tar.bz2 graphics_libs

# EXTRACT	tar -jxf graphics_libs.tar.bz2

# curl -o graphics_libs.tar.bz2 http://www.noxs.net/42project/resources/graphics_libs.tar.bz2

# LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L $(SFML)/lib -Wl,-rpath=$(SFML)/lib -Wl,-rpath-link=$(SFML)/lib

CLANG = clang++

NAME = lib_sfml_2d.so

# GL = -framework opengl -L ~/.brew/Cellar/sfml/2.2/lib -lsfml-graphics -lsfml-window -lsfml-system

DIR_SFML = ../graphics_libs/sfml/2.2

GL =	-framework opengl \
		$(DIR_SFML)/lib/libsfml-graphics.2.2.0.dylib \
		$(DIR_SFML)/lib/libsfml-window.2.2.0.dylib \
		$(DIR_SFML)/lib/libsfml-system.2.2.0.dylib \
		-L $(DIR_SFML)/lib -Wl,-rpath,$(DIR_SFML)/lib

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

$(NAME): extract $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(LIB_FLAG) $(SFML_FLAGS) -o $(NAME) $(OBJ) $(GL)

extract:
	curl -o graphics_libs.tar.bz2 http://www.noxs.net/42project/resources/graphics_libs.tar.bz2
	tar -jxf graphics_libs.tar.bz2
	mv graphics_libs ../
	rm graphics_libs.tar.bz2

run:
	$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
