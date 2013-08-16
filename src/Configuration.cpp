#include <Configuration.hpp>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;

Configuration::Configuration(void)
{
   ifstream aFile("offsetA.txt");
   if(aFile.is_open())
   {
      float at;
      float bt;
      aFile >> at >> bt;
      offsetA = - bt / at;
      offsetAa = at;
      offsetAb = bt;
      aFile.close();
   }
   ifstream bFile("offsetB.txt");
   if(bFile.is_open())
   {
      float at;
      float bt;
      bFile >> at >> bt;
      offsetB = - bt / at;
      offsetBa = at;
      offsetBb = bt;
      bFile.close();
   }
   verticalScaleA = ONE_V;
   verticalScaleB = ONE_V;
   horizontalScale = HUNDRED_MS;
   couplingA = DC;
   couplingB = DC;
   channelA = false;
   channelB = false;
   measure = NOMEASURE;
   cursor.push_back(0);
   cursor.push_back(0);
   cursor.push_back(0);
   cursor.push_back(0);
   mathematic = NOMATHEMATIC;
   mode = RUN;
   triggerMode = NORMAL;
   triggerChannel = CHANNEL_A;
   triggerSlope = POSITIVE;
   triggerLevel = 0;
   triggerNoiseReject = false;
   triggerHighFrequencyReject = false;
   triggerHoldOff = ONE_US;
   average = TWO_CERO;
   memoryDepth = 1024;
   delay = 0;
   step = 1;
   modifiedTrigger = true;
   modifiedSampleRate = true;
   modifiedChannelA = true;
   modifiedChannelB = true;
}

