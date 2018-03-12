<div class="prototype">
  LUA format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The LUA format is a fully recursive format: arrays can have nodes as children,
    hasmap can have nodes as children... But nodes can only be an array, an hashmap
    or a value. It is very close to the JSON format.
    <br />
    The general appeirence of LUA is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo lua_file(dirname(__FILE__)."/301_lua_format.lua"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    field = "value"<br />
    scope.field = "value"<br />
    array[0] = 1<br />
    array[1] = 2<br />
    <br />
    The bunny configuration LUA format support expressions as field value. Unlike
    the INI format for example, no '$' is required.
    <br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br >
    <br />
    Inline LUA commentaries start with "#!" or "--". Block LUA commentaries
    start with "--[[" and end with "]]"
    <br />
    The LUA programming language is not supported: only the data structure is.
  </p>
  <br />
  <br />
</div>
