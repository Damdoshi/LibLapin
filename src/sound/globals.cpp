#include			"lapin_private.h"

std::vector<sf::SoundChannel> gl_channels[5] =
  {
    {
      sf::SoundChannel::Unspecified,
    },
    {
      sf::SoundChannel::Mono
    },
    {
      sf::SoundChannel::Unspecified,
      sf::SoundChannel::Mono,
      sf::SoundChannel::FrontLeft
    },
    {
      sf::SoundChannel::Unspecified,
      sf::SoundChannel::Mono,
      sf::SoundChannel::FrontLeft,
      sf::SoundChannel::FrontRight
    },
    {
      sf::SoundChannel::Unspecified,
      sf::SoundChannel::Mono,
      sf::SoundChannel::FrontLeft,
      sf::SoundChannel::FrontRight,
      sf::SoundChannel::FrontCenter
    }
  };

