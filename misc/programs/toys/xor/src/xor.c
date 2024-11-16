

#include <lapin.h>

struct skey
{
  int32_t len;
  char buffer[9];
};

int main(int argc, char **argv)
{
  if (argc != 2)
    return (0);
  struct skey skey = {9, "schmolduc"};
  return (!bunny_cipher_file(argv[1], BS_XOR, &skey));
}


