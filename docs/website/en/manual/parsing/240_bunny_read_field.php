k<div class="prototype">
  $Tbool@ $Sbunny_read_field@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Increase *$Sindex@ to reach the space after any found field.
  A field is a valid C like symbol: a word that start with a letter or
  an underscore and that go one with letters, underscores or numbers.
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
    <li>bunny_read_double</li>
    <li>bunny_read_integer</li>
    <li>bunny_read_cstring</li>
    <li>bunny_read_rawstring</li>
  </ul>
</div>

