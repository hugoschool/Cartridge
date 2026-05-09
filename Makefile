CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I third_party

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

SDK_SRC	:=	sdk/main.cpp \
			sdk/Header.cpp \
			sdk/Arguments.cpp \
			sdk/Build.cpp

SDK_OBJ	:=	$(SDK_SRC:.cpp=.o)

BINARY	:=	cartridge

all:	$(BINARY)

$(BINARY):	$(SDK_OBJ)
	$(CXX) -o $(BINARY) $(SDK_OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(SDK_OBJ)

fclean:	clean
	$(RM) $(BINARY)

re:	fclean all

.PHONY:	all clean fclean re
