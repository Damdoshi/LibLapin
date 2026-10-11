#include <lapin.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  t_bunny_arduino *arduino;
  if (argc != 2 || !(arduino = bunny_new_arduino(argv[1])))
    {
      fprintf(stderr, "Usage: %s /dev/ttyACM0 (Bunny UNO firmware required)\n", argv[0]);
      return 1;
    }
  if (!bunny_arduino_pin_mode(arduino, 13, BUNNY_ARDUINO_OUTPUT))
    return 2;
  for (int i = 0; i < 10; ++i)
    {
      arduino->digital_outputs[13] = (i % 2) == 0;
      if (!bunny_arduino_write(arduino))
        return 3;
      usleep(250000);
    }
  arduino->digital_outputs[13] = false;
  bunny_arduino_write(arduino);
  bunny_delete_arduino(arduino);
  return 0;
}
