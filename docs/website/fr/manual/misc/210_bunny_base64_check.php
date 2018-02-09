<div class="prototype">
  $Tbool@ $Sbunny_base64_encode@(
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Check the sent base64 encoded data is valid base64.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to check
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length of $Sdata@ in bytes.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Returns $Ctrue@ or $Cfalse@ depending if the base64 is correct or not.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_base64_encode</li>
    <li>bunny_base64_decode</li>
  </ul>
</div>

