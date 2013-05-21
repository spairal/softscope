#include <MiniWahoo.hpp>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

MiniWahoo::MiniWahoo(string dir)
{
	stringstream ss;
	stringstream fn;
	
	ss << dir <<"/";
	
	fn = ss;
	fn << "channelAstate";
	channelAFile = open(fn.data(), O_RDWR);
	
	fn = ss;
	fn << "channelBstate";
	channelBFile = open(fn.data(), O_RDWR);
	
	fn = ss;
	fn << "channelAdata";
	channelADataFile = open(fn.data(), O_RDONLY);
	
	fn = ss;
	fn << "channelBdata";
	channelBDataFile = open(fn.data(), O_RDONLY);
	
	fn = ss;
	fn << "trigger";
	triggerFile = open(fn.data(), O_RDWR);

	fn = ss;
	fn << "sampleRate";
	sampleRateFile = open(fn.data(), O_RDWR);

	fn = ss;
	fn << "reset";
	resetFile = open(fn.data(), O_WRONLY);
	
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

char * MiniWahoo::getChannelDataBuffer(Configuration::Channels chann)
{	
	return (chann == Configuration::CHANNEL_A) ? channelAData : channelBData;
}

int MiniWahoo::fetchChannelSamples(Configuration::Channels chann)
{
	int ret = 0;
	int f;
	char * buf;
	
	f = (chann == Configuration::CHANNEL_A) ? channelADataFile : channelBDataFile;
	buf = (chann == Configuration::CHANNEL_A) ? channelAData : channelBData;
	
	ret = read(f, buf, CHANNEL_MEMORY_DEPTH);
	
	return ret;
	
}

bool MiniWahoo::setChannelConf(Configuration::Channels chann, char on,	unsigned char gain, char coupling, unsigned int offset)
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
	
	if(write(f,&channel,sizeof(struct chan)) < 0 )
	{
		ret = false;
	}
		
	return ret;
	
}

bool MiniWahoo::setTriggerConf(Configuration::Channels chann, char slope, char aut, char roll, char noise, char hf, char holdOff, char level)
{
	struct trig trigger;
	bool ret = true;
	
	trigger.channel = (char) chann;
	trigger.slope = slope;
	trigger.aut = aut;
	trigger.roll = roll;
	trigger.noise = noise;
	trigger.hf = hf;
	trigger.holdOff = holdOff;
	trigger.level = level;
	
	if(write(triggerFile,&trigger,sizeof(struct trig)) < 0)
	{
		ret = false;
	}
	
	return ret;
}

bool MiniWahoo::setSampleRate(char sampleRate)
{
	bool ret = true;
	
	if(write(sampleRateFile,&sampleRate,1) < 0)
	{
		ret = false;
	}
	
	return ret;
}

bool MiniWahoo::reset(void)
{
	bool ret = true;
	
	if(write(resetFile,1,1) < 0)
	{
		ret = false;
	}
	
	return ret;
}
