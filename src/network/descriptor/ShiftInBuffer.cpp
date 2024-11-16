// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2024
// EFRITS SAS 2022-2024
// Pentacle Technologie 2008-2024
//
// Bibliothèque Lapin

#include		"private/network/network.hpp"

bool			network::Descriptor::ShiftInBuffer(const Info		&info)
{
  try
    {
      inqueue.push_back(Communication{info});
    }
  catch (...)
    {
      return (false);
    }
  inqueue.back().datas = std::move(inbuffer);
  inbuffer.clear();
  rcursor = 0;
  try
    {
      inbuffer.resize(size);
    }
  catch (...)
    {
      return (false);
    }
  return (true);
}

