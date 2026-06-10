## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2026 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## ----------------------------------------------------------------------------
## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

BIN     = cineplayer
FLAG    = -W -Wall -g -g3 -ggdb
INCLUDE += -I./include/
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
LIBPATH ?= -L$(HOME)/.froot/lib/

all: bin

bin: $(OBJ)
	@bcc $(LIBPATH) $(OBJ) -o $(BIN) $(LIB)
	@echo "[OUT] " $(BIN)
	@echo $(BIN) | tr '[:lower:]' '[:upper:]'

.c.o:
	@bcc $(INCLUDE) $(FLAG) -c $< -o $@
	@echo "[GCC]" $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re
.SUFFIXES: .c .o
