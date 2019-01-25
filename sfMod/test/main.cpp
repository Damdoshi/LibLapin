////////////////////////////////
// sfModTest 1.0.2            //
// Copyright © Kerli Low 2012 //
////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// License:                                                                 //
// sfModTest                                                                //
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
#include <fstream>

#include <SFML/Graphics.hpp>
#include <sfMod.h>



int main()
{
  sf::RenderWindow sfApp(sf::VideoMode(800, 600, 32), "SFML Window");

  sfApp.setFramerateLimit(60);

  sf::Sprite spr_bg;
  
  sf::Texture tex_bg;
  tex_bg.loadFromFile("bg.png");
  spr_bg.setTexture(tex_bg);

  spr_bg.setPosition(40.0f, 100.0f);

  sfmod::Mod testMod("rainysum.mod");
  if (testMod.hasError()) {
    std::cout<<"Error: "<<testMod.getError()<<"\n";
    return 1;
  }

  testMod.play();

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
                testMod.getPlayingOffset().asMilliseconds();
              if (playingOffset > 4000) {
                testMod.setPlayingOffset
                  (sf::milliseconds(playingOffset - 4000));
              }
              else
                testMod.setPlayingOffset(sf::Time::Zero);

              break;
            }

          case sf::Keyboard::Right:
            {
              sf::Int32 playingOffset =
                testMod.getPlayingOffset().asMilliseconds();

              testMod.setPlayingOffset
                (sf::milliseconds(playingOffset + 4000));

              break;
            }

          case sf::Keyboard::Space:
            {
              if (testMod.getStatus() != sf::SoundStream::Playing)
                testMod.play();
              else
                testMod.pause();
              break;
            }
        }
      }
    }

    sfApp.clear();

    sfApp.draw(spr_bg);

    sfApp.display();
  }

  return EXIT_SUCCESS;
}
