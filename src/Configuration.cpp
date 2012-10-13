#include <Configuration.hpp>
#include <sstream>
#include <cmath>

using namespace std;

Configuration::Configuration(void)
{
	this->offsetA = 0;
	this->offsetB = 0;
	this->verticalScaleA = Configuration::ONE_V;
	this->verticalScaleB = Configuration::ONE_V;
	this->delay = 0;
	this->horizontalScale = Configuration::ONE_S;
	this->coupling = Configuration::DC;
	this->channelA = true;
	this->channelB = false;
	this->meassure = Configuration::NOMEASSURE;
	this->verticalCursor[0] = 0;
	this->verticalCursor[1] = 0;
	this->horizontalCursor[0] = 0;
	this->horizontalCursor[1] = 0;
	this->mathematic = Configuration::NOMATHEMATIC;
	this->mode = Configuration::RUN;
	this->triggerLevel = 0;
	this->triggerMode = Configuration::NORMAL;
	this->triggerSlope = Configuration::POSITIVE;
	this->triggerChannel = Configuration::CHANNEL_A;
	this->triggerNoiseReject = false;
	this->triggerHighFrequencyReject = false;
	this->triggerHoldOff = 0;
	this->average = Configuration::TWO_CERO;
}

double Configuration::getOffsetA(void)
{
	return this->offsetA;
}

double Configuration::getOffsetB(void)
{
	return this->offsetB;
}

string Configuration::getOffsetString(Channels channel)
{
	double offset;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			offset = this->offsetA;
			break;
		case Configuration::CHANNEL_B:
			offset = this->offsetB;
			break;
	}
	stringstream ss;
	ss.precision(2);
	if(abs(offset) >= 1)
	{
		ss << fixed << offset << " V";
	}
	else
	{
		ss << fixed << offset * 1000 << " mV";
	}
	return ss.str();
}

double Configuration::getVerticalScale(Channels channel)
{
	double scale;
	VerticalScales verticalScale;
	switch(channel)
	{
		case Configuration::CHANNEL_A:
			verticalScale = this->verticalScaleA;
			break;
		case Configuration::CHANNEL_B:
			verticalScale = this->verticalScaleB;
			break;
	}
	switch(verticalScale)
	{
		case Configuration::TEN_MV:
			scale = 0.01;
			break;
		case Configuration::TWENTY_MV:
			scale = 0.02;
			break;
		case Configuration::FIFTY_MV:
			scale = 0.05;
			break;
		case Configuration::HUNDRED_MV:
			scale = 0.1;
			break;
		case Configuration::TWOHUNDRED_MV:
			scale = 0.2;
			break;
		case Configuration::FIVEHUNDRED_MV:
			scale = 0.5;
			break;
		case Configuration::ONE_V:
			scale = 1.0;
			break;
		case Configuration::TWO_V:
			scale = 2.0;
			break;
		case Configuration::FIVE_V:
			scale = 5.0;
			break;
		case Configuration::TEN_V:
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
		case Configuration::CHANNEL_A:
			verticalScale = this->verticalScaleA;
			break;
		case Configuration::CHANNEL_B:
			verticalScale = this->verticalScaleB;
			break;
	}
	switch(verticalScale)
	{
		case Configuration::TEN_MV:
			scale = "10 mV/div";
			break;
		case Configuration::TWENTY_MV:
			scale = "20 mV/div";
			break;
		case Configuration::FIFTY_MV:
			scale = "50 mV/div";
			break;
		case Configuration::HUNDRED_MV:
			scale = "100 mV/div";
			break;
		case Configuration::TWOHUNDRED_MV:
			scale = "200 mV/div";
			break;
		case Configuration::FIVEHUNDRED_MV:
			scale = "500 mV/div";
			break;
		case Configuration::ONE_V:
			scale = "1 V/div";
			break;
		case Configuration::TWO_V:
			scale = "2 V/div";
			break;
		case Configuration::FIVE_V:
			scale = "5 V/div";
			break;
		case Configuration::TEN_V:
			scale = "10 V/div";
			break;
	}
	return scale;
}

int Configuration::getDelay(void)
{
	return this->delay;
}

string Configuration::getDelayString(int pixelsPerDivision)
{
	double delay = this->getHorizontalScale() * ((double)this->delay) / ((double)pixelsPerDivision);
	stringstream ss;
	ss.precision(2);
	if(abs(delay) >= 1)
	{
		ss << fixed << delay << " s";
	}
	else if(abs(delay) >= 0.001)
	{
		ss << fixed << delay * 1000 << " ms";
	}
	else if(abs(delay) >= 0.000001)
	{
		ss << fixed << delay * 1000000 << " us";
	}
	else
	{
		ss << fixed << delay * 1000000000 << " ns";
	}
	return ss.str();
}

