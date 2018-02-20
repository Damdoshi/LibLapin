
  t_bunny_configuration *adr;
  t_bunny_configuration *it;
  const char            *str;
  int                   i;

  // We get the node at some address, which contains three element in an array
  adr = bunny_configuration_access(cnf, "Country.Region[0].Department");
  for (i = 0; (it = bunny_configuration_access(adr, i)) != NULL; ++i)
    {
      // We stop if the string fetching failed
      assert(bunny_configuration_get(it, &str));
      // We print the name of the field followed by the value of the field
      printf("%s: %s\n", bunny_configuration_get_name(it), str);
    }
