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

CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -Iinclude -Itest_templates

SRC := main.cpp

SRC_VECTOR := vector_main.cpp print_result.cpp

SRC_STACK := stack_main.cpp print_result.cpp

SRC_SET := set_main.cpp
SRC_MAP := map_main.cpp

SRC_INTRA := intra_main.cpp

OBJ := $(SRC:cpp=o)
OBJ_VEC := $(SRC_VECTOR:cpp=o)
OBJ_MM := $(SRC_MAP:cpp=o)
OBJ_SETT := $(SRC_SET:cpp=o)
OBJ_STACK := $(SRC_STACK:cpp=o)
OBJ_INTRA := $(SRC_INTRA:cpp=o)

DIR_OBJ := ./obj/
OBJ_M := $(addprefix $(DIR_OBJ), $(OBJ))
OBJ_MAP := $(addprefix $(DIR_OBJ), $(OBJ_MM))
OBJ_SET := $(addprefix $(DIR_OBJ), $(OBJ_SETT))

OBJ_V := $(addprefix $(DIR_OBJ), $(OBJ_VEC))
OBJ_STACKK := $(addprefix $(DIR_OBJ), $(OBJ_STACK))

OBJ_INTRAA := $(addprefix $(DIR_OBJ), $(OBJ_INTRA))

VPATH := ./src/ \
		 ./test_templates/

all: $(OBJ_M) curr_test

$(DIR_OBJ)%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

curr_test: $(OBJ_M)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_M) -o curr_test

intra: $(OBJ_INTRAA)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_INTRAA) -o intra_test

vtest: $(OBJ_V)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_V) -o vector_test
	
mtest: $(OBJ_MAP)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_MAP) -o map_test

stest: $(OBJ_SET)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_SET) -o set_test

sktest: $(OBJ_STACKK)
	@mkdir -p test
	$(CC) $(CFLAGS) $(OBJ_STACKK) -o stack_test
	
test: mtest vtest stest intra_test sktest

re: clean curr_test

clean:
	rm -f stack_test
	rm -f curr_test
	rm -f vector_test
	rm -f intra_test
	rm -f map_test
	rm -f set_test
	rm -rf test
	rm -rf $(DIR_OBJ)
