<div class="prototype">
  Macro $SBUNNY_ALLOCATOR_DEACTIVATED@
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This macro can be used in two different fashion:
  <ul>
    <li>
      $BAt libray compile time:@ it disables inside the library itself
      any call to the bunny allocator, binding it to the system allocator.
    </li>
    <li>
      $BAt your compile time:@ it transforms calls to bunny allocator
      functions to regular allocator ones.
    </li>
  </ul>
</div>

<div class="related_functions">
  <h3>Related macros</h3>
  <ul>
    <li>BUNNY_ALLOCATOR_OVERLOAD</li>
  </ul>
</div>

