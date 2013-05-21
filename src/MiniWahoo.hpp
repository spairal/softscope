#include "wahoo.h"
#include <Configuration.hpp>
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
		char *getChannelDataBuffer(Configuration::Channels chan);
		int fetchChannelSamples(Configuration::Channels chan);
		bool setChannelConf(Configuration::Channels chan, char on,	unsigned char gain, char coupling, unsigned int offset);
		bool setTriggerConf(Configuration::Channels chan, char slope, char aut, char roll, char noise, char hf, char holdOff, char level);
		bool setSampleRate(char sampleRate);
		bool reset(void);
}
