<div class="prototype">
  $Tt_bunny_configuration_type@ $Sbunny_which_format@(
  $Kconst@ $Tchar@ *$Sfile@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Return the type of the sent file, after its extension.
  <ul>
    <li>Dabsic file: .dab</li>
    <li>INI file: .ini</li>
    <li>Lisp file: .lisp</li>
    <li>XML file: .xml</li>
    <li>LUA file: .lua</li>
    <li>CSV file: .csv</li>
    <li>JSON file: .json</li>
  </ul>
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Tt_bunny_configuration@ *$Sconfiguration@:<br />
      $A The file to test.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    Returns the found type or $SBC_CUSTOM@ if no handled format is found.
  </p>
</div>
