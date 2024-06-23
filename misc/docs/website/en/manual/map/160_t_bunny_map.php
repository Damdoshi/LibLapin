<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_map@<br />
  {<br />
  $A $Kconst@ $Tvoid@ * $Kconst@ $Sdata@;<br />
  $A $Kconst@ $Tvoid@ * $Kconst@ $Skey@;<br />
  $A $Tsize_t@ $Snbr_children@;<br />
  $A $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sup@;<br />
  $A $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sright@;<br />
  $A $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sleft@;<br />
  $A $Kconst@ $Tt_bunny_map_cmp@ $Scmp@;<br />
  $A $Kconst@ $Tt_bunny_map_dup@ $Sdup@;<br />
  $A $Kconst@ $Tt_bunny_map_del@ $Sdel@;<br />
  $A $Kconst@ $Tvoid@ * $Kconst@ $Sparam@;<br />
  <br />
  } $Tt_bunny_map@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is at the same time the map container and
  a node from it. It should be manipulated with map functions.
  It is created by bunny_new_map and deleted by bunny_delete_map.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $Sdata@:<br />
      $A A data store inside this current node.
    </li>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $Skey@:<br />
      $A The key of the current node.
    </li>
    <li>
      $Tsize_t@ $Snbr_children@:<br />
      $A How many nodes are under this one, directly or indirectly.
    </li>
    <li>
      $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sup@:<br />
      $A The parent of the current node. If $CNULL@, it means
      the current node is a root node.
    </li>
    <li>
      $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sright@:<br />
      $A A node that contains greater keys than the current one.
    </li>
    <li>
      $Kstruct@ $Ts_bunny_map@ * $Kconst@ $Sleft@:<br />
      $A A node that contains lower keys than the current one.
    </li>
    <li>
      $Kconst@ $Tt_bunny_map_cmp@ $Scmp@:<br />
      $A A function pointer to compare keys. If $CNULL@, the default value,
      keys are compared like $Tsize_t@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_map_dup@ $Sdup@:<br />
      $A A function pointer to duplicate keys. If $CNULL@, the default value,
      keys fields are copied directly from parameters. (Making, possibily, a shallow
      copy)
    </li>
    <li>
      $Kconst@ $Tt_bunny_map_del@ $Sdel@:<br />
      $A A function pointer to delete keys. If $CNULL@, the default value,
      keys are not deleted. This function pointer should be set to a valid
      function if you set a function to the $Sdup@ field.
    </li>
    <li>
      $Kconst@ $Tvoid@ * $Kconst@ $Sparam@:<br />
      $A An arbitrary value that will be sent to $Scmp@, $Sdup@ and
      $Sdel@ as last parameter.
    </li>
  </ul>
</div>

