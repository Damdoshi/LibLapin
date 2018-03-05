<p>
  The Bunny Pool is a fast container to store
  short-live elements all of the same type.<br />
  <br />
  Its inner design improve greatly creation and deletion
  operations, which are faster than for list, and still,
  bring the speed of arrays when it came to browsing
  and random access.<br />
  <br />
  Its drawback:
  <ul>
    <li>It is fixed in size and cannot be resize.</li>
    <li>It is quite volatile, this point is detailed after.</li>
  </ul>
</p>

<b>The pool module header is lapin/container/pool.h.</b>
