<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

if (!isset($_GET["doc"])
    || ($_GET["doc"] != "tutorial" && $_GET["doc"] != "manual")
    || !isset($_GET["mod"])
    || !filter_chars($_GET["mod"], "abcdefghijklmnopqrstuvwxyz")
)
{
  exit(1);
}
$doctype = $_GET["doc"];
$mod = $_GET["mod"];
$sym = get_all_symbols("$language/$doctype");
?>

<h1 id="Index"><?=pretty_name($mod); ?></h1>
<br />
<br />
<br />
<br />
<?php
if (file_exists("$language/$doctype/$mod/main.php"))
{
  echo '<div class="doc_entry">';
  require_once ("$language/$doctype/$mod/main.php");
  echo "</div>";
}
?>

<ul class="doc_entry index">
  <?php
  $entries = [];
  foreach (scandir("$language/$doctype/$mod/") as $dir)
  {
    if ($dir[0] != "." && $dir != "main.php" && $dir[strlen($dir) - 1] != "~" && $dir[0] != "#")
    {
      $dirx = skip_int_label($dir);
      $entries[] = [
        'file' => $dir,
        'label' => ($label = str_replace(".php", "", $dirx)),
        'title' => $label
      ];
    }
  }
  foreach ($entries as $ent)
  {
  ?>
  <a href="#<?=base64_encode($ent['label']); ?>">
    <li class="button index_item" style="text-align: left;">
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
