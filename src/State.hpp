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
		std::vector<int> measuresMenuCoordenates;
		std::vector<int> mathematicsCoordenates;
		std::vector<int> mathematicsMenuCoordenates;
		std::vector<int> modeCoordenates;
		std::vector<int> modeMenuCoordenates;
		std::vector<float> colorA;
		std::vector<float> colorB;
		std::vector<float> colorMathematics;
		bool offsetDrag;
		bool verticalScaleDrag;
		bool horizontalScaleDrag;
		std::vector<int> initialOffset;
		int initialVerticalScale;
		int initialHorizontalScale;
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
		std::vector<int> getMeasuresMenuCoordenates(void);
		std::vector<int> getMathematicsMenuCoordenates(void);
		std::vector<int> getModeMenuCoordenates(void);
		std::vector<float> getColor(Configuration::Channels channel);
		std::vector<float> getColorMathematics(void);
		bool getOffsetDrag(void);
		bool getVerticalScaleDrag(void);
		bool getHorizontalScaleDrag(void);
		void setOffsetDrag(bool drag);
		void setVerticalScaleDrag(bool drag);
		void setHorizontalScaleDrag(bool drag);
		std::vector<int> getInitialOffset(void);
		int getInitialVerticalScale(void);
		int getInitialHorizontalScale(void);
		void setInitialOffset(std::vector<int> offset);
		void setInitialVerticalScale(int scale);
		void setInitialHorizontalScale(int scale);
		Configuration::Channels getSelectedChannel(void);
		Configuration::Channels getUnselectedChannel(void);
		void setSelectedChannel(Configuration::Channels channel);
		bool getMeasuresButtonActive(void);
		bool getMathematicsButtonActive(void);
		bool getModeButtonActive(void);
		void setMeasuresButtonActive(bool active);
		void setMathematicsButtonActive(bool active);
		void setModeButtonActive(bool active);
};

#endif
