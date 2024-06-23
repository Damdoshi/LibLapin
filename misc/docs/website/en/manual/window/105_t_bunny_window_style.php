<div class="prototype">
  $Ktypedef enum@ $Te_bunny_window_style@<br />
  {<br />
  $A $S NO_BORDER @,<br />
  $A $S TITLEBAR @ = 1,<br />
  $A $S RESIZE_BUTTON @ = 2,<br />
  $A $S CLOSE_BUTTON @ = 4,<br />
  $A $S FULLSCREEN @ = 9,<br />
  $A $S DEFAULT_WIN_STYLE @ = TITLEBAR | RESIZE_BUTTON | CLOSE_BUTTON,<br />
  $A $S ANTIALIASING @<br />
  <br />
  } $Tt_bunny_window_style@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_window_style is an enumeration designed to support being used
  as netmask. This enumeration is only used by the bunny_start_style as
  parameter to precise the way the system will show the window.
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $S NO_BORDER @:<br />
      $A A simple rectangle of the requested size will be opened. There will not
      be any outline or button. It will not be possible to grab the window to move
      it on screen thanks to the titlebar without this.
    </li>
    <li>
      $S TITLEBAR @:<br />
      $A Display in the border the title of the window in a bar that can also
      be used to grab the window and move it.
    </li>
    <li>
      $S RESIZE_BUTTON @:<br />
      $A Display in the border a resize button to maximize the window.
    </li>
    <li>
      $S CLOSE_BUTTON @:<br />
      $A Display in the border a close button to shut the window. Note that
      not having this button may not prevent the close event to happen: the system
      may offer other ways to close the window.
    </li>
    <li>
      $S FULLSCREEN @:<br />
      $A Start the window in fullscreen mode.
    </li>
    <li>
      $S DEFAULT_WIN_STYLE @:<br />
      The style used by the bunny_start function.
    </li>
    <li>
      $S ANTIALIASING @:<br />
      A bitmask that can be added to any other mode to ask for an anti aliasing
      filter.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_start_style</li>
  </ul>
</div>

