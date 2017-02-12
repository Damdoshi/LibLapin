/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2016
**
** Hash test program
*/

#include		<inttypes.h>
#include		<string.h>
#include		<stdio.h>
#include		<lapin.h>

const char		*str[22] =
  {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
    "Morbi sit amet pretium sapien. Etiam consectetur, massa bibendum scelerisque gravida, eros felis ornare ipsum,",
    "at posuere odio tellus vitae erat. Fusce efficitur interdum nisl, eget rhoncus est cursus semper.",
    "Pellentesque id consectetur tellus. Proin tincidunt feugiat nibh ut aliquet. Mauris iaculis lectus sed",
    "odio cursus molestie. Integer pellentesque mi ut velit interdum sodales. Donec porttitor ornare sapien",
    "eget gravida. Curabitur elementum nisl vitae consequat pretium. Aliquam ac ligula tellus. Sed feugiat,",
    "nunc a dictum vulputate, erat enim luctus sem, a pellentesque elit ligula eu odio.",
    "Etiam id nulla vehicula, volutpat mi a, iaculis nulla. Duis at fringilla libero. Cras placerat orci",
    "consectetur diam suscipit, et porttitor ex suscipit. Sed ut finibus tellus, sit amet tincidunt odio.",
    "Duis sit amet luctus libero. Vivamus dapibus nibh a sapien tincidunt elementum. Morbi vulputate lectus",
    "sit amet arcu tempor vulputate. Sed pharetra nunc ac diam accumsan, et pellentesque urna iaculis.",
    "Cras pellentesque massa nec aliquam viverra. Mauris semper vehicula blandit. Aenean in ornare nibh. Proin a nunc odio. Fusce nec tempus leo.",
    "Nam sit amet ex in odio fermentum tincidunt non ut massa. Donec eu accumsan massa. Nunc ac ante dolor.",
    "Donec quis mauris ullamcorper, porttitor massa ac, semper augue. Integer tempor nisl non magna sodales dapibus.",
    "Curabitur in vulputate enim, vel mollis elit. Fusce pulvinar quis felis eget tempus. Praesent viverra feugiat interdum.",
    "Sed gravida porttitor metus id pellentesque. Aenean fermentum aliquet condimentum. Donec viverra felis in diam varius,",
    "a posuere ligula sodales. Fusce egestas hendrerit magna, id volutpat elit. Nunc quis scelerisque odio. Fusce fringilla",
    "ultricies magna, a tempus sapien posuere vitae. Nullam posuere ipsum at mollis imperdiet. Nulla condimentum nisi luctus diam",
    "tincidunt ultricies. Ut sed euismod ipsum, sit amet sodales tellus. Nam id consectetur tortor. Duis a mi massa.",
    "Aenean ornare eget orci pellentesque interdum. Praesent in leo tempor ligula facilisis dapibus. Curabitur tincidunt ex justo,",
    "in tincidunt dui aliquam at. Suspendisse tempus, purus id ullamcorper scelerisque, metus eros dictum nulla, pellentesque",
    "lobortis lorem purus eget eros. Proin sapien odio, malesuada non sapien sit amet, semper accumsan leo."
  };

int			main(void)
{
  size_t		i;

  puts("Multiplier hash:");
  for (i = 0; i < sizeof(str) / sizeof(str[i]); ++i)
    printf("%" PRIu64 "\n", bunny_hash(BH_MULTIPLIER, str[i], strlen(str[i])));

  puts("FNV hash:");
  for (i = 0; i < sizeof(str) / sizeof(str[i]); ++i)
    printf("%" PRIu64 "\n", bunny_hash(BH_FNV, str[i], strlen(str[i])));

  return (0);
}

