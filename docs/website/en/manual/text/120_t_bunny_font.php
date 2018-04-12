<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_font@<br />
  {<br />
  $A $T t_bunny_clipable @ $S clipable @ ;<br />
  $A $T size_t @           $S _private@[3] ;<br />
  $A $Kconst@ $Tchar@     *$S string @;<br />
  $A $T size_t @           $S string_offset @;<br />
  $A $T size_t @           $S string_len @;<br />
  $A $T t_bunny_align @    $S halign @;<br />
  $A $T t_bunny_align @    $S valign @;<br />
  $A $T unsigned int @     $S color @;<br />
  $A $T unsigned int @     $S outline @;<br />
  $A $T double @           $S outline_size @;<br />
  $A $T t_bunny_position @ $S offset @;<br />
  $A $T t_bunny_position @ $S glyph_size @;<br />
  $A $T t_bunny_position @ $S interglyph_space @;<br />
  <br />
  } $Tt_bunny_font@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is a t_bunny_clipable with additionnal attributes
  to handle text writing. It is compatible with every function that
  takes a t_bunny_font, a t_bunny_clipable/t_bunny_picture or a t_bunny_buffer.
  <br />
  <br />
  t_bunny_font can turn around a TTF ressource or a picture ressource.
  Some functionnalities are not available accordingly to the original type.<br />
  <br />
  This structure is a little wrongly named: the structure itself does not
  represents a font but more a textbox.
  The t_bunny_clipable contained by the t_bunny_font is not the font but
  where the text will be drawn.
</div>
<hr />

<div class="resume">
  <h3>Known bugs</h3>
  <ul>
    <li>Horizontal justify does not work flawlessly.</li>
    <li>
      Sometimes, characters that overflow horizontaly, even when
      they are drawn on the next line are also drawn on the original one.
    </li>
    <li>
      Valgrind report a buffer overflow of 1 byte.
    </li>
  </ul>
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $T t_bunny_clipable @ $Sclipable@:<br />
      $A The clipable used as base by t_bunny_font.
    </li>
    <li>
      $K const @ $T size_t @ $S_private@[3]:<br />
      $A Private fields you must not modify or your program may crash.
    </li>
    <li>
      $K const @ $T char @ * $Sstring@:<br />
      $A The string that will be draw when bunny_draw is called with
      the t_bunny_font.
    </li>
    <li>
      $T size_t @ $S string_offset @:<br />
      $A The first index in $Sstring@ that will be displayed.
    </li>
    <li>
      $T size_t @ $S string_len @:<br />
      $A The length of the displayed string.
    </li>
    <li>
      $T t_bunny_align @ $S halign @:<br />
      $A The horizontal alignment of the text.
    </li>
    <li>
      $T t_bunny_align @ $S valign @:<br />
      $A The vertical alignment of the text.
    </li>
    <li>
      $T unsigned int @ $S color @:<br />
      $A The color of the text.
      On picture based font, this field is used as color mask, so it will
      fully work well only if your font is made of white, gray or black.
      A red font, for example, will not become blue if you set blue as color,
      but black because it will erase the red component without having
      any effects on other components.
    </li>
    <li>
      $T unsigned int @ $S outline @:<br />
      $A The color of the lining that runs around characters.
      Currently only available for TTF based t_bunny_font.
    </li>
    <li>
      $T double @ $S outline_size @:<br />
      $A The width of the lining that runs around characters.<br />
      Currently only available for TTF based t_bunny_font.
    </li>
    <li>
      $T t_bunny_position @ $S offset @:<br />
      $A The offset in pixels that moves where to text will be written.
    </li>
    <li>
      $T t_bunny_size @ $S glyph_size @:<br />
      $A The size of the glyph. It is copied straight from the $Sglyph_size@
      parameter of bunny_load_font.<br />
      TTF based font use this field as the size of the written text and
      only care about $Ssize->height@.<br />
      Picture based font use this field as clip size to extract letters
      from the picture containing the font.
    </li>
    <li>
      $T t_bunny_size @ $S interglyph_space @:<br />
      $A Arbiter space betwen characters.
    </li>
  </ul>
</div>
<hr />

