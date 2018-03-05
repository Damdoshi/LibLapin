<div class="prototype">
  Open a window and close it
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The first step to get a graphic program is to create a window.<br />
    A window is a rectangle on screen that can have any size.<br />
    To open a window, the function bunny_start must be used.<br />
    <br />
    The window is generally open all time during the program lifetime.
    The window can be moved, resized, fullscreen, can request the focus
    to the operating system.<br />
    <br />
    The window is the main target for drawing and even when it is not
    the immediate target, it always end on it. <br />
    As target for drawing, opening it does not means its inner graphics
    are refreshed. To refresh it, and having its real content displayed,
    the bunny_display function must be used.
  </p>
  <br />
  <br />
  <div class="prototype">
    $Tt_bunny_window@ *$Sbunny_start@($Tunsigned int@ $Swidth@,
    $Tunsigned int@ $Sheight@,
    $Tbool@ $Sfullscreen@,
    $Kconst@ $Tchar@ *$Sname@
    );
  </div>
  <p>
    By calling this function, a window will be created. You
    will be responsible for the management of it right after
    it is created: you must have a way to store it to use it
    and close it when you do not need it anymore.<br />
    <br />
    By default, the window is filled with a nice pink color.
  </p>
  <br />
  <div class="prototype">
    $Tvoid@ $Sbunny_display@($Kconst@ $Tt_bunny_window@ *$Swindow@);
  </div>
  <p>
    This function display on screen what was before in the window graphic memory.
    This operation is quite expansive and should be done only when <b>everything</b>
    is drawn and ready.
  </p>
  <br />
  <div class="prototype">
    $Tvoid@ $Sbunny_stop@($Tt_bunny_window@ *$Swindow@);
  </div>
  <p>
    This function close the sent window, and if it was fullscreen, it also
    restore the previous screen resolution. It is very important to use it well!
  </p>
  <br />
  <hr />
  <br />
  <p>
    Here is a simple program which create a window, wait a little
    and then exit:<br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/101_open_a_window_script.c"); ?>
    </div>
  </p>
</div>
