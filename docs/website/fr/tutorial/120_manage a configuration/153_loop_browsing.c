
  t_bunny_configuration *adr;
  t_bunny_configuration *it;
  const char            *str;

  // We get the node at some address, which contains Name, Population and Regime
  adr = bunny_configuration_access(cnf, "Country");
  for (it = bunny_configuration_first(adr);
       it != bunny_configuration_end(adr);
       it = bunny_configuration_next(it))
    {
      // We stop if the string fetching failed
      assert(bunny_configuration_get(it, &str));
      // We print the name of the field followed by the value of the field
      printf("%s: %s\n", bunny_configuration_get_name(it), str);
    }

