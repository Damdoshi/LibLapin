<div class="prototype">
  Program Life cycle
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The second step to get a graphic program is to manage the window
    to get a program lifecycle.<br />
    In the previous part, we have created a simple program that open, wait
    and close the window, but there was no interaction with the user. This time,
    there will be one.<br />
    <br />
    We will use several additionnal functions to do a new colorful program
    that exit on demand, those functions are:
    bunny_set_key_response, bunny_fill and bunny_loop.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_set_key_response@($Tt_bunny_key@ $Sfunction@);
  </div>
  <p>
    This function allow you to define a function that will be called
    when a key is pressed or released. The function will be <b>automatically</b>
    called by a mechanism inside another function you will use: bunny_loop.<br />
    <br />
  </p>

  <div class="prototype">
    $Tvoid@ $Sbunny_fill@(
    $Tt_bunny_buffer@ *$Starget@,
    $Tunsigned int@ $Scolor@
    );
  </div>
  <p>
    This function, which takes a t_bunny_buffer can be used on t_bunny_window
    because t_bunny_window contains a t_bunny_buffer! This function, when used
    on a window, will entirely fill the window with the sent color.<br />
    To give to bunny_fill a window, you can do it two ways:<br />
    <br />
    $A $Sbunny_fill@(($Tt_bunny_buffer@*)win);
    <br />
    or:
    <br />
    $A $Sbunny_fill@(&win->buffer);
    <br />
    <br />
    The second fashion is the one I will use in all tutorials.<br />
    <br />
  </p>

  <div class="prototype">
    $Tt_bunny_response@ $Sbunny_loop@(
    $Tt_bunny_window@ *$Swindow@,
    $Tuint8_t@ $Sfrequency@,
    $Tvoid@ *$Sdata@
    );
  </div>
  <p>
    This function is a huge part of the bunny library: it handles all events
    the bunny library can handle, it is real time locked, that means you can
    set a frequency and it will run this frequency on high speed machine like
    on low speed machine (if performences are good enough) so your program
    speed does not rely on the computer.<br />
    In this program, the bunny_loop will be useful to us because we will need
    to handle key events. We set with bunny_set_key_response a request to
    bunny_loop to call a function when it is needed.
    <br />
    <br />
  </p>
  <hr />
  <br />

  <p>
    Here is a simple program which create a window, exit on escape and change
    color of window for any other key.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/151_color_window_script.c"); ?>
    </div>
  </p>
</div>
