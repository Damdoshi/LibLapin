<div class="prototype">
  $Tt_bunny_buffer@
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  The t_bunny_buffer structure represents a 2D graphic memory chunk.
  It is used by several other types as root structure, in a way that
  look likes C++ simple inheritence.<br />
  <br />
  $A The purpose of this structure is to gather datas that are always
  found in some kind of objects and to create an indication:<br />
  $A Any function that accept a t_bunny_buffer as parameter can
  accept a type that derived from t_bunny_buffer.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $S_private@:<br />
      $A A reserved chunk of memory containing LibLapin specific datas.
      An attempt to edit them would end in a crash, sooner or later.
    </li>
    <li>
      $Tssize_t@ $Swidth@:<br />
      $A The width of the buffer in pixels.
    </li>
    <li>
      $Tssize_t@ $Sheight@:<br />
      $A The height of the buffer in pixels.
    </li>
  </ul>
</div>

