#include <Configuration.hpp>
#include <sstream>
#include <cmath>

using namespace std;

Configuration::Configuration(void)
{
	offsetA = 0;
	offsetB = 0;
	verticalScaleA = ONE_V;
	verticalScaleB = ONE_V;
	delay = 0;
	horizontalScale = ONE_S;
	couplingA = DC;
	couplingB = DC;
	channelA = false;
	channelB = false;
	measure = NOMEASURE;
	verticalCursor[0] = 0;
	verticalCursor[1] = 0;
	horizontalCursor[0] = 0;
	horizontalCursor[1] = 0;
	mathematic = NOMATHEMATIC;
	mode = RUN;
	triggerMode = NORMAL;
	triggerChannel = CHANNEL_A;
	triggerSlope = POSITIVE;
	triggerLevel = 0;
	triggerNoiseReject = false;
	triggerHighFrequencyReject = false;
	triggerHoldOff = 0;
	average = TWO_CERO;
}

double Configuration::getOffset(Channels channel)
{
	double offset;
	switch(channel)
	{
		case CHANNEL_A:
			offset = offsetA;
			break;
		case CHANNEL_B:
			offset = offsetB;
			break;
		case NO_CHANNEL:
			offset = 0;
			break;
	}
	return offset;
}

string Configuration::getOffsetString(Channels channel)
{
	return voltageToString(getOffset(channel));
}

double Configuration::getVerticalScale(Channels channel)
{
	double scale;
	VerticalScales verticalScale;
	switch(channel)
	{
		case CHANNEL_A:
			verticalScale = verticalScaleA;
			break;
		case CHANNEL_B:
			verticalScale = verticalScaleB;
			break;
	}
	switch(verticalScale)
	{
		case TEN_MV:
			scale = 0.01;
			break;
		case TWENTY_MV:
			scale = 0.02;
			break;
		case FIFTY_MV:
			scale = 0.05;
			break;
		case HUNDRED_MV:
			scale = 0.1;
			break;
		case TWOHUNDRED_MV:
			scale = 0.2;
			break;
		case FIVEHUNDRED_MV:
			scale = 0.5;
			break;
		case ONE_V:
			scale = 1.0;
			break;
		case TWO_V:
			scale = 2.0;
			break;
		case FIVE_V:
			scale = 5.0;
			break;
		case TEN_V:
			scale = 10.0;
			break;
	}
	return scale;
}

string Configuration::getVerticalScaleString(Channels channel)
{
	string scale;
	VerticalScales verticalScale;
	switch(channel)
	{
		case CHANNEL_A:
			verticalScale = verticalScaleA;
			break;
		case CHANNEL_B:
			verticalScale = verticalScaleB;
			break;
	}
	switch(verticalScale)
	{
		case TEN_MV:
			scale = "10 mV/div";
			break;
		case TWENTY_MV:
			scale = "20 mV/div";
			break;
		case FIFTY_MV:
			scale = "50 mV/div";
			break;
		case HUNDRED_MV:
			scale = "100 mV/div";
			break;
		case TWOHUNDRED_MV:
			scale = "200 mV/div";
			break;
		case FIVEHUNDRED_MV:
			scale = "500 mV/div";
			break;
		case ONE_V:
			scale = "1 V/div";
			break;
		case TWO_V:
			scale = "2 V/div";
			break;
		case FIVE_V:
			scale = "5 V/div";
			break;
		case TEN_V:
			scale = "10 V/div";
			break;
	}
	return scale;
}

int Configuration::getDelay(void)
{
	return delay;
}

string Configuration::getDelayString(void)
{
	return timeToString(getHorizontalScale() * delay);
}

double Configuration::getHorizontalScale(void)
{
	double scale;
	switch(horizontalScale)
	{
		case TEN_NS:
			scale = 0.00000001;
			break;
		case TWENTY_NS:
			scale = 0.00000002;
			break;
		case FIFTY_NS:
			scale = 0.00000005;
			break;
		case HUNDRED_NS:
			scale = 0.0000001;
			break;
		case TWOHUNDRED_NS:
			scale = 0.0000002;
			break;
		case FIVEHUNDRED_NS:
			scale = 0.0000005;
			break;
		case ONE_US:
			scale = 0.000001;
			break;
		case TWO_US:
			scale = 0.000002;
			break;
		case FIVE_US:
			scale = 0.000005;
			break;
		case TEN_US:
			scale = 0.00001;
			break;
		case TWENTY_US:
			scale = 0.00002;
			break;
		case FIFTY_US:
			scale = 0.00005;
			break;
		case HUNDRED_US:
			scale = 0.0001;
			break;
		case TWOHUNDRED_US:
			scale = 0.0002;
			break;
		case FIVEHUNDRED_US:
			scale = 0.0005;
			break;
		case ONE_MS:
			scale = 0.001;
			break;
		case TWO_MS:
			scale = 0.002;
			break;
		case FIVE_MS:
			scale = 0.005;
			break;
		case TEN_MS:
			scale = 0.01;
			break;
		case TWENTY_MS:
			scale = 0.02;
			break;
		case FIFTY_MS:
			scale = 0.05;
			break;
		case HUNDRED_MS:
			scale = 0.1;
			break;
		case TWOHUNDRED_MS:
			scale = 0.2;
			break;
		case FIVEHUNDRED_MS:
			scale = 0.5;
			break;
		case ONE_S:
			scale = 1.0;
			break;
	}
	return scale;
}

