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

  # Present recursive builds as a single build instead of exposing make's
  # internal directory stack.
  MAKEFLAGS	+=	--no-print-directory

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
  DESTDIR	?=
  INSTALL_BIN_DIR =	$(DESTDIR)/usr/bin/
  INSTALL_ETC_DIR =	$(DESTDIR)/etc/lapin/
  INSTALL_SHR_DIR =	$(DESTDIR)/usr/share/lapin/
  INSTALL_INC_DIR =	$(DESTDIR)/usr/include/
  INSTALL_LIB_DIR =	$(DESTDIR)/usr/lib/

  BUILD_TOOLS	=	bcc b++ bcontext
  BUILD_TOOLS_PATH ?=	$(CURDIR)

  UTILS_DIR 	=	misc/programs/utils/
  UTILS_INCLUDE =	-I$(CURDIR)/include					\
			-I$(CURDIR)/include/lapin/				\
			-I$(CURDIR)/include/lapin/deps/				\
			-I$(CURDIR)/external/include/				\
			-I/opt/local/include/					\
			-I/usr/include/opencv4/

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
prod:			prepare_logs $(PRODA) # $(PRODSO)
debug:			prepare_logs $(DBGA) # $(DBGSO)
tests:			prepare_logs $(TSTA)
			(cd tests/ && $(MAKE))
