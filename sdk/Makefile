CXX	:=	clang++
CXXFLAGS	:=	-Wall -Wextra -std=c++20
CPPFLAGS	:=	-I ../third_party

ifeq ($(ENV), dev)
	CXXFLAGS	+=	-g3
endif

SDK_SRC	:=	main.cpp \
			Header.cpp \
			Arguments.cpp \
			Build.cpp \
			Convert.cpp

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

move:
	mv $(BINARY) ../

.PHONY:	all clean fclean re move