double Configuration::getHorizontalScale(void)
{
	double scale;
	switch(this->horizontalScale)
	{
		case Configuration::TEN_NS:
			scale = 0.00000001;
			break;
		case Configuration::TWENTY_NS:
			scale = 0.00000002;
			break;
		case Configuration::FIFTY_NS:
			scale = 0.00000005;
			break;
		case Configuration::HUNDRED_NS:
			scale = 0.0000001;
			break;
		case Configuration::TWOHUNDRED_NS:
			scale = 0.0000002;
			break;
		case Configuration::FIVEHUNDRED_NS:
			scale = 0.0000005;
			break;
		case Configuration::ONE_US:
			scale = 0.000001;
			break;
		case Configuration::TWO_US:
			scale = 0.000002;
			break;
		case Configuration::FIVE_US:
			scale = 0.000005;
			break;
		case Configuration::TEN_US:
			scale = 0.00001;
			break;
		case Configuration::TWENTY_US:
			scale = 0.00002;
			break;
		case Configuration::FIFTY_US:
			scale = 0.00005;
			break;
		case Configuration::HUNDRED_US:
			scale = 0.0001;
			break;
		case Configuration::TWOHUNDRED_US:
			scale = 0.0002;
			break;
		case Configuration::FIVEHUNDRED_US:
			scale = 0.0005;
			break;
		case Configuration::ONE_MS:
			scale = 0.001;
			break;
		case Configuration::TWO_MS:
			scale = 0.002;
			break;
		case Configuration::FIVE_MS:
			scale = 0.005;
			break;
		case Configuration::TEN_MS:
			scale = 0.01;
			break;
		case Configuration::TWENTY_MS:
			scale = 0.02;
			break;
		case Configuration::FIFTY_MS:
			scale = 0.05;
			break;
		case Configuration::HUNDRED_MS:
			scale = 0.1;
			break;
		case Configuration::TWOHUNDRED_MS:
			scale = 0.2;
			break;
		case Configuration::FIVEHUNDRED_MS:
			scale = 0.5;
			break;
		case Configuration::ONE_S:
			scale = 1.0;
			break;
	}
	return scale;
}

string Configuration::getHorizontalScaleString(void)
{
	string scale;
	switch(this->horizontalScale)
	{
		case Configuration::TEN_NS:
			scale = "10 ns/div";
			break;
		case Configuration::TWENTY_NS:
			scale = "20 ns/div";
			break;
		case Configuration::FIFTY_NS:
			scale = "50 ns/div";
			break;
		case Configuration::HUNDRED_NS:
			scale = "100 ns/div";
			break;
		case Configuration::TWOHUNDRED_NS:
			scale = "200 ns/div";
			break;
		case Configuration::FIVEHUNDRED_NS:
			scale = "500 ns/div";
			break;
		case Configuration::ONE_US:
			scale = "1 us/div";
			break;
		case Configuration::TWO_US:
			scale = "2 us/div";
			break;
		case Configuration::FIVE_US:
			scale = "5 us/div";
			break;
		case Configuration::TEN_US:
			scale = "10 us/div";
			break;
		case Configuration::TWENTY_US:
			scale = "20 us/div";
			break;
		case Configuration::FIFTY_US:
			scale = "50 us/div";
			break;
		case Configuration::HUNDRED_US:
			scale = "100 us/div";
			break;
		case Configuration::TWOHUNDRED_US:
			scale = "200 us/div";
			break;
		case Configuration::FIVEHUNDRED_US:
			scale = "500 us/div";
			break;
		case Configuration::ONE_MS:
			scale = "1 ms/div";
			break;
		case Configuration::TWO_MS:
			scale = "2 ms/div";
			break;
		case Configuration::FIVE_MS:
			scale = "5 ms/div";
			break;
		case Configuration::TEN_MS:
			scale = "10 ms/div";
			break;
		case Configuration::TWENTY_MS:
			scale = "20 ms/div";
			break;
		case Configuration::FIFTY_MS:
			scale = "50 ms/div";
			break;
		case Configuration::HUNDRED_MS:
			scale = "100 ms/div";
			break;
		case Configuration::TWOHUNDRED_MS:
			scale = "200 ms/div";
			break;
		case Configuration::FIVEHUNDRED_MS:
			scale = "500 ms/div";
			break;
		case Configuration::ONE_S:
			scale = "1 s/div";
			break;
	}
	return scale;
}

bool Configuration::getChannelA(void)
{
	return this->channelA;
}

bool Configuration::getChannelB(void)
{
	return this->channelB;
}
