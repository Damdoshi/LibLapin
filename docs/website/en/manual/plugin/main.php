<p>
  A bunny plugin is not a simple dynamic library.<br />
  <br />
  To be a valid bunny plugin, a dynamic library <b>must</b>
  implement a $S__get_function_list@ function of type
  t_bunny_get_function_list.<br />
  <br />
  This function must return an array of t_bunny_prototype that <b>should</b>
  be statically allocated. The array must be terminated by a t_bunny_prototype
  with $CNULL@ stored inside $Sfunction_ptr@.<br />
  <br />
  Prototypes described inside this array must match the real definition
  of functions or your program will crash when a function will be incorrectly
  called, matching its description but not its real type.
</p>
<br />
<b>The plugin module header is lapin/container/plugin.h.</b>