<div class="details">
  <h3>Configuration file format</h3>

  <p>
    You can set properties of a t_bunny_front thanks to a file at runtime.
    This allow you to get rid of a lot of configuration and to create space
    for any outside editor.
    <br />
    <br />
  </p>

  <h4>INI format and complete field description</h4>

  <p>
    The t_bunny_font configuration file extend the t_bunny_clipable configuration file
    format. You should read it before going on if you do not know it yet.
    Every t_bunny_clipable fields are available in the t_bunny_font format.
    <br />
    <br />
  </p>

  <h5>Mandatory fields</h5>

  <ul>
    <li>
      RessourceFile, as for t_bunny_clipable is mandatory. It contains
      in this case not the picture that will be painted inside the clipable but
      the font that will be used to write. It can be a true type font or a bitmap
      font.<br />
      <br />
      $SRessourceFile@=$L"Font file or picture file that will be loaded and used a font."@
    </li>
    <li>
      BoxSize is an array of two integers. It define the size in pixel of the
      drawing surface of the t_bunny_font.<br />
      <br />
      $SBoxSize@=XSize,YSize
    </li>
    <li>
      GlyphSize is an array of one or two integers.<br />
      It define the size of a single character.<br />
      For true type font, a single value is enough: it will be used as height.<br />
      For bitmap font, two values are required for width and height of the glyph
      inside the RessourceFile. If a single value is used, then it will be used
      for both width and height, so it could fit for square characters.<br />
      <br />
      $SGlyphSize@=XSize,YSize<br />
      $SGlyphSize@=Size
    </li>
  </ul>

  <h5>Optionnal fields</h5>

  <ul>
    <li>
      The String field is the one that will contains the text to display.
      Default value of String is $L""@. If several values are set, exploiting
      this field like an array, they are concatenated.<br />
      <br />
      $SString@=$L"This is the Bunny Library!"@
    </li>
    <li>
      StringOffset allow you to define a subpart of the string to be displayed.
      Characters before StringOffset in String will not be drawn.<br />
      Default value for StringOffset is 0.<br />
      <br />
      $SStringOffset@=3
    </li>
    <li>
      StringLength allow you to define a subpart of the string to be displayed.
      Characters after StringLength + StringOffset in String will not be drawn.
      <br />
      DefaultValue for StringOffset is the length of String.<br />
      <br />
      $SStringLength@=5
    </li>
    <li>
      HorizontalAlign allow you to precise if the text will be aligned on the left
      with "Left", the center with "Middle", the right with "Right" or justified with
      "Justify".<br />
      <br />
      $SHorizontalAlign@=$L"Left"@
    </li>
    <li>
      VerticalAlign allow you to precise if the text will be aligned on the top
      with "Top", the center with "Middle", the bottom with "Bottom" or justified with
      "Justify".<br />
      <br />
      $SVerticalAlign@=$L"Justify"@
    </li>
    <li>
      Color define the color of the text that will be written. It is a collection
      of integer between 0 and 255 used as color components.<br />
      It can be one field long to create a grey color.<br />
      It can be three fields long to create a RGB color with no transparency.<br />
      It can be four fields long to create a RGBA mask.<br />
      <br />
      $A $SColor@=GreyLevel<br />
      $A $SColor@=Red,Green,Blue<br />
      $A $SColor@=Red,Green,Blue,Alpha<br />
    </li>
    <li>
      OutlineColor define the color of the lining of the text that will be written.
      It works the same way as Color, it is a collection of integer between 0 and 255
      used as components.<br />
      It can be one field long to create a grey color.<br />
      It can be three fields long to create a RGB color with no transparency.<br />
      It can be four fields long to create a RGBA mask.<br />
      <br />
      $A $SOutlineColor@=GreyLevel<br />
      $A $SOutlineColor@=Red,Green,Blue<br />
      $A $SOutlineColor@=Red,Green,Blue,Alpha<br />
    </li>
    <li>
      OutlineSize is the thickness of the lining of the text.<br />
      <br />
      $SOutlineSize@=5
    </li>
    <li>
      Interglyph is an array of one or two elements matching the space between
      each characters on X and Y.<br />
      <br />
      $SInterglyph@=2,3
    </li>
    <li>
      Scrolling is an offset that affect the drawing of the text. It is an array
      of two values for X and Y.<br />
      <br />
      $SScrolling@=10,30
    </li>
  </ul>

  <h4>DAB format</h4>

  <p>Not documented yet.</p>

  <h4>CSV format</h4>

  <p>Not documented yet.</p>

  <h4>XML format</h4>

  <p>Not documented yet.</p>

  <h4>LUA format</h4>

  <p>Not documented yet.</p>

  <h4>JSON format</h4>

  <p>Not documented yet.</p>

  <h4>YAML format</h4>

  <p>Not documented yet.</p>

  <h4>LISP format</h4>

  <p>Not documented yet.</p>


</div>


<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_font</li>
    <li>bunny_draw</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>
