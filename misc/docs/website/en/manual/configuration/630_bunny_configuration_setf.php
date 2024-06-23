<div class="prototype">
  <b>C11</b> Macro
  $Tt_bunny_configuration@ *$Sbunny_configuration_setf(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sdata@,
  $Kconst@ $Tchar@ *$Sfpattern_address@,
  ...
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set a data inside the configuration tree. The address of the node
  is composed in a printf fashion with the pattern and variadic parameters.<br />
  <br />
  <br />
  This macro is <b>only</b> available if you are using <b>C11</b> or a newer
  version of C. C++ does not support this macro.<br />
  Underlying functions, that you must use if you cannot use the macro, are:
  <ul>
    <li>
      bunny_configuration_setf_node, with $Sdata@ as $Tt_bunny_configuration@*.
    </li>
    <li>
      bunny_configuration_setf_string, with $Sdata@ as $Kconst@ $Tchar@*.
    </li>
    <li>
      bunny_configuration_setf_int, with $Sdata@ as $Tint@.
    </li>
    <li>
      bunny_configuration_setf_double, with $Sdata@ as $Tdouble@.
    </li>
  </ul>
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The configuration to inspect.
    </li>
    <li>
      $Sdata@:<br />
      $A This $Sdata@ can be a $Tt_bunny_configuration@**, $Kconst@ $Tchar@**, a $Tdouble@* or
      an $Tint@*. This is the place in which the catched data will be stored.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfpattern_address@:<br />
      $A The pattern to be combined with variadic parameters to create the address
      of the node to reach.
    </li>
    <li>
      ...:<br />
      $A Any valid printf-pattern valid parameter.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns $Ctrue@ if the value was stored inside the tree or $Cfalse@ if
    it was not.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    bool $Sbunny_configuration_setf_node(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    t_bunny_configuration *$Sdata@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_setf_string(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    const char *$Sdata@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_setf_int(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    int $Sdata@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_setf_double(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    double $Sdata@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_getf</li>
  </ul>
</div>

