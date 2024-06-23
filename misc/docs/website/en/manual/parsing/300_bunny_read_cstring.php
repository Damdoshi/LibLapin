<div class="prototype">
  $Tbool@ $Sbunny_read_cstring@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  $Tchar@ *$Sval@,
  $Tsize_t@ $Sout_len@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Increase *$Sindex@ if there is a C-String at &$Sstr@[*$Sindex@],
  and get this value inside $Sval@, which is a buffer of size $Sout_len@.<br />
  <br />
  A C-String start with '"' and end with '"'. Inside a C-String, backslash
  tokens can be used to escape characters ('\n', '\r', etc.).<br />
  This function support utf-8 characters.<br />
  This function support hexadecimal with the following syntax: '\0xHEXA'<br />
  This function support binary with the following syntax: '\0bBINARY'<br />
  This function support octal with the following syntax: '\0OCTAL'
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
      $A The size of the sent buffer $Sval@.
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
    <li>bunny_write_cstring</li>
    <li>bunny_read_field</li>
    <li>bunny_read_integer</li>
    <li>bunny_read_double</li>
    <li>bunny_read_rawstring</li>
  </ul>
</div>

