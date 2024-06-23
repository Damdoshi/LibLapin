/*
**
**
**
**
*/

#include <lapin.h>

// use valgrind

int main(void)
{
  t_bunny_picture *pic;

  pic = bunny_load_picture("./pic.png");
  bunny_delete_clipable(pic);
  return (0);
}
