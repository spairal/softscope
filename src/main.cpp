#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Measurer.hpp>
#include <Mathematician.hpp>
#include <Touch.hpp>
#include <FPGA.hpp>
#include <Display.hpp>
#include <MiniFB.hpp>
#include <signal.h>

using namespace std;

bool* shutdown;

void signalHandler(int signo)
{
   *shutdown = true;
}

int main(int argc, char** argv)
{
   Configuration configuration;
   State state;
   Samples samples;
   Touch touch(configuration, state);
   FPGA fpga(configuration, samples);
   Display display(configuration, state, samples);
   shutdown = &state.shutdown;
   signal(SIGTERM, signalHandler);
   while(!state.shutdown)
   {
      touch.getInput();
      fpga.fetchSamples();
      display.print();
   }
   return 0;
}

