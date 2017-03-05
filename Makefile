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

  CONFIG	=	-W -Wall -fPIC						\
			-Wno-unused-result					\
			-DBUNNY_ALLOCATOR_DEACTIVATED				\
			-DBUNNY_DEBUG -DBUNNY_LOG

  DEBUG		=	-O0 -g -g3 -ggdb
#  OPTIM		=	-O2

  RM		=	rm -f
  ECHO		=	/bin/echo -e
  LOGFILE	=	errors~
  ERRLOG	=	2>> $(LOGFILE)

  HEADER	=	-I./include						\
			-I./include/deps/					\
			-I./external/include/

  DEFAULT	=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Source                                                                      ##
#################################################################################

  SRC		=	$(wildcard ./src/allocator/*.cpp)			\
			$(wildcard ./src/configuration/*.cpp)			\
			$(wildcard ./src/configuration/archive/*.cpp)		\
			$(wildcard ./src/configuration/ini/*.cpp)		\
			$(wildcard ./src/configuration/dabsic/*.cpp)		\
			$(wildcard ./src/configuration/xml/*.cpp)		\
			$(wildcard ./src/configuration/lua/*.cpp)		\
			$(wildcard ./src/events/*.cpp)				\
			$(wildcard ./src/graphics/*.cpp)			\
			$(wildcard ./src/hardware/*.cpp)			\
			$(wildcard ./src/misc/*.cpp)				\
			$(wildcard ./src/network/*.cpp)				\
			$(wildcard ./src/sound/*.cpp)				\
			$(wildcard ./src/threads/*.cpp)				\
			$(wildcard ./src/window/*.cpp)				\
			$(wildcard ./src/security/*.cpp)			\
			$(wildcard ./src/asynclock/*.cpp)			\
			$(wildcard ./src/database/*.cpp)			\
			$(wildcard ./src/text/*.cpp)				\
			$(wildcard ./src/plugin/*.cpp)				\
			$(wildcard ./src/collide/*.cpp)				\
			$(wildcard ./src/hash/*.cpp)				\
			$(wildcard ./src/deps/*/*.cpp)
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
