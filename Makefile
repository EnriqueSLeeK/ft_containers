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
CFLAGS := -g -Wall -Wextra -Werror -std=c++98 -Iinclude -Itest_templates

SRC := main.cpp

SRC_VECTOR := vector_main.cpp vector_test.cpp

SRC_SET := set_main.cpp
SRC_MAP := map_main.cpp

OBJ := $(SRC:cpp=o)
OBJ_VEC := $(SRC_VECTOR:cpp=o)
OBJ_MM := $(SRC_MAP:cpp=o)
OBJ_SETT := $(SRC_SET:cpp=o)

DIR_OBJ := ./obj/
OBJ_M := $(addprefix $(DIR_OBJ), $(OBJ))
OBJ_MAP := $(addprefix $(DIR_OBJ), $(OBJ_MM))
OBJ_SET := $(addprefix $(DIR_OBJ), $(OBJ_SETT))
OBJ_V := $(addprefix $(DIR_OBJ), $(OBJ_VEC))

VPATH := ./src/ \
		 ./test_templates/

all: $(OBJ_M) curr_test

$(DIR_OBJ)%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

curr_test: $(OBJ_M)
	$(CC) $(CFLAGS) $(OBJ_M) -o curr_test

intra_test: $(OBJ_M)
	$(CC) $(CFLAGS) $(OBJ_M) -o intra_test

vtest: $(OBJ_V)
	$(CC) $(CFLAGS) $(OBJ_V) -o vector_test
	
mtest: $(OBJ_MAP)
	$(CC) $(CFLAGS) $(OBJ_MAP) -o map_test

stest: $(OBJ_SET)
	$(CC) $(CFLAGS) $(OBJ_SET) -o set_test
	
test: mtest vtest stest intra_test

re: clean curr_test

clean:
	rm -rf curr_test
	rm -rf vector_test
	rm -rf map_test
	rm -rf set_test
	rm -rf $(DIR_OBJ)
