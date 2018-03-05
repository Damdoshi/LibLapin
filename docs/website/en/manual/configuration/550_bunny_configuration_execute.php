<div class="prototype">
  $Tbool@ $Sbunny_configuration_execute@(
  $Tt_bunny_configuration@ *$Sconfiguration@,
  $Tbool@ $Srecursive@,
  $Tt_bunny_configuration@ *$Sparameters@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Execute scripts and expressions located in the sent node or behind.<br />
  Every scripts and expressions will be executed.<br />
  They will consider the root of the sent node as the root context.<br />
  The local context as the one containing local variables.<br />
  The parameter context as the sent one for parameters.<br />
  The artifical context is the context where the node is located, but can be
  modified by the "width" statement.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *S$configuration@:<br />
      $A The configuration node that serves as artifical context and that will be executed.
    </li>
    <li>
      $Tbool@ $Srecursive@:<br />
      $A If $Ctrue@, all fields under the sent one will be executed too.
    </li>
    <li>
      $Tt_bunny_configuration@ *$Sparameters@:<br />
      $A Parameters sent to the function inside $Sconfiguration@.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function was correctly executed. The result of the operation
      can be found in nodes themselves. It returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    Many error logs can happen when executing a script and a lot of them may not be
    related to the script execution itself but about what is executed. A simple
    error value is not enough to signify enough information, a look at logs is required.
  </p>
  <p>
    Logs written by this function are tagged with the $L"syntax"@ label.
  </p>
</div>

