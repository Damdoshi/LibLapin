<div class="prototype">
  $Tt_bunny_font@ *$Sbunny_load_font@(
  $T unsigned int @ $S width @,
  $T unsigned int @ $S height @,
  $K const @ $T char @ * $S file @,
  $K const @ $T t_bunny_position @ * $S glyph_size @
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Create a t_bunny_font, which is a textbox with an integrated font
  utility. Supported font types are TTF, PNG, 24 bits BMP and JPG. TTF and
  other types are not handled exactly the same way but can be both used
  the same way.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $T unsigned int @ $S width @:<br />
      $A The width of the textbox: the picture which underly the t_bunny_font
      structure.
    </li>
    <li>
      $T unsigned int @ $S height @:<br />
      $A The height of the tetxbox: the picture which underly the t_bunny_font
      structure.
    </li>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A The file to load that will be used to build the t_bunny_font.
      <b>
        Configuration file are not supported yet. Only plain ressource files
        can be currently used.
      </b>
    </li>
    <li>
      $Kconst@ $Tt_bunny_position@ *$Sglyph_size@:<br />
      $A The size of a single character. TTF fonts are only interested in
      height. Picture based font will use this parameter to define
      the size of the extracted clip.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_font.
    </li>
    <li>
      On $Bfailure@, it returns $CNULL@.
    </li>
  </ul>
</div>
<hr />

<div class="error_and_log">
  <h3>Error values and logs</h3>
  <p>
    On error, $Sbunny_errno@ is set to:
  </p>
  <br />
  <ul>
    <li>
      $CENOMEM@:<br />
      <p>
        Out of memory.
      </p>
    </li>
    <li>
      $CEINVAL@:<br />
      <p>
        The sent file is not a font or not a picture, or the picture is too wide.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with $L"ressource"@
    and $L"text"@ labels.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <h4>Picture base font format:</h4>
  <p>
    Pictures used as font must be a serie of 128 clips of the sent
    $Sglyph_size@. If you do not need all glyphs, you can just leave
    their space empty, but they have to be there. Each clip will be
    associated with a character from the 128 length long ASCII table.
    You can have several lines of clips, but pay attention to never have
    trailing pixels.<br />
    <br />
    Your characters should be white, gray or black to exploit correctly
    the color attribute of t_bunny_font.<br />
    <br />
    You should avoid having picture wider than 4096*409 because a lot
    of graphic card will not allow it to be loaded inside them and
    bunny_load_font will fail with EINVAL in bunny_errno.
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_delete_clipable</li>
    <li>bunny_draw</li>
  </ul>
</div>

