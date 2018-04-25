<p>
  This tutorial "Configuration files" is about the configuration
  module of the bunny library and will teach you how to use
  the configuration itself but also details about the supported
  format themselves.
  <br />
  The configuration module supports the following formats:<br />
  <br />
  $A The INI format. As a dialect, our version have some specificities.<br />
  $A The DABSIC format. Which is an original format.<br />
  $A The XML format. With some extensions.<br />
  $A The LUA format.<br />
  $A The CSV format.<br />
  $A The JSON format.<br />
  $A The LISP format.<br />
  $A In a future version, the YAML format may be supported.<br />
  <br />
  All those formats are extended with $T&#64;insert@ and $T&#64;include@ directives
  that allow while loading a file to load some others, inserting them in place
  or at root. Parameters of those directives can be file or directory.
  If it is directory, then it is not recursive.
  <br />
  <br />
  Configurations of bunny library are trees. Each node can have at the same time
  named children, indexed children and a value: nodes are at the same time hashmap,
  arrays and value.
  Each node can have a value which can be an integer, a double or a string.<br />
  It is currently only supported while using a file format that support it
  (and cannot be created by hand in your program), but a node can also be
  a reference to another node. Reference are automatically resolved on request.<br />
  <br />
  Expression available operators are:<br />
  <br />
  $A Assignation, with symbols '=', '<-' or ':='.<br />
  $A Recursive assignation of value, hashmap and array, with symbols '[=]', '[<-]' or '[:=]'.<br />
  $A Recursive assignation of value and hashmap, with symbols '[Hash=]', '[Hash<-]' or '[Hash:=]'.<br />
  $A Recursive assignation of value and array, with symbols '[Array=]', '[Array<-]' or '[Array:=]'.<br />
  <br />
  $A Logic or assignation with symbol '||='.<br />
  $A Logic xor assignation with symbol '^^='.<br />
  $A Logic and assignation with symbol '&&='.<br />
  $A Binary or assignation with symbol '|='.<br />
  $A Binary xor assignation with symbol '^='.<br />
  $A Binary and assignation with symbol '&='.<br />
  $A Left shift assignation with symbol '<<='.<br />
  $A Right shift assignation with symbol '>>='.<br />
  $A Addition assignation with symbol '+='.<br />
  $A Subtract assignation with symbol '-='.<br />
  $A Multiply assignation with symbol '*='.<br />
  $A Divide assignation with symbol '/='.<br />
  $A Modulo assignation with symbol '%='.<br />
  $A Power assignation with symbol '**='.<br />
  $A Concat assignation with symbol '#='.<br />
  <br />
  $A Ternary with symbols '?' and ':'.<br />
  <br />
  $A Logic or with symbols '||', 'or' or 'ou'.<br />
  $A Logic xor with symbols '^^', 'xor' or 'oux'.<br />
  $A Logic and with symbols '&&', 'and' or 'et'.<br />
  <br />
  $A Equal test with symbols '==', 'is', '.eq.' or '-eq'.<br />
  $A Recursive equal on hashmap, array and value test with symbols '[==]', '[is]'.<br />
  $A Inequal test with symbols '!=', '<>', '.ne.' or '-ne'.<br />
  $A Recursive inequal on hashmap, array and value test with symbols '[!=]', '[<>]'.<br />
  $A Lower or equal test with symbols '<=', '.le.' or '-le'.<br />
  $A Greater or equal test with symbols '>=', '.ge.' or '-ge'.<br />
  $A Lower or equal test with symbols '<', '.lt.' or '-lt'.<br />
  $A Greater or equal test with symbols '>', '.gt.' or '-gt'.<br />
  <br />
  $A Binary or with symbol '|'.<br />
  $A Binary xor with symbol '^'.<br />
  $A Binary and with symbol '&'.<br />
  $A Left shift with symbol '<<'.<br />
  $A Right shift with symbol '<<'.<br />
  <br />
  $A Addition with symbol '+'.<br />
  $A Subtract with symbol '-'.<br />
  $A Multiplication with symbol '*'.<br />
  $A Division with symbol '/'.<br />
  $A Modulo with symbol '%'.<br />
  $A Power with symbol '**'.<br />
  $A Concat with symbol '#'.<br />
</p>
