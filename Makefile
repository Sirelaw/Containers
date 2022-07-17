NAME = containers

CC = c++

FLAGS = -std=c++98 -Wall -Wextra -g3 #-Werror 

SRC_DIR = ./
OBJ_DIR = ./obj/
INC_DIR = ./

SRC_FILES =  main.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all : $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(INC_DIR)*.hpp
	@$(CC) $(FLAGS) -I $(INC_DIR) -o $@ -c $<
	@echo updated $@

$(NAME) : obj $(OBJ)
	@echo ".o files updated!...linking..."
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) executable compiled!"

SRC_FILES1 =  main1.cpp
SRC_FILES2 =  main2.cpp
SRC_FILES3 =  main3.cpp

main1:
	@c++ main1.cpp -c
	@$(CC) $(FLAGS) main1.o -o $(NAME)
	@echo "$(NAME) executable compiled for main1!"


main2:
	@c++ main2.cpp -c
	@$(CC) $(FLAGS) main2.o -o $(NAME)
	@echo "$(NAME) executable compiled for main2!"

main3:
	@c++ main3.cpp -c
	@$(CC) $(FLAGS) main3.o -o $(NAME)
	@echo "$(NAME) executable compiled for main3!"

main4:
	@c++ main4.cpp -c
	@$(CC) $(FLAGS) main4.o -o $(NAME)
	@echo "$(NAME) executable compiled for main4!"

vector_test_ft:
	@c++ vector_test.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) vector_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for FT_vector_test!"
	@./containers

vector_test_std:
	@c++ vector_test.cpp -c $(FLAGS) -DFT=0
	@$(CC) $(FLAGS) vector_test.o -o $(NAME)
	@echo "$(NAME) executable compiled for STD_vector_test!"
	@./containers

map_test_ft:
	@c++ set_tester.cpp -c $(FLAGS) -DFT=1
	@$(CC) $(FLAGS) set_tester.o -o $(NAME)
	@echo "$(NAME) executable compiled for FT_map_test!"
	@./containers

map_test_std:
	@c++ set_tester.cpp -c $(FLAGS) -DFT=0
	@$(CC) $(FLAGS) set_tester.o -o $(NAME)
	@echo "$(NAME) executable compiled for STD_map_test!"
	@./containers


obj:
	@mkdir -p $(OBJ_DIR)

clean :
	cd $(OBJ_DIR) && rm -rf $(OBJ_FILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all