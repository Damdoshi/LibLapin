#################################################################################

 ###############################################################################
 ## Jason Brillante "Damdoshi"                                                ##
 ## Hanged Bunny Studio 2014-2016                                             ##
 ##                                                                           ##
 ## ------------------------------------------------------------------------- ##
 ## ------------------------------------ ---   -   --- ---- --  --   - --- -- ##
 ## ------------------------------------ ---- --- - -- --- - - - -- --  -- -- ##
 ## -----|\-//-------------------------- ---- ---   -- --- - -  --- -- - - -- ##
 ## -----||//___------------------------ ---- --- - -- ---   - ---- -- - - -- ##
 ## ----O  /    \----------------------- ---- --- - -- --- - - ---- -- --  -- ##
 ## ---<________/-----------------------   -   -   ---   - - - ---   - --- -- ##
 ## ------------------------------------------------------------------------- ##
 ##                                                                           ##
 ##                              - LibLapin -                                 ##
 ##                                                                           ##
 ###############################################################################

#################################################################################
## Information about the project                                               ##
#################################################################################

  NAME		=	liblapin.a
  TITLE		=	"LIBLAPIN - BUNNY LIBRARY"

#################################################################################
## Building details                                                            ##
#################################################################################

  LINKER	?=	ar rcs
  COMPILER	?=	g++

  CONFIG	=	-W -Wall -Werror -fPIC -std=gnu++03			\
			-D_GLIBCXX_USE_CXX11_ABI=0 -Wno-unused-result
  DEBUG		=	-O0 -g -g3 -ggdb -DBUNNY_ALLOCATOR_DEACTIVATED
  OPTIM		=	-O2

  RM		=	rm -f
  ECHO		=	/bin/echo -e
  LOGFILE	=	errors~
  ERRLOG	=	2>> $(LOGFILE)

  HEADER	=	-I./include -I./include/dep/				\
			-I${HOME}/.froot/include/

  DEFAULT	=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Source                                                                      ##
#################################################################################

  SRC		=	$(wildcard ./allocator/*.cpp)				\
			$(wildcard ./configuration/*.cpp)			\
			$(wildcard ./events/*.cpp)				\
			$(wildcard ./graphics/*.cpp)				\
			$(wildcard ./hardware/*.cpp)				\
			$(wildcard ./misc/*.cpp)				\
			$(wildcard ./network/*.cpp)				\
			$(wildcard ./sound/*.cpp)				\
			$(wildcard ./threads/*.cpp)				\
			$(wildcard ./window/*.cpp)				\
			$(wildcard ./dep/*/*.cpp)
  OBJ		=	$(SRC:.cpp=.o)

#################################################################################
## Rules                                                                       ##
#################################################################################

all:			erase $(NAME)
$(NAME):		title $(OBJ)
			@$(LINKER) $(NAME) $(OBJ) $(ERRLOG) &&			\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(NAME) $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $(NAME) $(DEFAULT)
.cpp.o:
			@$(COMPILER) -c $< -o $@ $(DEBUG) $(OPTIM) $(CONFIG)	\
			 $(HEADER) $(ERRLOG) &&					\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $< $(DEFAULT)

#################################################################################
## Misc                                                                        ##
#################################################################################

title:
			@$(ECHO) $(TEAL) $(TITLE) $(DEFAULT)
clean:
			find . -name "*.o" -delete
			@$(RM) $(OBJ) &&					\
			 $(ECHO) $(GREEN) "Object file deleted" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in clean rule!" $(DEFAULT)
fclean:			clean
			@$(RM) $(NAME) &&					\
			 $(ECHO) $(GREEN) "Program deleted!" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in fclean rule!" $(DEFAULT)
re:			fclean all
erase:
			@$(RM) $(LOGFILE)
