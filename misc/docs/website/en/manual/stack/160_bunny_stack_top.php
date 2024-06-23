<div class="prototype">
  Macro
  $Ttype@ $Sbunny_stack_top@($Tt_bunny_stack@ *$Sstack@, $Stype@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the element that is on top of the sent Stack.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_stack@ *$Sstack@:<br />
      $A The stack to extract the top element from.
    </li>
    <li>
      $Stype@:<br />
      $A The type of the element you want to extract. For example:<br />
      <br />
      $A $A int *ptr;<br />
      <br />
      $A $A ptr = bunny_stack_top(stack, $Tint@*);
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function returns the top element of the sent Stack or $CNULL@ if there
      is none.
    </li>
  </ul>
</div>


