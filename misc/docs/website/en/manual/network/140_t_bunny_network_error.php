<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_network_error@<br />
  {<br />
  $A $Tt_bunny_comptype@ $Scomtype@;<br />
  $A $Tunsigned int@ $Stime@;<br />
  $A $Tt_bunny_comerror@ $Serrortype@;<br />
  <br />
  } $Tt_bunny_network_error@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is used by t_bunny_communication if its t_bunny_comtype
  is $SERROR@. It indicates an error occured during network scheduling.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_comtype@ $Scomtype@:<br />
      $A Should contain $SERROR@ if this is effectively a t_bunny_network_error.
    </li>
    <li>
      $Tunsigned int@ $Stime@:<br />
      $A Time that was not consumed by the scheduling operation returning
      the t_bunny_communication.
    </li>
    <li>
      $Tt_bunny_comerror@ $Serrortype@:<br />
      $A The error type.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>t_bunny_communication</li>
    <li>t_bunny_comtype</li>
    <li>t_bunny_comerror</li>
  </ul>
</div>
