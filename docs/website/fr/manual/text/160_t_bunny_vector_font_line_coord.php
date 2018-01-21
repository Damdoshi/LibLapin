<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_vector_font_line_coord@<br />
  {<br />
  $A $T int @ $Sx0@;<br />
  $A $T int @ $Sy0@;<br />
  $A $T int @ $Sx1@;<br />
  $A $T int @ $Sy1@;<br />
  <br />
  } $Tt_bunny_vector_font_line_coord@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is part of the t_bunny_letter structure.
  It represents a single line in a 2D space, which goes from
  (x0, y0) to (x1, y1).
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $T int @ $S x0 @:<br />
      $A The beginning of the line on the X axis.
    </li>
    <li>
      $T int @ $S y0 @:<br />
      $A The beginning of the line on the Y axis.
    </li>
    <li>
      $T int @ $S x1 @:<br />
      $A The end of the line on the X axis.
    </li>
    <li>
      $T int @ $S y1 @:<br />
      $A The end of the line on the Y axis.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_letter</li>
    <li>gl_vector_font</li>
  </ul>
</div>
