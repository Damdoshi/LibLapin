## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2017 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## ----------------------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  BIN		=	$(shell basename `pwd`)
  FLAG		=	-W -Wall -Werror -g -g3 -ggdb

  INCLUDE	=	-I./include/ -I../../include/
  SRC		=	$(wildcard src/*.c)
  OBJ		=	$(SRC:.c=.o)
  LIBPATH	=	-L../../ -L/usr/local/lib/
  LIB		=	-llapin -lsfml-graphics -lsfml-audio -lsfml-window	\
			-lsfml-system -lstdc++ -lm -ldl -lpthread -lavcall

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		gcc $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
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
