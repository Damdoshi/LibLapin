/*
** Jason Brillante "Damdoshi"
** Hanged Bunny Studio 2014-2019
**
** LibLapin
*/

function switch_css(newfile) {

  var oldlink = document.getElementsByTagName("link").item(2);
  var newlink = document.createElement("link");

  newlink.setAttribute("rel", "stylesheet");
  newlink.setAttribute("type", "text/css");
  newlink.setAttribute("href", newfile);
  document.getElementsByTagName("head").item(0).replaceChild(newlink, oldlink);
}

