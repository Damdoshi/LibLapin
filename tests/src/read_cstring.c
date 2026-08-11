#include <lapin.h>
#include <string.h>

static int test_success(const char *src, size_t buffer_size, const char *expected)
{
  char buffer[128];
  ssize_t i = 0;

  memset(buffer, 0x7F, sizeof(buffer));
  if (buffer_size > sizeof(buffer))
    return (1);
  if (!bunny_read_cstring(src, &i, buffer, buffer_size))
    return (1);
  if (strcmp(buffer, expected) != 0)
    return (1);
  return (0);
}

static int test_too_small(const char *src, size_t buffer_size)
{
  char buffer[128];
  ssize_t i = 0;

  memset(buffer, 0x7F, sizeof(buffer));
  if (buffer_size > sizeof(buffer))
    return (1);
  return (bunny_read_cstring(src, &i, buffer, buffer_size) ? 1 : 0);
}

int main(void)
{
  /* The output buffer only needs the decoded bytes plus the terminating NUL. */
  if (test_success("\"Student\"", sizeof("Student"), "Student"))
    return (1);
  if (test_success("\"ccccccccccc\"", sizeof("ccccccccccc"), "ccccccccccc"))
    return (1);
  if (test_success("\"école\"", sizeof("école"), "école"))
    return (1);
  if (test_too_small("\"Student\"", sizeof("Student") - 1))
    return (1);
  return (0);
}
