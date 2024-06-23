<div class="prototype">
  $Kconst@ $Tt_bunny_cipher_key@ *$Sbunny_default_key@($Tvoid@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Get the embedded key of the program, edit it if it was never done before
  and return it.
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The embedded key of your program, edited dynamically to prevent
    simple extraction of it.<br />
    The t_bunny_key_twist gl_bunny_my_key_twist
    global should be set by you to run your proper version of the
    key transformation.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>gl_bunny_my_key_twist</li>
    <li>t_bunny_key_twist</li>
  </ul>
</div>

