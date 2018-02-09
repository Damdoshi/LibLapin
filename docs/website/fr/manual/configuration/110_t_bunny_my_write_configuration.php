<div class="prototype">
  $Ktypedef@ $Tchar@ *(*$St_bunny_my_write_configuration@)(
  $Tt_bunny_configuration_type@ $Stype@,
  $Kconst@ $Tt_bunny_configuration@ *$Sconfig@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_write_configuration function pointer
  that may be used to extend the support of bunny_write_configuration and all
  functions using it (like bunny_save_configuration) to your own custom formats.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration_type@ $Stype@:<br />
      $A The $Stype@ sent to a writing or saving configuration function.
    </li>
    <li>
      $Kconst@ $Tt_bunny_configuration@ *$Sconfig@:<br />
      $A The configuration node to write.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_save_configuration</li>
    <li>bunny_write_configuration</li>
    <li>gl_bunny_my_write_configuration</li>
  </ul>
</div>

