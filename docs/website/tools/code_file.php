<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

function code_file($file)
{
  $cnt = file_get_contents($file);
  $cnt = str_replace("\r", "", $cnt);
  $cnt = str_replace(" ", "&nbsp;", $cnt);
  $cnt = str_replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;", $cnt);
  $cnt = str_replace("<", '$L&lt;', $cnt);
  $cnt = str_replace(">", '&gt;@', $cnt);

  foreach ([
    "EXIT_FAILURE", "EXIT_SUCCESS", "EXIT_ON_SUCCESS", "EXIT_ON_FAILURE",
    "EXIT_ON_CROSS", "GO_ON", "SWITCH_CONTEXT", "GO_DOWN", "GO_UP",
    "LOST_FOCUS", "GOT_FOCUS", "CONNECTED", "DISCONNECTED", "ENTERING",
    "LEAVING"
  ] as $x)
    $cnt = str_replace($x, '$S'.$x.'@', $cnt);
  foreach ([
    "NULL", "false", "true", "TRANSPARENT", "BLACK", "RED", "GREEN", "BLUE",
    "PURPLE", "TEAL", "YELLOW", "WHITE", "PINK", "PINK2"
  ] as $x)
    $cnt = str_replace($x, '$C'.$x.'@', $cnt);
  foreach ([
    "struct", "return", "while", "for", "if", "typedef", "extern", "volatile",
    "register", "continue", "break", "goto", "switch"
  ] as $x)
    $cnt = str_replace($x, '$K'.$x.'@', $cnt);
  foreach ([
    "int", "double", "char", "uint64_t", "int64_t", "short", "long", "void"
  ] as $x)
    $cnt = str_replace($x, '$T'.$x.'@', $cnt);
  $cnt = preg_replace('/"[a-zA-Z\S0-9]+\"/', '$T${0}</span>', $cnt);
  $cnt = preg_replace("/&nbsp;t_[a-zA-Z0-9_]+/", '$T${0}@', $cnt);
  $cnt = preg_replace("/&nbsp;s_[a-zA-Z0-9_]+/", '$T${0}@', $cnt);
  $cnt = preg_replace("/\(t_[a-zA-Z0-9_]+/", '$T${0}@', $cnt);
  $cnt = preg_replace("/^t_[a-zA-Z0-9_]+/", '$T${0}@', $cnt);
  $cnt = preg_replace("/BKS_[a-zA-Z0-9_]+/", '$S${0}@', $cnt);
  $cnt = preg_replace("/BMB_[a-zA-Z0-9_]+/", '$S${0}@', $cnt);
  $cnt = preg_replace("/BA_[a-zA-Z0-9_]+/", '$S${0}@', $cnt);
  $cnt = preg_replace("/LAST_[a-zA-Z0-9_]+/", '$S${0}@', $cnt);
  $cnt = preg_replace('@//.*@', '<span style="color: red;">${0}</span>', $cnt);
  $cnt = preg_replace('@#[a-z]+@ ', '<span style="color: darkblue;">${0}</span>', $cnt);

  $cnt = str_replace("\n", "<br/>", $cnt);
  return ($cnt);
}
