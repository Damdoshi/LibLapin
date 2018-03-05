<div class="prototype">
  $Tbool@ $Sbunny_base64_encode@(
  $Kconst@ $Tvoid@ *$Sdata@,
  $Tsize_t@ $Slength@,
  $Tchar@ **$Sout@,
  $Tsize_t@ *$Soutlen@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Decode using base64 algorithm the sent $Sdata@ of size $Slength@.<br />
  Store the memory space used address at *$Sout@ or use the one given directly.<br />
  Store the size of the output in *$Soutlen@.<br />
  The output size is up to 3 * $Slength / 4.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ *$Sdata@:<br />
      $A The data to decode.
    </li>
    <li>
      $Tsize_t@ $Slength@:<br />
      $A The length of $Sdata@ in bytes.
    </li>
    <li>
      $Tchar@ **$Sout@:<br />
      If *$Sout@ is $CNULL@, then the function will allocate a memory space
      wide enough with bunny_malloc and store its address in *$Sout@.
      If it is not $CNULL@, then it may allocate, depending on the size sent
      in *$Soutlen@ being sufficient or not.<br />
      The decoded data with be store there.
    </li>
    <li>
      $Tsize_t@ *$Soutlen@:<br />
      $A The size of the sent buffer in *$Sout@ if one is sent, or any
      space where to store the size of the function output. It will
      be overwritten if the function is succesfull. $CNULL@ may be sent
      if you do not want to retrieve the size.
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_base64_encode</li>
    <li>bunny_base64_check</li>
  </ul>
</div>

