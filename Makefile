NAME = containers

CC = c++

FLAGS = -std=c++98 -Wall -Wextra -Werror 

SRC_DIR = ./
OBJ_DIR = ./obj/
INC_DIR1 = ./src/
INC_DIR2 = ./src/base/
INC_DIR3 = ./src/iterators/
INC_DIR4 = ./src/utils/

SRC_FILES =  main.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_FILES =  $(INC_DIR1)Map.hpp $(INC_DIR1)Pair.hpp $(INC_DIR1)Set.hpp\
			$(INC_DIR1)Stack.hpp $(INC_DIR1)Vector.hpp \
			$(INC_DIR2)Node.hpp $(INC_DIR2)RBTree.hpp\
			$(INC_DIR3)IteratorTraits.hpp $(INC_DIR3)reverse_iterator.hpp\
			$(INC_DIR3)TreeIterator.hpp $(INC_DIR3)VecIterator.hpp\
			$(INC_DIR4)Algorithm.hpp $(INC_DIR4)type_traits.hpp\
			$(INC_DIR4)utils.hpp $(INC_DIR4)verbose.hpp

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_FILES)
	@$(CC) $(FLAGS) -I $(INC_DIR1) -I $(INC_DIR2) -I $(INC_DIR3) -I $(INC_DIR4) -o $@ -c $<

$(NAME) : obj $(OBJ)
	@echo ".o files updated!...linking..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) executable compiled!"

vector_test_ft:
	@c++ ./my_tests/vector_test.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) vector_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for FT_vector_test!"
	@./containers

vector_test_std:
	@c++ ./my_tests/vector_test.cpp -c $(FLAGS) -DFT=0
	@$(CC) $(FLAGS) vector_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for STD_vector_test!"
	@./containers

map_test_ft:
	@c++ ./my_tests/map_test.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) map_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for FT_map_test!"
	@./containers

map_test_std:
	@c++ ./my_tests/map_test.cpp -c $(FLAGS) -DFT=0
	@$(CC) $(FLAGS) map_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for STD_map_test!"
	@./containers

set_test_ft:
	@c++ ./my_tests/set_test.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) set_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for FT_set_test!"
	@./containers

set_test_std:
	@c++ ./my_tests/set_test.cpp -c $(FLAGS) -DFT=0
	@$(CC) $(FLAGS) set_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for STD_set_test!"
	@./containers

vec_iter_relation:
	@c++ ./my_tests/vec_iter_relation.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) vec_iter_relation.o -o $(NAME)
	@echo "$(NAME) executable compiled for vector_iter_relation_test!"
	@./containers

obj:
	@mkdir -p $(OBJ_DIR)

clean :
	cd $(OBJ_DIR) && rm -rf $(OBJ_FILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all