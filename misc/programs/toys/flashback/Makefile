
all:
	../../../../b++ -DMAX_HISTORY=1024 src/*.cpp -I./include -I./../../../../include/ -L../../../../ -o flashback -std=gnu++2a -g -g3 -ggdb 2> errors~ || \
	( test -f errors~ && emacs errors~ )
clean:
fclean:
	rm -f flashback
re: fclean all

