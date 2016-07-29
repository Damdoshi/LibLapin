## -----------------------------------------------------------------------------
## --Jason Brillante 2015-2016 ------------ ---   -   --- ---- --  --   - --- --
## ---------------------------------------- ---- --- - -- --- - - - -- --  -- --
## ---------------------------------------- ---- --- - -- --- - - - -- --  -- --
## -----|\-//------------------------------ ---- ---   -- --- - -  --- -- - - --
## -----||//___---------------------------- ---- --- - -- ---   - ---- -- - - --
## ----O  /    \--------------------------- ---- --- - -- --- - - ---- -- --  --
## ---<________/---------------------------   -   -   ---   - - - ---   - --- --
## -----------------------------------------------------------------------------

LIBNAME		=	lapin
NAME		=	lib$(LIBNAME).a
ERRLOG		=	errors~

CC		=	g++
FLAGS		=	-W -Wall -Werror		\
			-fPIC -std=gnu++03		\
			-D_GLIBCXX_USE_CXX11_ABI=0	\
			-fnothrow-opt			\
			-Wno-unused-result -std=c++11
#FLAGS		+=	-g -g3 -ggdb -D BUNNY_ALLOCATOR_DEACTIVATED
FLAGS		+=	-O2

## Define some stuff
ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

## Source
INC		=	-I./include/			\
			-I./include/dep/		\
			-I/home/${USER}/.froot/include/
SRC		=	$(wildcard ./dep/*/*.cpp)	\
			$(wildcard ./bas/*.cpp)		\
			$(wildcard ./adv/*.cpp)		\
			$(wildcard ./ext/*.cpp)
OBJ		=	$(SRC:.cpp=.o)

#all:		title erase $(NAME) anim
all:		title erase $(NAME)
all-quiet:	$(NAME)
title:
		@$(ECHO) $(GREEN)LIB$(TEAL)LAPIN$(DEFAULT)
erase:
		@rm -f $(ERRLOG)
clean:		erase
		@rm -f $(OBJ)
fclean:		clean
		@rm -f $(NAME)
re:		fclean all
anim:
		@./bunny.sh

## Compile ---------------------------------------------------------------------
$(NAME):	$(OBJ)
		@ar r $(NAME) $(OBJ) 2>> $(ERRLOG) && \
		 $(ECHO) $(GREEN) "[AR]" $(TEAL) $(NAME) $(DEFAULT) || \
		 $(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)
		@ranlib $(NAME) && \
		 $(ECHO) $(GREEN) "[OK]" $(TEAL) $(NAME) $(DEFAULT) || \
		 $(ECHO) $(RED) "[XX]" $(TEAL) $(NAME)
.cpp.o:
		@$(CC) $(INC) $(FLAGS) -c $< -o $@ 2>> $(ERRLOG) && \
		 $(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

