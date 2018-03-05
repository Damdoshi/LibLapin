<div class="prototype">
  $Tvoid@ $Sbunny_capture_get_size@(
  $Kconst@ $T t_bunny_capture@ *$Scapture@
  $T t_bunny_size @ * $Sout@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return throught $Sout@ the size in pixels of the sent camera capture.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $T t_bunny_capture @ *$S capture @:<br />
      $A The capture to inspect
    </li>
    <li>
      $T t_bunny_size @ * $Sout@:
      $A An output parameter that will contain the size in pixel of $Scapture@.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_capture</li>
    <li>bunny_capture</li>
    <li>bunny_capture_to_pixelarray</li>
  </ul>
</div>

