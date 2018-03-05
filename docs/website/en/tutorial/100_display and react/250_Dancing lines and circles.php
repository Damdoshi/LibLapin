<div class="prototype">
  Dancing lines and circles
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    Now that you have learnt how to draw pixel, you will learn
    how to draw lines and circle with bunny_set_line and bunny_set_circle,
    on GPU side.<br />
    <br />
    This time, the drawing will be automatic: we will simply
    use events to exit the program.<br />
    <br .>
    The shape we will draw will be made of several lines and
    circles in rotation, drawn recursively.<br />
    <br />
    Because this tutorial talks about "dancing", then graphics on screen
    will move! For this, we will learn how to use the real time clock of
    the bunny library.<br />
    <br />
    You will also learn how to display correctly in the bunny library:
    you will not draw anywhere but in a single function which is called
    under specific circumstances.<br />
    <br />
    This tutorial will also show you a way to broadcast your
    main data between different events.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_set_line@($Tt_bunny_buffer@ *$Starget@,
    $Kconst@ $Tt_bunny_position@ *$Scoordinates@,
    $Kconst@ $Tunsigned int@ *$Scolors@);
  </div>
  <p>
    This function will draw on $Starget@ a single line from the position
    in $Scoordinates@[0] to the position in $Scoordinates@[1],
    starting from $Scolors@[0] and gradually arriving to
    $Scolors@[1].
    <br />
    <br />
  </p>
  <div class="prototype">
    $Tvoid@ $Sbunny_set_circle@($Tt_bunny_buffer@ *$Starget@,
    $Tt_bunny_position@ $Scoordinate@,
    $Tt_bunny_position@ $Sradius@,
    $Tunsigned int@ $Scolor@);
  </div>
  <p>
    This function will draw on $Starget@ a single circle with its
    center at position $Scoordinate@ and with its width and height
    in $Sradius@ and color in $Scolor@. To draw a real circle
    instead of an ovoid, $Sradius.x@ must equal $Sradius.y@.
    <br />
    <br />
  </p>
  <div class="prototype">
    $Tvoid@ $Sbunny_set_loop_main_function@($Tt_bunny_loop@ $Sloop_function@);
  </div>
  <p>
    This function is guarantee to be averagely called at a given frequency.
    The frequency is given throught the second parameter of the bunny_loop
    (or bunny_loop_mw, we will say later) function. This is the "loop main function"
    because of this. It exploits the real time clock of the bunny library.
    <br />
    <br />
  </p>
  <div class="prototype">
    $Tvoid@ $Sbunny_set_display_function@($Tt_bunny_display@ $Sdisplay_function@);
  </div>
  <p>
    This function is called when the program needs to refresh its display.
    It is called if there is enough time at the end of the whole main loop
    and a single time per loop.<br />
    <br />
    What does that mean? It means if your program became very laggy a short
    moment and a lot of calls to your loop function is made to catch up, then
    no call to display will be made if there is not enough time, or a single
    one if there is enough.<br />
    <br />
    There is a security that prevent the screen from being frozen: even if
    the main loop is really slow, there will always be at least one display
    every twenty loops.
    <br />
    <br />
  </p>
  <br />
  <hr />
  <br />
  <p>
    This program is a little more complex than simply drawing circle
    and lines, in order to bring a little more fun. This paragraph will
    explain to you what is going on. We will start with the main data
    definition:
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/252_rl_main_data.c"); ?>
    </div>
    This structure contains a window and a step attribute that will be
    used to store the animation <b>progression</b>.<br />
    <br />
  </p>
  <hr />
  <br />
  <p>
    The loop function will be quite empty: the program does almost nothing
    else than displaying things on screen, but it got a few off screen work too!
    The animation progression is, for example, off screen, even if it has
    to do with what will be displayed!<br />
    Understand this: <b>loop function has to do with everything that
    must be real time synchronized</b>... if the animation progression
    was outside, it may changed depending of machine performences!
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/253_rl_main_loop.c"); ?>
    </div>
  </p>
  <hr />
  <br />
  <p>
    The display function is where most of the work is made.
    First, we fill the whole screen with a very transparent black (25% opacity only),
    so everything on screen is not whipped directly must transit to black.<br />
    This is a quite cheap (<b>on GPU</b>) fashion to create trails.<br />
    <br />
    The objective of the following part is to get a circle moving likes it is in 3D.
    <br />
    <br />
    So, right after screen cleaning, we set two $Tt_bunny_position@ structures,
    one for the size of the circle and the other one the the position.<br />
    <br />
    Without surprise, the center of the circle is the middle of the window.<br />
    The size of the circle will vary accordingly to the value of $Sstep@ inside
    the main data structure. Using the $Scos@ or $Ssin@ function with $Sstep@ will
    generate a value between -1 and 1 that we will multiply with the maximum
    space we can take inside the window without going out, consider its size
    and the position of the circle.<br />
    Note that we use $Scos@ <b>and</b> $Ssin@ so the size of the circle will
    be altered in a way it look likes 3D. If we do not want this, simple use
    $Scos@ or $Ssin@ on <b>both</b> the computation of $Scircle_size.x@ and
    $Scircle_size.y@ will keep the circle facing the user.<br />
    <br />
    Ultimately, we call bunny_set_circle to draw our circle.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/254_rl_circle.c"); ?>
    </div>
  </p>
  <hr />
  <br />
  <p>
    Here is the hardest part. In this part, we will draw wings on the disk part
    of the circle.<br />
    We start by creating two arrays: an array of color, and an array of
    position. We need them for calling bunny_set_line. Colors are set immediatly,
    and the first coordinate is also set immediatly: all lines will start
    from the center of the circle.<br />
    <br />
    Additionnal, we set $Sadditional_step@, a double which will be used
    as loop index. The content of the loop will be useful to set to some values
    to the second coordinate of the line.<br />
    <br />
    Here is how we create those wings: we will draw circle rays going shorter
    and shorter. When entering the loop, we set a first line going from
    the center of the circle to the border of the circle, and then, another
    rays softly shifted and shorter, and then another one, etc.<br />
    <br />
    The $Scos/sin@(2 * data->step + additional_step) is used to compute the angle
    of the circle: As we want wings to turn, we need data->step because
    it evolves constantly because of loop_function. Additionnaly, because we
    need to have several lines shifted to create wings, we add it to
    additional_step. The 2.3 coefficient is present to break the synchronicity
    between the circle move and the wing move.<br />
    <br />
    This call to $Scos/sin@ give a coefficient we will multiply by the circle
    size to the wings scale follow the circle scale. By multiplying it by
    (1 - additional_step), considering additional_step goes from 0 to 1,
    it means additional lines will be shorter and shorted.<br />
    <br />
    As you may notice, there is two calls to bunny_set_line: this is because
    to create a single rays, two calls are needed in order to have a gradiant
    from red on borders to black on center. So one line is drawn from a side
    of the circle to the center, and another one from the opposite to the
    circle.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/255_rl_lines.c"); ?>
    </div>
  </p>
  <hr />
  <br />
  <p>
    Ultimately, we call bunny_display to refresh the screen output will all
    our drawings and we exit the function.<br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/256_rl_display.c"); ?>
    </div>
  <hr />
  <br />
  <p>
    Here is the full program. You may notice some parts were not explained
    before: the key handling function and the main you may understand alone.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/251_rotative_lines.c"); ?>
    </div>
  </p>
</div>
