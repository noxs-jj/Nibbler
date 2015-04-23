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

CLANG = clang++

NAME = lib_sfml_2d.so

DIR_SFML = sfml/2.2

GL =	-framework opengl \
		$(DIR_SFML)/lib/libsfml-graphics.2.2.0.dylib \
		$(DIR_SFML)/lib/libsfml-window.2.2.0.dylib \
		$(DIR_SFML)/lib/libsfml-system.2.2.0.dylib \
		-L $(DIR_SFML)/lib -Wl,-rpath,$(DIR_SFML)/lib \
		-Wl,-rpath,lib_sfml/sfml/2.2/lib

CFLAGS = -Wall -Werror -Wextra

LIB_FLAG = -shared -fPIC

SFML_FLAGS = -I $(DIR_SFML)/include

HEADER = lib_sfml.class.hpp

SRC =	../src/Api.class.cpp lib_sfml.class.cpp

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	@$(CLANG) $(CFLAGS) $(SFML_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): extract $(OBJ) $(HEADER)
	@$(CLANG) $(CFLAGS) $(LIB_FLAG) $(SFML_FLAGS) -o $(NAME) $(OBJ) $(GL)

extract:
	@curl -o sfml.tar.bz2 http://www.noxs.net/42project/resources/sfml.tar.bz2
	@tar jxf sfml.tar.bz2
	@rm sfml.tar.bz2

run:
	$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

clean:
	@rm -rf $(OBJ)
	@rm -rf sfml

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
