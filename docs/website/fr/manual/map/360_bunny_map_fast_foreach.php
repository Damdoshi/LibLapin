<div class="prototype">
  $Sbool@ $Sbunny_map_fast_foreach@(
  $Tt_bunny_threadpool@ *$Spool@,
  $Tt_bunny_map@ *$Smap@,
  $Tvoid@ (*$Sfunction@)($Tt_bunny_map@ *$Smap@, $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfunction with every nodes of $Smap@ as first parameter throught
  threads from $Spool@, one after the other. Send $Sparam@ as second parameter.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_threadpool@ *$Spool@:<br />
      $A The thread pool that power the foreach.
    </li>
    <li>
      $Tt_bunny_map@ *$Smap@:<br />
      $A The map that got the nodes you want to be computed by
      bunny_map_fast_foreach.
    </li>
    <li>
      $Tvoid@ (*$Tfunction@)($Tt_bunny_map@ *$Smap@, $Tvoid@ *$Sparam@):<br />
      $A The function to call with every nodes of the sent $Smap@.
    </li>
    <li>
      $Tvoid@ *$Sparam@:<br />
      $A The parameter sent to $Sfunction@ as the second one.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On complete $Bsuccess@, the function returns $Ctrue@.
    </li>
    <li>
      On $Bfailure@, it returns $Cfalse@. Failire indicates all
      datas were not treated by threads, some of them may have been
      treated by the main thread because of a thread pool memory exhaustion.
      Elements are always <b>all</b> computed.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_map_foreach</li>
  </ul>
</div>

