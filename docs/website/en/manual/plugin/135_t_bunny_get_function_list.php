<div class="prototype">
  $Ktypedef@ $Kconst@ $Tt_bunny_prototype@ *(*$Tt_bunny_get_function_list@)(void);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This function type is the one that <b>must</b> be defined inside
  any bunny plugin wanabe to become effectively a bunny plugin. This
  function is the function __get_function_list, and it must returns
  an array of t_bunny_prototype that <b>should</b> be statically
  allocated and that describes every function you want to be called
  with bunny_plugin_call or bunny_plugin_callv and every script
  that use those functions to work.<br />
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_prototype</li>
    <li>bunny_new_plugin</li>
  </ul>
</div>

