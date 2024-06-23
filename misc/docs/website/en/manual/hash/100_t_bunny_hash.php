<div class="prototype">
  $Ktypedef enum@ $Te_bunny_rgb@<br />
  {<br />
  $A $SBH_MULTIPLIER@,<br />
  $A $SBH_FNV@,<br />
  $A $SBH_FNV_A@,<br />
  $A $SBH_DJB2@,<br />
  $A $SBH_SDBM@,<br />
  $A $SBH_LOSELOSE,@<br />
  $A $SBH_CUSTOM@<br />
  <br />
  } $Tt_bunny_rgb@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This is the list of supported hash. $BH_CUSTOM@ or any greater value
  will trigger in bunny_hash functions calls to customable function pointers.
</div>
<hr />

<div class="parameters">
  <h3>Some notes about specific symbols</h3>
  <ul>
    <li>
      $SBH_MULTIPLIER@:<br />
      $A This algorithm is efficient with strings.
    </li>
    <li>
      $SBH_DJB2@:<br />
      $A Seems quite efficient in terms of collision.
    </li>
    <li>
      $SBH_LOSELOSE@:<br />
      $A Checksum.
    </li>
    <li>
      $SBH_CUSTOM@:<br />
      $A Hashing with this algorithm of any higher value trigger the call to
      gl_bunny_my_hash.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_hash</li>
    <li>bunny_wide_hash</li>
  </ul>
</div>

