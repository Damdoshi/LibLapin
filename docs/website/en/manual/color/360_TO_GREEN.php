<div class="prototype">
  Macro
  $Tunsigned int@ $S TO_GREEN @ ($Tunsigned char@ $Scolor_component@)
</div>

<div class="resume">
  <h3>Description</h3>
  This macro transform the sent color component to a valid component value that
  could be added or binary OGreen to a full 4 byte color. Example:
  <br />
  <br />
  unsigned int color = BLACK;<br />
  <br />
  color |= TO_GREEN(128); // The color is now draw green
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tunsigned char@ $Scolor_component@:<br />
      $A The color component that will be turned into a 4 byte color format.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      This function return a 4 byte color format version of the send
      1 byte color component.
    </li>
  </ul>
</div>


