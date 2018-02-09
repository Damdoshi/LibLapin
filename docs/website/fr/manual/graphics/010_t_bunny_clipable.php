<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_clipable@<br />
  {<br />
  $A $Tt_bunny_buffer@ $Sbuffer@;<br />
  $A $Tint32_t@ $Sclip_x_position@;<br />
  $A $Tint32_t@ $Sclip_y_position@;<br />
  $A $Tint32_t@ $Sclip_width@;<br />
  $A $Tint32_t@ $Sclip_height@;<br />
  $A $Tt_bunny_accurate_position@ $Sposition@;<br />
  $A $Tt_bunny_accurate_position@ $Sorigin@;<br />
  $A $Tt_bunny_accurate_position@ $Sscale@;<br />
  $A $Tdouble@ $Srotation@;<br />
  $A $Tt_bunny_color@ $Scolor_mask@;<br />
  <br />
  } $Tt_bunny_clipable@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure inherit from t_bunny_buffer and represent any picture
  that can serve as graphical source. This source can be used in different
  fashion: it can be partially used only, can be rotated, can be placed
  and its color can be altered without touching the real material.<br />
  <br />
  The t_bunny_clipable format can be describe by a configuration file.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Tt_bunny_buffer@ $Sbuffer@:<br />
      $A Informations about the buffer itself can be found here.
      Having this field make t_bunny_clipable compatible with
      all functions that use t_bunny_buffer.
    </li>
    <li>
      $Tint32_t@ $Sclip_x_position@:<br />
      $A The X position of the subpart that will be used as source.
      By default, it is 0.
    </li>
    <li>
      $Tint32_t@ $Sclip_y_position@:<br />
      $A The Y position of the subpart that will be used as source.
      By default, it is 0.
    </li>
    <li>
      $Tint32_t@ $Sclip_width@:<br />
      $A The width of the subpart that will be used as source.
      By default, it is $Sbuffer@.$Swidth@, the complete width.
    </li>
    <li>
      $Tint32_t@ $Sclip_height@:<br />
      $A The height of the subpart that will be used as source.
      By default, it is $Sbuffer@.$Sheight@, the complete height.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Sposition@:<br />
      $A When the clipable is used as source with bunny_blit or bunny_blit_shader
      and that the $Sposition@ parameter is $CNULL@, this attribute
      indicates where on the target the subpart will be drawn.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Sorigin@:<br />
      $A The origin of the clipable and the center of rotation. By default,
      it is on top left corner.
    </li>
    <li>
      $Tt_bunny_accurate_position@ $Sscale@:<br />
      $A The scale of the clipable. By default, it is 1, 1.
    </li>
    <li>
      $Tdouble@ $Srotation@:<br />
      $A The rotation in degree of the clipable. By default, it is 0.
    </li>
    <li>
      $Tt_bunny_color@ $Scolor_mask@:<br />
      $A A AND mask used on every color when the clipable is being used
      as source. By default, it is fully opaque white.
    </li>
  </ul>
</div>

