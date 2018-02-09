<div class="prototype">
  $Sbool@ $Sbunny_list_fast_foreach@(
  $Tt_bunny_threadpool@ *$Spool@,
  $Tt_bunny_list@ *$Slist@,
  $Tvoid@ (*$Sfunction@)($Tvoid@ *$Sdata@, $Tvoid@ *$Sparam@),
  $Tvoid@ *$Sparam@,
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Call $Sfunction with every data of $Slist@ as first parameter throught
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
      $Tt_bunny_list@ *$Slist@:<br />
      $A The list that got the datas you want to be computed by
      bunny_list_fast_foreach.
    </li>
    <li>
      $Tvoid@ (*$Tfunction@)($Tvoid@ *$Sdata@, $Tvoid@ *$Sparam@):<br />
      $A The function to call with every data of the sent $Smap@.
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
    <li>bunny_list_foreach</li>
  </ul>
</div>

