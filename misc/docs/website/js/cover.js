/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2018
**
** La Caverne Aux Lapins Noirs
*/

// // // // // // // // // // // // // // // // // // // // //

var LogoRotation = 0.0;
var CoverOpacity = 1.0;

function LogoDance(id_cover, id_logo)
{
  var cover = document.getElementById(id_cover);
  var logo = document.getElementById(id_logo);

  logo.style.width =
    logo.naturalWidth * Math.abs(Math.cos(LogoRotation += 0.2)) + "px";
  logo.style.height =
    logo.naturalHeight + "px";

  // fuck CSS
  logo.style.left = (window.innerWidth - logo.clientWidth) / 2.0 + "px";
  logo.style.top = (window.innerHeight - logo.clientHeight) / 2.0 + "px";

  logo.style.display = "initial";

  if (CoverOpacity >= 0)
	  window.setTimeout(LogoDance, 20, id_cover, id_logo);
}

function Reveal(id_cover)
{
  var cover = document.getElementById(id_cover);
  var opac;

  if (CoverOpacity > 0)
  {
	  cover.style.opacity = (CoverOpacity -= 0.15);
	  window.setTimeout(Reveal, 50, id_cover);
  }
  else
	  cover.style.display = "none";
}
