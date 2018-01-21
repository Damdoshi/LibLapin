<div class="prototype">
  $Tt_bunny_window@
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  The t_bunny_window structure represents a window opened on screen.
  Its structure is made of a t_bunny_buffer, which contains informations
  like its width and height - a thing that is common to every 2D surface
  in LibLapin - so it can be used anywhere a t_buffer_buffer can be used.
  <br />
  <br />
  The window is opened with bunny_start or bunny_start_style and closed with bunny_stop.<br />
  Windows are write only - they can only be read by the eyes of users.
  To show the window content on screen, a call to bunny_display is required.
  Each call refresh the window content.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ $Sbuffer@:<br />
      $A The buffer structure which contains the width and height and
      allows you to use a t_bunny_window everywhere you can use a t_bunny_buffer.
    </li>
    <li>
      $Kconst@ $Tchar@ * $Kconst@ $Sname@:<br />
      $A The name of the window. Set when the window was open
      throught the name parameter of bunny_start or bunny_start_style.
    </li>
  </ul>
</div>

