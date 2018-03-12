<div class="prototype">
  Animate a sprite using pictures
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    This chapter is quite important: sprites are often the fondation
    video game programs. In this chapter, you will learn how to
    edit a t_bunny_clipable to get what you wish on screen.
    <b>
      This chapter is not about t_bunny_sprite: if you want
      to learn how to use them, go to Animate a sprite using sprites
      tutorial.
    </b><br />
    <br />
    Sprite sheets are pictures containing a single character with
    different pose and that are supposed to be played one after
    the other to make it animated. To do so, you will first need
    a sprite sheet. We will use this <a href="res/sprite.png">one</a>, download
    it. The program you will make will display this sprite
    moving on screen while being animated, in four direction.<br />
    <br />
    This sprite contains two animation: the first one on the first line
    contains only a single frame (so.. technically, it is not an animation).
    The second one on the second line contains height frames.<br />
    <br />
    To complete a little more, we will also learn a new event: the mouse
    wheel event.
  </p>
  <br />
  <br />
  <div class="prototype">
    $Tt_bunny_picture@ *$Sbunny_load_picture@($Kconst@ $Tchar@ *$Sfile@);
  </div>
  <p>
    This function allows you to load a picture file like the
    <a href="res/sprite.png">sprite sheet we will use</a>. It may returns $CNULL@
    on error and the generated t_bunny_picture must be freed with
    bunny_delete_clipable.
  </p>
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_delete_clipable@($Tt_bunny_clipable@ *$Sclipable@);
  </div>
  <p>
    The function that is useful to delete clipable.
  </p>
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_blit@($Tt_bunny_buffer@ *$Starget@,
    $Kconst@ $Tt_bunny_clipable@ *$Sclipable@,
    $Kconst@ $Tt_bunny_position@ *$Sposition@);
  </div>
  <p>
    This function is very important: it is the one that will draw
    your picture on the surface you want it to be: the window, most of times.
    Third third parameter is optional and can be set to $CNULL@: in this case,
    the $Sposition@ field inside the $Sclipable@ parameter will be used instead.
  </p>
  <br />

  <div class="prototype">
    $Tsize@ $Sbunny_get_frequency@($Tvoid@);
  </div>
  <p>
    Get the frequency sent to bunny_loop. Should be used when trying
    to compute speeds instead of pure arbitrary value. For example,
    300.0 / bunny_get_frequency() if use to move an object on screen
    will produce a double value that can be used each main loop. It means
    300 pixel per seconds which is a really more convenient way to
    write such a thing than an arbitrary 12 and of course it keeps
    the same speed even if you change the loop frequency, which
    is really better!<br />
    It means you can increase the bunny_loop frequency accordingly
    to performances, to allow more frame per seconds.
  </p>
  <br />

  <div class="prototype">
    $Kconst@ $Tbool@ *$Sbunny_get_keyboard@($Tvoid@);
  </div>
  <p>
    This function returns an array which contains all keys status. It will
    works <b>only if a keyboard response is set</b>. In our case, it is set
    to catch the escape key and exit the program.<br />
    The purpose of this function is to get status instead of events like
    key pressed or released. It is convienent to use, especially in the
    main loop of your program.
  </p>
  <br />

  <div class="prototype">
    $Tvoid@ $Sbunny_set_wheel_response@($Tt_bunny_wheel@ $Sfunction@);
  </div>
  <p>
    This function allow you to define a function that will be called
    when a mouse wheel is scrolled. We will use it to scale the sprite.
  </p>

  <br />
  <hr />
  <br />
  <p>
    This is the main data that will be sent to all events. You
    can find the window inside it, the picture containing the sprite
    you have downloaded before and $Sanimation_frame@.
    I indicates which animation frame will be displayed: it is a
    double because we need it to be able to evolve with a step like
    10.0 / bunny_get_frequency(), that means "10 frames per second"
    which may not be an integer... but it is used as an integer when
    it came to picking up a specific frame, as we will see later.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/302_sp_data.c"); ?>
    </div>
  </p>

  <br />
  <hr />
  <br />
  <p>
    Let it start with the display function of the program. It is quite
    straightforward:
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/303_sp_display.c"); ?>
    </div>
  </p>

  <br />
  <hr />
  <br />
  <p>
    Here is the beginning of the main, the part when the sprite will
    be initialized. The picture is first loaded and then fields are
    sets to specific values.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/304_sp_init.c"); ?>
    </div>
    <p>
      $Sclip_height@ and $Sclip_width@ are purely linked to the sprite
      itself: as you will see by opening the sprite sheet, a single
      character is 107*100 pixels.<br />
      <br />
      The origin field is by default on the top left corner. Sometimes
      it is convient, sometimes not. Right now, we are setting the
      origin to the center of the clip (remember: the clip is the part
      of the picture that is displayed when calling bunny_blit) so
      if we draw the sprite at the center of the window, the center of the
      clip will be at the center of the window, not the top left corner.<br />
      <br />
      The position field is by default 0, 0. We set it to the center
      of the window.<br />
      <br />
      Other fields are keeping their original value: 0 for $Srotation@.
      1, 1 for $Sscale@, 0 for $Sclip_x_position@ and 0 for $Sclip_y_position@.<br />
      <br />
      Color mask stay white so all sprite colors are unaltered.<br />
      <br />
      At the end, we set $Sanimation_frame@ from the main data to 0,
      se when we will animate the sprite, it will start with the first
      frame.
    </p>
  </p>

  <br />
  <hr />
  <br />
  <p>
    The $Sset_clip_to_set@ is a small sub procedure called in the loop_function
    and that factorize some operations:<br />
    <br />
    It takes the main data structure and set the sprite clip to the
    appropriate frame. To do so, it use $Sanimation_frame@ from the main
    data, casted as an integer, and use the modulo operator to keep it
    in [0; 8[ and always growing. By multiplying this integer after that by
    $Sclip_width@ of the sprite, we positionate the clip on the right frame
    of the current animation.<br />
    <br />
    We set to the sent animation the $Sclip_y_position@ accordingly to
    the specification of the sprite sheet: by multiplying $Sanimation@
    by $Sclip_height@, we set the right line for the requested animation.<br />
    <br />
    The $Srotation@ field may appeir strange to you: The sub procedure
    receives a rotation value but apply it only if it is a multiple of 90.
    This is only for conveniance, this is not animation related: it is made
    so when someone want to call the subprocedure without changing the
    rotation, this person will be able to do it simply by sending a fitting value.
    <br />
    <br />
    The $Sanimation_frame@ is increased by a value which will make it go
    as fast as 18 frames per seconds.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/305_sp_clip.c"); ?>
    </div>
  </p>

  <br />
  <hr />
  <br />
  <p>
    This is the main loop of the program. Every arrow keys are tested
    and provoke reactions of your program.<br />
    We enter the first $Kif@ if the left arrow key is currently pressed:
    it means the character must walk to the left side of the screen.
    So we call the sub procedure $Sset_clip_to_set@ with the main data,
    the animation number (1 being the line on the sprite sheet: the walking animation
    in our case) and the angle of the sprite rotation we need.<br />
    Because the sprite in our sprite sheet is looking up, when going left,
    we need it to being rotated by -90 degrees.<br />
    After that, the effectively change the sprite position on screen by
    removing a value which will make it go as fast as 100 pixels per seconds.<br />
    <br />
    Note that in computing, the coordinate system place the origin on the top
    left corner of the window/screen, goes from left to right on X and from top
    to bottom on Y. It is not like in mathematics, it may be strange at the
    beginning, but you will get accustomed to. I do not recommand making
    abstraction to change this: that would lost any computer people working with you.
    <br />
    <br />
    If we did not enter any $Kif@, then we set the $Sanimation_frame@ to 0 to
    reset the animation and call $Sset_clip_to_set@ with the main data,
    the animation number 0 (the "stay still animation") and an angle which
    is not a multiple of 90 and so will not provoke a rotation change in
    the $Sset_clip_to_set@ sub procedure so we keep the current orientation.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/306_sp_loop.c"); ?>
    </div>
  </p>

  <br />
  <hr />
  <br />
  <p>
    The last thing, the wheel event response. We divide $Sdelta@ by five
    to get a smaller impact of the wheel. Currently, it means: add 100%
    of the original size for each 5 step of wheel. We use the scale
    on both the X and Y axis so the whole character is scaled and it look
    likes we got closer.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/307_sp_wheel.c"); ?>
    </div>
  </p>

  <br />
  <hr />
  <br />
  <p>
    The whole program.
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/301_sprite_with_pictures.c"); ?>
    </div>
  </p>
</div>
