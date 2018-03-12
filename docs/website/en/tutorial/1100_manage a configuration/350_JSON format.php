<div class="prototype">
  JSON format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The JSON format is a fully recursive format: arrays can have nodes as children,
    hasmap can have nodes as children... But nodes can only be an array, an hashmap
    or a value. It is very close to the LUA format.
    <br />
    The general appeirence of JSON is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo json_file(dirname(__FILE__)."/351_json_format.json"); ?>
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
    The bunny configuration JSON format support expressions as field value. Unlike
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
    Inline JSON commentaries start with "//" Block JSON commentaries
    start with "/*" and end with "*/". Commentaries are not standard in JSON
    but are provided by the bunny configuration module.
    <br />
    The Javascript programming language is not supported: only the JSON itself is.
  </p>
  <br />
  <br />
</div>
