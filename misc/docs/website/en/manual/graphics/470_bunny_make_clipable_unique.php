<div class="prototype">
  $Tbool@ $Sbunny_make_clipable_unique@(
  $Tt_bunny_clipable@ *$Sclipable@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A In the bunny library, some bottom level ressources are shared. This means
  that when you load several times the same picture, the picture
  itself is only loaded once and then it is given to multiples holders.<br />
  <br />
  Sometimes, you only base your work on a picture but plan to edit
  it to create a new one... And editing it would edit all sounds played
  by all other holders, so before doing it, you will need to call
  bunny_make_picture_unique so your picture got duplicated and pulled
  out the ressource manager.<br />
  <br />
  In t_bunny_clipable, shared parts are the private side. In t_bunny_pixelarray,
  they include the $Spixels@ array itself and all t_bunny_clipable shared parts.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_clipable@ *$Sclipable@:<br />
      $A The clipable to turn unique.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Return $Ctrue@ if everything went well. $Cfalse@ if instead it went wrong.
  </p>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Vbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.<br />
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function or subfunctions may be tagged with
    $L"sound"@
    labels.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_clipable</li>
  </ul>
</div>

