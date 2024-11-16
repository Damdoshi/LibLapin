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

  SRC_DIR	=	../src/
  REPORT	?=	./report/
  COMPILER	?=	../bcc -L./ -L../
  LIB_TO_TEST	=	LD_LIBRARY_PATH=../

  INC_DIR	?=	/usr/include/

  LIB		=	-lgcov
  STANDARD	?=	-std=gnu11
  WARNINGS	=	-W -Wall -Wno-format-security

  OPTS		=	-O0 -g -g3 -ggdb -fprofile-arcs -ftest-coverage		\
			--coverage -rdynamic -fno-omit-frame-pointer		\
			-fno-align-functions -fno-align-loops
  FLAGS		=	$(OPTS) $(WARNINGS) $(STANDARD)

  RM		=	rm -rf
  ECHO		=	/bin/echo -e
  LOGFILE	=	errors~
  ERRLOG	=	2>> $(LOGFILE)
  FERRLOG	=	>> $(LOGFILE) 2>> $(LOGFILE)
  NEGATE	= 	> /dev/null 2> /dev/null

  DEFLT		=	"\033[00m"
  PINK		=	"\033[1;35m"
  GREEN		=	"\033[0;32m"
  TEAL		=	"\033[1;36m"
  RED		=	"\033[0;31m"

#################################################################################
## Source                                                                      ##
#################################################################################

  HEADER	=	-I./../include/
  SRC		=	$(wildcard src/*.c) $(wildward src/*.cpp)
  OBJ		=	$(basename $(SRC))

#################################################################################
## Rules                                                                       ##
#################################################################################

all:			rmlog $(REPORT)
$(OBJ):
			@$(COMPILER) $@.c -o $@ $(FLAGS)			\
			 $(HEADER) $(LIB) $(ERRLOG)
			@test -f $@ || $(ECHO) $(RED)  "[KO]" $@.c $(DEFLT)
			@test -f $@ && $(ECHO) "------\n$@ :" $(FERRLOG) &&	\
			 ($(LIB_TO_TEST) $@ $(FERRLOG) &&			\
			 $(ECHO) $(TEAL) "[OK]" $(GREEN)$(notdir $@)		\
			 $(DEFLT) ||						\
			 $(ECHO) $(RED) "[KO]" $(notdir $@) $(DEFLT))

$(REPORT):		$(OBJ)
			@lcov --directory . --directory $(SRC_DIR) -c		\
			 -o coverage_raw.info $(NEGATE) &&			\
			 lcov --remove coverage_raw.info '$(INC_DIR)*' '7/*'	\
			 -o coverage.info $(NEGATE) &&				\
			 genhtml -o $(REPORT) -t "TechnoCore" coverage.info |	\
			 grep "\%" ;						\
			 $(RM) coverage_raw.info

#################################################################################
## Misc                                                                        ##
#################################################################################

rmlog:
			@$(RM) $(LOGFILE)
clean:
			@find . -name "*.gc*" -delete
			@find . -name "*.info" -delete
			@$(RM) $(OBJ)
fclean:			clean
			@$(RM) $(REPORT)
re:			fclean all
