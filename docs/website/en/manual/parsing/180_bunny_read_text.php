<div class="prototype">
  $Tbool@ $Sbunny_read_text@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  $Kconst@ $Tchar@ *$Stoken@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Browse $Sstr@ if starting from &$str@[*$Sindex@] $Stoken@ can be found.
  Only read one time. Return if something was read.<br />
  <br />
  Move *$Sindex@ if something was found.
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
      $Kconst@ $Tchar@ *$Stoken@:<br />
      $A The string to match.
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
    <li>bunny_read_char</li>
    <li>bunny_check_char</li>
    <li>bunny_check_text</li>
  </ul>
</div>

