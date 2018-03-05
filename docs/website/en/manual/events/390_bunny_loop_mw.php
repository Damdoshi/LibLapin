<div class="prototype">
  $Tt_bunny_response@ $Sbunny_loop_mw@(
  $Tt_bunny_window@ **$Swindow@,
  $Tsize_t@ $Snbr_win@,
  $Tuint8_t@ $Sfrequency@,
  $Tvoid@ *$Sdata@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function is a giant loop that handles events and real-time pacing.
  It manages $Snbr_win@ windows.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_window@ **$Swindow@:<br />
      $A Windows that will have their events managed by bunny loop. The array
      is $Snbr_win@ window long.
    </li>
    <li>
      $Tsize_t@ $Snbr_win@:<br />
      $A The length of the $Swindow@ array in cases.
    </li>
    <li>
      $Tuint8_t@ $Sfrequency@:<br />
      $A The frequency in Hertz of the event loop and the average frequency
      of calls to the function set with bunny_set_loop_main_function.
    </li>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A data that will be given to every event handlers, loop and
      display function. It should be your program main data.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    This function returns the first value returned by an event or display or loop
    function that is not $SGO_ON@ from t_bunny_event.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_set_loop_main_function</li>
    <li>bunny_set_display_function</li>
    <li>bunny_loop</li>
  </ul>
</div>

