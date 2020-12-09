# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 20:20:36 by jeldora           #+#    #+#              #
#    Updated: 2020/12/09 12:45:21 by jeldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		clang++
NAME1 =		stack_test
NAME2 =		queue_test
FLAGS =		-Wall -Wextra -Werror -g -std=c++98 -o
SRCS_1 =	stack_test.cpp 
SRCS_2 =	queue_test.cpp 
HEADERS =	vector.hpp stack.hpp list.hpp queue.hpp map.hpp

all: $(NAME1)
	
$(NAME1): $(SRCS_1) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME1) $(SRCS_1)
	@./$(NAME1)

$(NAME2): $(SRCS_2) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME2) $(SRCS_2)
	@./$(NAME2)
clean:
	rm -fr $(NAME1) $(NAME1).dSYM
	rm -fr $(NAME2) $(NAME2).dSYM
re: clean all