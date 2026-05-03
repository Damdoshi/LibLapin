#!/usr/bin/env php
<?php
/*
 * Generate LibLapin manual pages from Doxygen-like bilingual comments.
 * Version 6.1: infers logs/bunny_errno and emits historical resume newlines as explicit double <br /> separators without $A indentation.
 * Place this script at the repository root and run:
 *   php generate_doc.php
 *
 * Supported block shape:
 *   /**
 *    * @doc-symbol bunny_start          optional, otherwise inferred
 *    * @doc-module window               optional, otherwise inferred from path/header
 *    * @doc-order 120                   optional, unnumbered entries go after numbered ones
 *    * @doc-since 0                    optional, first LibLapin 1.x version supporting the symbol
 *    * @doc-until latest               optional, last LibLapin 1.x version supporting the symbol
 *    * @doc-level beginner             optional: beginner/common/intermediate/advanced/expert or a number
 *    * @doc-lang en
 *    * @brief Opens a window.
 *    * @description ...
 *    * @param width Window width in pixels.
 *    * @return-success A valid t_bunny_window pointer.
 *    * @return-failure NULL.
 *    * @error BE_UNKNOWN_DISPLAY_DEVICE Missing DISPLAY variable.
 *    * @log Logs written by this function are tagged with the "window" label.
 *    * @see bunny_stop
 *    *
 *    * @doc-lang fr
 *    * @brief Ouvre une fenêtre.
 *    * ...
 *    * /                             remove this space in real comments
 *
 * It writes:
 *   misc/docs/website/en/manual/<module>/<order>_<symbol>.php
 *   misc/docs/website/fr/manual/<module>/<order>_<symbol>.php
 */

final class DocItem {
  public string $symbol = '';
  public string $module = '';
  public ?int $order = null;
  public int $since = 0;
  /** @var int|string */
  public $until = 'latest';
  public int $level = 0;
  public string $prototype = '';
  /** @var array<string,array<string,mixed>> */
  public array $lang = [];
  public string $source = '';
  public string $body = '';
  /** @var array<int,string> */
  public array $autoLogs = [];
  /** @var array<string,string> */
  public array $autoErrors = [];
}


$root = getcwd();
$outRoot = $root . '/misc/docs/website';
$langs = ['en', 'fr'];
$dryRun = false;
$cleanGenerated = false;

foreach (array_slice($argv, 1) as $arg) {
  if ($arg === '--dry-run') $dryRun = true;
  else if ($arg === '--clean-generated') $cleanGenerated = true;
  else if (str_starts_with($arg, '--out=')) $outRoot = $root . '/' . substr($arg, 6);
  else if (str_starts_with($arg, '--lang=')) $langs = array_values(array_filter(explode(',', substr($arg, 7))));
  else if ($arg === '-h' || $arg === '--help') {
    echo "Usage: php generate_doc.php [--dry-run] [--clean-generated] [--out=misc/docs/website] [--lang=en,fr]\n";
    exit(0);
  }
}

function fail(string $msg): void { fwrite(STDERR, "error: $msg\n"); exit(1); }
function warnx(string $msg): void { fwrite(STDERR, "warning: $msg\n"); }

function parse_doc_version(string $value, $default) {
  $v = strtolower(trim($value));
  if ($v === '' || $v === 'latest') return 'latest';
  if ($v === '-1') return -1;
  return (int)$v;
}

function parse_doc_level(string $value): int {
  $v = strtolower(trim($value));
  $map = [
    'all' => 0, 'everyone' => 0, 'beginner' => 0, 'basic' => 0, 'common' => 0,
    'intermediate' => 10, 'normal' => 10,
    'advanced' => 20, 'confirmed' => 20,
    'expert' => 30, 'internal' => 40,
  ];
  if (isset($map[$v])) return $map[$v];
  if (preg_match('/^-?[0-9]+$/', $v)) return (int)$v;
  warnx("unknown @doc-level '$value', using beginner/0");
  return 0;
}


function list_files(string $dir, array $exts): array {
  if (!is_dir($dir)) return [];
  $rii = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($dir, FilesystemIterator::SKIP_DOTS));
  $out = [];
  foreach ($rii as $file) {
    if (!$file->isFile()) continue;
    $path = $file->getPathname();
    if (preg_match('/\.(' . implode('|', array_map('preg_quote', $exts)) . ')$/i', $path))
      $out[] = $path;
  }
  sort($out);
  return $out;
}

