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
 ##                          - LibLapin project -                             ##
 ##                                                                           ##
 ###############################################################################

#################################################################################
## Information about the project                                               ##
#################################################################################

  NAME		=	liblapin_project
  TITLE		=	'"LIBLAPIN PROJECT"'
  FREQUENCY	=	20

#################################################################################
## Building details                                                            ##
#################################################################################

  LINKER	?=	gcc
  COMPILER	?=	gcc

  CONFIG	=	-W -Wall -Werror					\
			-D_GLIBCXX_USE_CXX11_ABI=0 -Wno-unused-result		\
			-DBUNNY_TITLE=$(TITLE)					\
			-DBUNNY_FREQUENCY=$(FREQUENCY)
  DEBUG		=	-O0 -g -g3 -ggdb -DBUNNY_ALLOCATOR_DEACTIVATED
  OPTIM		=	-O2

  RM		=	rm -f
  ECHO		=	/bin/echo -e
  LOGFILE	=	errors~
  ERRLOG	=	2>> $(LOGFILE)

  HEADER	=	-I./include						\
			-I${HOME}/.froot/include/

  DEFAULT	=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Source                                                                      ##
#################################################################################

  SRC		=	$(wildcard ./src/*.c)
  OBJ		=	$(SRC:.c=.o)

  LIB		=	-L${HOME}/.froot/lib/					\
			-llapin							\
			-lsfml-audio						\
			-lsfml-graphics						\
			-lsfml-window						\
			-lsfml-system						\
			-lpthread						\
			-lusb							\
			-lm							\
			-lstdc++

#################################################################################
## Rules                                                                       ##
#################################################################################

all:			erase $(NAME)
$(NAME):		title $(OBJ)
			@$(LINKER) $(LIB) -o $(NAME) $(OBJ) $(LIB) $(ERRLOG) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(NAME) $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $(NAME) $(DEFAULT)
.c.o:
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
