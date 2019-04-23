<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// LibLapin

require_once ("./tools.php");

$latest_version = 2;
$latest_release = 2;

?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
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
    ----
    ----     La  Caverne  Aux  Lapins  Noirs - LibLapin
    --->
    <title>LibLapin</title>
    <meta
        name="description"
        content="<?=htmlentities(file_get_contents("./tools/$language/description.htm")); ?>"
    />
    <script type="text/javascript">
     var Pages = Array("MainPage", "Tutorials", "Manuals", "Downloads", "Gallery");

     <?php
     foreach (scandir("tools/js/") as $file)
       if ($file[0] != "." && $file[strlen($file) - 1] != "~")
         echo file_get_contents($file)."\n";
     ?>
    </script>

    <style>
     <?php require_once ("tools/style/neutralize.css"); ?>
     <?php require_once ("tools/style/structure.css"); ?>
     <?php
     foreach (scandir("./tools/style/") as $css)
       if (strncmp($css, "theme_", 6) == 0 && strstr($css, ".css") != false && $css[strlen($css) - 1] != -1)
         echo file_get_contents($css)."\n";
     ?>
    </style>
  </head>

  <?php if (isset($_COOKIE["first_visit"])) { // Loading bunny - auto remove ?>
  <body onLoad="Reveal('Cover');" class="Theme">
    <div id="Cover">
  <?php } else { // Loading bunny + message - click to remove ?>
  <body class="Theme">
    <div id="Cover" onClick="Reveal('Cover');">
  <?php } ?>
      <img src="res/coverlogo.png" alt="..." id="LoadingLogo" />
      <script type="text/javascript">
       LogoDance('Cover', 'LoadingLogo');
      </script>
      <?php
        // First visit
        if (!isset($_COOKIE["first_visit"])) {
          echo "<p><br />$FirstVisitMessage<br /><br /></p>";
        }
      ?>
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
      <div class="HeaderOverlay">
        <a onClick="Show('MainPage')"
          <div><?=$MainPage; ?></div>
        </a>
        <a href="Show('Tutorials')">
          <div><?=$Tutorials; ?></div>
        </a>
        <a href="Show('Manuals')">
          <div><?=$Manuals; ?></div>
        </a>
        <a href="Show('Downloads')">
          <div><?=$Download; ?></div>
        </a>
        <a href="Show('Gallery')">
          <div><?=$Gallery; ?></div>
        </a>
      </div>
    </nav>

    <div id="Body">
      <div id="Mainpage"><?php require_once ("main.php"); ?></div>
      <div id="Tutorials"><?php require_once ("tuto.php"); ?></div>
      <div id="Manuals"><?php require_once ("manual.php"); ?></div>
      <div id="Downloads"><?php require_once ("download.php"); ?></div>
      <div id="Gallery"><?php require_once ("gallery.php"); ?></div>
    </div>

    <footer>
      <form method="post" class="style">
        <select name="theme" onChange="this.form.submit();">
          <?php
          foreach(scandir("./tools/style/") as $css)
          {
            if (strncmp($css, "theme_", 6) == 0
                && strstr($css, ".css") != false
                && $css[strlen($css) - 1] != -1)
            {
              $css = str_replace(".css", "", $css);
              $name = substr($css, 6);
          ?>
            <option
                value="<?=$css; ?>"
                <?=$theme == $css ? "selected" : ""; ?>
            >
              Style: <?=pretty_name($name); ?>
            </option>
          <?php
            }
          }
          ?>
        </select>
      </form>

      <form method="post" class="style">
        <select name="ads" onChange="this.form.submit();">
          <option value="ads" <?=$ads == "ads" ? "selected" : ""; ?>>Ads</option>
          <option value="no_ads" <?=$ads == "no_ads" ? "selected" : ""; ?>>No ads</option>
        </select>
      </form>
      <form method="post" class="style">
        <label for="circle">
          <?=$UserLevel; ?>
        </label>
        <select name="circle" onChange="this.form.submit();">
          <?php
          $rings = [
            00 => "Beginner's manual",
            10 => "Rookie's manual",
            20 => "Intermediate's manual",
            30 => "Skillful's manual",
            40 => "Expert's manual",
            50 => "Full manual",
          ];
          foreach ($rings as $k => $v) {
          ?>
            <option value="<?=$k; ?>" <?=$k == $circle ? "selected" : ""; ?>>
              <?=$LevelRing[$v]; ?>
            </option>
          <?php } ?>
        </select>
      </form>
      <form method="post" class="style">
        <label for="version">
          <?=$LibraryVersion; ?>
        </label>
        <select name="version" onChange="this.form.submit();">
          <?php
          for ($i = $latest_version; $i >= 0; --$i) {
          ?>
            <option value="<?=$i; ?>" <?=$i == $version ? "selected" : ""; ?>>
              1.<?=$i ?>
              <?php if ($i == $latest_release) echo "(".$LatestVersion.")"; ?>
              <?php if ($i == 9) echo "(".$LastEpitechVersion.")"; ?>
              <?php if ($i == 2) echo "(".$FirstEpitechVersion.")"; ?>
            </option>
          <?php } ?>
          <option value="-1" <?=$version == "-1" ? "selected" : "" ?>>
            <?=$DisplayAllSymbols; ?>
          </option>
        </select>
      </form>

      Hanged Bunny Studio 2014-<?=date("Y"); ?>

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