fix Configuration::getOffset(Channels channel)
{
   fix offset;
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

fix Configuration::getOffsetValue(Channels channel)
{
	fix offset = getOffset(channel);
	fix a;
   fix b;
   switch(channel)
   {
      case CHANNEL_A:
         a = offsetAa;
         b = offsetAb;
         break;
      case CHANNEL_B:
         a = offsetBa;
         b = offsetBb;
         break;
   }
   offset *= a;
   offset += b;
   return offset;
}

string Configuration::getOffsetString(Channels channel)
{
   return voltageToString(getOffsetValue(channel));
}

void Configuration::setOffset(Channels channel, fix offset)
{
   fix a;
   fix b;
   switch(channel)
   {
      case CHANNEL_A:
         a = offsetAa;
         b = offsetAb;
         break;
      case CHANNEL_B:
         a = offsetBa;
         b = offsetBb;
         break;
   }
   offset -= b;
   offset /= a;
   if(offset < -40)
   {
      offset = -40;
   }
   else if(offset > 40)
   {
      offset = 40;
   }
   switch(channel)
   {
      case CHANNEL_A:
         offsetA = offset;
         modifiedChannelA = true;
         break;
      case CHANNEL_B:
         offsetB = offset;
         modifiedChannelB = true;
         break;
   }
}

Configuration::VerticalScales Configuration::getVerticalScale(Channels channel)
{
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
   return verticalScale;
}

fix Configuration::getVerticalScaleValue(Channels channel)
{
   fix scale = 1;
   VerticalScales verticalScale = getVerticalScale(channel);
   switch(verticalScale)
   {
      case TEN_MV:
         scale = 0.01f;
         break;
      case TWENTY_MV:
         scale = 0.02f;
         break;
      case FIFTY_MV:
         scale = 0.05f;
         break;
      case HUNDRED_MV:
         scale = 0.1f;
         break;
      case TWOHUNDRED_MV:
         scale = 0.2f;
         break;
      case FIVEHUNDRED_MV:
         scale = 0.5f;
         break;
      case ONE_V:
         scale = 1.0f;
         break;
      case TWO_V:
         scale = 2.0f;
         break;
      case FIVE_V:
         scale = 5.0f;
         break;
      case TEN_V:
         scale = 10.0f;
         break;
   }
   return scale;
}

string Configuration::getVerticalScaleString(Channels channel)
{
   string scale;
   VerticalScales verticalScale = getVerticalScale(channel);
   switch(verticalScale)
   {
      case TEN_MV:
         scale = "10mV/div";
         break;
      case TWENTY_MV:
         scale = "20mV/div";
         break;
      case FIFTY_MV:
         scale = "50mV/div";
         break;
      case HUNDRED_MV:
         scale = "100mV/div";
         break;
      case TWOHUNDRED_MV:
         scale = "200mV/div";
         break;
      case FIVEHUNDRED_MV:
         scale = "500mV/div";
         break;
      case ONE_V:
         scale = "1V/div";
         break;
      case TWO_V:
         scale = "2V/div";
         break;
      case FIVE_V:
         scale = "5V/div";
         break;
      case TEN_V:
         scale = "10V/div";
         break;
   }
   return scale;
}

void Configuration::setVerticalScale(Channels channel, VerticalScales verticalScale)
{
   if(verticalScale < TEN_MV)
   {
      verticalScale = TEN_MV;
   }
   if(verticalScale > TEN_V)
   {
      verticalScale = TEN_V;
   }
   switch(channel)
   {
      case CHANNEL_A:
         verticalScaleA = verticalScale;
         modifiedChannelA = true;
         break;
      case CHANNEL_B:
         verticalScaleB = verticalScale;
         modifiedChannelB = true;
         break;
   }
}

Configuration::HorizontalScales Configuration::getHorizontalScale(void)
{
   return horizontalScale;
}

fix Configuration::getHorizontalScaleValue(void)
{
   fix scale;
   switch(horizontalScale)
   {
      case ONE_US:
         scale = 0.000001f;
         break;
      case TWO_US:
         scale = 0.000002f;
         break;
      case FIVE_US:
         scale = 0.000005f;
         break;
      case TEN_US:
         scale = 0.00001f;
         break;
      case TWENTY_US:
         scale = 0.00002f;
         break;
      case FIFTY_US:
         scale = 0.00005f;
         break;
      case HUNDRED_US:
         scale = 0.0001f;
         break;
      case TWOHUNDRED_US:
         scale = 0.0002f;
         break;
      case FIVEHUNDRED_US:
         scale = 0.0005f;
         break;
      case ONE_MS:
         scale = 0.001f;
         break;
      case TWO_MS:
         scale = 0.002f;
         break;
      case FIVE_MS:
         scale = 0.005f;
         break;
      case TEN_MS:
         scale = 0.01f;
         break;
      case TWENTY_MS:
         scale = 0.02f;
         break;
      case FIFTY_MS:
         scale = 0.05f;
         break;
      case HUNDRED_MS:
         scale = 0.1f;
         break;
      case TWOHUNDRED_MS:
         scale = 0.2f;
         break;
      case FIVEHUNDRED_MS:
         scale = 0.5f;
         break;
      case ONE_S:
         scale = 1;
         break;
   }
   return scale;
}

string Configuration::getHorizontalScaleString(void)
{
   string scale;
   switch(horizontalScale)
   {
      case ONE_US:
         scale = "1us/div";
         break;
      case TWO_US:
         scale = "2us/div";
         break;
      case FIVE_US:
         scale = "5us/div";
         break;
      case TEN_US:
         scale = "10us/div";
         break;
      case TWENTY_US:
         scale = "20us/div";
         break;
      case FIFTY_US:
         scale = "50us/div";
         break;
      case HUNDRED_US:
         scale = "100us/div";
         break;
      case TWOHUNDRED_US:
         scale = "200us/div";
         break;
      case FIVEHUNDRED_US:
         scale = "500us/div";
         break;
      case ONE_MS:
         scale = "1ms/div";
         break;
      case TWO_MS:
         scale = "2ms/div";
         break;
      case FIVE_MS:
         scale = "5ms/div";
         break;
      case TEN_MS:
         scale = "10ms/div";
         break;
      case TWENTY_MS:
         scale = "20ms/div";
         break;
      case FIFTY_MS:
         scale = "50ms/div";
         break;
      case HUNDRED_MS:
         scale = "100ms/div";
         break;
      case TWOHUNDRED_MS:
         scale = "200ms/div";
         break;
      case FIVEHUNDRED_MS:
         scale = "500ms/div";
         break;
      case ONE_S:
         scale = "1s/div";
         break;
   }
   return scale;
}

void Configuration::setHorizontalScale(HorizontalScales scale)
{
   HorizontalScales minScale;
   if(mode == ROLL)
   {
      minScale = HUNDRED_MS;
   }
   else
   {
      minScale = ONE_US;
   }
   if(scale < minScale)
   {
      scale = minScale;
   }
   if(scale > ONE_S)
   {
      scale = ONE_S;
   }
   horizontalScale = scale;
   modifiedSampleRate = true;
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
         modifiedChannelA = true;
         break;
      case CHANNEL_B:
         couplingB = coupling;
         modifiedChannelB = true;
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
         modifiedChannelA = true;
         break;
      case CHANNEL_B:
         channelB = isActive;
         modifiedChannelB = true;
         break;
   }
}

