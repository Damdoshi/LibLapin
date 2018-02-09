/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** La Caverne Aux Lapins Noirs
*/

var symbols = {};
var regex = null;

function search(mod, input)
{
  if (input.value == "")
  {
    for (var key in symbols) if (symbols.hasOwnProperty(key))
      document.getElementById(symbols[key]).style.display = "inline-block";
  }
  else
  {
    if (global_roll == -1)
      roll_unroll_all(mod);
    regex = new RegExp(input.value);

    for (var key in symbols) if (symbols.hasOwnProperty(key))
      document.getElementById(symbols[key]).style.display =
        regex.test(key) ? "inline-block" : "none";
  }

  for (var key in mod) if (mod.hasOwnProperty(key))
  {
    var ul = document.getElementById(mod[key] + "_list");
    var ils = ul.getElementsByTagName("li");
    var display = false;

    for (var li in ils) if (ils.hasOwnProperty(li))
    {
      if (ils[li].style.display != "none")
      {
        display = true;
        break ;
      }
    }
    if (display)
      ul.style.display = "block";
    else
      ul.style.display = "none";
  }

  window.setTimeout(search, 100, mod, input);
}

