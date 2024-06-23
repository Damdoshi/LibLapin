<div class="prototype">
  $Ktypedef@ $Tt_bunny_configuration@ (*$St_bunny_my_read_configuration@)(
  $Tt_bunny_configuration_type@ $Stype@,
  $Kconst@ $Tchar@ *$Scode@,
  $Tt_bunny_configuration@ *$Sconfig@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_read_configuration function pointer
  that may be used to extend the support of bunny_read_configuration and all
  functions using it (like bunny_load_configuration and bunny_open_configuration)
  to your own custom formats.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration_type@ $Stype@:<br />
      $A The $Stype@ sent to a loading of reading configuration function.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Scode@:<br />
      $A The code to parse.
    </li>
    <li>
      $Tt_bunny_configuration@ *$Sconfig@:<br />
      $A The configuration node to garnish.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_configuration</li>
    <li>bunny_read_configuration</li>
    <li>gl_bunny_my_read_configuration</li>
  </ul>
</div>

