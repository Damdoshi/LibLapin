<div class="prototype">
  $Tvoid@ $Sbunny_delete_trap@(
  $Tt_bunny_trap@ *$Strap@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Delete the sent trap from the system.
  Actually, it does not delete it but mark it for deletion.
  The function bunny_asynclock will delete it itself when browsing
  traps and seeing it is marked.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_trap@ *$Sfunction@:<br />
      $A The trap to delete.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_trap</li>
    <li>bunny_asynclock</li>
    <li>bunny_loop</li>
  </ul>
</div>

