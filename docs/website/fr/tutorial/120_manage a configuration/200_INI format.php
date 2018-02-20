<div class="prototype">
  INI format
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The INI format is a non recursive simple format. Non recursive means all nodes
    cannot have any kind of nodes.<br />
    The basic structure of an INI file is Scope.Field.Index.Value or
    Field.Index.Value, Index being optionnal if Field contains only a single
    value at index 0. Section with addresses are extensions brought by the
    bunny library. Directives are extensions.
    <br />
    <br />
    The general appeirence of INI is the following:
    <br />
    <br />
    <span class="code" style="width: 60%; margin: 0; display: inline-block;">
      <?php echo ini_file(dirname(__FILE__)."/201_ini_file.ini"); ?>
    </span>
    <br />
    <br />
    Inserts and includes appart, this evolves into this serie of fields:<br />
    <br />
    GlobalField = 42<br />
    Section.Field[0] = $L"1"@<br />
    Section.Field[1] = 1 + 1<br />
    Section.Field[2] = 3<br />
    AnotherSection.DeepSection[2].Hell.DeepField = 1<br />
    <br />
    The '$' token in INI format allow you to write a mathematical expression.
    This mathematical expression can use all operators and variables, except assignation.<br />
    <br />
    The include directive will include at the root of the file the precised
    file. The position of the include directive is not important.<br />
    <br />
    The insert directive will include at the written position in the file the
    precised file. The position of the insert directive show the insertion
    position.<br />
    <br />
    The commentary token is '#' and is inline. There is no block commentary token.
  </p>
  <br />
  <br />

  <div class="prototype">
    $Tt_bunny_configuration@ *$Sbunny_open_configuration@($Kconst@ $Tchar@
    *$Sfile@, $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function load the sent file and add the configuration inside the the sent
    one. If $Sconfiguration@ is $CNULL@, a configuration node is created.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tchar@ *$Sbunny_write_configuration@($Tt_bunny_configuration_type@ $Stype@,
    $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    Generate a string containing the saved configuration.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tbool@ $Sbunny_save_configuration@($Tt_bunny_configuration_type@ $Stype@,
    $Kconst@ $Tchar@ *$Sfile@,
    $Tt_bunny_configuration@ *$Sconfiguration@);
  </div>
  <p>
    This function save with the sent grammar the sent configuration into
    the sent file.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Here is a small program that load a file, modify the loaded configuration
    and then print on stdout the modified configuration in the INI format.
    <br />
    <br />
    <div class="code">
      <?php echo code_file(dirname(__FILE__)."/202_load_ini.c"); ?>
    </div>
  </p>
  <!------------------------------------------------------------------------->

</div>
