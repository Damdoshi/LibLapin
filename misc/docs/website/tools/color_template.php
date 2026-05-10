<?php

function symbol_boundary_pattern($symbols)
{
  $parts = [];
  foreach ($symbols as $cpl)
  {
    if (!isset($cpl["sym"]) || $cpl["sym"] === "")
      continue;
    $parts[] = preg_quote($cpl["sym"], '/');
  }
  if (empty($parts))
    return (null);

  // C and C++ identifiers must be matched as complete symbols.  The colon is
  // part of the left/right boundary so hbs::Frame does not match inside
  // hbs::Frame::Now, and an old unqualified Frame entry cannot match inside
  // hbs::Frame.
  return ('/(?<![A-Za-z0-9_:])(?:' . implode('|', $parts) . ')(?![A-Za-z0-9_:])/u');
}

function prepare_linkable_symbols($symbols)
{
  $out = [];
  $seen = [];
  foreach ($symbols as $cpl)
  {
    if (!isset($cpl["sym"], $cpl["typ"], $cpl["mod"]) || $cpl["sym"] === "")
      continue;

    // Do not autolink single-letter leftovers such as template parameters.
    // Real C++ documentation entries are emitted with their full namespace.
    if (strlen($cpl["sym"]) <= 1)
      continue;

    $key = $cpl["sym"];
    if (isset($seen[$key]))
      continue;
    $seen[$key] = true;
    if (!isset($cpl["anchor"]) || $cpl["anchor"] === "")
      $cpl["anchor"] = $cpl["sym"];
    $out[] = $cpl;
  }

  usort($out, function($a, $b) {
    $cmp = strlen($b["sym"]) <=> strlen($a["sym"]);
    if ($cmp != 0)
      return ($cmp);
    return (strcmp($b["sym"], $a["sym"]));
  });
  return ($out);
}

function link_symbols_in_text($page, $doc, $symbols, $text)
{
  $symbols = prepare_linkable_symbols($symbols);
  $pattern = symbol_boundary_pattern($symbols);
  if ($pattern === null)
    return ($text);

  $by_symbol = [];
  foreach ($symbols as $cpl)
    $by_symbol[$cpl["sym"]] = $cpl;

  $new_text = preg_replace_callback($pattern, function($m) use ($page, $doc, $by_symbol) {
    $sym = $m[0];
    if (!isset($by_symbol[$sym]))
      return ($sym);
    $cpl = $by_symbol[$sym];
    return (urlforge($page, $cpl["typ"], $cpl["mod"], $cpl["anchor"], $sym));
  }, $text);

  if ($new_text === null)
    return ($text);
  return ($new_text);
}

function link_symbols_outside_tags($page, $doc, $symbols, $cnt)
{
  $parts = preg_split('/(<[^>]*>)/', $cnt, -1, PREG_SPLIT_DELIM_CAPTURE);
  if ($parts === false)
    return ($cnt);

  foreach ($parts as $i => $part)
  {
    if ($part === '' || $part[0] == '<')
      continue;
    // Replace on the original text chunk in one pass.  This prevents shorter
    // symbols from being applied inside an <a> tag produced for a longer one.
    $parts[$i] = link_symbols_in_text($page, $doc, $symbols, $part);
  }

  return (implode('', $parts));
}

function color_template($page, $doc, $symbols, $cnt)
{
  $cnt = str_replace('$S', '<span class="doc_symbol">', $cnt);
  $cnt = str_replace('$K', '<span class="doc_keyword">', $cnt);
  $cnt = str_replace('$T', '<span class="doc_type">', $cnt);
  $cnt = str_replace('$C', '<span class="doc_constant">', $cnt);
  $cnt = str_replace('$B', '<span class="doc_strong">', $cnt);
  $cnt = str_replace('$L', '<span class="doc_litteral">', $cnt);
  $cnt = str_replace('$M', '<span class="doc_comment">', $cnt);
  $cnt = str_replace('$A', '&nbsp;&nbsp;&nbsp&nbsp;', $cnt);
  $cnt = str_replace('@', '</span>', $cnt);

  return (link_symbols_outside_tags($page, $doc, $symbols, $cnt));
}
