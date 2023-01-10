# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 18:41:03 by ensebast          #+#    #+#              #
#    Updated: 2023/01/10 00:11:01 by ensebast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := c++
CFLAGS := -g -Wall -Wextra -Werror -std=c++98 -Iinclude -Itest_templates

SRC := main.cpp

SRC_VECTOR := vector_main.cpp vector_test.cpp

OBJ := $(SRC:cpp=o)
OBJ_VEC := $(SRC_VECTOR:cpp=o)

DIR_OBJ := ./obj/
OBJ_M := $(addprefix $(DIR_OBJ), $(OBJ))
OBJ_V := $(addprefix $(DIR_OBJ), $(OBJ_VEC))

VPATH := ./src/ \
		 ./test_templates/

all: $(OBJ_M) intra_test

$(DIR_OBJ)%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

intra_test: $(OBJ_M)
	$(CC) $(CFLAGS) $(OBJ_M) -o curr_test

vtest: $(OBJ_V)
	$(CC) $(CFLAGS) $(OBJ_V) -o vector_test

re: clean $(NAME)

clean:
	rm -rf curr_test
	rm -rf vector_test
	rm -rf $(DIR_OBJ)
