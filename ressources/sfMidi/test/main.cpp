////////////////////////////////
// sfMidiTest 1.0.2           //
// Copyright © Kerli Low 2012 //
////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// License:                                                                 //
// sfMidiTest                                                               //
// Copyright (c) 2012 Kerli Low                                             //
// kerlilow@gmail.com                                                       //
//                                                                          //
// This software is provided 'as-is', without any express or implied        //
// warranty. In no event will the authors be held liable for any damages    //
// arising from the use of this software.                                   //
//                                                                          //
// Permission is granted to anyone to use this software for any purpose,    //
// including commercial applications, and to alter it and redistribute it   //
// freely, subject to the following restrictions:                           //
//                                                                          //
//    1. The origin of this software must not be misrepresented; you must   //
//    not claim that you wrote the original software. If you use this       //
//    software in a product, an acknowledgment in the product documentation //
//    would be appreciated but is not required.                             //
//                                                                          //
//    2. Altered source versions must be plainly marked as such, and must   //
//    not be misrepresented as being the original software.                 //
//                                                                          //
//    3. This notice may not be removed or altered from any source          //
//    distribution.                                                         //
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sfMidi.h>



int main()
{
  sf::RenderWindow sfApp(sf::VideoMode(800, 600, 32), "SFML Window");

  sfApp.setFramerateLimit(60);

  sf::Sprite spr_bg;
  
  sf::Texture tex_bg;
  tex_bg.loadFromFile("bg.png");
  spr_bg.setTexture(tex_bg);

  spr_bg.setPosition(40.0f, 100.0f);

  sfmidi::Midi testMidi("GeneralUser GS FluidSynth v1.44.sf2",
                        "All Night Long.mid");
  if (testMidi.hasError()) {
    std::cout<<testMidi.getError();
    return 1;
  }

  testMidi.setGain(1.0);

  // To preload the midi instead:
  // sfmidi::Music testMidi;

  // {
  //   sfmidi::Loader testLoader("GeneralUser GS FluidSynth v1.44.sf2");
  //   testLoader.setGain(1.0);

  //   testMidi.loadMidiFromFile(testLoader, "All Night Long.mid");
  // }

  testMidi.play();

  while (sfApp.isOpen()) {
    sf::Event sfEvent;
    while (sfApp.pollEvent(sfEvent)) {
      if (sfEvent.type == sf::Event::Closed)
        sfApp.close();

      if ((sfEvent.type == sf::Event::KeyPressed)) {
        switch (sfEvent.key.code) {
		      case sf::Keyboard::Escape:
            {
              sfApp.close();
              break;
            }

          case sf::Keyboard::F12:
            {
              sf::Image screen = sfApp.capture();
              screen.saveToFile("screenshot.png");

              break;
            }

          case sf::Keyboard::Left:
            {
              sf::Int32 playingOffset =
                testMidi.getPlayingOffset().asMilliseconds();
              if (playingOffset > 4000) {
                testMidi.setPlayingOffset
                  (sf::milliseconds(playingOffset - 4000));
              }
              else
                testMidi.setPlayingOffset(sf::Time::Zero);

              break;
            }

          case sf::Keyboard::Right:
            {
              sf::Int32 playingOffset =
                testMidi.getPlayingOffset().asMilliseconds();

              testMidi.setPlayingOffset
                (sf::milliseconds(playingOffset + 4000));

              break;
            }

          case sf::Keyboard::Space:
            {
              if (testMidi.getStatus() != sf::SoundStream::Playing)
                testMidi.play();
              else
                testMidi.pause();
              break;
            }
        }
      }
    }

    sfApp.clear();

    sfApp.draw(spr_bg);

    sfApp.display();
  }

  testMidi.stop();

  return 0;
}
