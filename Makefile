CXX	:=	clang++
CFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I include -I third_party

SRC	:=	src/main.cpp

OBJ	:=	$(SRC:.cpp=.o)

BINARY	:=	cartridge

all:	$(BINARY)

$(BINARY):	$(OBJ)
	$(CXX) -o $(BINARY) $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
