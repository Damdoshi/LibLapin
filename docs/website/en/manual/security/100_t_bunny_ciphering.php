<div class="prototype">
  $Ktypedef enum@ $Te_bunny_ciphering@<br />
  {<br />
  $A $SBS_XOR@,
  $A $SBS_CAESAR@,
  $A $SBS_SHAKER@,
  $A $SBS_SWITCH@,
  $A $SBS_CUSTOM@
  <br />
  } $Tt_bunny_ciphering@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration describes ciphering algorithm available in the LibLapin.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $SBS_XOR@:<br />
      $A Each byte of the data get treated by a XOR operation with
      a single byte of the key. <b>This cipher algorithm is not cumulative</b>:
      using two times this algorithm on the same data with the same key will
      uncipher the data that was ciphered.
    </li>
    <li>
      $SBS_CAESAR@:<br />
      $A Each byte of the data get treated by a ADD operation with
      a single byte of the key when ciphering, SUB when unciphering.
    </li>
    <li>
      $SBS_SHAKER@:<br />
      $A Each byte of the data get swapped with the value which is
      at a specific distance indicated by a byte in the key. Because
      swapping is made from the beginning and because it impacts even
      the end of the data, this algorithm is cumulative, even if it
      does not seems to be.
    </li>
    <li>
      $SBS_SWITCH@:<br />
      $A This algorithm transform the data from a state by state
      encoding to a status change encoding at the binary level.
      For example:<br />
      <br />
      1100 0011<br />
      <br />
      Will become:<br />
      <br />
      1010 0010<br />
      <br />
      <b>This ciphering does not use the key at all</b>.
      The unciphering level does the inverse operation. This cipher
      is cumulative.
    </li>
    <li>
      $SBS_CUSTOM@:<br />
      $A When calling the bunny_cipher_file, bunny_uncipher_file,
      bunny_cipher_data or bunny_uncipher_data with this as t_bunny_ciphering,
      the function set in gl_bunny_ressource_ciphering will be called.<br />
      <br />
      The purpose of this value is to allow you to extend the bunny library
      from outside.<br />
      <br />
      Any value superior or equal to $SBS_CUSTOM@ is valid and considered
      by all thoses functions as similar in purpose to $SBS_CUSTOM@ and
      transmit to your function so you can implement several algorithm.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>gl_bunny_ciphering_table</li>
    <li>bunny_get_ciphering</li>
  </ul>
</div>

