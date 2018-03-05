k<div class="prototype">
  $Ktypedef@ $Tuint64_t (*$St_bunny_my_hash@)(
  $Tt_bunny_hash@ $Shash@,
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function pointer type is used to define the gl_bunny_my_hash
  function pointer which is used by bunny_hash when $SBH_CUSTOM@ is
  sent as hash algorithm.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_hash@ $Shash@:<br />
      $A The hash algorithm sent to bunny_hash, should be greater or
      equal to $SBH_CUSTOM@. Having it here allow you to define several
      custom hashes.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to hash.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length of the data to hash in bytes.
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return the digest of $Sdata@ of size $Slength@ with your custom algorithm.</p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_hash</li>
    <li>bunny_hash</li>
    <li>gl_bunny_my_hash</li>
  </ul>
</div>

