<div class="prototype">
  $Tbool@ $Sbunny_stabilize_headtrack@(
  $Kconst@ $T t_bunny_area@ *$Sprevious_face_position@,
  $Tt_bunny_area@ *$Scurrent_face_position@,
  $Tdouble@ $Sspeed@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Smooth the movement on a detected face.<br />
  This function use directly bunny_smooth_move.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $T t_bunny_area @ *$S previous_face_position @:<br />
      $A The position of the previously detected face.
    </li>
    <li>
      $T t_bunny_area @ *$S current_face_position @:<br />
      $A The position of the currently detected face.
    </li>
    <li>
      $T double @ $Sspeed@:<br />
      $A The speed of the movement.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_smooth_move</li>
    <li>bunny_headtrack</li>
  </ul>
</div>

