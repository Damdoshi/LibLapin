<?php

require_once ("../split_file.php");
require_once ("../bassert.php");

$docs = split_file("./file_to_split.cpp");

BAssert(isset($docs[100]), "no order 100 was found");
BAssert($docs[100]["name"] == "bunny_set_log_descriptor", "invalid name");
BAssert($docs[100]["desc"] == "first description", "invalid desc");
BAssert($docs[100]["params"][0]["name"] == "fd", "invalid first parameter name");
BAssert($docs[100]["params"][0]["desc"] == "blah", "invalid first parameter value");
BAssert(!isset($docs[100]["params"][1]), "a single parameter was expected");
BAssert($docs[100]["return"] == "the return", "invalid return value");
BAssert($docs[100]["type"] == "function", "invalid type");

BAssert(isset($docs[120]), "no order 100 was found");
BAssert($docs[120]["name"] == "main", "invalid name");
BAssert($docs[120]["desc"] == "second description", "invalid desc");
BAssert(!isset($docs[120]["params"][0]), "no parameters were expected");
BAssert($docs[120]["return"] == "always 0", "invalid return value");
BAssert($docs[120]["type"] == "function", "invalid type");

BAssert($docs[140]["type"] == "enum", "invalid type ".$docs[140]["type"]);
BAssert($docs[160]["type"] == "union", "invalid type ".$docs[160]["type"]);
BAssert($docs[180]["type"] == "struct", "invalid type ".$docs[180]["type"]);
BAssert($docs[200]["type"] == "macro", "invalid type ".$docs[200]["type"]);
BAssert($docs[220]["type"] == "macro_constant", "invalid type ".$docs[220]["type"]);
BAssert($docs[240]["type"] == "alias", "invalid type ".$docs[240]["type"]);
BAssert($docs[260]["type"] == "global", "invalid type ".$docs[260]["type"]);
BAssert($docs[280]["type"] == "global", "invalid type ".$docs[280]["type"]);
BAssert($docs[300]["type"] == "global", "invalid type ".$docs[300]["type"]);

if ($ErrorHappened)
  echo "Failure! Got:\n";
else
  echo "Success! Got:\n";

print_r($docs);
exit($ErrorHappened ? 1 : 0);

