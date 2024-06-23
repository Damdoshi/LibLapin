<div class="prototype">
  $Tbool@ $Sbunny_headtrack@(
  $Kconst@ $T t_bunny_capture@ *$Scapture@,
  $Tt_bunny_area@ *$Sarea@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set into $Sarea@ the first detected face in capture.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $T t_bunny_capture @ *$S capture @:<br />
      $A The camera capture on which will runs the detection.
    </li>
    <li>
      $T t_bunny_area @ *$S area @:<br />
      $A The function output. The first detected face will have
      its coordinates stored in this structure.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The function returns $Ctrue@ if a face was detected.
    $Cfalse@ if not. If no face was detected, $Sarea is left untouched.
  </p>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CBE_CANT_GENERATE_RESSOURCE@:<br />
      <p>
        The system needs a ressource it generates at the first call and
        it failed to generate it.
      </p>
    </li>
    <li>
      $CEINVAL@:<br />
      <p>
        The sent capture was $CNULL@.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"camera"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_stabilize_headtrack</li>
  </ul>
</div>

