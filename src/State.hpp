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
		unsigned char colorGeneral;
		unsigned char colorA;
		unsigned char colorB;
		unsigned char colorMathematics;
		bool cursorDrag;
		bool offsetDrag;
		bool verticalScaleDrag;
		bool horizontalScaleDrag;
		bool triggerLevelDrag;
		std::vector<int> initialOffset;
		int initialVerticalScale;
		int initialHorizontalScale;
		Configuration::Channels selectedChannel;
		bool measuresButtonActive;
		bool mathematicsButtonActive;
		bool modeButtonActive;
		bool modeActive;
		bool triggerModeActive;
		bool triggerChannelActive;
		bool triggerSlopeActive;
		bool triggerNoiseRejectActive;
		bool triggerHighFrequencyRejectActive;
		bool triggerLevelActive;
		bool averageActive;
		int mouseX;
		int mouseY;

	public:
		State(void);
		std::vector<int> getGridCoordenates(void);
		int getPixelsPerDivision(void);
		std::vector<int> getChannelCoordenates(Configuration::Channels channel);
		std::vector<int> getCouplingCoordenates(Configuration::Channels channel);
		std::vector<int> getMeasuresCoordenates(void);
		std::vector<int> getMathematicsCoordenates(void);
		std::vector<int> getModeCoordenates(void);
		int getColorGeneral(void);
		int getColor(Configuration::Channels channel);
		int getColorMathematics(void);
		bool getCursorDrag(void);
		bool getOffsetDrag(void);
		bool getVerticalScaleDrag(void);
		bool getHorizontalScaleDrag(void);
		bool getTriggerLevelDrag(void);
		void setCursorDrag(bool drag);
		void setOffsetDrag(bool drag);
		void setVerticalScaleDrag(bool drag);
		void setHorizontalScaleDrag(bool drag);
		void setTriggerLevelDrag(bool drag);
		std::vector<int> getInitialOffset(void);
		int getInitialVerticalScale(void);
		int getInitialHorizontalScale(void);
		void setInitialOffset(const std::vector<int>& offset);
		void setInitialVerticalScale(int scale);
		void setInitialHorizontalScale(int scale);
		Configuration::Channels getSelectedChannel(void);
		Configuration::Channels getUnselectedChannel(void);
		void setSelectedChannel(Configuration::Channels channel);
		bool getMeasuresButtonActive(void);
		bool getMathematicsButtonActive(void);
		bool getModeButtonActive(void);
		bool getModeActive(void);
		bool getTriggerModeActive(void);
		bool getTriggerChannelActive(void);
		bool getTriggerSlopeActive(void);
		bool getTriggerNoiseRejectActive(void);
		bool getTriggerHighFrequencyRejectActive(void);
		bool getTriggerLevelActive(void);
		bool getAverageActive(void);
		void setMeasuresButtonActive(bool active);
		void setMathematicsButtonActive(bool active);
		void setModeButtonActive(bool active);
		void setModeActive(bool active);
		void setTriggerModeActive(bool active);
		void setTriggerChannelActive(bool active);
		void setTriggerSlopeActive(bool active);
		void setTriggerNoiseRejectActive(bool active);
		void setTriggerHighFrequencyRejectActive(bool active);
		void setTriggerLevelActive(bool active);
		void setAverageActive(bool active);
		int getMouseX(void);
		int getMouseY(void);
		void setMouseX(int x);
		void setMouseY(int y);
		std::vector<std::string> getAllModes(void);
};

#endif
