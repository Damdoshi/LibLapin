<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$St_bunny_my_uncipher@)(
  $Tt_bunny_ciphering@ $Sciphering@,
  $Tchar@ *$Sbuffer@,
  $Tsize_t@ $Slen@,
  $Kconst@ $Tt_bunny_uncipher_key@ *$Skey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_uncipher function pointer
  that may be used if you wish to bring your own unciphering algorithm.
  The bunny_uncipher_file and bunny_uncipher_data will call the gl_bunny_my_uncipher
  if the sent algorithm is equal or greater than $SBS_CUSTOM@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_ciphering@ $Sciphering@:<br />
      $A The ciphering sent to bunny_uncipher_file or bunny_uncipher_data.
    </li>
    <li>
      $Tchar@ *$Sbuffer@:<br />
      $A The buffer to uncipher.
    </li>
    <li>
      $Tsize_t@ $Slen@:<br />
      $A The length of $Sbuffer@ in bytes.
    </li>
    <li>
      $Kconst@ $Tt_bunny_uncipher_key@ *$Skey@:<br />
      $A The key used to uncipher the data.
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_my_cipher</li>
    <li>gl_bunny_my_uncipher</li>
    <li>t_bunny_my_uncipher</li>
    <li>gl_bunny_my_ununcipher</li>
  </ul>
</div>

