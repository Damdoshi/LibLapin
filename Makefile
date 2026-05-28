#################################################################################

 ###############################################################################
 ## Jason Brillante "Damdoshi"                  Hanged Bunny Studio 2014-2025 ##
 ## Pentacle Technologie 2008-2025                           EFRITS 2022-2025 ##
 ## "libmy" V9.14                                                             ##
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
  PRODA		=	/tmp/lib$(NAME).a
  DBGSO		=	lib$(NAME)-dbg.so
  DBGA		=	/tmp/lib$(NAME)-dbg.a
  TSTA		=	/tmp/lib$(NAME)-test.a

  TITLE		=	"LIBLAPIN - BUNNY LIBRARY"
  LAPINOPTS	=	-DBUNNY_COMPILATION					\
			-DBUNNY_ALLOCATOR_DEACTIVATED				\
			-DBUNNY_EXTENDED_DATA_LENGTH=4

#################################################################################
## Building details                                                            ##
#################################################################################

  ALINKER	?=	ar rcs
  SOLINKER	?=	g++ -shared -o
  COMPILER	?=	g++ -std=gnu++23
  WARNINGS	=	-W -Wall						\
			-Wno-write-strings					\
			-Wno-unused-result					\
			-Wno-format-security					\
			-Wno-frame-address					\
			-Wno-narrowing						\
			-Wno-cast-function-type

  DEBUGOPTS	=	-O0 -Og -g -g3 -ggdb					\
			-fno-omit-frame-pointer					\
			-fno-align-functions					\
			-fno-align-loops
  TESTOPTS	=	$(DEBUGOPTS) -fprofile-arcs -ftest-coverage		\
			--coverage
  PRODOPTS	=	-O3 -ffast-math -DNDEBUG
  DEPS		=	-lsfml-graphics -lsfml-audio				\
			-lsfml-window -lsfml-system				\
			-lopencv_imgproc -lopencv_highgui			\
			-lopencv_objdetect -lopencv_video			\
			-lopencv_videoio -lopencv_core				\
			-lavcall -lusb -ludev -lm -ldl -lpthread
  INSTALL_BIN_DIR =	/usr/bin/
  INSTALL_ETC_DIR =	/etc/lapin/
  INSTALL_SHR_DIR =	/usr/share/lapin/
  INSTALL_INC_DIR =	/usr/include/
  INSTALL_LIB_DIR =	/usr/lib/

  UTILS_DIR 	=	misc/program/utils

#################################################################################
## Source                                                                      ##
#################################################################################

  HEADER	=	-I./include						\
			-I./include/lapin/					\
			-I./include/lapin/deps/					\
			-I./external/include/					\
			-I/opt/local/include/					\
			-I/usr/include/opencv4/
  SRC		=	$(shell find src/ -name "*.cpp")

#################################################################################
## Misc                                                                        ##
#################################################################################

  PRODSRC	=	$(SRC)
  DBGSRC	=	$(patsubst %.cpp,%-dbg.cpp,$(SRC))
  TSTSRC	=	$(patsubst %.cpp,%-test.cpp,$(SRC))
  PRODOBJ	=	$(PRODSRC:.cpp=.o)
  DBGOBJ	=	$(DBGSRC:.cpp=.o)
  TSTOBJ	=	$(TSTSRC:.cpp=.o)

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

  COMMON	=	$(WARNINGS) -fPIC $(LAPINOPTS) $(HEADER)
  PRODFLAGS	=	$(COMMON) $(PRODOPTS)
  DBGFLAGS	=	$(COMMON) $(DEBUGOPTS)
  TSTFLAGS	=	$(COMMON) $(TESTOPTS)

all:			erase title $(PRODA) $(DBGA) $(TSTA) # $(DBGSO) $(PRODSO)
prod:			$(PRODA) # $(PRODSO)
debug:			$(DBGA) # $(DBGSO)
tests:			$(TSTA)
			(cd tests/ && $(MAKE))
