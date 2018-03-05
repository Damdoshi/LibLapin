<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_stack_node@<br />
  {<br />
  $A $Tvoid@ *$Sdata@;<br />
  $A $Kstruct@ $Ts_bunny_stack_node@	*$Snext@;<br />
  <br />
  } $Tt_bunny_stack_node@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is the node in which every single data is referenced
  inside the stack.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tvoid@ *$Sdata@:<br />
      $A A pointer to a stored data.
    </li>
    <li>
      $Kstruct@ $Ts_bunny_stack_node@ *$Snext@:<br />
      $A The node following the current one or $CNULL@ if there is none.<br />
      This type is an inside type of the Stack module and should not be created by you.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_stack</li>
    <li>bunny_delete_stack</li>
  </ul>
</div>
