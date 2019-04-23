// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Lapin library

#define			__LAPIN_H__
#include		"private2/logs.hpp"

/*?{
  "name": "bunny_set_log_descriptor",
  "order": 100,
  "desc": "first description",

  "params" : [
    {"name": "fd", "desc": "blah"}
  ],

  "return": "the return"
  }
*/
int			bunny_set_log_descriptor(int		fd)
{
  int			prev = bunny::LogDescriptor;

  bunny::LogDescriptor = fd;
  return (prev);
}

/*?{
  "name": "main",
  "order": 120,
  "desc": "second description",

  "params" : [],

  "return": "always 0"
  }
*/
int main(void);

/*?{
  "name": "t_enum",
  "order": 140
  }
*/
typedef enum e_enum
  {
    VALUE,
    OTHER_VALUE;
  }   t_enum;

/*?{
  "name": "t_union",
  "order": 160
  }
*/
typedef union u_union
{
  int i;
  char c[4];
}   t_union;

/*?{
  "name": "t_truc",
  "order": 180
  }
*/
typedef struct s_truc
{
  int i;
  char c[4];
}   t_truc;

/*?{
  "name": "my_macro",
  "order": 200
  }
*/
#define my_macro(a, b, c)

/*?{
  "name": "my_define",
  "order": 220
  }
*/
#define my_define

/*?{
  "name": "bigint",
  "order": 240
  }
*/
typedef int bigint;

/*?{
  "name": "my_global",
  "order": 260
  }
*/
int my_global = 42;

/*?{
  "name": "my_global2",
  "order": 280
  }
*/
int my_global2;

/*?{
  "name": "my_global2",
  "order": 300
  }
*/
int my_global3[3] =
  {
    42, 43, 44
  };

