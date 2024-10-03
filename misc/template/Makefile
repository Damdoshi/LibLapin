## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2024 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## Pentacle Technologie 2008-2024 ---- -- -    - - - -- -- - -- ---- -    -- --
## EFRITS SAS 2022-2024 -------------    -- -- - --- -    ---  --   -- -- -   -
## LibLapin -------------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

PRODUCT	= template
COMMAND = bcc */*.c -o $(PRODUCT) -Wall -Wextra -I./ -I./include/ -g -g3 -ggdb

all:
	$(COMMAND)
debug:
	$(COMMAND)
clean:
fclean:
	rm -f $(PRODUCT)
re:	fclean all

