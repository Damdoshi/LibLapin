************************************************************
** sfMod                                                  **
************************************************************

------------------------------------------------------------
-- About                                                  --
------------------------------------------------------------
  sfMod is a static library for playing module files (tracker musics) in SFML.


------------------------------------------------------------
-- Author                                                 --
------------------------------------------------------------
  Kerli Low (a.k.a. zorexx)
    kerlilow@gmail.com
    http://www.zorexxlkl.com

------------------------------------------------------------
-- Contributors                                           --
------------------------------------------------------------
  Benjamin Foster
    bfoster@ripe.li

------------------------------------------------------------
-- Download                                               --
------------------------------------------------------------
  sfMod is available for download at:
    http://www.zorexxlkl.com/sfmod


------------------------------------------------------------
-- Install                                                --
------------------------------------------------------------
  1. Download the "Clean package" from the link above.
  2. Extract the contents to "C:\" (You can extract it to anywhere you want,
     but I'll use "C:\" for this example)
  3. Add the include and lib paths to your compiler.
  4. You're set! A short tutorial is available in the above link as well.

------------------------------------------------------------
-- Building on linux                                      --
------------------------------------------------------------
  1. Install libsfmod-dev and libmodplug-dev:
       sudo apt-get install libsfmod-dev libmodplug-dev
  1. Clone the repository
  2. Build the project:
       cd /path/to/repo
       mkdir build && cd build
       cmake .. && make
  3. If all went well, you can check for any runtime faults
     using the 'sfmod-test' binary, inside the build directory

------------------------------------------------------------
-- Discussion                                             --
------------------------------------------------------------
  Discussion for sfMidi is available on the SFML forum:
    http://www.sfml-dev.org/forum/viewtopic.php?t=6178
