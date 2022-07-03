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



obj:
	@mkdir -p $(OBJ_DIR)

clean :
	cd $(OBJ_DIR) && rm -rf $(OBJ_FILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all