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

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_load_font</li>
    <li>bunny_draw</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>
