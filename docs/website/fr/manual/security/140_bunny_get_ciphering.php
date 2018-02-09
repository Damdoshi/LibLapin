<div class="prototype">
  $Tt_bunny_ciphering@ $Sbunny_get_ciphering@($Kconst@ $Tchar@ *$Sname@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Read the sent algorithm name and return the detected enumeration.
  $SBS_CUSTOM@ is returned if no LibLapin algorithm is found.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A An algorithm name to read.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The t_bunny_ciphering algorithm found or $SBS_CUSTOM@ if no algorithm
    is found.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_ciphering</li>
    <li>gl_bunny_ciphering_table</li>
  </ul>
</div>

