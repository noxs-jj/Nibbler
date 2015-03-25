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

CLANG = clang++

NAME = lib_opengl_2D.so

GL = -framework GLUT -framework OpenGL -framework Cocoa

CFLAGS = -Wall -Werror -Wextra -o3 -stdlib=libc++ -w

LIB_FLAG = -shared -fPIC

SRC = 	api.class.cpp \
		opengl_2D.class.cpp \
		main_test.cpp

OBJ = $(SRC:.cpp=.cpp.o)

%.cpp.o: %.cpp
	$(CLANG) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CLANG) $(CFLAGS) $(LIB_FLAG) -o $(NAME) $(SRC) $(GL)

run:
	$(CLANG) $(CFLAGS) -o run_test $(NAME) $(GL)

test:
	$(CLANG) $(CFLAGS) -o test_main $(SRC) $(GL)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
