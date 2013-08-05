#include <Touch.hpp>
#include <fix.hpp>

using namespace std;

Touch::Touch(Configuration& configuration, State& state) : configuration(configuration), state(state), miniInput("/dev/input/event0")
{
	buttonPressed = false;
	buttonReleased = false;
}

void Touch::getInput(void)
{
	if(miniInput.getPressed())
	{
		setButtonPressed(true);
	}
	if(miniInput.getReleased())
	{
		setButtonReleased(true);
	}
	parseScreen(miniInput.getX(), miniInput.getY());
}

void Touch::setButtonPressed(bool pressed)
{
	buttonPressed = pressed;
}

void Touch::setButtonReleased(bool released)
{
	buttonReleased = released;
}

void Touch::parseScreen(int x, int y)
{
	state.setMouseX(x);
	state.setMouseY(y);
	if(buttonPressed)
	{
		buttonPressed = false;
		if(!state.getMeasuresButtonActive() && !state.getMathematicsButtonActive() && !state.getModeButtonActive() && !state.getModeActive() && !state.getTriggerModeActive() && !state.getTriggerChannelActive() && !state.getTriggerSlopeActive() && !state.getTriggerNoiseRejectActive() && !state.getTriggerHighFrequencyRejectActive() && !state.getAverageActive())
		{
			vector<int> coordenates = state.getGridCoordenates();
			if(state.getTriggerLevelActive())
			{
				if(isIn(x, y, coordenates))
				{
					startDragTriggerLevel();
				}
			}
			else if(configuration.getMeasure() == Configuration::CURSORS)
			{
				if(isIn(x, y, coordenates))
				{
					startDragCursors(x, y);
				}
			}
			else
			{
				vector<int> verticalScaleCoordenates = coordenates;
				verticalScaleCoordenates[0] = verticalScaleCoordenates[1] - 2 * state.getPixelsPerDivision();
				vector<int> horizontalScaleCoordenates = coordenates;
				horizontalScaleCoordenates[3] = horizontalScaleCoordenates[2] + 2 * state.getPixelsPerDivision();
				if(isIn(x, y, verticalScaleCoordenates))
				{
					startDragVerticalScale(y);
				}
				else if(isIn(x, y, horizontalScaleCoordenates))
				{
					startDragHorizontalScale(x);
				}
				else if(isIn(x, y, coordenates))
				{
					startDragOffset(x, y);
				}
			}
		}
	}
	if(buttonReleased)
	{
		buttonReleased = false;
		resetDrag();
		if(state.getMeasuresButtonActive() || state.getMathematicsButtonActive() || state.getModeButtonActive() || state.getModeActive() || state.getTriggerModeActive() || state.getTriggerChannelActive() || state.getTriggerSlopeActive() || state.getTriggerNoiseRejectActive() || state.getTriggerHighFrequencyRejectActive() || state.getAverageActive())
		{
			vector<int> coordenates = state.getGridCoordenates();
			coordenates[1] = coordenates[1] - state.getPixelsPerDivision();
			if(isIn(x, y, coordenates))
			{
			   int option = 3 * ((y - coordenates[2]) / (2 * state.getPixelsPerDivision())) + (x - coordenates[0]) / (3 * state.getPixelsPerDivision());
			   if(state.getMeasuresButtonActive() && (option < configuration.getAllMeasures().size()))
			   {
				   selectMeasure((Configuration::Measures)option);
			   }
			   else if(state.getMathematicsButtonActive() && (option < configuration.getAllMathematics().size()))
			   {
				   selectMathematic((Configuration::Mathematics)option);
			   }
			   else if(state.getModeButtonActive() && (option < state.getAllModes().size()))
			   {
				   selectOption(option);
			   }
			   else if(state.getModeActive() && (option < configuration.getAllModes().size()))
			   {
				   selectMode((Configuration::Modes)option);
			   }
			   else if(state.getTriggerModeActive() && (option < configuration.getAllTriggerModes().size()))
			   {
				   selectTriggerMode((Configuration::TriggerModes)option);
			   }
			   else if(state.getTriggerChannelActive() && (option < configuration.getAllChannels().size()))
			   {
				   selectTriggerChannel((Configuration::Channels)option);
			   }
			   else if(state.getTriggerSlopeActive() && (option < configuration.getAllTriggerSlopes().size()))
			   {
				   selectTriggerSlope((Configuration::TriggerSlopes)option);
			   }
			   else if(state.getTriggerNoiseRejectActive() && (option < configuration.getAllTriggerNoiseRejects().size()))
			   {
				   selectTriggerNoiseReject((option < 0.5) ? false : true);
			   }
			   else if(state.getTriggerHighFrequencyRejectActive() && (option < configuration.getAllTriggerHighFrequencyRejects().size()))
			   {
				   selectTriggerHighFrequencyReject((option < 0.5) ? false : true);
			   }
			   else if(state.getAverageActive() && (option < configuration.getAllAverages().size()))
			   {
				   selectAverage((Configuration::Averages)option);
			   }
			   else
			   {
			      resetButtons();
			   }
			}
			else
			{
			   resetButtons();
			}
		}
		else
		{
			if(isIn(x, y, state.getChannelCoordenates(Configuration::CHANNEL_A)))
			{
				pressChannelButton(Configuration::CHANNEL_A);
			}
			if(isIn(x, y, state.getChannelCoordenates(Configuration::CHANNEL_B)))
			{
				pressChannelButton(Configuration::CHANNEL_B);
			}
			if(isIn(x, y, state.getCouplingCoordenates(Configuration::CHANNEL_A)))
			{
				pressCouplingButton(Configuration::CHANNEL_A);
			}
			if(isIn(x, y, state.getCouplingCoordenates(Configuration::CHANNEL_B)))
			{
				pressCouplingButton(Configuration::CHANNEL_B);
			}
		}
		if(isIn(x, y, state.getMeasuresCoordenates()))
		{
			pressMeasuresButton();
		}
		if(isIn(x, y, state.getMathematicsCoordenates()))
		{
			pressMathematicsButton();
		}
		if(isIn(x, y, state.getModeCoordenates()))
		{
			pressModeButton();
		}
	}
	if(state.getCursorDrag())
	{
		dragCursor(x, y);
	}
	if(state.getOffsetDrag())
	{
		dragOffset(x, y);
	}
	if(state.getVerticalScaleDrag())
	{
		dragVerticalScale(y);
	}
	if(state.getHorizontalScaleDrag())
	{
		dragHorizontalScale(x);
	}
	if(state.getTriggerLevelDrag())
	{
		dragTriggerLevel(x, y);
	}
}