<div class="details">
  <h3>Configuration file format</h3>

  <p>
    You can set properties of a t_bunny_clipable thanks to a file at runtime.
    This allow you to get rid of a lot of configuration and to create space for
    any outside editor.
    <br />
    <br />
  </p>

  <h4>INI format and complete field description</h4>
  <h5>Mandatory field</h5>

  <ul>
    <li>
      RessourceFile is a single string that contains the address of a picture.<br />
      Usage:<br />
      <br />
      RessourceFile="Picture file that will be loaded"<br />
    </li>
  </ul>

  <h5>Optionnal fields</h5>

  <ul>
    <li>
      Position is the position of the clipable when blitted.<br />
      It must be two int or double long.<br />
      Usage:<br />
      <br />
      $SPosition@=XPosition,YPosition<br />
    </li>

    <li>
      Scale is a zoom. It can be a single float or two.
      If there is a single float, then it scales on X and Y.
      If there is two floats, theen it scales accordingly on X and Y.<br />
      Usage:<br />
      <br />
      $SScale@=XandYScale<br />
      $SScale@=XScale,YScale
    </li>

    <li>
      Origin move the spot used to place the clipable, turn or scale it.
      It is two int or double long.<br />
      Usage:<br />
      <br />
      $SOrigin@=XPosition,YPosition
    </li>

    <li>
      Rotation is a float that represent the rotation in degree of the clipable.
      It turns as in trigonometry.<br />
      Usage:<br />
      <br />
      $SRotation@=Degree
    </li>

    <li>
      Color is a collection of integer between 0 and 255 used as color mask.<br />
      It can be one field long to create a grey mask.<br />
      It can be three fields long to create a RGB mask with no transparency.<br />
      It can be four fields long to create a RGBA mask.<br />
      About transparency, 0 is transparent.<br />
      Usage:<br />
      <br />
      $SColor@=GreyLevel<br />
      $SColor@=Red,Green,Blue<br />
      $SColor@=Red,Green,Blue,Alpha<br />
    </li>

    <li>
      Transparency is a single integer between 0 and 255 used as color mask.
      It is redundant with the Color field and will override it.
      About transparency, 0 is transparent.<br />
      Usage:<br />
      <br />
      $STransparency@=TransparencyLevel
    </li>

    <li>
      Clip.Position is the position of a clip inside the clipable.
      It is two positive integer long.<br />
      Usage:<br />
      <br />
      [$TClip@]<br />
      $SPosition@=XPosition,YPosition
    </li>

    <li>
      Clip.Size is the size of the clip inside the clipable.
      It is two positive integer long.<br />
      Usage:<br />
      <br />
      [$TClip@]<br />
      $SSize@=Width,Height
    </li>

    <li>
      Clip.Selected is the number of the current clip. This field needs
      the Clip.Size field to be set. It is a positive integer.
      This field is redundant with the Clip.Position field and will override it.
      <br />
      Usage:<br />
      <br />
      [$TClip@]<br />
      $SSize@=Width,Height<br />
      $SSelected@=NbrCase<br />
    </li>

    <h4>DABSIC format</h4>

    <p>
      The Dabsic format follow the same architecture as the INI one.
      Here is a complete usage:<br />
      <br />
      $SRessourceFile@=$L"PathToRessourceFile"@<br />
      $SPosition@=XPosition,YPosition<br />
      $SScale@=XScale,YScale<br />
      $SScale@=XYScale<br />
      $SOrigin@=XPosition,YPosition<br />
      $SRotation@=Degree<br />
      $SColor@=GreyLevel<br />
      $SColor@=Red,Green,Blue<br />
      $SColor@=Red,Green,Blue,Alpha<br />
      $STransparency@=TransparencyLevel<br />
      [$TClip@<br />
      $A $SSize@=Width,Height<br />
      $A $SPosition@=XPosition,YPosition<br />
      $A $SSelected@=NbrCase<br />
      ]<br />
    </p>

    <p>
      Note that the ability of Dabsic to create array with the following fashion:
      <br />
      <br />
      $SColor@ = [$TArray@<br />
      $A Red<br />
      $A Green<br />
      $A Blue<br />
      ]<br />
      <br />
      Does not interfere with the way the value is get. It is perfectly equivalent.
    </p>

    <h4>CSV format</h4>

    <p>
      The CSV format does not follow the same architecture as the INI one.
      Here is its architecture:<br />
      <br />
      $L"ressourcefile"@;$L"path_to_ressource_file"@<br />
      $L"position"@;xposition;ypostition<br />
      $L"scale"@;xscale;yscale<br />
      $L"scale"@;xscale<br />
      $L"origin"@;xposition;yposition<br />
      $L"rotation"@;degree<br />
      $L"color"@;greylevel<br />
      $L"color"@;red;green;blue<br />
      $L"color"@;red;green;blue;alpha<br />
      $L"transparency"@;transparency<br />
      $L"clip"@<br />
      ;$L"size"@;width;height<br />
      ;$L"position"@;xposition;yposition<br />
      ;$L"selected"@;nbrcase<br />
      <br />
      <b>Note that fields inside clip does not start on the first column!</b>
    </p>

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
    <li>t_bunny_picture</li>
    <li>t_bunny_pixelarray</li>
    <li>t_bunny_font</li>
    <li>t_bunny_sprite</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>
