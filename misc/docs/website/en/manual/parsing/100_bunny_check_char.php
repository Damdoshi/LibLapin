<div class="prototype">
  $Tint@ $Sbunny_check_char@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@,
  $Kconst@ $Tchar@ *$Stoken@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Check how many char starting from &$Sstr@[*$Sindex@] can be found
  in $Stoken@, stops when a unfound character is encoutered.<br />
  <br />
  Example:<br />
  <br />
  int i = 2;<br />
  <br />
  bunny_check_char("abcdefg", &i, "dc");<br />
  <br />
  Will return 2.
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
      $A An array of allowed characters.
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    How many characters were found.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_read_char</li>
    <li>bunny_check_text</li>
  </ul>
</div>

