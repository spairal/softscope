#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>

class Configuration
{
   public:
      enum VerticalScales {TEN_MV, TWENTY_MV, FIFTY_MV, HUNDRED_MV, TWOHUNDRED_MV, FIVEHUNDRED_MV, ONE_V, TWO_V, FIVE_V, TEN_V};
      enum HorizontalScales {TEN_NS, TWENTY_NS, FIFTY_NS, HUNDRED_NS, TWOHUNDRED_NS, FIVEHUNDRED_NS, ONE_US, TWO_US, FIVE_US, TEN_US, TWENTY_US, FIFTY_US, HUNDRED_US, TWOHUNDRED_US, FIVEHUNDRED_US, ONE_MS, TWO_MS, FIVE_MS, TEN_MS, TWENTY_MS, FIFTY_MS, HUNDRED_MS, TWOHUNDRED_MS, FIVEHUNDRED_MS, ONE_S};
      enum Couplings {AC, DC};
      enum Meassures {NOMEASSURE, CURSORS, MEAN, PEAK, RMS, FREQUENCY, PERIOD, RISETIME, FALLTIME, DUTYCYCLE, PHASE, RATIO};
      enum Mathematics {NOMATHEMATIC, DIFFERENCE, FFT};
      enum Modes {RUN, STOP, SINGLE, ROLL};
      enum TriggerModes {NORMAL, AUTOMATIC};
      enum TriggerSlopes {POSITIVE, NEGATIVE};
      enum Channels {NO_CHANNEL, CHANNEL_A, CHANNEL_B};
      enum Averages {TWO_CERO, TWO_ONE, TWO_TWO, TWO_THREE, TWO_FOUR, TWO_FIVE, TWO_SIX, TWO_SEVEN, TWO_EIGHT, TWO_NINE, TWO_TEN};

   private:
      double offsetA;
      double offsetB;
      VerticalScales verticalScaleA;
      VerticalScales verticalScaleB;
      int delay;
      HorizontalScales horizontalScale;
      Couplings coupling;
      bool channelA;
      bool channelB;
      Meassures meassure;
      double verticalCursor[2];
      int horizontalCursor[2];
      Mathematics mathematic;
      Modes mode;
      double triggerLevel;
      TriggerModes triggerMode;
      TriggerSlopes triggerSlope;
      Channels triggerChannel;
      bool triggerNoiseReject;
      bool triggerHighFrequencyReject;
      double triggerHoldOff;
      Averages average;

   public:
      Configuration(void);
      double getOffsetA(void);
      double getOffsetB(void);
      std::string getOffsetString(Channels channel);
      double getVerticalScale(Channels channel);
      std::string getVerticalScaleString(Channels channel);
      int getDelay(void);
      std::string getDelayString(int pixelsPerDivision);
      double getHorizontalScale(void);
      std::string getHorizontalScaleString(void);
      bool getChannelA(void);
      bool getChannelB(void);
};

#endif
