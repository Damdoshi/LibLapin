k<div class="prototype">
  $Ktypedef union@ $Tu_bunny_color@<br />
  {<br />
  $A $Tuint32_t@ $Sfull@;<br />
  $A $Tuint8_t@ $Sargb@[4];<br />
  $A $Tint8_t@ $Smod@[4];<br />
  <br />
  } $Tt_bunny_color@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_color union is 4 bytes length and contains a color. This
  color, thanks to its attributes, can be accessed in several ways, matching
  several usage.<br />
  <br />
</div>
<hr />

<div class="parameters">
  <h3>Symbols</h3>
  <ul>
    <li>
      $Tuint32_t@ $Sfull@:<br />
      $A This attribute offer the first obvious usage of t_bunny_color.
      It is to use it as an integer.
      With this attribute, you can simply move the full color easily. One drawback
      is that you cannot make efficient math on it.
    </li>
    <li>
      $Suint8_t@ $Sargb@[4]<br />
      $A This array of 4 bytes store the same color as $Sfull@, but allows you
      to access each color component separately. Used with the t_bunny_rgb symbolic
      constant $SALPHA_CMP@, $SRED_CMP@, $SGREEN_CMP@ and $SBLUE_CMP@, you can
      access readably the field you need.<br />
      Thanks to this field, you can make efficient math on colors, but you cannot
      do all kind of operations because of the nature of unsigned integers. This
      field is cool to store colors, but not color offset because of this.
    </li>
    <li>
      $Tint8_t@ $Smod@[4]:<br />
      $A This array of 4 bytes do not really store a color. It stores a color offset.
      It can be, for example, added to a color, or subtract, with care about overflow, of course.
      <br />
      <br />
      You may find it quite limited because of its integer nature and this is right. It may
      be inefficient: if it is, make your own 4 float array.
    </li>
  </ul>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_rgb</li>
  </ul>
</div>

