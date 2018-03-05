<div class="prototype">
  $Tbool@ $Sbunny_read_rawstring@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  $Tchar@ *$Sval@,
  $Tsize_t@ $Sout_len@,
  $Tchar@ *$Send_token@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Read from &$Sstr@[*$Sindex@] until one of the characters inside $Send_tok@ is
  reached. Store what was read inside $Sval@, which is a buffer of size $Sout_len@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sstr@:<br />
      $A The string to explore.
    </li>
    <li>
      $Tssize_t@ *$Sindex@:<br />
      $A A pointer to the position to explore in $Sstr@.
    </li>
    <li>
      $Tint@ *$Sval@:<br />
      $A Where to store the read value.
    </li>
    <li>
      $Tsize_t@ $Sout_len@:<br />
      $A The size of the reception buffer $Sval@.
    </li>
    <li>
      $Tchar@ *$Send_token@:<br />
      $A An array of characters that provoke the end of the reading if reach.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    $Ctrue@ if *$Sindex@ was modified or $Cfalse@ if it was not.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_read_field</li>
    <li>bunny_read_integer</li>
    <li>bunny_read_double</li>
    <li>bunny_read_cstring</li>
  </ul>
</div>

