<div class="prototype">
  $Tvoid@ $Sbunny_set_context@($Kconst@ $Tt_bunny_context@ *$Scontext@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set all callbacks of bunny loop in a single call with function pointers
  from $Scontext@.<br />
  <br />
  A C++ version, Bunny::SetContext is available in the Context module.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_context@ *$Scontext@:<br />
      $A The context to set to the bunny loop
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_context</li>
    <li>t_bunny_anonymous_context</li>
    <li>bunny_get_context</li>
  </ul>
</div>

