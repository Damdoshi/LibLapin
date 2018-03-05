<div class="prototype">
  Macro
  $Tssize_t@ $Sbunny_printl@($Kconst@ $char@ *$Slitteral_string@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Write a <b>litteral string</b> on stdout. Example:<br />
  bunny_printl($L"this is a litteral string"@);<br />
  <br />
  Bad example:
  $Kconst@ $Tchar@ *$Sstr@ = $L"this is not a literal string"@;<br />
  <br />
  bunny_printl(str);
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Slitteral_string@:<br />
      $A A string litteral.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>The length of the string litteral or -1 on error.
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>bunny_errno match write errno values.</p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_printlerr</li>
    <li>bunny_trace</li>
  </ul>
</div>

