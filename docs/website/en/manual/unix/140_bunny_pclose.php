<div class="prototype">
  $Tint@ $Sbunny_pclose@(
  $Tt_bunny_subprocess@ *$Ssubproc@,
  $Tint@ $Sdelay_in_seconds
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The bunny_pclose close communication and end a subprogram (if not already terminated)
  after the sent delay. It may return faster if the program end before the delay is
  consumed.<br />
  <br />
  If the delay is consumed, a SIGINT is sent to the process with the pid stored inside $Ssubproc@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_subprocess@ *$Ssubproc@:<br />
      $A A structure that store the pid of the process to terminate and
      file descriptor of opened communications.
    </li>
    <li>
      $Tint@ $Sdelay_in_seconds@:<br />
      $A The delay before killing the subprocess with SIGINT.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      If the subprocess was terminate correctly, the function returns its return value.
    </li>
    <li>
      If the subprocess was killed, the function return 0.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_subprocess</li>
    <li>bunny_popen</li>
  </ul>
</div>