function strip_comment_stars(string $comment): array {
  $comment = preg_replace('#^/\*\*?#', '', $comment);
  $comment = preg_replace('#\*/$#', '', trim($comment));
  $lines = preg_split('/\R/', $comment);
  $out = [];
  foreach ($lines as $line) {
    $line = preg_replace('/^\s*\* ?/', '', $line);
    $out[] = rtrim($line);
  }
  return $out;
}

function parse_doc_block(string $comment): array {
  $lines = strip_comment_stars($comment);
  $meta = ['symbol' => null, 'module' => null, 'order' => null, 'since' => 0, 'until' => 'latest', 'level' => 0];
  $langs = [];
  $cur = null;
  $lastTag = null;
  $lastName = null;

  $ensure = function(string $lang) use (&$langs): void {
    if (!isset($langs[$lang]))
      $langs[$lang] = ['brief' => '', 'description' => '', 'params' => [], 'returns' => [], 'return' => '', 'errors' => [], 'logs' => '', 'see' => []];
  };

  foreach ($lines as $raw) {
    $line = trim($raw);
    if ($line === '') {
      if ($cur !== null && $lastTag === 'description') $langs[$cur]['description'] .= "\n";
      continue;
    }
    if (preg_match('/^@doc-lang\s+([a-z][a-z0-9_-]*)\s*$/i', $line, $m)) {
      $cur = strtolower($m[1]); $ensure($cur); $lastTag = null; $lastName = null; continue;
    }
    if (preg_match('/^@doc-symbol\s+([A-Za-z_][A-Za-z0-9_]*)\s*$/', $line, $m)) { $meta['symbol'] = $m[1]; continue; }
    if (preg_match('/^@doc-module\s+([A-Za-z0-9_ -]+)\s*$/', $line, $m)) { $meta['module'] = trim($m[1]); continue; }
    if (preg_match('/^@doc-order\s+([0-9]+)\s*$/', $line, $m)) { $meta['order'] = (int)$m[1]; continue; }
    if (preg_match('/^@doc-since\s+([0-9]+|latest|-1)\s*$/i', $line, $m)) { $meta['since'] = parse_doc_version($m[1], 0); continue; }
    if (preg_match('/^@doc-until\s+([0-9]+|latest|-1)\s*$/i', $line, $m)) { $meta['until'] = parse_doc_version($m[1], 'latest'); continue; }
    if (preg_match('/^@doc-level\s+([A-Za-z0-9_-]+)\s*$/i', $line, $m)) { $meta['level'] = parse_doc_level($m[1]); continue; }

    if ($cur === null) continue;
    $ensure($cur);

    if (preg_match('/^@brief\s+(.*)$/', $line, $m)) { $langs[$cur]['brief'] = $m[1]; $lastTag = 'brief'; continue; }
    if (preg_match('/^@description\s*(.*)$/', $line, $m)) { $langs[$cur]['description'] .= ($langs[$cur]['description'] === '' ? '' : "\n") . $m[1]; $lastTag = 'description'; continue; }
    if (preg_match('/^@param\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.*)$/', $line, $m)) { $langs[$cur]['params'][$m[1]] = $m[2]; $lastTag = 'param'; $lastName = $m[1]; continue; }
    if (preg_match('/^@return(?:-([A-Za-z0-9_-]+))?\s+(.*)$/', $line, $m)) {
      if (($m[1] ?? '') !== '') {
        $label = strtolower(trim($m[1]));
        $langs[$cur]['returns'][$label] = $m[2];
        $lastTag = 'return-case'; $lastName = $label;
      } else {
        $langs[$cur]['return'] = $m[2];
        $lastTag = 'return';
      }
      continue;
    }
    if (preg_match('/^@error\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.*)$/', $line, $m)) { $langs[$cur]['errors'][$m[1]] = $m[2]; $lastTag = 'error'; $lastName = $m[1]; continue; }
    if (preg_match('/^@log\s+(.*)$/', $line, $m)) { $langs[$cur]['logs'] .= ($langs[$cur]['logs'] === '' ? '' : "\n") . $m[1]; $lastTag = 'logs'; continue; }
    if (preg_match('/^@see\s+(.+)$/', $line, $m)) { foreach (preg_split('/\s*,\s*|\s+/', trim($m[1])) as $s) if ($s !== '') $langs[$cur]['see'][] = $s; $lastTag = 'see'; continue; }

    // Continuation lines.
    if ($lastTag === 'brief') $langs[$cur]['brief'] .= ' ' . $line;
    else if ($lastTag === 'description') $langs[$cur]['description'] .= ($langs[$cur]['description'] === '' ? '' : "\n") . $line;
    else if ($lastTag === 'param' && $lastName !== null) $langs[$cur]['params'][$lastName] .= ' ' . $line;
    else if ($lastTag === 'return') $langs[$cur]['return'] .= ' ' . $line;
    else if ($lastTag === 'return-case' && $lastName !== null) $langs[$cur]['returns'][$lastName] .= ' ' . $line;
    else if ($lastTag === 'logs') $langs[$cur]['logs'] .= ($langs[$cur]['logs'] === '' ? '' : "\n") . $line;
    else if ($lastTag === 'error' && $lastName !== null) $langs[$cur]['errors'][$lastName] .= ' ' . $line;
  }
  return [$meta, $langs];
}

