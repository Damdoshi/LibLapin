<div class="prototype">
  Macro
  $Ttype@ $Sbunny_queue_front@($Tt_bunny_queue@ *$Squeue@, $Stype@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the element that is at the front of the sent Queue.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_queue@ *$Squeue@:<br />
      $A The queue to extract the front element from.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the element you want to extract. For example:<br />
      <br />
      $A $A int *ptr;<br />
      <br />
      $A $A ptr = bunny_queue_front(queue, $Tint@*);
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function returns the front element of the sent Queue or $CNULL@ if there
      is none.
    </li>
  </ul>
</div>


