<div class="prototype">
  The pixelarray type itself
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    The t_bunny_pixelarray structure is a structure that inherit from
    t_bunny_clipable: it has all his field inside it but have specific limitation.
    <br />
    The following fields does not work: rotation, scale, color_mask and origin. Also
    note the opacity field is ignored so all color are considered fully opaque.
    They can be enabled while blitting on a t_bunny_picture or a
    t_bunny_window with the bunny_enable_full_blit but they will
    never work on another t_bunny_pixelarray unless you programmed it by yourself.
    <br />
    <br />
    Additionnaly to the t_bunny_clipable, the main thing that makes a
    t_bunny_pixelarray what it is: the pixels field, which is a pointer to
    the beginning of the memory buffer. This section will teach you, if
    you do not it yet, how to use this memory, without never telling you directly
    how to do it. We will start with functions linked to t_bunny_pixelarray.
  </p>
  <br />
  <br />
  <!------------------------------------------------------------------------->
  <div class="prototype">
    $Tt_bunny_pixelarray@ *$Sbunny_new_pixelarray@($Tunsigned int@ $Swidth@, $Tunsigned int@ $Sheight@);
  </div>
  <p>
    This function create a t_bunny_pixelarray of the sent size.
    It may return $CNULL@ if no enough
    memory was available (which may really happen if your bunny library use
    the bunny allocator and have default limitation). This t_bunny_pixelarray,
    as any other t_bunny_clipable must be destroyed with bunny_delete_clipable.
  </p>
  <br />
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    This is the only function you will need for now. We will now talk about
    this mighty $Tvoid@ * $Kconst@ $Spixels@. First, it is a constant pointer,
    that means that you cannot reassign it, but the data that is pointed can.<br />
    <br />
    Which data? What are the data at the edge of this pointer?<br />
    <br />
    A picture is made of pixels. The size of the picture in pixels is the
    size you sent to bunny_new_pixelarray. What is a pixel? A pixel is a color
    stored in a specific place.<br />
    <br />
    Pixels came one after the other in the graphic memory buffer. The first
    pixel is the one at the top left of the picture. The second is the one
    at its immediate right. The last one is the pixel at the bottom right
    of the picture.<br />
    <br />
    Colors are made of four unsigned bytes aligned in a specific order. In the bunny
    library, you can find an union, the t_bunny_color, which respect the format
    of the color in graphic memory buffer. A color is made of four components:
    a red one, a blue one, a green one and a fourth we will ignore for the moment.
    <br />
    The lower each component are, the lower they have an impact on the final
    color: if they are all set to 0, the color will be black.<br />
    If they are all set to their maximum, 255 as they are unsigned bytes,
    the color will be white. <br />
    Max to red, zero to other: the color will be red, etc.<br />
  </p>
</div>
