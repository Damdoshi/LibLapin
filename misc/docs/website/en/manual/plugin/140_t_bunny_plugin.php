<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_plugin@<br />
  {<br />
  $A $Kconst@ $Tchar@ * $Kconst@ $Sname@;<br />
  $A $Kconst@ $Tvoid@ * $Kconst@ $Slibrary_handler@;<br />
  $A $Kconst@ $Tsize_t@ $Snbr_functions@;
  $A $Kconst@ $Tt_bunny_prototype@ $Sprototypes@[];
  <br />
  } $Tt_bunny_plugin@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure represents a loaded dynamic library which match the
  bunny plugin format.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ * $Kconst@ $Sname@:<br />
      $A The name of the file containing the loaded library.
    </li>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $Slibrary_handler@:<br />
      $A The library itself, loaded into memory.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Snbr_functions@:<br />
      $A The size of the $Sprototypes@ array in elements.
    </li>
    <li>
      $Kconst@ $Tt_bunny_prototype@ $Sprototypes@[]:<br />
      $A All functions in the loaded plugin that was returned
      by the bunny plugin interface.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_plugin</li>
    <li>bunny_delete_plugin</li>
    <li>bunny_plugin_get_function</li>
    <li>bunny_plugin_call</li>
    <li>bunny_plugin_callv</li>
  </ul>
</div>