string Configuration::getHorizontalScaleString(void)
{
	string scale;
	switch(horizontalScale)
	{
		case TEN_NS:
			scale = "10 ns/div";
			break;
		case TWENTY_NS:
			scale = "20 ns/div";
			break;
		case FIFTY_NS:
			scale = "50 ns/div";
			break;
		case HUNDRED_NS:
			scale = "100 ns/div";
			break;
		case TWOHUNDRED_NS:
			scale = "200 ns/div";
			break;
		case FIVEHUNDRED_NS:
			scale = "500 ns/div";
			break;
		case ONE_US:
			scale = "1 us/div";
			break;
		case TWO_US:
			scale = "2 us/div";
			break;
		case FIVE_US:
			scale = "5 us/div";
			break;
		case TEN_US:
			scale = "10 us/div";
			break;
		case TWENTY_US:
			scale = "20 us/div";
			break;
		case FIFTY_US:
			scale = "50 us/div";
			break;
		case HUNDRED_US:
			scale = "100 us/div";
			break;
		case TWOHUNDRED_US:
			scale = "200 us/div";
			break;
		case FIVEHUNDRED_US:
			scale = "500 us/div";
			break;
		case ONE_MS:
			scale = "1 ms/div";
			break;
		case TWO_MS:
			scale = "2 ms/div";
			break;
		case FIVE_MS:
			scale = "5 ms/div";
			break;
		case TEN_MS:
			scale = "10 ms/div";
			break;
		case TWENTY_MS:
			scale = "20 ms/div";
			break;
		case FIFTY_MS:
			scale = "50 ms/div";
			break;
		case HUNDRED_MS:
			scale = "100 ms/div";
			break;
		case TWOHUNDRED_MS:
			scale = "200 ms/div";
			break;
		case FIVEHUNDRED_MS:
			scale = "500 ms/div";
			break;
		case ONE_S:
			scale = "1 s/div";
			break;
	}
	return scale;
}

Configuration::Couplings Configuration::getCoupling(Channels channel)
{
	Couplings coupling;
	switch(channel)
	{
		case CHANNEL_A:
			coupling = couplingA;
			break;
		case CHANNEL_B:
			coupling = couplingB;
			break;
	}
	return coupling;
}

string Configuration::getCouplingString(Channels channel)
{
	string couplingString;
	Couplings coupling = getCoupling(channel);
	switch(coupling)
	{
		case AC:
			couplingString = "AC";
			break;
		case DC:
			couplingString = "DC";
			break;
	}
	return couplingString;
}

void Configuration::setCoupling(Channels channel, Couplings coupling)
{
	switch(channel)
	{
		case CHANNEL_A:
			couplingA = coupling;
			break;
		case CHANNEL_B:
			couplingB = coupling;
			break;
	}
}

bool Configuration::getChannel(Channels channel)
{
	bool channelBool;
	switch(channel)
	{
		case CHANNEL_A:
			channelBool = channelA;
			break;
		case CHANNEL_B:
			channelBool = channelB;
			break;
		case NO_CHANNEL:
			channelBool = false;
			break;
	}
	return channelBool;
}

void Configuration::setChannel(Channels channel, bool isActive)
{
	switch(channel)
	{
		case CHANNEL_A:
			channelA = isActive;
			break;
		case CHANNEL_B:
			channelB = isActive;
			break;
	}
}

string Configuration::getMeasureString(Channels channel)
{
	string measureString;
	switch(measure)
	{
		case NOMEASURE:
			measureString = "No Measure";
			break;
		case CURSORS:
			measureString = getCursorsString(channel);
			break;
		case MEAN:
			measureString = "Mean";
			break;
		case PEAK:
			measureString = "Peak";
			break;
		case RMS:
			measureString = "RMS";
			break;
		case FREQUENCY:
			measureString = "Frequency";
			break;
		case PERIOD:
			measureString = "Period";
			break;
		case RISETIME:
			measureString = "Rise Time";
			break;
		case FALLTIME:
			measureString = "Fall Time";
			break;
		case DUTYCYCLE:
			measureString = "Duty Cycle";
			break;
		case PHASE:
			measureString = "Phase";
			break;
		case RATIO:
			measureString = "Ratio";
			break;
	}
	return measureString;
}

