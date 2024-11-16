## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2016 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## ----------------------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  MOD		=	`pwd | rev | cut -d "/" -f3 | rev`

  BIN		=	`pwd | rev | cut -d "/" -f1 | rev`
  FLAG		=	-W -Wall -Werror -g -g3 -ggdb

  INCLUDE	=	-I./include/
  SRC		=	$(wildcard src/*.cpp)
  OBJ		=	$(SRC:.c=.o)
  LIBPATH	=	-L${HOME}/.froot/lib/ -L/usr/local/lib

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		@b++ $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .c.o:
		@b++ $(INCLUDE) $(FLAG) -c $< -o $@
		@echo "[B++]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all

## ----------------------------------------------------------------------------
## MISC -----------------------------------------------------------------------

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o
