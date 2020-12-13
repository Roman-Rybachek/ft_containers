# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 20:20:36 by jeldora           #+#    #+#              #
#    Updated: 2020/12/13 19:38:28 by jeldora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		clang++ 
FLAGS =		-Wall -Wextra -Werror -o

NAME1 =		stack_test
NAME2 =		queue_test
NAME3 =		vector_test
NAME4 =		list_test
NAME5 =		map_test
SRCS_1 =	stack_test.cpp 
SRCS_2 =	queue_test.cpp 
SRCS_3 =	vector_test.cpp 
SRCS_4 =	list_test.cpp 
SRCS_5 =	map_test.cpp 
HEADERS =	vector.hpp stack.hpp list.hpp queue.hpp map.hpp

all: $(NAME5) $(NAME4) $(NAME3) $(NAME2) $(NAME1)
	
$(NAME1): $(SRCS_1) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME1) $(SRCS_1)
	@./$(NAME1)

$(NAME2): $(SRCS_2) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME2) $(SRCS_2)
	@./$(NAME2)

$(NAME3): $(SRCS_3) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME3) $(SRCS_3)
	@./$(NAME3)
	
$(NAME4): $(SRCS_4) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME4) $(SRCS_4)
	@./$(NAME4)

$(NAME5): $(SRCS_5) Makefile $(HEADERS)
	@$(CC) $(FLAGS) $(NAME5) $(SRCS_5)
	@./$(NAME5)

clean:
	rm -fr $(NAME1) 
	rm -fr $(NAME2) 
	rm -fr $(NAME3) 
	rm -fr $(NAME4) 
	rm -fr $(NAME5) 
re: clean all