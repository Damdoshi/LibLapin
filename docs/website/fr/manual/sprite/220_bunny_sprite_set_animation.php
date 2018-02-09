<div class="prototype">
  <b>C11</b> Macro
  $Tbool@ $Sbunny_sprite_set_animation@($Tt_bunny_sprite@ *$Ssprite@, $Sanimation@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Set to a specific animtaion the sent sprite.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_sprite@ *$Ssprite@:<br />
      $A The sprite to edit.
    </li>
    <li>
      $Sanimation@:<br />
      $A The animation to set. It can be a string containing the configuration
      name or a hash returned by bunny_sprite_animation_name from the configuration
      name.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>Return $Ctrue@ if the animation was existing and set.</p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>
    Because it is based on _Generic, this macro cannot
    be provided in C++ and C version inferior to 2011.
    <br />
    You may use bunny_sprite_set_animation_name or
    bunny_sprite_set_animation_id instead to set an animation
    from a string or a hash.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sprite_animate</li>
    <li>bunny_load_sprite</li>
  </ul>
</div>

