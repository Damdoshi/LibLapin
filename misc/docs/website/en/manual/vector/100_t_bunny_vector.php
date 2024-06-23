<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_vector@<br />
  {<br />
  $A $Tt_bunny_constructor@
  $Sctor@;<br />
  $A $Tt_bunny_destructor@
  $Sdtor@;<br />
  $A $Kconst@ $Tsize_t@	$Snmemb@;<br />
  $A $Kconst@ $Tsize_t@	$Selemsize@;<br />
  $A $Tvoid@ * $Kconst@	$Sarray@;<br />
  <br />
  } $Tt_bunny_vector@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is the main data of the Vector container.
  It allow to set and retrieve a few informations, but is preferably
  considered as an abstract type: to use only with its associated functions.
  <br />
  <br />
  $A This type cannot be declared on stack. It must be created by a call
  to bunny_new_vector.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_constructor@ $Sctor@:<br />
      $A The ctor attribute contains a function pointer that will be used
      when the container needs to build a new object: at the beginning
      while building the vector itself or while resizing.<br />
      $CNULL@ is an acceptable value.
    </li>
    <li>
      $Tt_bunny_destructor@ $Sdtor@:<br />
      $A The dtor attribute contains a function pointer that will be used
      when the container needs to delete an object: at the end while
      deleting the vector itself or while resizing.<br />
      $CNULL@ is an acceptable value.
    </li>
    <li>
      $Kconst@ $Tsize_t@	$Snmemb@:<br />
      $A This attribute contains the number of elements inside the vector.
    </li>
    <li>
      $Kconst@ $Tsize_t@	$Selemsize@:<br />
      $A This attribute contains the size in byte of a single element in the
      vector.
    </li>
    <li>$Tvoid@ * $Kconst@	$Sarray@:<br />
      $A This attribute is the array containing your data. It cannot
      be used without precising the type of the stored data.
      You can use the bunny_vector_data macro
      to set or get a value from the vector.
      You can use the bunny_vector_address
      macro to get the address of a value in the vector.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_new_vector</li>
    <li>bunny_delete_vector</li>
  </ul>
</div>
