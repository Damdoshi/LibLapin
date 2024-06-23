<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_letter@<br />
  {<br />
  $A $T int @ $Snb_edge@;<br />
  $A $T t_bunny_vector_font_line_coord@ $S edge @[5];<br />
  <br />
  } $Tt_bunny_letter@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure contains a specific amount of lines that compose
  a letter.<br />
  Characters amplitude is 0-20 on both axis.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $T int @ $S nb_edge @:<br />
      $A How many lines are composing the letter.
    </li>
    <li>
      $T t_bunny_vector_font_line_coord @ $S edge @[5]:<br />
      $A Lines composing the letter. Only use $Snb_edge@! Other
      indexes in the array do not have a defined value.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_vector_font_line_coord</li>
    <li>gl_vector_font</li>
  </ul>
</div>
