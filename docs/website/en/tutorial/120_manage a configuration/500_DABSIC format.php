<div class="prototype">
  DABSIC format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The DABSIC format is an original format inspired by INI. It is fully recursive:
    hashmaps contains nodes, arrays contains nodes and contrary the JSON format
    or the LUA format, a DABSIC format node can be defined as an array, as an
    hashmap and as a value at the same time.
    <br />
    The general appeirence of DABSIC is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo dabsic_file(dirname(__FILE__)."/501_dabsic_format.dab"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    Field = "Value"<br />
    Scope = "Value2"<br />
    Scope.Scope.DeepField = "ValueX"<br />
    Scope.Array[0] = 800<br />
    Scope.Array[0] = 600<br />
    AnotherScope.Field = "Val"<br />
    Array = "Value3"<br />
    Array[0] = "Entry0"<br />
    Array[1] = "Entry1"<br />
    AnotherArray[0] = "Even here"<br />
    AnotherArray[0][0] = Entry00<br />
    AnotherArray[0][1] = Entry01<br />
    AnotherArray[1].Field = "We are in a scope"<br />
    AnotherArray[2] = "Entry10"<br />
    <br />
    The DABSIC format supports expressions as field value. Unlike
    the INI format for example, no '$' is required.<br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br >
    <br />
    Inline DABSIC commentaries start with token "'".<br />
    <br />
    Block DABSIC commentaries start with token '[*' and end with token '*]'.<br />
    <br />
    The DABSIC format syntax is rich and various. There is different ways
    to declare an array or a scope, all fitting for a specific context as their
    esthetic is different.<br />
    <br />
    The DABSIC format can include other formats thanks to specific scopes
    opening.<br />
    <br />
    The DABSIC format is not only a data format in the bunny configuration
    module but a complete programming language.<br />
    <br />
    All those aspects are described in another chapter:
    the Dabsic Programming Language.
  </p>
  <br />
  <br />
</div>
