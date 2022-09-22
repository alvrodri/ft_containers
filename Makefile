# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/12 17:35:33 by alvrodri          #+#    #+#              #
#    Updated: 2022/09/22 11:36:10 by alvrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex00

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CXX = clang++
CXXFLAGS = -fsanitize=address -g3 -I ./containers_test/srcs/vector -I .

$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re