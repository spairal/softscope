#include <MiniWahoo.hpp>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

MiniWahoo::MiniWahoo(string dir)
{
   stringstream ssa;
   ssa << dir << "/" << "channelAstate";
   channelAFile = open(ssa.str().data(), O_RDWR);
   stringstream ssb;
   ssb << dir << "/" << "channelBstate";
   channelBFile = open(ssb.str().data(), O_RDWR);
   stringstream ssc;
   ssc << dir << "/" << "channelAdata";
   channelADataFile = open(ssc.str().data(), O_RDONLY);
   stringstream ssd;
   ssd << dir << "/" << "channelBdata";
   channelBDataFile = open(ssd.str().data(), O_RDONLY);
   stringstream sse;
   sse << dir << "/" << "trigger";
   triggerFile = open(sse.str().data(), O_RDWR);
   stringstream ssf;
   ssf << dir << "/" << "sampleRate";
   sampleRateFile = open(ssf.str().data(), O_RDWR);
   stringstream ssg;
   ssg << dir << "/" << "reset";
   resetFile = open(ssg.str().data(), O_WRONLY);
   channelAData = new char[CHANNEL_MEMORY_DEPTH];
   channelBData = new char[CHANNEL_MEMORY_DEPTH];
}

MiniWahoo::~MiniWahoo(void)
{
   close(channelAFile);
   close(channelBFile);
   close(channelADataFile);
   close(channelBDataFile);
   close(triggerFile);
   close(sampleRateFile);
   close(resetFile);
   delete[] channelAData;
   delete[] channelBData;
}

char* MiniWahoo::getChannelDataBuffer(Configuration::Channels chann)
{   
   return (chann == Configuration::CHANNEL_A) ? channelAData : channelBData;
}

int MiniWahoo::fetchChannelSamples(Configuration::Channels chann)
{
   int ret = 0;
   int f;
   char* buf;
   f = (chann == Configuration::CHANNEL_A) ? channelADataFile : channelBDataFile;
   buf = (chann == Configuration::CHANNEL_A) ? channelAData : channelBData;
   ret = read(f, buf, CHANNEL_MEMORY_DEPTH);
   return ret;
}

bool MiniWahoo::setChannelConf(Configuration::Channels chann, char on, unsigned char gain, char coupling, unsigned int offset)
{
   struct chan channel;
   bool ret = true;
   int f;
   f = (chann == Configuration::CHANNEL_A) ? channelAFile : channelBFile;
   channel.id = (char) chann;
   channel.on = on;
   channel.gain = gain;
   channel.coupling = coupling;
   channel.offset = offset;
   if(write(f, &channel, sizeof(struct chan)) < 0)
   {
      ret = false;
   }   
   return ret;
}

bool MiniWahoo::setTriggerConf(Configuration::Channels chann, char slope, char aut, char roll, char noise, char hf, char holdOff, char level)
{
   struct trig trigger;
   bool ret = true;
   trigger.channel = (char)chann;
   trigger.slope = slope;
   trigger.aut = aut;
   trigger.roll = roll;
   trigger.noise = noise;
   trigger.hf = hf;
   trigger.holdOff = holdOff;
   trigger.level = level;
   if(write(triggerFile, &trigger, sizeof(struct trig)) < 0)
   {
      ret = false;
   }
   return ret;
}

bool MiniWahoo::setSampleRate(char sampleRate)
{
   bool ret = true;
   if(write(sampleRateFile, &sampleRate, 1) < 0)
   {
      ret = false;
   }
   return ret;
}

bool MiniWahoo::reset(void)
{
   bool ret = true;
   char a = 1;
   if(write(resetFile, &a, 1) < 0)
   {
      ret = false;
   }
   return ret;
}

