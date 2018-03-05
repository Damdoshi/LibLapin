<div class="prototype">
  <b>C11</b> Macro
  $Tint@ $Sbunny_real_width@($Sbuffer_base_structure@*);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the displayed width of $Sbuffer_base_structure@.
  <br />
  Rotation is ignored.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Sbuffer_base_structure@:<br />
      $A A t_bunny_buffer*, t_bunny_picture*, t_bunny_clipable*,
      t_bunny_pixelarray* or t_bunny_font* that will have its display width
      computed accordingly to its complete size, clip size and scale.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    The computed width of the displayable sent element.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>
    Because it is based on _Generic, this macro cannot
    be provided in C++ and C version inferior to 2011.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_real_height</li>
  </ul>
</div>

