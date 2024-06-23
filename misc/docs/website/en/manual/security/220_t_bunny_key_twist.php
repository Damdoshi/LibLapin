<div class="prototype">
  $Ktypedef@ $Tt_bunny_cipher_key@ *(*$St_bunny_key_twist@)(
  $Kconst@ $Tt_bunny_cipher_key@ *$Sinkey@,
  $Tt_bunny_cipher_key@ *$Soutkey@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer type is used to define the gl_bunny_my_key_twist
  function pointer which is used by bunny_default_key to transform
  the embedded key to prevent cracking by simple extraction.<br />
  <br />
  The function must be deterministic.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_cipher_key@ *$Sinkey@:<br />
      $A The original key that you will have to transform
      inside $Soutkey@.
    </li>
    <li>
      $Tt_bunny_cipher_key@ *$Soutkey@:<br />
      $A The space in which you must write the generated key.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return $Soutkey@</p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>gl_bunny_my_key_twist</li>
    <li>bunny_default_key</li>
  </ul>
</div>

