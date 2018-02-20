<div class="prototype">
  LISP format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The LISP format parse ML like structure.
    <br />
    The general appeirence of LISP is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo lisp_file(dirname(__FILE__)."/451_lisp_format.ml"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    hashmap.array[0] = 0<br />
    hashmap.array[1] = 1<br />
    hashmap.array[2] = 2<br />
    hashmap.value = "42"<br />
    hashmap.another_array[0] = 0<br />
    hashmap.another_array[0] = 1<br />
    hashmap.another_array[0] = 2<br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br >
    <br />
    LISP commentaries are only inline. The ';' token make it starts.
  </p>
  <br />
  <br />
</div>