function next_code_statement(string $text, int $offset): string {
  $tail = substr($text, $offset);
  $tail = preg_replace('#^\s*(?:/\*.*?\*/\s*|//[^\n]*\n\s*)*#s', '', $tail);
  if (preg_match('/^(.*?)(?:\{|;)/s', $tail, $m))
    return trim($m[1]);
  return '';
}

function normalize_ws(string $s): string { return trim(preg_replace('/\s+/', ' ', $s)); }

function infer_symbol_from_proto(string $proto): string {
  $p = normalize_ws($proto);
  if (preg_match('/(?:^|[\s\*&])([A-Za-z_][A-Za-z0-9_]*)\s*\(/', $p, $m)) return $m[1];
  if (preg_match('/\b(?:typedef\s+)?(?:struct|enum|union)\s+(?:[A-Za-z_][A-Za-z0-9_]*\s*)?(?:\{.*\}\s*)?([A-Za-z_][A-Za-z0-9_]*)\s*$/s', $p, $m)) return $m[1];
  if (preg_match('/\b([A-Za-z_][A-Za-z0-9_]*)\s*$/', $p, $m)) return $m[1];
  return '';
}

function infer_module(string $path, string $root): string {
  $rel = str_replace('\\', '/', substr($path, strlen($root) + 1));
  if (preg_match('#include/lapin/([^/.]+)\.h$#', $rel, $m)) return $m[1];
  if (preg_match('#src/([^/]+)/#', $rel, $m)) return $m[1];
  return 'misc';
}

function find_header_proto(string $root, string $symbol): ?string {
  static $headers = null;
  if ($headers === null) $headers = list_files($root . '/include', ['h', 'hpp']);
  foreach ($headers as $h) {
    $txt = file_get_contents($h);
    if ($txt === false || !str_contains($txt, $symbol)) continue;
    $q = preg_quote($symbol, '/');
    if (preg_match('/((?:[A-Za-z_][A-Za-z0-9_]*|const|unsigned|signed|struct|enum|union|\s|\*|&)+\s+' . $q . '\s*\([^;{}]*\))\s*;/s', $txt, $m))
      return normalize_ws($m[1]) . ';';
    if (preg_match('/((?:typedef\s+)?(?:struct|enum|union)\s+[^;]*\b' . $q . '\b\s*;)/s', $txt, $m))
      return normalize_ws($m[1]);
    if (preg_match('/((?:extern\s+)?(?:const\s+)?[A-Za-z_][A-Za-z0-9_\s\*]+\s+' . $q . '\s*;)/s', $txt, $m))
      return normalize_ws($m[1]);
  }
  return null;
}

function split_params(string $prototype): array {
  if (!preg_match('/\((.*)\)/s', $prototype, $m)) return [];
  $inside = trim($m[1]);
  if ($inside === '' || $inside === 'void') return [];
  $parts = [];
  $cur = ''; $depth = 0;
  for ($i = 0; $i < strlen($inside); ++$i) {
    $ch = $inside[$i];
    if ($ch === '(') $depth++;
    if ($ch === ')') $depth--;
    if ($ch === ',' && $depth === 0) { $parts[] = trim($cur); $cur = ''; }
    else $cur .= $ch;
  }
  if (trim($cur) !== '') $parts[] = trim($cur);
  return $parts;
}

function param_name(string $param): string {
  $p = trim($param);
  $p = preg_replace('/=.*$/', '', $p);
  if (preg_match('/\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)/', $p, $m)) return $m[1];
  if (preg_match('/([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])?\s*$/', $p, $m)) return $m[1];
  return '';
}

