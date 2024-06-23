<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_history@<br />
  {<br />
  $A$Kconst@ $Tsize_t@ $Sframe_size@;<br />
  $A$Kconst@ $Tsize_t@ $Slast_frame_time@;<br />
  $A$Kconst@ $Tsize_t@ $Soldest_frame_time@;<br />
  $A$Kconst@ $Tsize_t@ $Snbr_frame@;<br />
  $A$Tvoid@ *$Slast_frame@;<br />
  <br />
  } $Tt_bunny_history@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A The t_bunny_history structure is made to store the state of an object
  throught time. Each field can be seen as a meta data of the underlying recorded
  states.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $Sframe_size@:<br />
      $AThe size of a single frame. The size of the element pointed by $Slast_frame@.
    </lI>
    <li>
      $Kconst@ $Tsize_t@ $Slast_frame_time@:<br />
      $AThe more recent frame time index in the current history.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Soldest_frame_time@:<br />
      $AThe more ancient frame time index in the current history.
    </li>
    <li>
      $Kconst@ $Tsize_t@ $Snbr_frame@:<br />
      $AHow many frames are stored inside the current history.
      You can get the approximative memory consumption by multiplying
      this field with the frame_size.
    </li>
    <li>
      $Tvoid@ *$Slast_frame@:<br />
      $AA pointer to the more recent frame in the current history.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_history</li>
    <li>bunny_delete_history</li>
  </ul>
</div>
