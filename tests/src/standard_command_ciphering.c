
#include <assert.h>
#include <lapin.h>
#include <stdint.h>
#include <string.h>

typedef struct s_command
{
  t_bunny_ciphered_standard_command_header header;
  char data[32];
} t_command;

int main(void)
{
  size_t i, j, k;
  t_bunny_identity srv_ids[3] = {
    { "damdoshi", "", BIS_AWAITING_CONFIRMATION, (t_bunny_hash)-1, {}, 0, 0, 0 },
    { "mordanis", "", BIS_AWAITING_CONFIRMATION, (t_bunny_hash)-1, {}, 0, 0, 0 },
    { "", "", BIS_AWAITING_CONFIRMATION, (t_bunny_hash)-1, {}, 0, 0, 0 }
  };
  t_bunny_identity clt_id;
  for (i = 0; i < NBRCELL(srv_ids[0].secret); ++i)
    {
      srv_ids[0].secret[i] = rand() % 256;
      srv_ids[1].secret[i] = rand() % 256;
    }
  t_bunny_network_info bad = {};
  for (i = 0; i < sizeof(srv_ids[0].info); ++i)
    {
      ((char*)&srv_ids[0].info)[i] = rand() % 256;
      ((char*)&srv_ids[1].info)[i] = rand() % 256;
    }
  t_bunny_network_info info = srv_ids[1].info;
  t_bunny_identity *id;

  assert(bunny_resolve_identity(srv_ids, bad) == NULL);
  id = bunny_resolve_identity(srv_ids, info);
  assert(id == &srv_ids[1]);
  clt_id = *id;

  for (i = 0; i < BH_CUSTOM; ++i)
    for (j = 0; j < BS_CUSTOM; ++j)
      {
        t_command cmd[3];
        cmd[0].header.ciphered = 0;
        cmd[0].header.command =
          rand() % (UINT32_MAX - BSCT_LAST_STANDARD_COMMAND) + BSCT_LAST_STANDARD_COMMAND;
        cmd[0].header.declared_sending_date = (float)bunny_get_time();
        for (k = 0; k < NBRCELL(cmd[0].header.mask_source); ++k)
          cmd[0].header.mask_source[k] = 0;
        for (k = 0; k < NBRCELL(cmd[0].data); ++k)
          cmd[0].data[k] = (char)k;

        memcpy(&cmd[1], &cmd[0], sizeof(cmd[1]));
        assert(bunny_cipher_standard_command(id, (t_bunny_standard_command*)&cmd[1], sizeof(cmd[1]), i, j));
        assert(cmd[1].header.ciphered);
        cmd[1].header.ciphered = 0;
        assert(!memcmp(&cmd[0].header,
                       &cmd[1].header,
                       sizeof(cmd[0].header) - sizeof(cmd[0].header.mask_source)));
        assert(memcmp(&cmd[0].header.mask_source,
                      &cmd[1].header.mask_source,
                      sizeof(cmd[0].header.mask_source)));
        cmd[1].header.ciphered = 1;

        memcpy(&cmd[2], &cmd[1], sizeof(cmd[2]));
        assert(bunny_handle_standard_command(&clt_id,
                                             (t_bunny_standard_command*)&cmd[2],
                                             sizeof(cmd[2]),
                                             i,
                                             j) == BSCH_TO_BE_DONE);
        assert(!memcmp(&cmd[0], &cmd[2], sizeof(cmd[0])));
      }

  return EXIT_SUCCESS;
}
