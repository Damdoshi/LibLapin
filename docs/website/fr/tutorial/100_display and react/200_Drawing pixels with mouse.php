<div class="prototype">
  Drawing pixels with mouse
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    You know how to open, manage and close window, you know how to
    handle simple events.<br />
    <br />
    Drawing can be done on several kind of surfaces: the first
    kind is pictures managed by graphic cards and the second one
    pictures managed by CPU.<br />
    <br />
    The first kind of picture is fast when doing clip works:<br />
    sprites, complex shapes, special effects.<br />
    <br />
    The second kind of picture is fast when doing pixel per pixel works.<br />
    <br />
    The first kind is mainly presented as t_bunny_picture in bunny library
    and the second one t_bunny_pixelarray. In this tutorial, we will only
    use t_bunny_picture because basics are easier.<br />
    <br />
    t_bunny_pixelarray will be treated in specific chapters
    which are designed for schoolarship usage and less purely informative.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_set_move_response@($Tt_bunny_move@ $Sfunction@);
  </div>
  <p>
    This function allow you to define a function that will be called
    when the mouse move. We will use this function to start drawing.
    <br />
    <br />
  </p>

  <div class="prototype">
    $Kconst@ $Tt_bunny_position@ *$Sbunny_get_mouse_position@($Tvoid@);
  </div>
  <p>
    This function will return to us the mouse position on window.
    <br />
    <br />
  </p>

  <div class="prototype">
    $Tvoid@ $Sbunny_set_click_response@($Tt_bunny_click@ $Sfunction@);
  </div>
  <p>
    This function allow you to define a function that will be called
    when a mouse button is pressed or released.<br />
    We will use this function to register if the current left
    mouse button is down or up.
    <br />
    <br />
  </p>

  <div class="prototype">
    $Kconst@ $Tbool@ *$Sbunny_get_mouse_button@($Tvoid@);
  </div>
  <p>
    This function will return to us the mouse button status.
    <br />
    <br />
  </p>

  <div class="prototype">
    $Tvoid@ $Sbunny_set_pixel@($Tt_bunny_buffer@ *$Starget@,
    $Tt_bunny_position@ $Sposition@,
    $Tunsigned int@ $Scolor@
    );
  </div>
  <p>
    This function will color a single pixel at
    the position you sent and with the color you sent.
  </p>
  <br />
  <hr />
  <br />

  <p>
    Here is a simple program which trigger the drawing when the
    left mouse button is pressed and draw when the mouse is moving.
    You can exit this program with the right mouse button.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/201_color_pencil_script.c"); ?>
    </div>
  </p>
</div>
