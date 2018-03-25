<div class="prototype">
  $Ktypedef enum@ $Te_bunny_value_type@<br />
  {<br />
  $A $S BVT_VOID@ = $L'v'@,<br />
  $A $S BVT_INTEGER@ = $L'i'@,<br />
  $A $S BVT_DOUBLE@ = $L'd'@,<br />
  $A $S BVT_STRING@ = $L's'@,<br />
  $A $S BVT_POINTER@ = $L'p'@,<br />
  <br />
  } $Tt_bunny_value_type@;
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This enumeration is associated to the t_bunny_value union
  to indicates in which wayt it is exploited. This is some sort of runtime
  type casting: if the t_bunny_value inside the t_bunny_value is $SINTEGER,
  then the inside the union, the integer field must be the one in use.<br />
  <br />
  This enumeration is used by t_bunny_prototype to type return value and
  parameters of functions t_bunny_prototype represents.
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_value</li>
  </ul>
</div>

