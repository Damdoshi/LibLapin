<?php

//////////////
// Language //
//////////////

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

/////////
// Ads //
/////////

if (isset($_POST['ads'])
    && filter_chars($_POST['ads'], "abcdefghijklmnopqrstuvwxyz_"))
{
  $ads = $_POST['ads'];
  setcookie("ads", $ads, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['ads'])
    || !filter_chars($_COOKIE['ads'], "abcdefghijklmnopqrstuvwxyz_"))
  $ads = "ads";
else
  $ads = $_COOKIE['ads'];

/////////////////////
// Learning circle //
/////////////////////

if (isset($_POST['circle']))
{
  $circle = (int)$_POST['circle'];
  setcookie("circle", $circle, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['circle']))
  $circle = 50;
else
  $circle = (int)$_COOKIE['circle'];

/////////////
// Version //
/////////////

if (isset($_POST['version']))
{
  $version = (int)$_POST['version'];
  setcookie("version", $version, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['version']))
  $version = $latest_version;
else
  $version = (int)$_COOKIE['version'];

///////////
// Theme //
///////////

if (isset($_POST['theme'])
    && filter_chars($_POST['theme'], "abcdefghijklmnopqrstuvwxyz_"))
{
  $theme = $_POST['theme'];
  setcookie("theme", $theme, time() + 60 * 60 * 24 * 365);
}
else if (!isset($_COOKIE['theme'])
    || !filter_chars($_COOKIE['theme'], "abcdefghijklmnopqrstuvwxyz_"))
  $theme = "theme_granit";
else
  $theme = $_COOKIE['theme'];
if (file_exists("./style/$theme.css") == false)
  $theme = "theme_granit";

if (!isset($_COOKIE["first_visit"]))
  setcookie("first_visit", "1", time() + 60 * 60 * 24 * 365);

