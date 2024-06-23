<div class="prototype">
  Not implemented
  $Tvoid@ $Sbunny_wide_hash@(
  $Tt_bunny_hash@ $Shash@,
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@,
  $Tvoid@ *$Starget@,
  $Tsize_t@ $Starget_length@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Generate a digest with the sent $Shash@ algorithm of $Sdata@ which is
  of size $Slength@ bytes and store it inside $Starget@. The size of the
  hash will be $Starget_length@ bytes.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_hash@ $Shash@:<br />
      $A The algorithm to use. If $SBH_CUSTOM@ or any higher value is sent,
      then gl_bunny_my_hash is called.
    </li>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to hash.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length in bytes of $Sdata@.
    </li>
    <li>
      $Tvoid@ *$Starget@:<br />
      $A A memory space where to write the hash.
    </li>
    <li>
      $Tsize_t@ $Starget_length@:<br />
      $A The size of the save memory space in bytes.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_hash</li>
    <li>bunny_hash</li>
  </ul>
</div>

