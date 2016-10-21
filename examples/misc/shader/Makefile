## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2016 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## ----------------------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  MOD		=	`pwd | rev | cut -d "/" -f3 | rev`

  BIN		=	`pwd | rev | cut -d "/" -f1 | rev`
  FLAG		=	-W -Wall -Werror -D_GLIBCXX_USE_CXX11_ABI=0 -g -g3 -ggdb

  INCLUDE	=	-I./include/
  SRC		=	$(wildcard src/*.c)
  OBJ		=	$(SRC:.c=.o)
  LIBPATH	=	-L${HOME}/.froot/lib/
  LIB		=	-llapin -lsfml-graphics -lsfml-audio -lsfml-window	\
			-lsfml-system -lstdc++ -lm -ldl -lpthread

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		@gcc $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .c.o:
		@gcc $(INCLUDE) $(FLAG) -c $< -o $@
		@echo "[GCC]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all

## ----------------------------------------------------------------------------
## MISC -----------------------------------------------------------------------

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o
