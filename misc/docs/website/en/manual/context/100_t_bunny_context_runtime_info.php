<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_context_runtime_info@<br />
  {<br />
  $A $Tvoid@ *$Smain_structure@;<br />
  $A $Tt_bunny_context@ $Ssubcontext@;<br />
  $A $Tt_bunny_buffer@ *$Sscreen@;<br />
  $A $Tsize_t@ $Snext_context@;<br />
  <br />
  } $Tt_bunny_stack_node@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is a base structure useful for any context library.
  All context defined in bunny library will lay on it.<br />
  Some fields are required and should be field by you before.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tvoid@ *$Smain_structure@:<br />
      $A The $Smain_structure@ pointer is present to be set to your own
      data address. It is mainly present to be passed to callbacks that may
      be additionnally provided by the context. It is also present in case
      you wish to create your own context.<br />
    </li>
    <li>
      $Tt_bunny_context@ $Ssubcontext@:<br />
      $A The $Ssubcontext@ will allow you to set callbacks that will be
      called by the foreground context. Note that those calls
      entirely depends of the context. About the return value, the
      behaviour should be to always return the first not t_bunny_response $SGO_ON@
      value to bunny_loop.<br />
      <br />
      This is specifically useful when you are writing a context library:
      it allows you to create your library whithout preventing any user of your
      library to insert events as he or she needs.
    </li>
    <li>
      $Tt_bunny_buffer@ *$Sscreen@:<br />
      $A The screen pointer is the area where pixels are drawn. It may be the window
      or something else compatible with t_bunny_buffer.<br />
      <br />
      $A An interesting example mixing the usage of a t_bunny_picture for
      screen and an additionnal display function in subcontext would be to
      resize the graphic output from the original one to the real window size.
    </li>
    <li>
      $Tsize_t@ $Snext_context@:<br />
      $A The next_context field is the id of the context that should be used
      after leaving the current one.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_context_key</li>
    <li>bunny_context_click</li>
  </ul>
</div>
