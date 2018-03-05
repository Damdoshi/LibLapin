<div class="prototype">
  $Tt_bunny_window@ *$Sbunny_start_style@($Tunsigned int@ $Swidth@,
  $Tunsigned int@ $Sheight@,
  $Tt_bunny_window_style@ $Sstyle@,
  $Kconst@ $Tchar@ *$Sname@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function works almost like bunny_start but allow
  you to defined more finely the window style. See t_bunny_window_style
  for more details about those style.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned int@ $Swidth@:<br />
      $A The width in pixel of the bunny to open.
    </li>
    <li>
      $Tunsigned int@ $Sheight@:<br />
      $A The height in pixel of the bunny to open.
    </li>
    <li>
      $Tt_bunny_window_style@ $Sstyle@:<br />
      $A The style of the window that will be opened.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sname@:<br />
      $A The window name. It will be used on the window outline itself and
      on most system in the status bar of the desktop manager.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_window structure.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $C BE_UNKNOWN_DISPLAY_DEVICE @:<br />
      <p>
        The environment is missing the DISPLAY variable..<br />
      </p>
    </li>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"window"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_start</li>
    <li>bunny_get_screen_resolution</li>
    <li>bunny_get_fullscreen_modes</li>
    <li>bunny_stop</li>
  </ul>
</div>