$(PRODSO):		$(PRODOBJ) | prepare_logs
			@$(SOLINKER) $(PRODSO) $(DEPS) $(PRODOBJ) 2>> $(LOGDIR)/$(PRODSO) && \
			 $(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) $(PRODSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[PRD-KO]" $(PRODSO) $(DEFAULT)
			@find $(LOGDIR)/$(PRODSO) -size 0 -delete || true
$(PRODA):		$(PRODOBJ) | prepare_logs
			@$(ALINKER) $(PRODA) $(PRODOBJ) 2>> $(LOGDIR)/$(PRODA) && \
			 $(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) $(PRODA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[PRD-KO]" $(PRODA) $(DEFAULT)
			@find $(LOGDIR)/$(PRODA) -size 0 -delete || true
$(DBGSO):		$(DBGOBJ) | prepare_logs
			@$(SOLINKER) $(DBGSO) $(DEPS) $(DBGOBJ) 2>> $(LOGDIR)/$(DBGSO) &&	\
			 $(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) $(DBGSO) $(DEFAULT) ||\
			 $(ECHO) $(RED)  "[DBG-KO]" $(DBGSO) $(DEFAULT)
			@find $(LOGDIR)/$(DBGSO) -size 0 -delete || true
$(DBGA):		$(DBGOBJ) | prepare_logs
			@$(ALINKER) $(DBGA) $(DBGOBJ) 2>> $(LOGDIR)/$(DBGA) &&	\
			 $(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) $(DBGA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[DBG-KO]" $(DBGA) $(DEFAULT)
			@find $(LOGDIR)/$(DBGA) -size 0 -delete || true
$(TSTA):		$(TSTOBJ) | prepare_logs
			@$(ALINKER) $(TSTA) $(TSTOBJ) 2>> $(LOGDIR)/$(TSTA) &&	\
			 $(ECHO) $(TEAL) "[TST-OK]" $(GREEN) $(TSTA) $(DEFAULT) || \
			 $(ECHO) $(RED)  "[TST-KO]" $(TSTA) $(DEFAULT)
			@find $(LOGDIR)/$(TSTA) -size 0 -delete || true

%.o:			%.cpp | prepare_logs
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

prepare_logs:
			@mkdir -p $(LOGDIR) $(LOGDIR)/tmp

title:			prepare_logs
			@$(ECHO) $(TEAL) $(TITLE) $(DEFAULT)
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
build_utils:		$(PRODA) | prepare_logs
			@if [ -d "$(UTILS_DIR)" ]; then				\
			  $(ECHO) $(TEAL) "[UTILS]" $(GREEN) "Bundled programs" $(DEFAULT); \
			  for makefile in "$(UTILS_DIR)"*/Makefile; do		\
			    [ -f "$$makefile" ] || continue;			\
			    directory="$${makefile%/Makefile}";			\
			    utility="$${directory##*/}";			\
			    trace="$(LOGDIR)utils-$$utility.log";		\
			    $(RM) "$$trace";					\
			    if PATH="$(BUILD_TOOLS_PATH):$$PATH"			\
			       LD_LIBRARY_PATH="/tmp:$$LD_LIBRARY_PATH"		\
			       $(MAKE) --silent -C "$$directory"			\
			       LIBPATH="-L/tmp" INCLUDE="$(UTILS_INCLUDE)"		\
			       >/dev/null 2>"$$trace"; then			\
			      if [ -s "$$trace" ]; then				\
			        $(ECHO) $(PINK) "[UTL-WARN]" $(GREEN) "$$utility" \
			          $(DEFAULT) "(details: $$trace)";			\
			      else						\
			        $(RM) "$$trace";					\
			        $(ECHO) $(TEAL) "[UTL-OK]" $(GREEN) "$$utility" $(DEFAULT); \
			      fi;						\
			    else							\
			      status=$$?;					\
			      $(ECHO) $(RED) "[UTL-KO]" "$$utility" $(DEFAULT) \
			        "(details: $$trace)";				\
			      [ ! -s "$$trace" ] || sed 's/^/    /' "$$trace";	\
			      exit $$status;					\
			    fi;							\
			  done;							\
			fi
install_build_tools:
			@mkdir -p "$(INSTALL_BIN_DIR)"
			@install -m 755 $(BUILD_TOOLS) "$(INSTALL_BIN_DIR)"
			@$(ECHO) $(TEAL) "[TOOLS-OK]" $(GREEN) $(BUILD_TOOLS) $(DEFAULT)

install_utils:		install_build_tools $(PRODA)
			+@$(MAKE) build_utils					\
			 BUILD_TOOLS_PATH="$(abspath $(INSTALL_BIN_DIR)):$(CURDIR)"
			@set -e; if [ -d "$(UTILS_DIR)" ]; then			\
			  for makefile in "$(UTILS_DIR)"*/Makefile; do	\
			    [ -f "$$makefile" ] || continue;			\
			    directory="$${makefile%/Makefile}";			\
			    utility="$${directory##*/}";			\
			    if [ ! -x "$$directory/$$utility" ]; then		\
			      $(ECHO) $(RED) "[UTL-KO]" $(DEFAULT)		\
			        "missing built utility: $$directory/$$utility";	\
			      exit 1;						\
			    fi;							\
			    install -m 755 "$$directory/$$utility" "$(INSTALL_BIN_DIR)"; \
			  done;							\
			fi

install_tools:		install_utils
			@mkdir -p "$(INSTALL_ETC_DIR)"
			@mkdir -p "$(INSTALL_SHR_DIR)context/"
			@cp -r misc/ressources/context/* "$(INSTALL_SHR_DIR)context/"
			@$(ECHO) $(TEAL) "[RES-OK]" $(GREEN) "context resources" $(DEFAULT)

install_headers:	install_tools
			@mkdir -p "$(INSTALL_INC_DIR)" "$(INSTALL_INC_DIR)lapin/"
			@cp include/lapin.h "$(INSTALL_INC_DIR)"
			@cp -r include/lapin/* "$(INSTALL_INC_DIR)lapin/"
			@chmod 644 "$(INSTALL_INC_DIR)lapin.h"
			@find "$(INSTALL_INC_DIR)lapin/" -type d -exec chmod 755 {} + \
			 -o -type f -exec chmod 644 {} +
			@$(ECHO) $(TEAL) "[HDR-OK]" $(GREEN) "LibLapin headers" $(DEFAULT)

install_debug:		install_headers debug
			@mkdir -p "$(INSTALL_LIB_DIR)"
			@install -m 644 "$(DBGA)" "$(INSTALL_LIB_DIR)"
			@$(ECHO) $(TEAL) "[DBG-OK]" $(GREEN) "$(notdir $(DBGA))" $(DEFAULT)

install_main:		all install_debug
			@mkdir -p "$(INSTALL_LIB_DIR)"
			@install -m 644 "$(PRODA)" "$(INSTALL_LIB_DIR)"
			@$(ECHO) $(TEAL) "[PRD-OK]" $(GREEN) "$(notdir $(PRODA))" $(DEFAULT)

install:		install_main
			@$(ECHO) $(TEAL) "[INSTALL-OK]" $(GREEN) "LibLapin" $(DEFAULT)

package:
			dpkg-buildpackage -us -uc
.POSIX:
.PHONY:			tests prepare_logs title erase install install_build_tools install_utils install_tools install_headers install_debug install_main install_package build_utils utils
