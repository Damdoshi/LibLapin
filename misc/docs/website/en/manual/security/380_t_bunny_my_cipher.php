<div class="prototype">
  $Ktypedef@ $Tvoid@ *(*$St_bunny_my_cipher@)(
  $Tt_bunny_ciphering@ $Sciphering@,
  $Tchar@ *$Sbuffer@,
  $Tsize_t@ $Slen@,
  $Kconst@ $Tt_bunny_cipher_key@ *$Skey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This type is the one used by gl_bunny_my_cipher function pointer
  that may be used if you wish to bring your own ciphering algorithm.
  The bunny_cipher_file and bunny_cipher_data will call the gl_bunny_my_cipher
  if the sent algorithm is equal or greater than $SBS_CUSTOM@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_ciphering@ $Sciphering@:<br />
      $A The ciphering sent to bunny_cipher_file or bunny_cipher_data.
    </li>
    <li>
      $Tchar@ *$Sbuffer@:<br />
      $A The buffer to cipher.
    </li>
    <li>
      $Tsize_t@ $Slen@:<br />
      $A The length of $Sbuffer@ in bytes.
    </li>
    <li>
      $Kconst@ $Tt_bunny_cipher_key@ *$Skey@:<br />
      $A The key used to cipher the data.
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>gl_bunny_my_cipher</li>
    <li>t_bunny_my_uncipher</li>
    <li>gl_bunny_my_uncipher</li>
  </ul>
</div>

