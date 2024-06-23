<div class="prototype">
  Macro
  $Tunsigned int @ $S GET_COLOR @ ($Tunsigned int@ $Scolor@)
</div>

<div class="resume">
  <h3>Description</h3>
  This macro extract the color part of the sent 4 byte color. For example, sending
  an half transparent purple will return a transparent purple: only the three
  bytes composing the red, green and blue are returned. The fourth byte containing
  the opacity is erased and set to 0.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned int@ $Scolor@:<br />
      $A A 4 byte color that will be partially erased to remove its opacity
      component.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return a 4 byte color format version of the send
      color without its opacity byte.
    </li>
  </ul>
</div>
