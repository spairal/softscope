#ifndef FPGA_HPP
#define FPGA_HPP

#include <Configuration.hpp>
#include <Samples.hpp>
#include <MiniWahoo.hpp>
#include <fix.hpp>

class FPGA
{
   private:
      Configuration& configuration;
      Samples& samples;
      MiniWahoo miniWahoo;
      char* channelABuffer;
      char* channelBBuffer;

   public:
      FPGA(Configuration& configuration, Samples& samples);
      void fetchSamples(void);
   
   private:
      int getMask(int bits);
      int quantize(bool value);
      int quantize(fix value, fix minimum, int bits);
};

#endif
