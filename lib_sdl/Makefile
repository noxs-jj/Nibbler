#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoiroux <jmoiroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/27 12:42:13 by jmoiroux          #+#    #+#              #
#    Updated: 2015/03/27 12:42:14 by jmoiroux         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CLANG =		clang++

NAME =		lib_sdl_2d.so

NAME_TEST =	test_sdl

GL =		-framework opengl

CFLAGS =	-Wall -Werror -Wextra

LIB_FLAG =	-shared -fPIC

HEADER =	sdl.class.hpp

SRC =		../src/Api.class.cpp sdl.class.cpp

OBJ =		$(SRC:.cpp=.cpp.o)



%.cpp.o: %.cpp
	@$(CLANG) $(CFLAGS) `sdl2-config --cflags` -c $< -o $@

all: $(NAME)

# brew update && brew install SDL2 && reset
$(NAME): $(OBJ) $(HEADER)
	@$(CLANG) $(CFLAGS) $(LIB_FLAG) `sdl2-config --libs` -o $(NAME) $(OBJ) $(GL)

extract:
	@brew update && brew install sdl

run:
	@$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

test:
	@clear ; $(CLANG) -Wall -Werror -Wextra -stdlib=libc++ -w -o $(NAME_TEST) \
	sdl.class.cpp ../Api.class.cpp main_test.cpp \
	`sdl2-config --libs` `sdl2-config --cflags` \
	-framework opengl

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
