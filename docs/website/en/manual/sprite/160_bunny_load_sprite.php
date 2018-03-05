<div class="prototype">
  $Tt_bunny_sprite@ *$Sbunny_load_sprite@($Kconst@ $Tchar@ *$Sfile@);
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Load a configuration file and every of its dependencies to generate
  the requested t_bunny_sprite.
  <br />
  <br />
  The returned memory space must be freed with bunny_delete_clipable.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tchar@ *$Sfile@:<br />
      $A A complete configuration of the t_bunny_sprite. The format
      is described in the format section.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <ul>
    <li>
      On $Bsuccess@, the function returns a valid t_bunny_sprite.
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
      $CENOENT@:<br />
      <p>
        The sent file was not found.
      </p>
    </li>
    <li>
      $CBE_SYNTAX_ERROR@:<br />
      <p>
        An error was encountered during reading the configuration file.
      </p>
    </li>
  </ul>
  <br />
  <p>
    Logs written by this function are tagged with the
    $L"ressource"@,
    $L"sprite"@ or
    $L"syntax"@
    label.
  </p>
</div>
<hr />

<div class="details">
  <h3>Configuration file format</h3>

  <p>
    You can set properties of a t_bunny_sprite thanks to a file at runtime.
    This allow you to get rid of a lot of configuration and to create space
    for any outside editor.
    <br />
    <br />
  </p>

  <h4>DABSIC format and complete field description</h4>
  <h5>Fields inherited from t_bunny_clipable</h5>

  <ul>
    <li>
      All mandatory fields of t_bunny_clipable configuration format are mandatory
      in t_bunny_sprite configuration file. So, basically, RessourceFile is
      mandatory.
    </li>
    <li>
      Any optionnal fields of t_bunny_clipable configuration format are optionnal
      in t_bunny_sprite configuration file.
    </li>
    <li>
      Additionnaly, the Clip.Size field present in clipable and which is optionnal
      for a simple clipable is *mandatory* for a sprite.
    </li>
  </ul>

  <h5>Mandatory fields</h5>

  <ul>
    <li>
      The Animations node is mandatory. The Animations node is a hashmap node
      (it contains named fields) that contains every animation available for
      the sprite:<br />
      <br />
      [Animations<br />
      $A [Running<br />
      $A $A$M'... Animation description ...@<br />
      $A ]<br />
      $A [Jumping<br />
      $A $A$M'... Animation description ...@<br />
      $A ]<br />
      ]<br />
    </li>

    <li>
      The InitialAnimation field is mandatory. Its purpose is to indicates
      which animation must be set at the beginning, before any manipulation
      is made in your program:<br />
      <br />
      InitialAnimation = $L"Running"@<br />
    </li>

    <li>
      The Frequency field is not completly mandatory inside the root scope
      of the sprite: it must be defined globaly, or at least, localy, inside
      the animation description node.
      The Frequency node indicates at how many frame per second the animation
      is running, its unit is the Hertz. Example:<br />
      <br />
      [Animations<br />
      $A $M'... Animations@<br />
      ]<br />
      Frequency = 3<br />
      <br />
      Or<br />
      <br />
      [Animations<br />
      $A [Running<br />
      $A $A $M'...@<br />
      $A $A Frequency = 3<br />
      $A ]<br />
      $A [Jumping<br />
      $A $A $M'...@<br />
      $A $A Frequency = 3<br />
      $A ]<br />
      ]<br />

      <br />Or<br />
      <br />

      [Animations<br />
      $A [Running<br />
      $A $A $M'...@<br />
      $A $A Frequency = 3<br />
      $A ]<br />
      $A [Jumping<br />
      $A $A $M'...@<br />
      $A ]<br />
      ]<br />
      Frequency = 3<br />
      <br />
      A global Frequency may be precised for all nodes.<br />
      It a node precise itself a Frequency value, it is the one that is used.
    </li>

    <li>
      Inside the Animations node should be at least one node describing an
      animation. In these node, there is several mandatory fields:
      <ul>
        <li>
          The Frame field is mandatory. It indicates how many picture clips are
          being used by the animation.
        </li>
        <li>
          The Position array is composed of two cases: 0 and 1 and it indicates
          respectively the coordinates as X and Y of the first picture clip
          that compose the animation:<br />
          <br />
          [Animlations<br />
          $A [Running<br />
          $A $A $M'...@<br />
	        $A $A Position=100,200<br />
          $A ]<br />
          ]<br />
        </li>
      </ul>
    </li>
  </ul>

  <h5>Optionnal fields</h5>

  <p>
    Inside the Animations node should be at least one node describing an
    animation. In these node, there is several optionnal fields:

    <ul>
      <li>
        The AnimationPlay or RepeatAnimation field tells how many time
        the full animation must loop before being stopped. Note that
        AnimationPlay and RepeatAnimation are the same field, it is just
        an alternative name. By default, this field value is -1, which means
        infinit repeatition if there is no next animation:<br />
        <br />
        [Animations<br />
        $A [Running<br />
        $A $A $M'...@<br />
	      $A $A RepeatAnimation=3 'Repeat three times the animation<br />
        $A ]<br />
        ]<br />
      </li>
      <li>
        The FramePlay array must have same length as the animation.
        This length match the value given in the Frame field. The
        FramePlay array describe, case after case, how many time
        length frames. For example:<br />
        <br />
        [Animations<br />
        $A [Idle<br />
        $A $A Frame=5<br />
	      $A $A Frequency=4<br />
	      $A $A {FramePlay<br />
        $A $A $A 20, 1, 1, 1, 1<br />
        $A $A }<br />
        $A ]<br />
        ]<br />
        <br />
        This animation show a still character on frame 0, which
        brush its hair on frame 1, 2, 3 and 4. The frame 0
        last 20 times more than other frame and as written with
        Frequency=4, there is 4 frames per seconds.
        Write 0 as frame repeat have the same effect as writing 1.
      </li>
      <li>
        The Browsing field can value "LeftToRight", "RightToLeft" or
        "BackAndForth" and indicates the way the clips composing the
        animation are played:<br />
        <br />
        [Animations<br />
        $A [Running<br />
        $A $A $M'...@<br />
        $A $A Browsing=$L"LeftToRight"@<br />
        $A ]<br />
        ]<br />
        <br />
        By default, this field value is $L"LeftToRight"@
      </li>
      <li>
        The NextAnimation field indicates which animation will
        follow the described one after its termination. It allows
        animation to follow eachother, and even to cycle them:<br />
        <br />
        [Animations<br />
        $A [Jumping<br />
        $A $A $M'...@<br />
        $A $A NextAnimation=$L"Idle"@<br />
        $A ]<br />
        $A [Running<br />
        $A $A $M'...@<br />
        $A $A NextAnimation=$L"Idle"@<br />
        $A ]<br />
        $A [Idle<br />
        $A $A $M'...@<br />
        $A ]<br §>
        ]<br />
        <br />
        By default, there is no next animation, and the animation stop
        or loop depending of other fields.
      </li>
    </ul>
  </p>

  <h5>Here is a complete working example:</h5>

  <p>
    RessourceFile=$L"./ressource/pinkman.png"@<br />
    Frequency=5<br />
    InitialAnimation=$L"Running"@<br />
    [Clip<br />
    $A Size=100,100 'Size of a single frame<br />
    ]<br />
    [Animations<br />
    $A [Running<br />
    $A $A Position=0,0<br />
    $A $A Frame=5<br />
    $A $A RepeatAnimation=5<br />
    $A $A NextAnimation=$L"Idle"@<br />
    $A ]<br />
    $A [Idle<br />
    $A $A Position=0,100 'Note that Clip.Size[1] is 100. so this is the line under<br />
    $A $A Frame=5<br />
    $A $A Browsing=$L"BackAndForth"@<br />
    $A $A {FramePlay<br />
    $A $A $A 20, 1, 1, 1, 1<br />
    $A $A }<br />
    $A $A Frequency=3<br />
    $A ]<br />
    ]<br />
  </p>

  <h4>INI format and complete field description</h4>

  <p>
    This is the architecture of the INI format by example, with the same script
    as for Dabsic:<br />
    <br />
    RessourceFile=$L"./ressource/pinkman.png"@<br />
    Frequency=5<br />
    InitialAnimation=$L"Running"@<br />
    <br />
    [Clip]<br />
    Size=100,100<br />
    <br />
    [Animations.Running]<br />
    Position=0,0<br />
    Frame=5<br />
    RepeatAnimation=5<br />
    NextAnimation=$L"Idle@"<br />
    <br />
    [Animations.Idle]<br />
    Position=0,100<br />
    Frame=5<br />
    Browsing=$L"BackAndForth"@<br />
    FramePlay=20,1,1,1,1<br />
    Frequency=3<br />
  </p>
</div>
<hr />

<div class="related_functions">
  <h3>Related functions</h3>
  <ul>
    <li>bunny_sprite_animate</li>
    <li>bunny_delete_clipable</li>
  </ul>
</div>

