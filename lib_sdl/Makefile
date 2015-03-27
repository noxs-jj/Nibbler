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

CLANG = clang++

NAME = lib_opengl_2D.so
NAME_TEST = test_sdl

GL = -framework SDL -framework Cocoa

CFLAGS = -Wall -Werror -Wextra -stdlib=libc++ -w

LIB_FLAG = -shared -fPIC

SRC =	sdl.class.cpp \
		main_test.cpp \
		../Api.class.cpp

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	$(CLANG) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CLANG) $(CFLAGS) $(LIB_FLAG) -o $(NAME) $(SRC) $(GL)

run:
	$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

test:
	clear ; $(CLANG) -Wall -Werror -Wextra -stdlib=libc++ -w -o $(NAME_TEST) $(SRC) \
	`sdl-config --libs` `sdl-config --cflags` \
	-framework opengl

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