$(PRODSO):		$(PRODOBJ)
			@$(SOLINKER) $(PRODSO) $(DEPS) $(PRODOBJ) 2>> $(LOGDIR)/$(PRODSO) && \
			 $(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) $(PRODSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[PRD-KO]" $(PRODSO) $(DEFAULT)
			@find $(LOGDIR)/$(PRODSO) -size 0 -delete || true
$(PRODA):		$(PRODOBJ)
			@$(ALINKER) $(PRODA) $(PRODOBJ) 2>> $(LOGDIR)/$(PRODA) && \
			 $(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) $(PRODA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[PRD-KO]" $(PRODA) $(DEFAULT)
			@find $(LOGDIR)/$(PRODA) -size 0 -delete || true
$(DBGSO):		$(DBGOBJ)
			@$(SOLINKER) $(DBGSO) $(DEPS) $(DBGOBJ) 2>> $(LOGDIR)/$(DBGSO) &&	\
			 $(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) $(DBGSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[DBG-KO]" $(DBGSO) $(DEFAULT)
			@find $(LOGDIR)/$(DBGSO) -size 0 -delete || true
$(DBGA):		$(DBGOBJ)
			@$(ALINKER) $(DBGA) $(DBGOBJ) 2>> $(LOGDIR)/$(DBGA) &&	\
			 $(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) $(DBGA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[DBG-KO]" $(DBGA) $(DEFAULT)
			@find $(LOGDIR)/$(DBGA) -size 0 -delete || true
$(TSTA):		$(TSTOBJ)
			@$(ALINKER) $(TSTA) $(TSTOBJ) 2>> $(LOGDIR)/$(TSTA) &&	\
			 $(ECHO) $(TEAL) "[TST-OK]" $(GREEN) $(TSTA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[TST-KO]" $(TSTA) $(DEFAULT)
			@find $(LOGDIR)/$(TSTA) -size 0 -delete || true

.cpp.o:
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $< -o $@ $(PRODFLAGS)			\
			 $(HEADER) 2>> $(TRACE) &&				\
			 $(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[PRD-KO]" $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true
%-dbg.o:		%.cpp
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $(subst -dbg,,$<) -o $@ $(DBGFLAGS)	\
			 $(HEADER) 2>> $(TRACE) &&				\
			 $(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[DBG-KO]" $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true
%-test.o:		%.cpp
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@$(COMPILER) -c $(subst -test,,$<) -o $@ $(TSTFLAGS)	\
			 $(HEADER) 2>> $(TRACE) &&				\
			 $(ECHO) $(TEAL) "[TST-OK]" $(GREEN) $< $(DEFAULT) ||	\
			 $(ECHO) $(RED)  "[TST-KO]" $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true

#################################################################################
## Misc                                                                        ##
#################################################################################

title:
			@$(ECHO) $(TEAL) $(TITLE) $(DEFAULT)
			@mkdir -p $(LOGDIR)
clean:
			@find . -name "*.o" -delete
			@find . -name "*.gcno" -delete
			@find . -name "*.gcda" -delete
fclean:			clean erase
			@$(RM) $(DBGA) $(DBGSO) $(PRODA) $(PRODSO) &&		\
			 $(ECHO) $(GREEN) "Program deleted!" $(DEFAULT) ||	\
			 $(ECHO) $(RED) "Error in fclean rule!" $(DEFAULT)
re:			fclean all
erase:
			@$(RM) -r $(LOGDIR)/*.*
utils:			build_utils
build_utils:		$(PRODA)
			@if [ -d "$(UTILS_DIR)" ]; then				\
			  for makefile in "$(UTILS_DIR)"*/Makefile; do		\
				    [ -f "$$makefile" ] || continue;		\
			    directory="$${makefile%/Makefile}";			\
			    echo "[UTL] $$directory";				\
			    PATH="$$(pwd):$$PATH"				\
			    LD_LIBRARY_PATH="/tmp:$$LD_LIBRARY_PATH"		\
			    $(MAKE) -C "$$directory" LIBPATH="-L/tmp" ||	\
			    exit $$?;						\
			  done;							\
			fi
install_tools:		build_utils
			mkdir -p "$(INSTALL_BIN_DIR)"
			cp bcc b++ bcontext $(INSTALL_BIN_DIR)
			@if [ -d "$(UTILS_DIR)" ]; then				\
			  for makefile in "$(INSTALL_UTILS_DIR)"*/Makefile; do	\
			    [ -f "$$makefile" ] || continue;			\
			    directory="$${makefile%/Makefile}";			\
			    utility="$${directory##*/}";			\
			    if [ ! -x "$$directory/$$utility" ]; then		\
			      echo "[UTL-KO] missing built utility: $$directory/$$utility"; \
			      exit 1;						\
			    fi;							\
			    cp "$$directory/$$utility" "$(INSTALL_BIN_DIR)";	\
			    chmod 755 "$(INSTALL_BIN_DIR)/$$utility";		\
			  done;							\
			fi
			mkdir -p /etc/lapin/
			chmod 755 $(INSTALL_BIN_DIR)/bcc 			\
			 $(INSTALL_BIN_DIR)/b++					\
			 $(INSTALL_BIN_DIR)/bcontext
			mkdir -p $(INSTALL_SHR_DIR)context/
			cp -r misc/ressources/context/* $(INSTALL_SHR_DIR)context/

install_headers:	install_tools
			cp include/lapin.h $(INSTALL_INC_DIR)
			mkdir -p $(INSTALL_INC_DIR)lapin/
			cp -r include/lapin/* $(INSTALL_INC_DIR)lapin/
			chmod 644 $(INSTALL_INC_DIR)lapin.h
			find $(INSTALL_INC_DIR)lapin/ -type d -exec chmod 755 {} + -o -type f -exec chmod 644 {} +

install_debug:		install_headers debug
			cp $(DBGA) $(INSTALL_LIB_DIR)

install_main:		all install_debug
			cp $(PRODA) $(DBGA) $(INSTALL_LIB_DIR)

install:		install_main install_debug

package:
			dpkg-buildpackage -us -uc
.POSIX:
.PHONY:			tests title erase install_tools install_headers install_debug install_main install_package build_utils utils

