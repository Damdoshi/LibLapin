<div class="prototype">
  $Ktypedef struct@ $Tt_bunny_subprocess@<br />
  {<br />
  $A $T pid_t @ $S pid @ ;<br />
  $A $T int   @ $S stdin @ ;<br />
  $A $T int   @ $S stdout @ ;<br />
  $A $T int   @ $S stderr @ ;<br />
  $A $T int   @ $S custom_data_input @ ;<br />
  $A $T int   @ $S custom_data_output @ ;<br />
  $A $T int   @ $S custom_command_input @ ;<br />
  $A $T int   @ $S custom_command_output @ ;<br />
<br />
  } $Tt_bunny_subprocess@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_subprocess serve two purpose: the first one is to be
  filled with boolean values to indicates to bunny_popen which inputs and outputs to create.
  The second one is to retrieve file descriptor that match those inputs and outputs.
  <br />
  <br />
  The $Spid@ field is ignored on the first step, but return the forked processed
  pid on the second one.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tpid_t@ $Spid@:<br />
      $A The pid of the forked process. This attribute is an output.
    </li>
    <li>
      $Tint@ $Sstdin@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the stdin of the forked program.
    </li>
    <li>
      $Tint@ $Sstdout@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the stdout of the forked program.
    </li>
    <li>
      $Tint@ $Sstderr@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the stderr of the forked program.
    </li>
    <li>
      $Tint@ $Scustom_data_input@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the input file descriptor 3 of the forked program.<br />
      The file descriptor value may be different on forked program side,
      depending of previously opened file descriptor.<br />
      The only guarantee LibLapin give you is that bunny_popen decriptors value
      are following eachother depending of which one you required.
    </li>
    <li>
      $Tint@ $Scustom_data_output@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the output file descriptor 4 of the forked program.<br />
      The file descriptor value may be different on forked program side,
      depending of previously opened file descriptor.<br />
      The only guarantee LibLapin give you is that bunny_popen decriptors value
      are following eachother depending of which one you required.
    </li>
    <li>
      $Tint@ $Scustom_command_input@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the input file descriptor 5 of the forked program.<br />
      The file descriptor value may be different on forked program side,
      depending of previously opened file descriptor.<br />
      The only guarantee LibLapin give you is that bunny_popen decriptors value
      are following eachother depending of which one you required.
    </li>
    <li>
      $Tint@ $Scustom_command_output@:<br />
      $A Send $Ctrue@ or $Cfalse@ to open or not a pipe between
      a file descriptor that will be stored in this attribute in the main
      program and the output file descriptor 6 of the forked program.<br />
      The file descriptor value may be different on forked program side,
      depending of previously opened file descriptor.<br />
      The only guarantee LibLapin give you is that bunny_popen decriptors value
      are following eachother depending of which one you required.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_popen</li>
    <li>bunny_pclose</li>
  </ul>
</div>

