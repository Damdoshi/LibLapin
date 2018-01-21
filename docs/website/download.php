<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

?>

<h1><?=$Download; ?></h1>
<br />
<div class="download">
  <h3>LibLapin V1.12:</h3>
  <ul>
    <a href=""><li class="button">
      Windows - <?=$AllInOne; ?>
    </li></a>
    <a href=""><li class="button">
      Windows - <?=$OnlyLib; ?>
    </li></a>
    <a href=""><li class="button">
      Linux - <?=$ManualInstall; ?>
    </li></a>
    <li>
      Linux - <?=$DebianInstall; ?>:<br />
      <br />
      <ul>
        <li>sudo add-apt-repository "deb http://hangedbunnystudio.com/debian yyy"</li>
        <li>sudo apt-get update</li>
        <li>sudo apt-get install liblapin-dev</li>
      </ul>
    </li>
  </ul>
</div>

<div class="download">
  <h3>LibLapin <?=$On; ?> GitHub:</h3>
  <ul>
    <a href="https://github.com/Damdoshi/LibLapin" target="_blank">
      <li class="button">
        https://github.com/Damdoshi/LibLapin
      </lI>
    </a>
  </ul>
</div>

<div id="deps" class="download">
  <h3><?=$Dependencies; ?>:</h3>
  <?php require_once ("$language/deps.htm"); ?>
</div>
