<div class="prototype">
  $Tint@ $Sbunny_popen@(
  $Tt_bunny_subprocess@ *$Ssubproc@,
  $Tchar@ **$Senviron@,
  $Tsize_t@ $Snbr_param@,
  $S...@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The bunny_popen function opens a process and creates several pipes
  as required. Pipes are unidirectional but they are several so you can
  create complex communications if needed.<br />
  <br />
  The subprocess and associated communications must be ended with
  bunny_pclose.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_subprocess@ *$Ssubproc@:<br />
      $A A structure that configure the way the communication will be established
      between the main process and the new one. The pid of the children will be stored
      inside the structure after the process forked. $Ctrue@ fields will be overwritten
      by file descriptor values of opened pipes.
    </li>
    <li>
      $Tchar@ **$Senviron@:<br />
      $A The environment of the newly created process.
    </li>
    <li>
      $Tsize_t@ $Snbr_param@:<br />
      $A The amount of parameters sent in the variadic part of the function.
    </li>
    <li>
      $S...@:<br />
      Variadic parameters. Parameters sent here are command line like: the first
      parameter is the command, other parameters are the command parameter. For example:<br />
      <br />
      ls -l -a<br />
      <br />
      Will become:<br />
      <br />
      bunny_popen( ... , 3, "ls", "-l", "-a");
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns the pid of the created process.
    </li>
    <li>
      On $Bfailure@, it returns -1.
    </li>
  </ul>
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
      $CEMFILE@:<br />
      <p>
        The per-process limit on the number of open file descriptors has been reached.
      </p>
    </li>
    <li>
      $CENFILE@:<br />
      <p>
        The system-wide limit on the total number of open files has been reached.
      </p>
    </li>
    <li>
      $CEAGAIN@:<br />
      <p>
        A system-imposed limit on the number of threads was encountered.
      </p>
    </li>
    <li>
      $CENOSYS@:<br />
      <p>
        fork() is not supported on this platform
      </p>
    </li>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the $L"unix"@ label.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_subprocess</li>
    <li>bunny_pclose</li>
  </ul>
</div>

