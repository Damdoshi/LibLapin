k<div class="prototype">
  $Ktypedef struct@ $Tu_bunny_cipher_key@<br />
  {<br />
  $A $Tuint32_t@ $Slength@;<br />
  $A $Tchar@ $Skey@[];<br />
  <br />
  } $Tt_bunny_cipher_key@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A A key used as ciphering ressource. If you need to reserve space for a specific
  size, you can do it this way:<br />
  <br />
  t_bunny_cipher_key *k = bunny_malloc(sizeof(*k) + length * sizeof(k->key[0]));
  <br />
  <br />
  You can also use bunny_alloca instead of bunny_malloc if a local key is
  enough for your function. Do not forget to set the $Slength@ field and to fill
  the $Skey@ one.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tint32_t@ $Slength@:<br />
      $A The length in byte of the $Skey@ attribute.
    </li>
    <li>
      $Tchar@ $Skey@[]:<br />
      $A An array of $Slength@ byte containing the data used as key
      for ciphering.
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_default_key</li>
    <li>bunny_cipher_file</li>
    <li>bunny_uncipher_file</li>
    <li>bunny_cipher_data</li>
    <li>bunny_uncipher_data</li>
  </ul>
</div>

