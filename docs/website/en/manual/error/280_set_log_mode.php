<div class="prototype">
  $Tvoid@ $Sbunny_set_log_mode@($Tbool@ $Scomplete@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set if you prefer having complete logs or only human readable message.<br />
  The complete format is:<br />
  FAILURE/LOG [tags][timestamp][file:line][Error type][Detailed message]<br />
  <br />
  If the log is an error, the incomplete format is:<br />
  Error type - Detailed message<br />
  <br />
  If it is a standard log, the incomplete format is:<br />
  Detailed message
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tbool@ $Scomplete@:<br />
      $A $Ctrue@ or $Cfalse@ if you want complete or incomplete log.
    </li>
  </ul>
</div>

