#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <vector>

class Configuration
{
	public:
		enum VerticalScales {TEN_MV, TWENTY_MV, FIFTY_MV, HUNDRED_MV, TWOHUNDRED_MV, FIVEHUNDRED_MV, ONE_V, TWO_V, FIVE_V, TEN_V};
		enum HorizontalScales {TEN_NS, TWENTY_NS, FIFTY_NS, HUNDRED_NS, TWOHUNDRED_NS, FIVEHUNDRED_NS, ONE_US, TWO_US, FIVE_US, TEN_US, TWENTY_US, FIFTY_US, HUNDRED_US, TWOHUNDRED_US, FIVEHUNDRED_US, ONE_MS, TWO_MS, FIVE_MS, TEN_MS, TWENTY_MS, FIFTY_MS, HUNDRED_MS, TWOHUNDRED_MS, FIVEHUNDRED_MS, ONE_S};
		enum Couplings {AC, DC};
		enum Measures {NOMEASURE, CURSORS, MEAN, PEAK, RMS, FREQUENCY, PERIOD, RISETIME, FALLTIME, DUTYCYCLE, PHASE, RATIO};
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
		double delay;
		HorizontalScales horizontalScale;
		Couplings couplingA;
		Couplings couplingB;
		bool channelA;
		bool channelB;
		Measures measure;
		std::vector<double> verticalCursor;
		std::vector<double> horizontalCursor;
		Mathematics mathematic;
		Modes mode;
		TriggerModes triggerMode;
		Channels triggerChannel;
		TriggerSlopes triggerSlope;
		double triggerLevel;
		bool triggerNoiseReject;
		bool triggerHighFrequencyReject;
		double triggerHoldOff;
		Averages average;

	public:
		Configuration(void);
		double getOffset(Channels channel);
		std::string getOffsetString(Channels channel);
		void setOffset(Channels channel, double offset);
		VerticalScales getVerticalScale(Channels channel);
		double getVerticalScaleValue(Channels channel);
		std::string getVerticalScaleString(Channels channel);
		void setVerticalScale(Channels channel, VerticalScales verticalScale);
		double getDelay(void);
		std::string getDelayString(void);
		void setDelay(double d);
		HorizontalScales getHorizontalScale(void);
		double getHorizontalScaleValue(void);
		std::string getHorizontalScaleString(void);
		void setHorizontalScale(HorizontalScales scale);
		Couplings getCoupling(Channels channel);
		std::string getCouplingString(Channels channel);
		void setCoupling(Channels channel, Couplings coupling);
		bool getChannel(Channels channel);
		void setChannel(Channels channel, bool isActive);
		Measures getMeasure(void);
		std::string getMeasureString(Channels channel);
		std::string getCursorsString(Channels channel);
		std::string getMathematicString(void);
		std::string getModeString(void);
		std::string getRunString(void);
		std::string getSingleString(void);
		std::string getTriggerString(void);
		std::string getTriggerModeString(void);
		std::string getTriggerChannelString(void);
		std::string getTriggerSlopeString(void);
		std::string getTriggerLevelString(void);
		std::vector<std::string> getAllMeasures(void);
		std::vector<std::string> getAllMathematics(void);
		std::vector<std::string> getAllModes(void);
		void setMeasure(Measures selected);
		void setMathematic(Mathematics selected);
		void setMode(Modes selected);
		int getAverage(void);
		std::string getAverageString(void);
		std::string voltageToString(double voltage);
		std::string timeToString(double time);
		std::string frequencyToString(double frequency);
		std::string percentageToString(double percentage);
		std::string deciBellToString(double deciBell);
};

#endif

