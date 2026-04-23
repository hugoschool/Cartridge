CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I include -I third_party

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

SRC	:=	src/main.cpp \
		src/Header.cpp \
		src/Arguments.cpp

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
