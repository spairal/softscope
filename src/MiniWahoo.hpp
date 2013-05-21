#ifndef MINIWAHOO_HPP
#define MINIWAHOO_HPP

#include <Configuration.hpp>
#include <wahoo.h>
#include <string>

class MiniWahoo
{
	private:
		int channelAFile;
		int channelBFile;
		int channelADataFile;
		int channelBDataFile;
		int triggerFile;
		int sampleRateFile;
		int resetFile;
		char *channelAData;
		char *channelBData;
		
	public:
		MiniWahoo(std::string dir);
		~MiniWahoo(void);
		char *getChannelDataBuffer(Configuration::Channels chann);
		int fetchChannelSamples(Configuration::Channels chann);
		bool setChannelConf(Configuration::Channels chann, char on,	unsigned char gain, char coupling, unsigned int offset);
		bool setTriggerConf(Configuration::Channels chann, char slope, char aut, char roll, char noise, char hf, char holdOff, char level);
		bool setSampleRate(char sampleRate);
		bool reset(void);
};

#endif // MINIWAHOO_HPP

