<b>The events module header is lapin/events.h.</b>
<p>
  Note that every function pointer typedef have a function typedef equivalent!<br />
  For example:<br />
  <ul>
    <li>t_bunny_loop is a function pointer typedef.</li>
    <li>t_bunny_loop_function is a function typedef.</li>
    <li>
      So when you prototype your loop function, you can do as above:<br />
      t_bunny_loop_function my_loop_function;<br />
      <br />
      Instead of writing the whole prototyping of the function.
    </li>
  </ul>
</p>

