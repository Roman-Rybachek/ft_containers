# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 20:20:36 by jeldora           #+#    #+#              #
#    Updated: 2020/11/29 00:56:02 by jeldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		clang++
NAME =		ft_containers
FLAGS =		-Wall -Wextra -Werror -g -std=c++98 -o $(NAME)
SRCS =		main.cpp 
HEADERS =	vector.hpp stack.hpp list.hpp queue.hpp

all: $(NAME)
	
$(NAME): $(SRCS) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(SRCS)
	#@./$(NAME)
clean:
	rm -f $(NAME)