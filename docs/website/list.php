<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

if (!isset($doctype))
  exit(1);

$all_mods = "[ ";
foreach (scandir("$language/$doctype/") as $mod)
{
  if ($mod[0] != "." && strstr($mod, ".php") == false)
  {
    $all_mods .= "'$mod',";
  }
}
$all_mods[strlen($all_mods) - 1] = "]";

?>
<div class="roll_button">
  <a onClick="roll_unroll_all(<?=$all_mods; ?>);">
    <h3 class="button control_button"><?=$RollUnrollAll; ?></h3>
  </a>
  <br />
  <a>
    <input type="text" placeholder="<?=$Search; ?>" id="SearchButton" />
  </a>
  <?php
  if ($ads == "ads")
  {
    echo "<br /><br />";
    echo "<a>";
    require_once ("pub.php");
    echo "</a>";
  }
  ?>
</div>

<ul class="prime_list">
<?php
$i = 0;
foreach (scandir("$language/$doctype/") as $dir)
{
  $mod = $dir;
  if (file_exists("$language/$doctype/$dir/meta.php"))
    require_once ("$language/$doctype/$dir/meta.php");
  if (!isset($circle_level))
    $circle_level = [];
  if (!isset($meta))
    $meta = "";

  if ($mod[0] != "." && strstr($mod, ".php") == false)
  {
?>
  <li id="<?=$mod; ?>_list" class="button prime_list_item <?=$i % 2 ? 'altbutton' : ''; ?>">
    <div class="prime_list_item">
      <a onClick="roll_unroll('<?=$mod; ?>');">
        <img id="<?=$mod; ?>_arrow" src="res/arrow_right.png" />
      </a>
      <a href="index.php?pag=4&amp;doc=<?=$doctype; ?>&amp;mod=<?=$dir; ?>">
        <h2><?=$meta; ?><?=pretty_name(skip_int_label($mod)); ?></h2>
      </a>
    </div>
    <ul id="<?=$mod; ?>_sublist" class="second_list" style="display: none;">
    <?php
    $entries = [];
    foreach (scandir("$language/$doctype/$dir/") as $sym)
    {
      if ($sym[0] != "."
          && $sym[0] != "#"
          && $sym != "main.php"
          && $sym != "meta.php"
          && strstr($sym, ".php") != false
          && $sym[strlen($sym) - 1] != "~"
      )
      {
        $sym = str_replace(".php", "", $sym);
        $label = skip_int_label($sym);
        if (!isset($circle_level[$label]) || $circle_level[$label] <= $circle)
          $entries[] = $label;
      }
    }
    $inside = 0;
    foreach ($entries as $sym)
    {
      $inside += 1;
    ?>
      <script language="javascript">
       symbols["<?=$sym; ?>"] = "<?=base64_encode($sym); ?>";
      </script>
      <li id="<?=base64_encode($sym); ?>">
        <a href="index.php?pag=4&amp;doc=<?=$doctype; ?>&amp;mod=<?=$mod; ?>#<?=base64_encode($sym); ?>">
          <h3 class="button second_list_entry"><?=$sym; ?></h3>
        </a>
      </li>
    <?php
    }
    if ($inside > 0)
      $i += 1;
    ?>
    </ul>
  </li>
<?php
  }
}
?>
</ul>
<script language="javascript">
 search(<?=$all_mods; ?>, document.getElementById("SearchButton"));
</script>
