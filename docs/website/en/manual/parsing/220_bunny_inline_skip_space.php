<div class="prototype">
  $Tvoid@ $Sbunny_inline_skip_space@(
  $Kconst@ $Tchar@ *$Sstr@,
  $Tssize_t@ *$Sindex@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Increase *$Sindex@ while $Sstr@[*$Sindex@] is any kind of inline whitespaces.
  Those are ' ' and '\t'.
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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_skip_space</li>
  </ul>
</div>

