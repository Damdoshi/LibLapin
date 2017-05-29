![LibLapin logo](http://hangedbunnystudio.com/content/lapin_title.png)

# LibLapin - "Bunny Library"

LibLapin is an easy and direct graphic and game library offering a C API.
It provides features from graphics, events and sound to network and configuration scripts.
It is written in "C+" and can be used in both C and C++.

It was originally designed to be used as rookie library for a private french school with three objectives:
- Make pupils progress in graphic programming
- Make pupils progress in C programming
- Allow them to compete in game jam and demo parties

LibLapin is based on SFML but does not bind all its features and is not only made of binds to SFML.
(Even this readme.md is a shameful rip off the SFML one)

## Authors

  * Jason Brillante (damdoshi@hotmail.com)

## Download

There is currently no tarball to get, but you can clone our master branch to get the latest stable, or the working branch if you feel aventurous.

## Install

For Linux:
* Install SFML on your system.
* Download the LibLapin version of your choice.
* Execute install.sh or school_install.sh
* Reset your shell

For Windows (May need some tweaks - will be fixed soon):
* Get SFML.
* Download the LibLapin version of your choice.
* Install Code Block
* Run the LibLapin code block project
* You may need to add missing source files
* Compile

## Links

 * The [manual] (http://hangedbunnystudio.com/sub/liblapin/)
 * The [tutorials] (http://)
 * The [LibLapin Facebook page] (https://www.facebook.com/LeGrandLapinNoir/)
 * The [Hanged Bunny Studio forum] 

## Contribute

LibLapin is an open-source project and there is still a lot of work to do to make it great. It needs your help!
If you want to contribute, your are absolutely welcome!
You can suggest new features, report bugs and of course bring code.

If you want to commit something, my only request is: please, keep the project homogeneous:

 * You may found names too long but that is the way it is, make your symbols'name the same way.
 * Use existing types if you bring a new object that have similar behaviour to one and patch functions that use the parent types to make it work on yours.
 * Try to keep the coding style as it is, at least inside the headers file. I don't care much about code files.
 * If you create a new module, add a small program in example/misc/ to demonstrate what your module do.
 * If you need to break the API to extend it, don't break it: create a new function with your new prototype and bring an additional macro with the old one that call the new one.
 * Doxygen all

