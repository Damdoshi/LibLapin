<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_prototype@<br />
  {<br />
  $A $Kconst@ $Tchar@ *$Sname@;<br />
  $A $Kconst@ $Tvoid@ *$Sfunction_ptr@;<br />
  $Tt_bunny_value_type@ $Sreturn_value@;<br />
  $Tsize_t@ $Snbrparam@;<br />
  $Tt_bunny_value_type@ $Sparameters@[];<br />
  <br />
  } $Tt_bunny_prototype@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a single function loaded from a dynamic library
  that match the bunny plugin format. It can be called by using bunny_plugin_call
  with its $Sname@ used as $Sfuncname@.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The name of the function represented by this structure.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sfunction_ptr:<br />
      $A The address of the function in memory.
    </li>
    <li>
      $Tt_bunny_value_type@ $Sreturn_value@:<br />
      $A The type of the returned value of the represented function.
    </li>
    <li>
      $Tsize_t@ $Snbrparam@:<br />
      $A The quantity of parameters the function takes. This is also
      the size in elements of the attribute $Sparameters@.
    </li>
    <li>
      $Tt_bunny_value_type@ $Sparameters@[]:<br />
      $A An array of $Snbrparam@ elements, which indicates which types
      are expected when calling the function represented by this structure.
    </li>
  </ul>
</div>

