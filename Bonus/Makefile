##
## EPITECH PROJECT, 2024
## make
## File description:
## file
##

SRC =	src/*.cpp

SRC1 = src/Error.cpp\
	 	src/open_wave.cpp

NAME =	stone_analysis

TEST =	tests/test_project.cpp

all:
		g++ $(SRC) -o $(NAME) -g3 -lsfml-graphics -lsfml-system -lsfml-window

clean:
	rm -f *#
	rm -f *~
	rm -f *.o
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all

unit_tests: fclean
			g++ -o unit_tests $(SRC1) $(TEST) -lcriterion --coverage

tests_run:	unit_tests
			./unit_tests
