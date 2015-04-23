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
	@$(CLANG) $(CFLAGS) -Isdl2/2.0.3/include/SDL2 -D_THREAD_SAFE -c $< -o $@

all: $(NAME)

$(NAME): extract $(OBJ) $(HEADER)
	@$(CLANG) $(CFLAGS) $(LIB_FLAG) -Lsdl2/2.0.3/lib -lSDL2 -o $(NAME) $(OBJ) $(GL)

extract:
	curl -o sdl2.tar.bz2 http://www.noxs.net/42project/resources/sdl2.tar.bz2
	tar jxf sdl2.tar.bz2
	rm sdl2.tar.bz2

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
	@rm -rf sdl2

re: fclean all

.PHONY: all clean fclean re
