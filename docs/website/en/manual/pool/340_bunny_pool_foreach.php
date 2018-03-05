<div class="prototype">
  $Tvoid@ $Sbunny_pool_foreach@(
  $Tt_bunny_pool@ *$Spool@,
  $Tt_bunny_pool_foreach@ $Sfunction@,
  $Tvoid@ *$Sparam@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Execute the sent $Sfunction@ on each element of the sent $Spool@
  Give to the executed function $Sparam@ as second parameter, data
  from $Spool@ being the first.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_pool@ *$Spool@:<br />
      $A The collection that will be use.
    </li>
    <li>
      $Tt_bunny_function@ $Sfunction@:<br />
      $A The function that will be called for each element of the sent
      $Spool@. Parameters will be an element from the array and $Sparam@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A A data that will be sent as second parameter of $Sfunction@.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_pool_foreach</li>
    <li>bunny_pool_fast_foreach</li>
  </ul>
</div>

