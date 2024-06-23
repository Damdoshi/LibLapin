<div class="prototype">
  $Tbool@ $Sbunny_check_text@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  $Kconst@ $Tchar@ *$Stoken@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Check if $Stoken@ can be found at &$Sstr@[*$Sindex@].
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
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    $Ctrue@ if $Stoken@ was found, else $Cfound@.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_read_char</li>
    <li>bunny_read_text</li>
    <li>bunny_check_text_case</li>
  </ul>
</div>