string Configuration::getCursorsString(Channels channel)
{
	stringstream ss;
	ss.precision(2);
	ss << "Cursors:" << endl;
	double x1 = getHorizontalScale() * horizontalCursor[0];
	ss << "x1 = " << timeToString(getHorizontalScale() * horizontalCursor[0]) << " ; x2 = " << timeToString(getHorizontalScale() * horizontalCursor[1]) << endl;
	ss << "y1 = " << voltageToString(getVerticalScale(channel) * verticalCursor[0]) << " ; y2 = " << voltageToString(getVerticalScale(channel) * verticalCursor[1]);
	return ss.str();
}

string Configuration::getMathematicString(void)
{
	string mathematicString;
	switch(mathematic)
	{
		case NOMATHEMATIC:
			mathematicString = "No Mathematic";
			break;
		case DIFFERENCE:
			mathematicString = "Difference";
			break;
		case FFT:
			mathematicString = "FFT";
			break;
	}
	return mathematicString;
}

string Configuration::getModeString(void)
{
	string modeString;
	switch(mode)
	{
		case RUN:
			modeString = getRunString();
			break;
		case STOP:
			modeString = "Stop";
			break;
		case SINGLE:
			modeString = getSingleString();
			break;
		case ROLL:
			modeString = "Roll";
			break;
	}
	return modeString;
}

string Configuration::getRunString(void)
{
	stringstream ss;
	ss << "Run:" << endl;
	ss << getTriggerString() << endl;
	ss << getAverageString();
	return ss.str();
}

string Configuration::getSingleString(void)
{
	stringstream ss;
	ss << "Single:" << endl;
	ss << getTriggerString();
	return ss.str();
}

string Configuration::getTriggerString(void)
{
	stringstream ss;
	ss << "Trigger: " << getTriggerModeString() << " " << getTriggerChannelString() << " " << getTriggerSlopeString() << " " << getTriggerLevelString();
	return ss.str();
}

string Configuration::getTriggerModeString(void)
{
	string mode;
	switch(triggerMode)
	{
		case NORMAL:
			mode = "Normal";
			break;
		case AUTOMATIC:
			mode = "Automatic";
			break;
	}
	return mode;
}

string Configuration::getTriggerChannelString(void)
{
	string channel;
	switch(triggerChannel)
	{
		case CHANNEL_A:
			channel = "Channel A";
			break;
		case CHANNEL_B:
			channel = "Channel B";
			break;
		case NO_CHANNEL:
			channel = "";
			break;
	}
	return channel;
}

string Configuration::getTriggerSlopeString(void)
{
	string slope;
	switch(triggerSlope)
	{
		case POSITIVE:
			slope = "Positive";
			break;
		case NEGATIVE:
			slope = "Negative";
			break;
	}
	return slope;
}

string Configuration::getTriggerLevelString(void)
{
	return voltageToString(triggerLevel);
}

int Configuration::getAverage(void)
{
	int averageInt;
	switch(average)
	{
		case TWO_CERO:
			averageInt = 1;
			break;
		case TWO_ONE:
			averageInt = 2;
			break;
		case TWO_TWO:
			averageInt = 4;
			break;
		case TWO_THREE:
			averageInt = 8;
			break;
		case TWO_FOUR:
			averageInt = 16;
			break;
		case TWO_FIVE:
			averageInt = 32;
			break;
		case TWO_SIX:
			averageInt = 64;
			break;
		case TWO_SEVEN:
			averageInt = 128;
			break;
		case TWO_EIGHT:
			averageInt = 256;
			break;
		case TWO_NINE:
			averageInt = 512;
			break;
		case TWO_TEN:
			averageInt = 1024;
			break;
	}
	return averageInt;
}

string Configuration::getAverageString(void)
{
	stringstream ss;
	ss << "Average: " << getAverage();
	return ss.str();
}

string Configuration::voltageToString(double voltage)
{
	stringstream ss;
	ss.precision(2);
	if(abs(voltage) >= 1)
	{
		ss << fixed << voltage << " V";
	}
	else
	{
		ss << fixed << voltage * 1000 << " mV";
	}
	return ss.str();
}

string Configuration::timeToString(double time)
{
	stringstream ss;
	ss.precision(2);
	if(abs(time) >= 1)
	{
		ss << fixed << time << " s";
	}
	else if(abs(time) >= 0.001)
	{
		ss << fixed << time * 1000 << " ms";
	}
	else if(abs(time) >= 0.000001)
	{
		ss << fixed << time * 1000000 << " us";
	}
	else
	{
		ss << fixed << time * 1000000000 << " ns";
	}
	return ss.str();
}
