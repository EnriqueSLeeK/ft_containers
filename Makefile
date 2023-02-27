# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 18:41:03 by ensebast          #+#    #+#              #
#    Updated: 2023/01/28 21:11:25 by ensebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := intra_test

CC := c++
CFLAGS := -g -Wall -Wextra -Werror -std=c++98 -Iinclude -Itest_templates

SRC_FUNC_TEST := functionality_test_main.cpp \
					print_result.cpp \
					map_main.cpp \
					vector_main.cpp \
					stack_main.cpp \
					set_main.cpp
					
SRC_TIME_TEST := performance_test_main.cpp

SRC_INTRA := intra_main.cpp

OBJ_FUNC := $(SRC_FUNC_TEST:cpp=o)
OBJ_INTRA := $(SRC_INTRA:cpp=o)

DIR_OBJ := ./obj/
OBJ_FUNCTIONALITY := $(addprefix $(DIR_OBJ), $(OBJ_FUNC))
OBJ_TIME := $(addprefix $(DIR_OBJ), $(SRC_TIME_TEST:cpp=o))

OBJ_INTRAA := $(addprefix $(DIR_OBJ), $(OBJ_INTRA))

VPATH := ./src/ \
		 ./test_templates/

all: $(OBJ_FUNCTIONALITY) functionality_test time_test

$(DIR_OBJ)%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

functionality_test: $(OBJ_FUNCTIONALITY)
	$(CC) $(CFLAGS) $(OBJ_FUNCTIONALITY) -o functionality_test

time_test: $(OBJ_TIME)
	$(CC) $(CFLAGS) $(OBJ_TIME) -o time_test

$(NAME): $(OBJ_INTRAA)
	$(CC) $(CFLAGS) $(OBJ_INTRAA) -o $(NAME)

test: functionality_test time_test intra

re: clean functionality_test time_test

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -f intra_test
	rm -f time_test
	rm -f functionality_test