function mark_token(string $tok, array $paramNames = []): string {
  static $keywords = ['const'=>1, 'volatile'=>1, 'static'=>1, 'extern'=>1, 'typedef'=>1, 'struct'=>1, 'enum'=>1, 'union'=>1, 'return'=>1];
  static $types = ['void'=>1,'char'=>1,'short'=>1,'int'=>1,'long'=>1,'float'=>1,'double'=>1,'bool'=>1,'signed'=>1,'unsigned'=>1,'size_t'=>1,'ssize_t'=>1,'uint8_t'=>1,'uint16_t'=>1,'uint32_t'=>1,'uint64_t'=>1,'int8_t'=>1,'int16_t'=>1,'int32_t'=>1,'int64_t'=>1];
  if (isset($keywords[$tok])) return '$K' . $tok . '@';
  if (isset($types[$tok]) || preg_match('/^(t_|s_|u_|e_)[A-Za-z0-9_]+$/', $tok)) return '$T' . $tok . '@';
  if (preg_match('/^[A-Z][A-Z0-9_]+$/', $tok)) return '$C' . $tok . '@';
  if (isset($paramNames[$tok]) || preg_match('/^(bunny_|gl_bunny_|t_bunny_|e_bunny_|s_bunny_|u_bunny_)[A-Za-z0-9_]+$/', $tok)) return '$S' . $tok . '@';
  return htmlspecialchars($tok, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8');
}

function prototype_param_names(string $prototype): array {
  $out = [];
  foreach (split_params($prototype) as $p) {
    $n = param_name($p);
    if ($n !== '') $out[$n] = true;
  }
  return $out;
}

function protect_literals(string $text, bool $code): array {
  $lits = [];
  // Nowdoc avoids PHP string escaping corrupting the PCRE character classes.
  // Matches C/PHP-like single and double quoted literals, including escaped chars.
  $pattern = <<<'REGEX'
~("(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*')~s
REGEX;
  $text = preg_replace_callback($pattern, function($m) use (&$lits) {
    $key = "\x1A" . count($lits) . "\x1A";
    $lit = htmlspecialchars($m[0], ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8');
    $lits[$key] = '$L' . $lit . '@';
    return $key;
  }, $text);
  if ($text === null) {
    warnx('literal colorization failed: ' . preg_last_error_msg());
    return ['', []];
  }
  return [$text, $lits];
}

function restore_literals(string $text, array $lits): string {
  return strtr($text, $lits);
}

function colorize_code(string $code, array $paramNames = []): string {
  [$work, $lits] = protect_literals($code, true);
  $work = htmlspecialchars($work, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8');
  $work = preg_replace_callback('/\b[A-Za-z_][A-Za-z0-9_]*\b/', fn($m) => mark_token($m[0], $paramNames), $work);
  return restore_literals($work, $lits);
}

function colorize_text(string $text, array $paramNames = []): string {
  [$work, $lits] = protect_literals($text, false);
  $work = htmlspecialchars($work, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8');
  $work = preg_replace_callback('/\b[A-Za-z_][A-Za-z0-9_]*\b/', function($m) use ($paramNames) {
    $tok = $m[0];
    if (isset($paramNames[$tok])) return '$S' . $tok . '@';
    if ($tok === 'true' || $tok === 'false' || $tok === 'NULL') return '$C' . $tok . '@';
    if (preg_match('/^(bunny_|gl_bunny_|t_bunny_|e_bunny_|s_bunny_|u_bunny_)[A-Za-z0-9_]+$/', $tok)) return '$S' . $tok . '@';
    if (preg_match('/^[A-Z][A-Z0-9_]+$/', $tok)) return '$C' . $tok . '@';
    return $tok;
  }, $work);
  return restore_literals($work, $lits);
}

function resume_text_html(string $brief, string $description, array $paramNames = []): string {
  $lines = [];

  $brief = trim($brief);
  if ($brief !== '') $lines[] = $brief;

  foreach (preg_split('/\R+/', trim($description)) as $line) {
    $line = trim($line);
    if ($line !== '') $lines[] = $line;
  }

  if (!$lines) return '';

  // Historical LibLapin documentation expects the resume block to be
  // plain inline text, not paragraphs.  Each logical source line from
  // @brief/@description is treated as one paragraph-like chunk and is
  // separated from the next one by TWO explicit <br /> tags.
  // Do not use $A here: the old resume blocks contain direct text, and
  // the website preprocessor/linker operates correctly on that form.
  $out = [];
  foreach ($lines as $line)
    $out[] = colorize_text($line, $paramNames);

  return "  " . implode("<br />\n  <br />\n  ", $out) . "<br />\n";
}

function paragraph_html(string $text, array $paramNames = []): string {
  $text = trim($text);
  if ($text === '') return '';
  $paras = preg_split('/\n\s*\n/', $text);
  $out = [];
  foreach ($paras as $p) {
    $p = trim(preg_replace('/\n+/', "\n", $p));
    $p = colorize_text($p, $paramNames);
    $p = preg_replace('/\n/', "<br />\n  ", $p);
    $out[] = "  <p>\n    $p\n  </p>";
  }
  return implode("\n", $out);
}

function label_title(string $label): string {
  $label = strtolower(trim($label));
  if ($label === 'success') return 'success';
  if ($label === 'failure' || $label === 'fail') return 'failure';
  if ($label === 'error') return 'error';
  return str_replace(['_', '-'], ' ', $label);
}

function page_html(DocItem $it, string $lang): string {
  $d = $it->lang[$lang] ?? null;
  if ($d === null) return '';
  $paramNames = prototype_param_names($it->prototype);
  $proto = colorize_code($it->prototype, $paramNames);
  $html = "<div class=\"prototype\">\n  $proto\n</div>\n<hr />\n\n";
  $html .= "<div class=\"resume\">\n  <h3>Description</h3>\n";
  $html .= resume_text_html($d['brief'] ?? '', $d['description'] ?? '', $paramNames);
  $html .= "</div>\n<hr />\n\n";

  $params = split_params($it->prototype);
  if ($params) {
    $html .= "<div class=\"parameters\">\n  <h3>Parameters</h3>\n  <ul>\n";
    foreach ($params as $p) {
      $name = param_name($p);
      $desc = $d['params'][$name] ?? '';
      $html .= "    <li>\n      " . colorize_code($p, $paramNames) . ":<br />\n";
      $html .= "      \$A " . colorize_text($desc, $paramNames) . "\n";
      $html .= "    </li>\n";
    }
    $html .= "  </ul>\n</div>\n<hr />\n\n";
  }

  if (!empty($d['returns']) || (($d['return'] ?? '') !== '')) {
    $html .= "<div class=\"return\">\n  <h3>Return value</h3>\n";
    if (!empty($d['returns'])) {
      $html .= "  <ul>\n";
      foreach ($d['returns'] as $label => $desc) {
        $html .= "    <li>\n      On \$B" . htmlspecialchars(label_title($label), ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8') . "@, " . colorize_text($desc, $paramNames) . "\n    </li>\n";
      }
      $html .= "  </ul>\n";
    } else {
      $html .= "  <p>\n    " . colorize_text($d['return'], $paramNames) . "\n  </p>\n";
    }
    $html .= "</div>\n<hr />\n\n";
  }

  if (!empty($d['errors']) || (($d['logs'] ?? '') !== '')) {
    $html .= "<div class=\"error_and_log\">\n  <h3>Error values and logs</h3>\n";
    if (!empty($d['errors'])) {
      $html .= "  <p>\n    On error, \$Sbunny_errno@ is set to:\n  </p>\n  <br />\n  <ul>\n";
      foreach ($d['errors'] as $err => $desc) {
        $html .= "    <li>\n      \$C" . htmlspecialchars($err, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8') . "@:<br />\n      <p>\n        " . colorize_text($desc, $paramNames) . "<br />\n      </p>\n    </li>\n";
      }
      $html .= "  </ul>\n";
    }
    if (($d['logs'] ?? '') !== '') {
      $html .= "  <br />\n" . paragraph_html($d['logs'], $paramNames) . "\n";
    }
    $html .= "</div>\n<hr />\n\n";
  }

  if (!empty($d['see'])) {
    $html .= "<div class=\"related_functions\">\n  <h3>Related functions</h3>\n  <ul>\n";
    foreach (array_unique($d['see']) as $see)
      $html .= "    <li>\$S" . htmlspecialchars($see, ENT_NOQUOTES | ENT_SUBSTITUTE, 'UTF-8') . "@</li>\n";
    $html .= "  </ul>\n</div>\n";
  }
  return $html;
}



function find_matching_brace(string $text, int $openPos): int {
  $len = strlen($text);
  $depth = 0;
  $state = 'code';
  for ($i = $openPos; $i < $len; ++$i) {
    $ch = $text[$i];
    $nx = $i + 1 < $len ? $text[$i + 1] : '';
    if ($state === 'code') {
      if ($ch === '/' && $nx === '/') { $state = 'line'; $i++; continue; }
      if ($ch === '/' && $nx === '*') { $state = 'block'; $i++; continue; }
      if ($ch === '"') { $state = 'dquote'; continue; }
      if ($ch === "'") { $state = 'squote'; continue; }
      if ($ch === '{') $depth++;
      else if ($ch === '}') {
        $depth--;
        if ($depth === 0) return $i;
      }
    } else if ($state === 'line') {
      if ($ch === "\n") $state = 'code';
    } else if ($state === 'block') {
      if ($ch === '*' && $nx === '/') { $state = 'code'; $i++; }
    } else if ($state === 'dquote') {
      if ($ch === '\\') { $i++; continue; }
      if ($ch === '"') $state = 'code';
    } else if ($state === 'squote') {
      if ($ch === '\\') { $i++; continue; }
      if ($ch === "'") $state = 'code';
    }
  }
  return -1;
}

function extract_function_body_after_comment(string $text, int $offset): string {
  $open = strpos($text, '{', $offset);
  $semi = strpos($text, ';', $offset);
  if ($open === false || ($semi !== false && $semi < $open)) return '';
  $close = find_matching_brace($text, $open);
  if ($close < 0) return '';
  return substr($text, $open, $close - $open + 1);
}

function strip_c_comments_and_strings(string $code): string {
  $code = preg_replace('#//[^\n]*#', ' ', $code);
  $code = preg_replace('#/\*.*?\*/#s', ' ', $code);
  return $code ?? '';
}

function split_call_args(string $args): array {
  $out = [];
  $cur = '';
  $depth = 0;
  $state = 'code';
  $len = strlen($args);
  for ($i = 0; $i < $len; ++$i) {
    $ch = $args[$i];
    if ($state === 'code') {
      if ($ch === '"') { $state = 'dquote'; $cur .= $ch; continue; }
      if ($ch === "'") { $state = 'squote'; $cur .= $ch; continue; }
      if ($ch === '(' || $ch === '[' || $ch === '{') $depth++;
      else if ($ch === ')' || $ch === ']' || $ch === '}') $depth--;
      if ($ch === ',' && $depth === 0) { $out[] = trim($cur); $cur = ''; continue; }
      $cur .= $ch;
    } else if ($state === 'dquote') {
      $cur .= $ch;
      if ($ch === '\\') { if ($i + 1 < $len) $cur .= $args[++$i]; continue; }
      if ($ch === '"') $state = 'code';
    } else if ($state === 'squote') {
      $cur .= $ch;
      if ($ch === '\\') { if ($i + 1 < $len) $cur .= $args[++$i]; continue; }
      if ($ch === "'") $state = 'code';
    }
  }
  if (trim($cur) !== '') $out[] = trim($cur);
  return $out;
}

function find_macro_calls(string $body, string $name): array {
  $calls = [];
  $offset = 0;
  while (($pos = strpos($body, $name . '(', $offset)) !== false) {
    $start = $pos + strlen($name);
    $depth = 0;
    $state = 'code';
    $len = strlen($body);
    for ($i = $start; $i < $len; ++$i) {
      $ch = $body[$i];
      if ($state === 'code') {
        if ($ch === '"') { $state = 'dquote'; continue; }
        if ($ch === "'") { $state = 'squote'; continue; }
        if ($ch === '(') $depth++;
        else if ($ch === ')') {
          $depth--;
          if ($depth === 0) {
            $calls[] = substr($body, $start + 1, $i - $start - 1);
            $offset = $i + 1;
            continue 2;
          }
        }
      } else if ($state === 'dquote') {
        if ($ch === '\\') { $i++; continue; }
        if ($ch === '"') $state = 'code';
      } else if ($state === 'squote') {
        if ($ch === '\\') { $i++; continue; }
        if ($ch === "'") $state = 'code';
      }
    }
    $offset = $pos + strlen($name);
  }
  return $calls;
}

function clean_expr(string $expr): string {
  return trim(preg_replace('/\s+/', ' ', $expr));
}

function is_errno_constant(string $expr): bool {
  $e = trim($expr);
  if ($e === '' || $e === '0' || $e === 'bunny_errno') return false;
  return (bool)preg_match('/^(BE_[A-Z0-9_]+|E[A-Z0-9_]+)$/', $e);
}

/** @return array{0:array<int,string>,1:array<string,string>} */
function infer_logs_and_errors(string $body): array {
  $logs = [];
  $errors = [];

  foreach (['scream_log_if', 'scream_warning_if', 'scream_error_if'] as $macro) {
    foreach (find_macro_calls($body, $macro) as $call) {
      $args = split_call_args($call);
      if ($macro === 'scream_error_if') {
        $err = $args[1] ?? '';
        if (is_errno_constant($err)) $errors[clean_expr($err)] = 'Can be set when the corresponding error path is reached.';
        $pattern = $args[2] ?? '';
        $domain = $args[3] ?? '';
        if ($pattern !== '' || $domain !== '') {
          $logs[] = 'May emit an error log' . ($domain !== '' ? ' in ' . clean_expr($domain) : '') . ($pattern !== '' ? ' with pattern ' . clean_expr($pattern) : '') . '.';
        }
      } else {
        $pattern = $args[0] ?? '';
        $domain = $args[1] ?? '';
        if ($pattern !== '' || $domain !== '') {
          $kind = $macro === 'scream_warning_if' ? 'warning log' : 'log';
          $logs[] = 'May emit a ' . $kind . ($domain !== '' ? ' in ' . clean_expr($domain) : '') . ($pattern !== '' ? ' with pattern ' . clean_expr($pattern) : '') . '.';
        }
      }
    }
  }

  $plain = strip_c_comments_and_strings($body);
  if (preg_match_all('/\bbunny_errno\s*=\s*([^;]+)\s*;/', $plain, $m)) {
    foreach ($m[1] as $expr) {
      $expr = clean_expr($expr);
      if (is_errno_constant($expr)) $errors[$expr] = 'Can be assigned by this function.';
    }
  }

  $logs = array_values(array_unique($logs));
  ksort($errors);
  return [$logs, $errors];
}


function translate_auto_text(string $text, string $lang): string {
  if ($lang !== 'fr') return $text;
  $text = str_replace('Can be set when the corresponding error path is reached.', 'Peut être renseigné lorsque le chemin d\'erreur correspondant est atteint.', $text);
  $text = str_replace('Can be assigned by this function.', 'Peut être assigné par cette fonction.', $text);
  $text = str_replace('May emit an error log', 'Peut émettre un log d\'erreur', $text);
  $text = str_replace('May emit a warning log', 'Peut émettre un log d\'avertissement', $text);
  $text = str_replace('May emit a log', 'Peut émettre un log', $text);
  $text = str_replace(' with pattern ', ' avec le motif ', $text);
  $text = str_replace(' in ', ' dans ', $text);
  return $text;
}

function merge_auto_doc(DocItem $it): void {
  if ($it->body === '') return;
  [$logs, $errors] = infer_logs_and_errors($it->body);
  $it->autoLogs = $logs;
  $it->autoErrors = $errors;
  foreach ($it->lang as $lang => &$d) {
    foreach ($errors as $err => $desc) {
      if (!isset($d['errors'][$err])) $d['errors'][$err] = translate_auto_text($desc, $lang);
    }
    if (!empty($logs)) {
      $auto = implode("\n", array_map(fn($x) => translate_auto_text($x, $lang), $logs));
      $d['logs'] = trim(($d['logs'] ?? '') . (($d['logs'] ?? '') !== '' ? "\n" : '') . $auto);
    }
  }
}

function version_php($v): string {
  if ($v === 'latest') return '$latest_version';
  return (string)((int)$v);
}

/** @param array<string,DocItem> $items */
function write_generated_meta(string $outRoot, array $items, array $langs, bool $dryRun): int {
  $byModule = [];
  foreach ($items as $it) $byModule[strtolower($it->module)][] = $it;
  $written = 0;
  foreach ($byModule as $module => $list) {
    usort($list, function(DocItem $a, DocItem $b): int {
      $oa = $a->order ?? 9999; $ob = $b->order ?? 9999;
      return [$oa, $a->symbol] <=> [$ob, $b->symbol];
    });
    foreach ($langs as $lang) {
      $dir = "$outRoot/$lang/manual/$module";
      $file = "$dir/meta.generated.php";
      $content = "<?php\n";
      $content .= "// Generated by generate_doc.php; do not edit manually.\n";
      $content .= "if (!isset(\$functions)) \$functions = [];\n";
      $content .= "if (!isset(\$circle_level)) \$circle_level = [];\n";
      $content .= "if (!isset(\$version_that_support)) \$version_that_support = [];\n\n";
      $groups = [];
      foreach ($list as $it) $groups[$it->order ?? 9999][] = $it->symbol;
      foreach ($groups as $ord => $symbols) {
        $content .= "\$functions[$ord] = array_values(array_unique(array_merge(\$functions[$ord] ?? [], [";
        foreach ($symbols as $sym) $content .= "\n  " . var_export($sym, true) . ",";
        $content .= "\n])));\n";
      }
      $content .= "\nforeach ([\n";
      foreach ($list as $it) $content .= "  " . var_export($it->symbol, true) . " => {$it->level},\n";
      $content .= "] as \$k => \$v) \$circle_level[\$k] = \$v;\n\n";
      $content .= "foreach ([\n";
      foreach ($list as $it) $content .= "  " . var_export($it->symbol, true) . " => [" . version_php($it->since) . ", " . version_php($it->until) . "],\n";
      $content .= "] as \$k => \$v) \$version_that_support[\$k] = \$v;\n";
      if ($dryRun) echo "$file\n";
      else {
        if (!is_dir($dir) && !mkdir($dir, 0775, true)) fail("cannot create $dir");
        file_put_contents($file, $content);
      }
      $written++;
    }
  }
  return $written;
}

function remove_old_generated(string $outRoot): void {
  foreach (['en', 'fr'] as $lang) {
    $dir = "$outRoot/$lang/manual";
    foreach (list_files($dir, ['php']) as $f) {
      $txt = file_get_contents($f);
      if ($txt !== false && str_contains($txt, 'Generated by generate_doc.php'))
        unlink($f);
    }
  }
}

if (!is_dir($root . '/include') || !is_dir($root . '/src'))
  fail('this script must be run from the LibLapin repository root');
if ($cleanGenerated && !$dryRun) remove_old_generated($outRoot);

$files = array_merge(list_files($root . '/src', ['c','cc','cpp','cxx','h','hpp']), list_files($root . '/include', ['h','hpp']));
$items = [];
foreach ($files as $file) {
  $txt = file_get_contents($file);
  if ($txt === false) continue;
  if (!preg_match_all('#/\*\*.*?@doc-lang\s+[a-z].*?\*/#is', $txt, $matches, PREG_OFFSET_CAPTURE)) continue;
  foreach ($matches[0] as [$comment, $pos]) {
    [$meta, $langsFound] = parse_doc_block($comment);
    $after = next_code_statement($txt, $pos + strlen($comment));
    $symbol = $meta['symbol'] ?: infer_symbol_from_proto($after);
    if ($symbol === '') { warnx("cannot infer symbol after doc block in $file"); continue; }
    $proto = find_header_proto($root, $symbol) ?: (normalize_ws($after) . (str_ends_with(trim($after), ';') ? '' : ';'));
    $it = new DocItem();
    $it->symbol = $symbol;
    $it->module = $meta['module'] ?: infer_module($file, $root);
    $it->order = $meta['order'];
    $it->since = is_int($meta['since']) ? $meta['since'] : 0;
    $it->until = $meta['until'];
    $it->level = (int)$meta['level'];
    $it->prototype = $proto;
    $it->lang = $langsFound;
    $it->source = substr($file, strlen($root) + 1);
    $it->body = extract_function_body_after_comment($txt, $pos + strlen($comment));
    merge_auto_doc($it);
    $items[$symbol] = $it;
  }
}

ksort($items);
$written = 0;
foreach ($items as $it) {
  $prefix = $it->order === null ? '9999' : sprintf('%03d', $it->order);
  foreach ($langs as $lang) {
    if (!isset($it->lang[$lang])) continue;
    $dir = "$outRoot/$lang/manual/" . strtolower($it->module);
    $file = "$dir/{$prefix}_{$it->symbol}.php";
    $content = "<?php /* Generated by generate_doc.php from {$it->source}; do not edit manually. */ ?>\n" . page_html($it, $lang);
    if ($dryRun) echo "$file\n";
    else {
      if (!is_dir($dir) && !mkdir($dir, 0775, true)) fail("cannot create $dir");
      file_put_contents($file, $content);
    }
    $written++;
  }
}

$metaWritten = write_generated_meta($outRoot, $items, $langs, $dryRun);
echo ($dryRun ? 'would write ' : 'wrote ') . $written . " manual page(s) and " . $metaWritten . " generated meta file(s) from " . count($items) . " documented symbol(s).\n";
