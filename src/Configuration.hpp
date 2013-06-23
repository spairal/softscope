#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fix.hpp>
#include <string>
#include <vector>

class Configuration
{
	public:
		enum VerticalScales {TEN_MV, TWENTY_MV, FIFTY_MV, HUNDRED_MV, TWOHUNDRED_MV, FIVEHUNDRED_MV, ONE_V, TWO_V, FIVE_V, TEN_V};
		enum HorizontalScales {ONE_US, TWO_US, FIVE_US, TEN_US, TWENTY_US, FIFTY_US, HUNDRED_US, TWOHUNDRED_US, FIVEHUNDRED_US, ONE_MS, TWO_MS, FIVE_MS, TEN_MS, TWENTY_MS, FIFTY_MS, HUNDRED_MS, TWOHUNDRED_MS, FIVEHUNDRED_MS, ONE_S};
		enum Couplings {AC, DC};
		enum Measures {NOMEASURE, CURSORS, MEAN, PEAK, RMS, FREQUENCY, PERIOD, RISETIME, FALLTIME, DUTYCYCLE, PHASE, RATIO};
		enum Mathematics {NOMATHEMATIC, DIFFERENCE, FFT};
		enum Modes {RUN, STOP, SINGLE, ROLL};
		enum TriggerModes {NORMAL, AUTOMATIC};
		enum TriggerSlopes {POSITIVE, NEGATIVE};
		enum Channels {CHANNEL_A, CHANNEL_B, NO_CHANNEL};
		enum Averages {TWO_CERO, TWO_ONE, TWO_TWO, TWO_THREE, TWO_FOUR, TWO_FIVE, TWO_SIX, TWO_SEVEN, TWO_EIGHT, TWO_NINE, TWO_TEN};

	private:
		fix offsetA;
		fix offsetB;
		VerticalScales verticalScaleA;
		VerticalScales verticalScaleB;
		HorizontalScales horizontalScale;
		Couplings couplingA;
		Couplings couplingB;
		bool channelA;
		bool channelB;
		Measures measure;
		std::vector<fix> cursor;
		Mathematics mathematic;
		Modes mode;
		TriggerModes triggerMode;
		Channels triggerChannel;
		TriggerSlopes triggerSlope;
		fix triggerLevel;
		bool triggerNoiseReject;
		bool triggerHighFrequencyReject;
		HorizontalScales triggerHoldOff;
		Averages average;
		int memoryDepth;
		fix delay;
		fix step;
		bool modifiedTrigger;
		bool modifiedSampleRate;
		bool modifiedChannelA;
		bool modifiedChannelB;

	public:
		Configuration(void);
		fix getOffset(Channels channel);
		std::string getOffsetString(Channels channel);
		void setOffset(Channels channel, fix offset);
		VerticalScales getVerticalScale(Channels channel);
		fix getVerticalScaleValue(Channels channel);
		std::string getVerticalScaleString(Channels channel);
		void setVerticalScale(Channels channel, VerticalScales verticalScale);
		HorizontalScales getHorizontalScale(void);
		fix getHorizontalScaleValue(void);
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
		Mathematics getMathematic(void);
		std::string getMathematicString(void);
		Modes getMode(void);
		TriggerModes getTriggerMode(void);
		Channels getTriggerChannel(void);
		TriggerSlopes getTriggerSlope(void);
		fix getTriggerLevel(void);
		bool getTriggerNoiseReject(void);
		bool getTriggerHighFrequencyReject(void);
		HorizontalScales getTriggerHoldOff(void);
		fix getTriggerHoldOffValue(void);
		fix getTriggerHoldOffValue(HorizontalScales THO);
		std::string getModeString(void);
		std::string getRunString(void);
		std::string getSingleString(void);
		std::string getTriggerString(void);
		std::string getTriggerModeString(void);
		std::string getTriggerChannelString(void);
		std::string getTriggerSlopeString(void);
		std::string getTriggerLevelString(void);
		std::string getTriggerNoiseRejectString(void);
		std::string getTriggerHighFrequencyRejectString(void);
		std::string getTriggerHoldOffString(void);
		std::vector<std::string> getAllMeasures(void);
		std::vector<std::string> getAllMathematics(void);
		std::vector<std::string> getAllModes(void);
		std::vector<std::string> getAllTriggerModes(void);
		std::vector<std::string> getAllChannels(void);
		std::vector<std::string> getAllTriggerSlopes(void);
		std::vector<std::string> getAllTriggerNoiseRejects(void);
		std::vector<std::string> getAllTriggerHighFrequencyRejects(void);
		std::vector<std::string> getAllAverages(void);
		void setMeasure(Measures selected);
		void setMathematic(Mathematics selected);
		void setMode(Modes selected);
		void setTriggerMode(TriggerModes mode);
		void setTriggerChannel(Channels channel);
		void setTriggerSlope(TriggerSlopes slope);
		void setTriggerNoiseReject(bool reject);
		void setTriggerHighFrequencyReject(bool reject);
		void setTriggerLevel(fix level);
		void setTriggerHoldOff(fix holdOff);
		std::vector<fix> getCursor(void);
		void setCursor(const std::vector<fix>& cursors);
		int getAverageValue(void);
		void setAverage(Averages avg);
		std::string getAverageString(void);
		std::string voltageToString(fix voltage);
		std::string timeToString(fix time);
		std::string frequencyToString(fix frequency);
		std::string percentageToString(fix percentage);
		std::string degreesToString(fix degrees);
		std::string deciBellToString(fix deciBell);
		std::string boolToString(bool b);
		int getMemoryDepth(void);
		fix getDelay(void);
		std::string getDelayString(void);
		void setDelay(fix d);
		fix getStep(void);
		void setStep(fix s);
		bool getModifiedTrigger(void);
		bool getModifiedSampleRate(void);
		bool getModifiedChannel(Channels channel);
};

#endif

