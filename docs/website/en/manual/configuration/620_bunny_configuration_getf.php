<div class="prototype">
  <b>C11</b> Macro
  $Tt_bunny_configuration@ *$Sbunny_configuration_getf(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Sstorage_space@,
  $Kconst@ $Tchar@ *$Sfpattern_address@,
  ...
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get a data inside the configuration tree. The address of the node
  is composed in a printf fashion with the pattern and variadic parameters.<br />
  <br />
  This macro is <b>only</b> available if you are using <b>C11</b> or a newer
  version of C. C++ does not support this macro.<br />
  Underlying functions, that you must use if you cannot use the macro, are:
  <ul>
    <li>
      bunny_configuration_getf_node, with $Sstorage_space@ as $Tt_bunny_configuration@**.
    </li>
    <li>
      bunny_configuration_getf_string, with $Sstorage_space@ as $Kconst@ $Tchar@**.
    </li>
    <li>
      bunny_configuration_getf_int, with $Sstorage_space@ as $Tint@*.
    </li>
    <li>
      bunny_configuration_getf_double, with $Sstorage_space@ as $Tdouble@*.
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
      $Sstorage_space@:<br />
      $A This $Sstorage_space@ can be a $Tt_bunny_configuration@**, $Kconst@ $Tchar@**, a $Tdouble@* or
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
    Returns $Ctrue@ if a value was stored inside $Sstorage_space@ or $Cfalse@ if
    it was not.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>This macro wraps several calls to real functions, which are:</p>
  <p>
    bool $Sbunny_configuration_getf_node(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    t_bunny_configuration **$Sstorage_space@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_getf_string(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    const char **$Sstorage_space@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_getf_int(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    int *$Sstorage_space@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
  <p>
    bool $Sbunny_configuration_getf_double(
    $Tt_bunny_configuration@ *$Sconfiguration@,
    double *$Sstorage_space@,
    $Kconst@ $Tchar@ *$Sfpattern_address@,
    ...
    );
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_configuration_setf</li>
  </ul>
</div>

