<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

require_once ("tools/tools.php");

if (isset($_GET['lan']))
  $_COOKIE['lan'] = $_GET['lan'];

$language = ["fr", "en"];
if (!isset($_COOKIE['lan']) || !in_array($_COOKIE['lan'], $language))
  $language = "fr";
else
{
  $language = $_COOKIE['lan'];
  setcookie("lan", $language, time() + 60 * 60 * 24 * 365);
}
require_once ("$language.php");

if (!isset($_COOKIE['theme']) || !filter_chars($_COOKIE['theme'], "abcdefghijklmnopqrstuvwxyz"))
  $theme = "granit";
else
  $theme = $_COOKIE['theme'];

?>
<!DOCTYPE html>
<!--   __________________________________________________________________
----  /                                                                 /\
---- /_________________________________________________________________/  \
----  \////////////////////////////////////////////////////////////////\   \
----   \/////     //     //      //     //     //     ///\/////       //\   \
----    \///_____//_____//__  __//_____//_____//_____///  \_//_______////\   \
----     \//\    \ \    \ \ \_\ \ \    \ |    \ \  /   \ /  \   \\  \/////\   \
----      \//\    \ \____\ \    /\ \    \ \    \ \_____/\____\   \\  \____/\   \
----       \//\  / \/\  //\ \  ///\ \  / \/\    \///   \ \  //\  / \ /   ///\   \
----        \//\___|//\////\/\/////\/\___|//\___|//_____\/\////\/___\___/////\  /
----         \________________________________________________________________\/
----
---- Jason Brillante "Damdoshi"
----   Hanged Bunny Studio 2014-<?=date("Y", time()); ?>

----     La  Caverne  Aux  Lapins  Noirs
--->

<html>
  <head>
    <meta charset="utf-8" />
    <title>LibLapin</title>
    <meta
        name="description"
        content="<?=htmlentities(file_get_contents("$language/description.htm")); ?>"
    />
    <link rel="stylesheet" href="style/neutralize.css" />
    <link rel="stylesheet" href="style/structure.css" />
    <link rel="stylesheet" href="style/<?=$theme; ?>.css" />
    <?php
    foreach (scandir("js/") as $file)
    {
      if ($file[0] != "." && $file[strlen($file) - 1] != "~")
      {
    ?>
      <script type="text/javascript" src="js/<?=$file; ?>"></script>
    <?php
      }
    }
    ?>
  </head>
  <body onLoad="Reveal('Cover');">
    <div id="Cover">
      <img src="res/coverlogo.png" alt="..." id="LoadingLogo" />
      <script type="text/javascript">
       LogoDance('Cover', 'LoadingLogo');
      </script>
    </div>

    <header>
      <a href="index.php">
        <div>
          <img src="res/bigbunny.png" alt="LibLapin's logo" />
        </div>
      </a>
      <a href="index.php"><h1>LibLapin</h1></a>
      <div class="HeaderOverlay">
      </div>
    </header>

    <nav>
      <a href="index.php?pag=0">
        <div><?=$MainPage; ?></div>
      </a>
      <a href="index.php?pag=1">
        <div><?=$Tutorials; ?></div>
      </a>
      <a href="index.php?pag=2">
        <div><?=$Manuals; ?></div>
      </a>
      <a href="index.php?pag=3">
        <div><?=$Download; ?></div>
      </a>
    </nav>

    <div id="Body">
      <?php
      $page = ["main.php", "tuto.php", "manual.php", "download.php", "docpage.php"];
      if (!isset($_GET['pag']) || (int)$_GET['pag'] < 0 || (int)$_GET['pag'] >= count($page))
        $_GET['pag'] = 0;
      require_once ($page[(int)$_GET['pag']]);
      ?>
    </div>

    <footer>
      Hanged Bunny Studio 2014-2018
      <a href="index.php?lan=fr">
        <div class="language">
          <img src="res/fr.png" alt="Francais" />
        </div>
      </a>
      <a href="index.php?lan=en">
        <div class="language">
          <img src="res/en.png" alt="Anglais" />
        </div>
      </a>
    </footer>
  </body>
</html>
