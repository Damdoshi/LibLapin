<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

if (!isset($_GET["doc"])
    || ($_GET["doc"] != "tutorial" && $_GET["doc"] != "manual")
    || !isset($_GET["mod"])
    || !filter_chars(strtolower($_GET["mod"]), "abcdefghijklmnopqrstuvwxyz _1234567890")
)
{
  exit(1);
}
$doctype = $_GET["doc"];
$mod = $_GET["mod"];
$sym = get_all_symbols("$language/$doctype", $doctype);
if ($doctype == "tutorial")
  $sym = get_all_symbols("$language/manual", "manual", $sym);
?>

<h1 id="Index"><?=pretty_name(skip_int_label($mod)); ?></h1>
<br />
<br />
<br />
<br />
<?php
if (file_exists("$language/$doctype/$mod/main.php"))
{
  echo '<div class="doc_entry">';
  ob_start();
  require_once ("$language/$doctype/$mod/main.php");
  $content = ob_get_clean();
  echo color_template(4, $doctype, $sym, $content);
  echo "</div>";
}
?>

<ul class="doc_entry index">
  <?php
  $entries = [];

  if (file_exists("$language/$doctype/$mod/meta.php"))
    require_once ("$language/$doctype/$mod/meta.php");
  if (!isset($circle_level))
    $circle_level = [];
  if (!isset($meta))
    $meta = "";

  foreach (scandir("$language/$doctype/$mod/") as $dir)
  {
    if ($dir[0] != "."
        && $dir != "main.php"
        && $dir != "meta.php"
        && $dir[strlen($dir) - 1] != "~"
        && $dir[0] != "#"
        && strstr($dir, ".php") != false)
    {
      $dirx = skip_int_label($dir);
      $label = str_replace(".php", "", $dirx);
      if (!isset($circle_level[$label]) || $circle_level[$label] <= $circle)
      {
        $entries[] = [
          'file' => $dir,
          'label' => $label,
          'title' => $label
        ];
      }
    }
  }
  $i = 0;
  foreach ($entries as $ent)
  {
  ?>
  <a href="#<?=base64_encode($ent['label']); ?>">
    <li class="button index_item <?=$i++ %2 ? 'altbutton' : ''; ?>"
        style="text-align: left;">
      <?=$ent['title']; ?>
    </li>
  </a>
  <?php
  }
  ?>
</ul>

<?php
foreach ($entries as $ent)
{
?>
  <div class="doc_entry" id="<?=base64_encode($ent['label']); ?>">
    <?php
    ob_start();
    require_once ("$language/$doctype/$mod/".$ent['file']);
    $content = ob_get_clean();
    echo color_template(4, $doctype, $sym, $content);
    ?>
    <br />
    <br />
    <p class="go_up">
      <a href="#Index">INDEX</a>
    </p>
  </div>
<?php
}
?>
