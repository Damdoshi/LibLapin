The AStack module provides a stack container which is fully built on the
program stack.<br />
<br />
By being fully on the program stack -which means malloc is never called-
an AStack instance is automatically destroyed when you leave the function
in which it was built.<br />
<br />
This container must be used with care:
<br />
<ul>
  <li>Create it in the function you want it to be destroyed</li>
  <li>Add nodes inside the stack only from the function where it was created</li>
  <li>
    You can insert elements allocated with:<br />
    <br />
    <ul>
      <li>bunny_alloca</li>
      <li>alloca</li>
      <li>By being a non static local variable</li>
      <li>Eventually, by being a global variable or a static variable</li>
    </ul>
    <br />
    Never insert elements created by:<br />
    <br />
    <ul>
      <li>malloc, calloc, realloc</li>
      <li>bunny_malloc, bunny_calloc, bunny_realloc</li>
    </ul>
    <br />
    The general rule being: do not insert elements that need to be freed.
  </li>
</ul>
<p>
  <b>
    The Astack module is only available on systems that provide an alloca function.
    <br />
    <br />
    The astack module header is lapin/container/astack.h.
  </b>
</p>
