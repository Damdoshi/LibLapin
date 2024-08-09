#################################################################################

 ###############################################################################
 ## Jason Brillante "Damdoshi"                  Hanged Bunny Studio 2014-2024 ##
 ## Pentacle Technologie 2008-2024                           EFRITS 2022-2024 ##
 ## "MyLib" V9.14                                                             ##
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

  NAME		=	lapin
  PRODSO	=	lib$(NAME).so
  PRODA		=	lib$(NAME).a
  DBGSO		=	lib$(NAME)-dbg.so
  DBGA		=	lib$(NAME)-dbg.a

  TITLE		=	"LIBLAPIN - BUNNY LIBRARY"
  LAPINOPTS	=	-DBUNNY_COMPILATION					\
			-DBUNNY_ALLOCATOR_DEACTICATED

#################################################################################
## Building details                                                            ##
#################################################################################

  ALINKER	?=	ar rcs
  SOLINKER	?=	g++ -shared
  COMPILER	?=	g++
  STANDARD	?=	-std=gnu++17
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
  PRODOPTS	=	-O3 -ffast-math -march=native -DNDEBUG

#################################################################################
## Source                                                                      ##
#################################################################################

  HEADER	=	-I./include						\
			-I./include/lapin/deps/					\
			-I./external/include/					\
			-I/opt/local/include/					\
			-I/usr/include/opencv4/
  SRC		=	$(shell find src/ -name "*.cpp")
  DBGSRC	=	$(shell find src/ -name "*.cpp")
  OBJ		=	$(SRC:.cpp=.o)
  DBGOBJ	=	$(DBGSRC:.cpp=-dbg.o)

#################################################################################
## Misc                                                                        ##
#################################################################################

  RM		=	rm -f
  ECHO		=	/bin/echo -e
  LOGDIR	=	errors/
  DEFAULT	=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Rules                                                                       ##
#################################################################################

  PRODFLAGS	=	$(STANDARD) $(WARNINGS) -fPIC $(LAPINOPTS) $(HEADER) $(PRODOPTS)
  DBGFLAGS	=	$(STANDARD) $(WARNINGS) -fPIC $(LAPINOPTS) $(HEADER) $(DEBUGOPTS)

all:			erase title $(PRODSO) $(PRODA) $(DBGSO) $(DBGA)
tests:			$(DBGA)
			(cd tests/ && $(MAKE))
$(PRODSO):		$(OBJ)
			@$(SOLINKER) $(PRODSO) $(OBJ) 2>> $(LOGDIR)/$(NAME) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(PRODSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[KO]" $(PRODSO) $(DEFAULT)
			@find $(LOGDIR)/$(PRODSO) -size 0 -delete || true
$(PRODA):		$(OBJ)
			@$(ALINKER) $(PRODA) $(OBJ) 2>> $(LOGDIR)/$(NAME) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(PRODA) $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $(PRODA) $(DEFAULT)
			@find $(LOGDIR)/$(PRODA) -size 0 -delete || true
$(DBGSO):		$(DBGOBJ)
			@$(SOLINKER) $(DBGSO) $(OBJ) 2>> $(LOGDIR)/$(NAME) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(DBGSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[KO]" $(DBGSO) $(DEFAULT)
			@find $(LOGDIR)/$(PRODSO) -size 0 -delete || true
$(DBGA):		$(DBGOBJ)
			@$(ALINKER) $(DBGA) $(OBJ) 2>> $(LOGDIR)/$(NAME) &&	\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $(DBGA) $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $(DBGAA) $(DEFAULT)
			@find $(LOGDIR)/$(PRODA) -size 0 -delete || true

$(OBJ):
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $< -o $@ $(PRODFLAGS)			\
			 $(HEADER) 2>> $(TRACE) &&				\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[KO]" $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true
$(DBGOBJ):
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $< -o $@ $(DBGLAGS)			\
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
			@$(RM) $(OBJ) $(DBGOBJ) &&				\
			 $(ECHO) $(GREEN) "Object file deleted" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in clean rule!" $(DEFAULT)
fclean:			clean erase
			@$(RM) $(DBGA) $(DBGSO) $(PRODA) $(PRODSO) &&		\
			 $(ECHO) $(GREEN) "Program deleted!" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in fclean rule!" $(DEFAULT)
re:			fclean all
erase:
			@$(RM) -r $(LOGDIR)/*.*

.POSIX:
.PHONY:			tests title erase