Configuration::Measures Configuration::getMeasure(void)
{
   return measure;
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
   ss << "Cursors:" << endl;
   ss << "x1 = " << timeToString(getHorizontalScaleValue() * (cursor[0] - delay)) << endl;
   ss << "x2 = " << timeToString(getHorizontalScaleValue() * (cursor[1] - delay)) << endl;
   ss << "y1 = " << voltageToString(getVerticalScaleValue(channel) * cursor[2] - getOffsetValue(channel)) << endl;
   ss << "y2 = " << voltageToString(getVerticalScaleValue(channel) * cursor[3] - getOffsetValue(channel));
   return ss.str();
}

Configuration::Mathematics Configuration::getMathematic(void)
{
   return mathematic;
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

Configuration::Modes Configuration::getMode(void)
{
   return mode;
}

Configuration::TriggerModes Configuration::getTriggerMode(void)
{
   return triggerMode;
}

Configuration::Channels Configuration::getTriggerChannel(void)
{
   return triggerChannel;
}

Configuration::TriggerSlopes Configuration::getTriggerSlope(void)
{
   return triggerSlope;
}

fix Configuration::getTriggerLevel(void)
{
   return triggerLevel;
}

bool Configuration::getTriggerNoiseReject(void)
{
   return triggerNoiseReject;
}

bool Configuration::getTriggerHighFrequencyReject(void)
{
   return triggerHighFrequencyReject;
}

Configuration::HorizontalScales Configuration::getTriggerHoldOff(void)
{
   return triggerHoldOff;
}

fix Configuration::getTriggerHoldOffValue(void)
{
   return getTriggerHoldOffValue(triggerHoldOff);
}

fix Configuration::getTriggerHoldOffValue(HorizontalScales THO)
{
   fix holdOff;
   switch(THO)
   {
      case ONE_US:
         holdOff = 0.00001f;
         break;
      case TWO_US:
         holdOff = 0.00002f;
         break;
      case FIVE_US:
         holdOff = 0.00005f;
         break;
      case TEN_US:
         holdOff = 0.0001f;
         break;
      case TWENTY_US:
         holdOff = 0.0002f;
         break;
      case FIFTY_US:
         holdOff = 0.0005f;
         break;
      case HUNDRED_US:
         holdOff = 0.001f;
         break;
      case TWOHUNDRED_US:
         holdOff = 0.002f;
         break;
      case FIVEHUNDRED_US:
         holdOff = 0.005f;
         break;
      case ONE_MS:
         holdOff = 0.01f;
         break;
      case TWO_MS:
         holdOff = 0.02f;
         break;
      case FIVE_MS:
         holdOff = 0.05f;
         break;
      case TEN_MS:
         holdOff = 0.1f;
         break;
      case TWENTY_MS:
         holdOff = 0.2f;
         break;
      case FIFTY_MS:
         holdOff = 0.5f;
         break;
      case HUNDRED_MS:
         holdOff = 1;
         break;
      case TWOHUNDRED_MS:
         holdOff = 2;
         break;
      case FIVEHUNDRED_MS:
         holdOff = 5;
         break;
      case ONE_S:
         holdOff = 10;
         break;
   }
   return holdOff;
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
   ss << "Trigger: " << getTriggerModeString() << endl;
   ss << getTriggerChannelString() << " " << getTriggerSlopeString() << endl;
   ss << getTriggerLevelString() << " " << getTriggerHoldOffString() << endl;
   ss << "NR:" << getTriggerNoiseRejectString() << " HFR:" << getTriggerHighFrequencyRejectString();
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
   return voltageToString(getVerticalScaleValue(triggerChannel) * triggerLevel - getOffsetValue(triggerChannel));
}

string Configuration::getTriggerNoiseRejectString(void)
{
   return boolToString(triggerNoiseReject);
}

string Configuration::getTriggerHighFrequencyRejectString(void)
{
   return boolToString(triggerHighFrequencyReject);
}

string Configuration::getTriggerHoldOffString(void)
{
   return timeToString(getTriggerHoldOffValue());
}

vector<string> Configuration::getAllMeasures(void)
{
   vector<string> allMeasures;
   allMeasures.push_back("No Measure");
   allMeasures.push_back("Cursors");
   allMeasures.push_back("Mean");
   allMeasures.push_back("Peak");
   allMeasures.push_back("RMS");
   allMeasures.push_back("Frequency");
   allMeasures.push_back("Period");
   allMeasures.push_back("Rise Time");
   allMeasures.push_back("Fall Time");
   allMeasures.push_back("Duty Cycle");
   allMeasures.push_back("Phase");
   allMeasures.push_back("Ratio");
   return allMeasures;
}

vector<string> Configuration::getAllMathematics(void)
{
   vector<string> allMathematics;
   allMathematics.push_back("No Mathematic");
   allMathematics.push_back("Difference");
   allMathematics.push_back("FFT");
   return allMathematics;
}

vector<string> Configuration::getAllModes(void)
{
   vector<string> allModes;
   allModes.push_back("Run");
   allModes.push_back("Stop");
   allModes.push_back("Single");
   allModes.push_back("Roll");
   return allModes;
}

vector<string> Configuration::getAllTriggerModes(void)
{
   vector<string> allModes;
   allModes.push_back("Normal");
   allModes.push_back("Automatic");
   return allModes;
}

vector<string> Configuration::getAllChannels(void)
{
   vector<string> allChannels;
   allChannels.push_back("Channel A");
   allChannels.push_back("Channel B");
   return allChannels;
}

vector<string> Configuration::getAllTriggerSlopes(void)
{
   vector<string> allSlopes;
   allSlopes.push_back("Positive");
   allSlopes.push_back("Negative");
   return allSlopes;
}

vector<string> Configuration::getAllTriggerNoiseRejects(void)
{
   vector<string> allNoiseReject;
   allNoiseReject.push_back("Off");
   allNoiseReject.push_back("On");
   return allNoiseReject;
}

vector<string> Configuration::getAllTriggerHighFrequencyRejects(void)
{
   vector<string> allHighFrequencyReject;
   allHighFrequencyReject.push_back("Off");
   allHighFrequencyReject.push_back("On");
   return allHighFrequencyReject;
}

vector<string> Configuration::getAllAverages(void)
{
   vector<string> allAverages;
   allAverages.push_back("1");
   allAverages.push_back("2");
   allAverages.push_back("4");
   allAverages.push_back("8");
   allAverages.push_back("16");
   allAverages.push_back("32");
   allAverages.push_back("64");
   allAverages.push_back("128");
   allAverages.push_back("256");
   allAverages.push_back("512");
   allAverages.push_back("1024");
   return allAverages;
}

void Configuration::setMeasure(Measures selected)
{
   measure = selected;
}

void Configuration::setMathematic(Mathematics selected)
{
   mathematic = selected;
}

void Configuration::setMode(Modes selected)
{
   mode = selected;
   modifiedTrigger = true;
   setHorizontalScale(horizontalScale);
}

void Configuration::setTriggerMode(TriggerModes mode)
{
   triggerMode = mode;
   modifiedTrigger = true;
}

void Configuration::setTriggerChannel(Channels channel)
{
   triggerChannel = channel;
   modifiedTrigger = true;
}

void Configuration::setTriggerSlope(TriggerSlopes slope)
{
   triggerSlope = slope;
   modifiedTrigger = true;
}

void Configuration::setTriggerNoiseReject(bool reject)
{
   triggerNoiseReject = reject;
   modifiedTrigger = true;
}

void Configuration::setTriggerHighFrequencyReject(bool reject)
{
   triggerHighFrequencyReject = reject;
   modifiedTrigger = true;
}

void Configuration::setTriggerLevel(fix level)
{
   if(level < -4)
   {
      level = -4;
   }
   else if(level > 4)
   {
      level = 4;
   }
   triggerLevel = level;
   modifiedTrigger = true;
}

void Configuration::setTriggerHoldOff(fix holdOff)
{
   HorizontalScales THO = ONE_US;
   fix error = (holdOff - getTriggerHoldOffValue(ONE_US)).abs();
   for(int i = TWO_US; i < ONE_S; i++)
   {
      if((holdOff - getTriggerHoldOffValue((HorizontalScales) i)).abs() < error)
      {
         THO = (HorizontalScales) i;
         error = (holdOff - getTriggerHoldOffValue((HorizontalScales) i)).abs();
      }
   }
   triggerHoldOff = THO;
   modifiedTrigger = true;
}

vector<fix> Configuration::getCursor(void)
{
   return cursor;
}

void Configuration::setCursor(const vector<fix>& cursors)
{
   cursor = cursors;
}

int Configuration::getAverageValue(void)
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

void Configuration::setAverage(Averages avg)
{
   average = avg;
}

string Configuration::getAverageString(void)
{
   stringstream ss;
   ss << "Average: " << getAverageValue();
   return ss.str();
}

string Configuration::voltageToString(fix voltage)
{
   stringstream ss;
   ss.precision(2);
   if(voltage.abs() >= 1)
   {
      ss << fixed << (float)voltage << "V";
   }
   else
   {
      ss << fixed << (float)voltage * 1000 << "mV";
   }
   return ss.str();
}

string Configuration::timeToString(fix time)
{
   stringstream ss;
   ss.precision(2);
   if(time.abs() >= 1)
   {
      ss << fixed << (float)time << "s";
   }
   else if(time.abs() >= 0.001f)
   {
      ss << fixed << (float)(time * 1000) << "ms";
   }
   else
   {
      ss << fixed << (float)(time * 1000000) << "us";
   }
   return ss.str();
}

string Configuration::frequencyToString(fix frequency)
{
   stringstream ss;
   ss.precision(2);
   if(frequency.abs() >= 1000000)
   {
      ss << fixed << (float)(frequency / 1000000) << "MHz";
   }
   else if(frequency.abs() >= 1000)
   {
      ss << fixed << (float)(frequency / 1000) << "kHz";
   }
   else if(frequency.abs() >= 1)
   {
      ss << fixed << (float)frequency << "Hz";
   }
   else
   {
      ss << fixed << (float)(frequency * 1000) << "mHz";
   }
   return ss.str();
}

string Configuration::percentageToString(fix percentage)
{
   stringstream ss;
   ss.precision(2);
   ss << fixed << (float)percentage * 100 << "%";
   return ss.str();
}

string Configuration::degreesToString(fix degrees)
{
   stringstream ss;
   ss.precision(2);
   ss << fixed << (float)degrees << "deg";
   return ss.str();
}

string Configuration::deciBellToString(fix deciBell)
{
   stringstream ss;
   ss.precision(2);
   ss << fixed << (float)deciBell << " dB";
   return ss.str();
}

string Configuration::boolToString(bool b)
{
   string boolean;
   if(b)
   {
      boolean = "On";
   }
   else
   {
      boolean = "Off";
   }
   return boolean;
}

int Configuration::getMemoryDepth(void)
{
   return memoryDepth;
}

fix Configuration::getDelay(void)
{
   return delay;
}

string Configuration::getDelayString(void)
{
   return timeToString(getHorizontalScaleValue() * delay);
}

void Configuration::setDelay(fix d)
{
   delay = d;
}

fix Configuration::getStep(void)
{
   return step;
}

void Configuration::setStep(fix s)
{
   step = s;
}

bool Configuration::getModifiedTrigger(void)
{
   bool tmp = modifiedTrigger;
   modifiedTrigger = false;
   return tmp;
}

bool Configuration::getModifiedSampleRate(void)
{
   bool tmp = modifiedSampleRate;
   modifiedSampleRate = false;
   return tmp;
}

bool Configuration::getModifiedChannel(Channels channel)
{
   bool tmp;
   switch(channel)
   {
      case CHANNEL_A:
         tmp = modifiedChannelA;
         modifiedChannelA = false;
         break;
      case CHANNEL_B:
         tmp = modifiedChannelB;
         modifiedChannelB = false;
         break;
   }
   return tmp;
}

