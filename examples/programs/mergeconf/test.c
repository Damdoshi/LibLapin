
int $([#Eval].TestFunctionName)(void)
{
  if ($([#Eval].FunctionName)(5) != 5)
    return (1);
  if ($([#Eval].FunctionName)(0) != 0)
    return (1);
  // A completer...
  return (0);
}

