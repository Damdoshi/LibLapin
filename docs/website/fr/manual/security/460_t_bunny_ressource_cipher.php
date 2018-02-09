<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$St_bunny_ressource_cipher@)(
  $Tchar@ *$Sbuffer@,
  $Tsize_t@ $Slen@,
  $Tvoid@ *$Sdata@,
  $Tbool@ $Scipher@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer type is used to define the gl_bunny_ressource_ciphering
  which is used by several loading functions like bunny_load_picture to
  uncipher; or by saving functions like bunny_save_configuration to cipher;
  the content being loaded or saved.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tchar@ *$Sbuffer@:<br />
      $A The data to cipher or uncipher.
    </li>
    <li>
      $Tsize_t@ $Slen@:<br />
      $A The length of $Sbuffer@ in bytes.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A The data stored inside gl_bunny_ressource_data.
    </li>
    <li>
      $Tbool@ $Scipher@:<br />
      $A $Ctrue@ if ciphering, $Cfalse if unciphering.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>gl_bunny_ressource_ciphering</li>
    <li>gl_bunny_ressource_data</li>
  </ul>
</div>

