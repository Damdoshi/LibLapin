<div class="prototype">
  $Tt_bunny_window@ *$Sbunny_start@($Tunsigned int@ $Swidth@,
  $Tunsigned int@ $Sheight@,
  $Tbool@ $Sfullscreen@,
  $Kconst@ $Tchar@ *$Sname@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Open a window and return a structure to handle it.
  If the window is started in fullscreen, then all size are not
  available. A call to bunny_get_fullscreen_modes will returns
  you an array of working fullscreen modes for the underlying system.
  <br />
  <br />
  The returned structure must be free with bunny_stop.
  It is important to call it <b>before</b> exiting, especially
  if you are fullscreen, because it will restores the original
  screen resolution if the window opening have changed it.
  <br />
  <br />
  A good idea, if you managed to create a program that can
  easily adapt to any screen resolution and that you want
  to start in fullscreen is to use bunny_get_screen_resolution
  to get the current screen resolution and create a window
  of the same size. It will not change the system resolution
  and use at the maximum the system capabilities.
  <br />
  <br />
  Note that you can open several window in windowed mode.
  <br />
  <br />
  This function perform a joystick scan. So when opening
  a window, all joysticks will be recognized. After opening
  the window, you will have to handle the connection and
  disconnection by yourself with events.
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
      $Tbool@ $Sfullscreen@:<br />
      $A Send $Ctrue@ to open the window in fullscreen. $Cfalse@ to windowed mode.
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
    <li>bunny_start_style</li>
    <li>bunny_get_screen_resolution</li>
    <li>bunny_get_fullscreen_modes</li>
    <li>bunny_stop</li>
  </ul>
</div>

