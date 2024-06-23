#################################################################################

 ###############################################################################
 ## Jason Brillante "Damdoshi"                  Hanged Bunny Studio 2014-2024 ##
 ## Pentacle Technologie 2008-2024                           EFRITS 2022-2024 ##
 ## "MyLib" V9.12                                                             ##
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
  LAPINOPTS	=	-DBUNNY_COMPILATION					\
			-DBUNNY_ALLOCATOR_DEACTICATED
  MODE		=	debug
#  MODE		=	release

#################################################################################
## Building details                                                            ##
#################################################################################

  LINKER	?=	ar rcs
  COMPILER	?=	g++
  STANDARD	?=	-std=c++14
  WARNINGS	=	-W -Wall						\
			-Wno-write-strings					\
			-Wno-unused-result					\
			-Wno-format-security					\
			-Wno-frame-address					\
			-Wno-narrowing						\
			-Wno-cast-function-type

  DEBUGOPTS	=	-O0 -g -g3 -ggdb -fprofile-arcs -ftest-coverage		\
			--coverage -fno-omit-frame-pointer -fno-align-functions	\
			-fno-align-loops
  RELEASEOPTS	=	-O3 -ffast-math -march=native -DNDEBUG

  ifeq ($(MODE), debug)
    MODEOPTS	=	$(DEBUGOPTS)
  else
    MODEOPTS	=	$(RELEASEOPTS)
  endif

  RM		=	rm -f
  ECHO		=	/bin/echo -e
  LOGDIR	=	errors/

  DEFAULT	=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Source                                                                      ##
#################################################################################

  HEADER	=	-I./include						\
			-I./include/deps/					\
			-I./external/include/					\
			-I/opt/local/include/					\
			-I/usr/include/opencv4/
  SRC		=	$(shell find src/ -name "*.cpp")
  OBJ		=	$(SRC:.cpp=.o)

#################################################################################
## Rules                                                                       ##
#################################################################################

  CXXFLAGS	=	$(STANDARD) $(WARNINGS) -fPIC $(LAPINOPTS) $(MODEOPTS)	\
			$(HEADER)

all:			erase $(NAME) tests
tests:
			(cd tests/ && $(MAKE))
$(NAME):		title $(OBJ)
			@$(LINKER) $(NAME) $(OBJ) 2>> $(LOGDIR)/$(NAME) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(NAME) $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $(NAME) $(DEFAULT)
			@find $(LOGDIR)/$(NAME) -size 0 -delete || true
.cpp.o:
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $< -o $@ $(CXXFLAGS)			\
			 $(HEADER) 2>> $(TRACE) &&				\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true

#################################################################################
## Misc                                                                        ##
#################################################################################

title:
			@$(ECHO) $(TEAL) $(TITLE) $(DEFAULT)
			@mkdir -p $(LOGDIR)
clean:
			@$(RM) $(OBJ) &&					\
			 $(ECHO) $(GREEN) "Object file deleted" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in clean rule!" $(DEFAULT)
fclean:			clean erase
			@$(RM) $(NAME) &&					\
			 $(ECHO) $(GREEN) "Program deleted!" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in fclean rule!" $(DEFAULT)
re:			fclean all
erase:
			@$(RM) -r $(LOGDIR)/*.*

.POSIX:
.PHONY:			tests
