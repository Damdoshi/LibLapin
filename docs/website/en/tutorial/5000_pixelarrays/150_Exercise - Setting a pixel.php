<div class="prototype">
  Exercise - Setting a pixel
</div>

<div class="description">
  <div class="youtube">
    XXX
  </div>
  <p class="maintext">
    Setting a pixel is the first step of graphic programming when it cames
    to manual CPU pictures. In the previous section, you accessed to the
    graphic buffer and filled it with random colors, but you did not have
    accessed to a specific pixel yet!<br />
    <br />
    This section is about transforming a 2D coordinate into a 1D coordinate
    that match the graphic buffer.<br />
    <br />
  </p>
  <br />
  <br />
  <hr />
  <br />
  <br />
  <p>
    To do so, you have to exploit informations
    you have about the picture.<br />
    Here is a list: you know the width of the
    picture, you know the height, you know where it starts. Maybe all those
    informations are not neccessary, maybe all some. You have to think about it.<br />
    <br />
    To help you, here is a scheme that show you the correlation between the
    2D representation of the graphic memory buffer and its 1D reality.
  </p>
  <p style="text-align: center;">
    <img src="res/support/matrice.png" />
  </p>
  <p>
    So, the index 0 in the 1D buffer match the 2D coordinate 0, 0 in the
    picture of 6x6 pixels.<br />
    Index 1, coordinate 1, 0.<br />
    Index 2, coordinate 2, 0.<br />
    Index 3, coordinate 3, 0.<br />
    Index 4, coordinate 4, 0.<br />
    Index 5, coordinate 5, 0.<br />
    Index 6, coordinate 0, 1.<br />
    Index 7, coordinate 0, 2.<br />
    Etc.
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <br />
  <hr />
  <br />
  <p>
    So $Spixels@ is a field of width and height pixels, each pixel is made
    of a single color. It is up to you to access it now, write the following
    function:<br />
    <br />
  </p>
  <div class="prototype">
    $Tvoid@ $Sbunny_my_set_pixel@($Tt_bunny_pixelarray@ *$Spicture@, $Tt_bunny_position@ $Sposition@, $Tunsigned int@ $Scolor@);
  </div>
  <p>
    This function assign $Scolor@ to the pixel at $Sposition@ in $Spicture@.
    <i>
      If you now what the fourth byte is made for, you can program its behaviour,
      it will not be test for the moment and it will not bother.
    </i><br />
    <br />
    After you have written this function, assign it to the function pointer
    $Sgl_bunny_my_set_pixel@ so the bunny_set_pixel function can handle well
    t_bunny_pixelarray pictures.<br />
    <br />
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <h4>Automatic correction</h4>
  <p>
    No automatic correction available yet.
  </p>
  <!------------------------------------------------------------------------->
  <br />
  <hr />
  <br />
  <p>
    Congratulation if you succedd! Keep trying if you did not, even, do not
    hesitate to question us on the <a href="">board</a>.<br />
    <br />
    This function is the first of your own library. It will serve as base
    for a lot of other ones, starting with the next exercise.
  </p>
</div>
