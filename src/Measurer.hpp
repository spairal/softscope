#ifndef MEASURER_HPP
#define MEASURER_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <fix.hpp>

class Measurer
{
   private:
      Configuration& configuration;
      State& state;
      Samples& samples;
      std::string measure;
      int cachedTime;
      Configuration::Channels cachedChannel;
      Configuration::Measures cachedMeasure;
   
   public:
      Measurer(Configuration& configuration, State& state, Samples& samples);
      std::string getMeasure(void);
   
   private:
      std::string getMean(void);
      std::string getPeak(void);
      std::string getRMS(void);
      std::string getFrequency(void);
      std::string getPeriod(void);
      std::string getRiseTime(void);
      std::string getFallTime(void);
      std::string getDutyCycle(void);
      std::string getPhase(void);
      std::string getRatio(void);
      fix maximum(const std::vector<fix>& signal);
      fix minimum(const std::vector<fix>& signal);
      int getMaxCorrelation(const std::vector<fix>& signalA, const std::vector<fix>& signalB);
};

#endif
