#ifndef STATE_HPP
#define STATE_HPP

#include <Configuration.hpp>
#include <vector>

class State
{
	private:
		std::vector<int> gridCoordenates;
		std::vector<int> channelCoordenatesA;
		std::vector<int> channelCoordenatesB;
		std::vector<int> couplingCoordenatesA;
		std::vector<int> couplingCoordenatesB;
		std::vector<int> measuresCoordenates;
		std::vector<int> mathematicsCoordenates;
		std::vector<int> modeCoordenates;
		std::vector<float> colorA;
		std::vector<float> colorB;
		Configuration::Channels selectedChannel;
		bool measuresButtonActive;
		bool mathematicsButtonActive;
		bool modeButtonActive;

	public:
		State(void);
		std::vector<int> getGridCoordenates(void);
		int getPixelsPerDivision(void);
		std::vector<int> getChannelCoordenates(Configuration::Channels channel);
		std::vector<int> getCouplingCoordenates(Configuration::Channels channel);
		std::vector<int> getMeasuresCoordenates(void);
		std::vector<int> getMathematicsCoordenates(void);
		std::vector<int> getModeCoordenates(void);
		std::vector<float> getColor(Configuration::Channels channel);
		Configuration::Channels getSelectedChannel(void);
		Configuration::Channels getUnselectedChannel(void);
		void setSelectedChannel(Configuration::Channels channel);
		bool getMeasuresButtonActive(void);
		bool getMathematicsButtonActive(void);
		bool getModeButtonActive(void);
};

#endif
