<div class="prototype">
  Exercise - No signal!
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    This is your first exercise: You will have to fill the whole picture
    randomly. What does that mean? It means from the first pixel to the last
    pixel, you will assign the returned value of (rand() | BLACK), one pixel
    after the other.<br />
    <br />
    To success to this exercise, you will need to understand how to handle
    the $Spixels@ pointer, how to turn it into the type you need. You do
    not need to understand how to positionate yourself into this 2D space
    yet, only to know how to browse it.<br />
    <br />
    The function you will write is the following one:<br />
    <br />
  </p>
  <br />
  <div class="prototype">
    $Tvoid@ $Sbunny_no_signal@($Tt_bunny_pixelarray@ *$Spicture@);
  </div>
  <p>
    This function fill from the first to the last pixel of the sent picture
    colors with (rand() | BLACK). Pay attention to the order: from the
    <b>first</b> to the <b>last</b> pixel, line after line. Any over order will
    provoke a different display that will not match with the TechnoCore, the
    checking bot.
  </p>
  <br />
  <br />
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <h4>Automatic correction</h4>
  <p>
    No automatic correction available yet.
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Do not stop here! Add a main to your function and use it in a complete program
    to create a nice software to show to your friend what you are capable of!<br />
    <br />
    Try calling at each main loop of your program the function again to create
    a real off-signal TV effect. Try variations too: display only gray pixels,
    or only fully black and fully white pixels.
  </p>
</div>