void Touch::startDragCursors(int x, int y)
{
	state.setCursorDrag(true);
	vector<int> coordenates = state.getGridCoordenates();
	vector<fix> cursor;
	cursor.push_back(fix(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
	cursor.push_back(fix(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
	cursor.push_back(fix(coordenates[2] + 4 * state.getPixelsPerDivision() - y) / state.getPixelsPerDivision());
	cursor.push_back(fix(coordenates[2] + 4 * state.getPixelsPerDivision() - y) / state.getPixelsPerDivision());
	configuration.setCursor(cursor);
}

void Touch::startDragOffset(int x, int y)
{
	state.setOffsetDrag(true);
	vector<int> offset;
	offset.push_back(x);
	offset.push_back(y);
	state.setInitialOffset(offset);
}

void Touch::startDragVerticalScale(int y)
{
	state.setVerticalScaleDrag(true);
	state.setInitialVerticalScale(y);
}

void Touch::startDragHorizontalScale(int x)
{
	state.setHorizontalScaleDrag(true);
	state.setInitialHorizontalScale(x);
}

void Touch::startDragTriggerLevel(void)
{
	state.setTriggerLevelDrag(true);
}

void Touch::resetDrag(void)
{
	state.setCursorDrag(false);
	state.setOffsetDrag(false);
	state.setVerticalScaleDrag(false);
	state.setHorizontalScaleDrag(false);
	state.setTriggerLevelDrag(false);
	state.setTriggerLevelActive(false);
}

void Touch::dragCursor(int x, int y)
{
	vector<int> coordenates = state.getGridCoordenates();
	vector<fix> cursor = configuration.getCursor();
	cursor[1] = fix(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision();
	cursor[3] = fix(coordenates[2] + 4 * state.getPixelsPerDivision() - y) / state.getPixelsPerDivision();
	configuration.setCursor(cursor);
}

void Touch::dragOffset(int x, int y)
{
	vector<int> initialOffset = state.getInitialOffset();
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		configuration.setOffset(state.getSelectedChannel(), configuration.getOffset(state.getSelectedChannel()) + configuration.getVerticalScaleValue(state.getSelectedChannel()) * (initialOffset[1] - y) / state.getPixelsPerDivision());
		initialOffset[1] = y;
	}
	configuration.setDelay(configuration.getDelay() + fix(x - initialOffset[0]) / state.getPixelsPerDivision());
	initialOffset[0] = x;
	state.setInitialOffset(initialOffset);
}

void Touch::dragVerticalScale(int y)
{
	int levels = (state.getInitialVerticalScale() - y) / state.getPixelsPerDivision();
	if((state.getSelectedChannel() != Configuration::NO_CHANNEL) && (levels != 0))
	{
		configuration.setVerticalScale(state.getSelectedChannel(), (Configuration::VerticalScales)(configuration.getVerticalScale(state.getSelectedChannel()) - levels));
		state.setInitialVerticalScale(y);
	}
}

void Touch::dragHorizontalScale(int x)
{
	int levels = (x - state.getInitialHorizontalScale()) / state.getPixelsPerDivision();
	if(levels != 0)
	{
		fix oldScale = configuration.getHorizontalScaleValue();
		configuration.setHorizontalScale((Configuration::HorizontalScales)(configuration.getHorizontalScale() - levels));
		fix newScale = configuration.getHorizontalScaleValue();
		if(configuration.getMode() == Configuration::STOP)
		{
			configuration.setStep(configuration.getStep() * newScale / oldScale);
		}
		state.setInitialHorizontalScale(x);
	}
}

void Touch::dragTriggerLevel(int x, int y)
{
	vector<int> coordenates = state.getGridCoordenates();
	configuration.setTriggerHoldOff(configuration.getHorizontalScaleValue() * fix(x - coordenates[0]) / state.getPixelsPerDivision());
	configuration.setTriggerLevel(fix(coordenates[2] + 4 * state.getPixelsPerDivision() - y) / state.getPixelsPerDivision() - configuration.getOffset(configuration.getTriggerChannel()) / configuration.getVerticalScaleValue(configuration.getTriggerChannel()));
}

void Touch::resetButtons(void)
{
	state.setMeasuresButtonActive(false);
	state.setMathematicsButtonActive(false);
	state.setModeButtonActive(false);
	state.setModeActive(false);
	state.setTriggerModeActive(false);
	state.setTriggerChannelActive(false);
	state.setTriggerSlopeActive(false);
	state.setTriggerNoiseRejectActive(false);
	state.setTriggerHighFrequencyRejectActive(false);
	state.setTriggerLevelActive(false);
	state.setAverageActive(false);
}

void Touch::pressChannelButton(Configuration::Channels channel)
{
	if(configuration.getChannel(channel))
	{
		if(state.getSelectedChannel() == channel)
		{
			configuration.setChannel(channel, false);
			if(configuration.getChannel(state.getUnselectedChannel()))
			{
				state.setSelectedChannel(state.getUnselectedChannel());
			}
			else
			{
				state.setSelectedChannel(Configuration::NO_CHANNEL);
			}
		}
		else
		{
			state.setSelectedChannel(channel);
		}
	}
	else
	{
		configuration.setChannel(channel, true);
		state.setSelectedChannel(channel);
	}
}

void Touch::pressCouplingButton(Configuration::Channels channel)
{
	switch(configuration.getCoupling(channel))
	{
		case Configuration::AC:
			configuration.setCoupling(channel, Configuration::DC);
			break;
		case Configuration::DC:
			configuration.setCoupling(channel, Configuration::AC);
			break;
	}
}

void Touch::pressMeasuresButton(void)
{
	if(state.getMeasuresButtonActive())
	{
		state.setMeasuresButtonActive(false);
	}
	else
	{
		state.setMeasuresButtonActive(true);
	}
	state.setMathematicsButtonActive(false);
	state.setModeButtonActive(false);
	state.setModeActive(false);
	state.setTriggerModeActive(false);
	state.setTriggerChannelActive(false);
	state.setTriggerSlopeActive(false);
	state.setTriggerNoiseRejectActive(false);
	state.setTriggerHighFrequencyRejectActive(false);
	state.setTriggerLevelActive(false);
	state.setAverageActive(false);
}

void Touch::pressMathematicsButton(void)
{
	if(state.getMathematicsButtonActive())
	{
		state.setMathematicsButtonActive(false);
	}
	else
	{
		state.setMathematicsButtonActive(true);
	}
	state.setMeasuresButtonActive(false);
	state.setModeButtonActive(false);
	state.setModeActive(false);
	state.setTriggerModeActive(false);
	state.setTriggerChannelActive(false);
	state.setTriggerSlopeActive(false);
	state.setTriggerNoiseRejectActive(false);
	state.setTriggerHighFrequencyRejectActive(false);
	state.setTriggerLevelActive(false);
	state.setAverageActive(false);
}

void Touch::pressModeButton(void)
{
	if(state.getModeButtonActive())
	{
		state.setModeButtonActive(false);
	}
	else
	{
		state.setModeButtonActive(true);
	}
	state.setMeasuresButtonActive(false);
	state.setMathematicsButtonActive(false);
	state.setModeActive(false);
	state.setTriggerModeActive(false);
	state.setTriggerChannelActive(false);
	state.setTriggerSlopeActive(false);
	state.setTriggerNoiseRejectActive(false);
	state.setTriggerHighFrequencyRejectActive(false);
	state.setTriggerLevelActive(false);
	state.setAverageActive(false);
}

void Touch::selectMeasure(Configuration::Measures measure)
{
	state.setMeasuresButtonActive(false);
	configuration.setMeasure(measure);
}

void Touch::selectMathematic(Configuration::Mathematics mathematic)
{
	state.setMathematicsButtonActive(false);
	configuration.setMathematic(mathematic);
}

void Touch::selectOption(int option)
{
	state.setModeButtonActive(false);
	switch(option)
	{
		case 0:
			state.setModeActive(true);
			break;
		case 1:
			state.setTriggerModeActive(true);
			break;
		case 2:
			state.setTriggerChannelActive(true);
			break;
		case 3:
			state.setTriggerSlopeActive(true);
			break;
		case 4:
			state.setTriggerNoiseRejectActive(true);
			break;
		case 5:
			state.setTriggerHighFrequencyRejectActive(true);
			break;
		case 6:
			state.setTriggerLevelActive(true);
			break;
		case 7:
			state.setAverageActive(true);
			break;
	}
}

void Touch::selectMode(Configuration::Modes mode)
{
	state.setModeActive(false);
	configuration.setMode(mode);
	switch(mode)
	{
		case Configuration::RUN:
			configuration.setDelay(0);
			configuration.setStep(1);
			break;
		case Configuration::STOP:
			break;
		case Configuration::SINGLE:
			configuration.setDelay(0);
			configuration.setStep(1);
			break;
		case Configuration::ROLL:
			configuration.setDelay(5 - configuration.getMemoryDepth() / (2.0f * state.getPixelsPerDivision()));
			configuration.setStep(1);
			break;
	}
}

void Touch::selectTriggerMode(Configuration::TriggerModes mode)
{
	state.setTriggerModeActive(false);
	configuration.setTriggerMode(mode);
}

void Touch::selectTriggerChannel(Configuration::Channels channel)
{
	state.setTriggerChannelActive(false);
	configuration.setTriggerChannel(channel);
}

void Touch::selectTriggerSlope(Configuration::TriggerSlopes slope)
{
	state.setTriggerSlopeActive(false);
	configuration.setTriggerSlope(slope);
}

void Touch::selectTriggerNoiseReject(bool reject)
{
	state.setTriggerNoiseRejectActive(false);
	configuration.setTriggerNoiseReject(reject);
}

void Touch::selectTriggerHighFrequencyReject(bool reject)
{
	state.setTriggerHighFrequencyRejectActive(false);
	configuration.setTriggerHighFrequencyReject(reject);
}

void Touch::selectAverage(Configuration::Averages average)
{
	state.setAverageActive(false);
	configuration.setAverage(average);
}

bool Touch::isIn(int x, int y, const vector<int>& coordenates)
{
	return (x > coordenates[0]) && (x < coordenates[1]) && (y > coordenates[2]) && (y < coordenates[3]);
}

