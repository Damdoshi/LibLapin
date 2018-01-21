/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** La Caverne Aux Lapins Noirs
*/

// // // // // // // // // // // // // // // // // // // // //

function roll_unroll(mod, all = 0)
{
  var list = document.getElementById(mod + "_sublist");
  var arrow = document.getElementById(mod + "_arrow");

  console.log("all => " + all);
  if (all == 0)
  {
    if (list.style.display == "none")
    {
      list.style.display = "block";
      arrow.src = "res/arrow_down.png";
    }
    else
    {
      list.style.display = "none";
      arrow.src = "res/arrow_right.png";
    }
  }
  else if (all == -1)
  {
    list.style.display = "block";
    arrow.src = "res/arrow_down.png";
  }
  else
  {
    list.style.display = "none";
    arrow.src = "res/arrow_right.png";
  }
}

var global_roll = -1;

function roll_unroll_all(arr)
{
  var i;

  for (i = 0; i < arr.length; ++i)
    roll_unroll(arr[i], global_roll);
  if (global_roll == -1)
    global_roll = 1;
  else
    global_roll = -1;
}

