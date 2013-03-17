#include <Touch.hpp>

using namespace std;

Touch::Touch(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples)
{
	buttonPressed = false;
	buttonReleased = false;
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
	if(buttonPressed)
	{
		buttonPressed = false;
		if(!state.getMeasuresButtonActive() && !state.getMathematicsButtonActive() && !state.getModeButtonActive() && !state.getTriggerModeActive() && !state.getTriggerChannelActive() && !state.getTriggerSlopeActive() && !state.getTriggerNoiseRejectActive() && !state.getTriggerHighFrequencyRejectActive() && !state.getAverageActive())
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
				verticalScaleCoordenates[0] = verticalScaleCoordenates[1] - state.getPixelsPerDivision();
				vector<int> horizontalScaleCoordenates = coordenates;
				horizontalScaleCoordenates[2] = horizontalScaleCoordenates[3] - state.getPixelsPerDivision();
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
		if(state.getMeasuresButtonActive() || state.getMathematicsButtonActive() || state.getModeButtonActive() || state.getTriggerModeActive() || state.getTriggerChannelActive() || state.getTriggerSlopeActive() || state.getTriggerNoiseRejectActive() || state.getTriggerHighFrequencyRejectActive() || state.getAverageActive())
		{
			vector<int> measuresMenuCoordenates = state.getMeasuresMenuCoordenates();
			vector<int> mathematicsMenuCoordenates = state.getMathematicsMenuCoordenates();
			vector<int> modeMenuCoordenates = state.getModeMenuCoordenates();
			vector<int> triggerModeCoordenates = modeMenuCoordenates;
			vector<int> triggerChannelCoordenates = modeMenuCoordenates;
			vector<int> triggerSlopeCoordenates = modeMenuCoordenates;
			vector<int> triggerNoiseRejectCoordenates = modeMenuCoordenates;
			vector<int> triggerHighFrequencyRejectCoordenates = modeMenuCoordenates;
			vector<int> averageCoordenates = modeMenuCoordenates;
			measuresMenuCoordenates[3] = measuresMenuCoordenates[2] + (measuresMenuCoordenates[3] - measuresMenuCoordenates[2]) * configuration.getAllMeasures().size();
			mathematicsMenuCoordenates[3] = mathematicsMenuCoordenates[2] + (mathematicsMenuCoordenates[3] - mathematicsMenuCoordenates[2]) * configuration.getAllMathematics().size();
			modeMenuCoordenates[3] = modeMenuCoordenates[2] + (modeMenuCoordenates[3] - modeMenuCoordenates[2]) * configuration.getAllModes().size();
			triggerModeCoordenates[3] = triggerModeCoordenates[2] + (triggerModeCoordenates[3] - triggerModeCoordenates[2]) * configuration.getAllTriggerModes().size();
			triggerChannelCoordenates[3] = triggerChannelCoordenates[2] + (triggerChannelCoordenates[3] - triggerChannelCoordenates[2]) * configuration.getAllChannels().size();
			triggerSlopeCoordenates[3] = triggerSlopeCoordenates[2] + (triggerSlopeCoordenates[3] - triggerSlopeCoordenates[2]) * configuration.getAllTriggerSlopes().size();
			triggerNoiseRejectCoordenates[3] = triggerNoiseRejectCoordenates[2] + (triggerNoiseRejectCoordenates[3] - triggerNoiseRejectCoordenates[2]) * configuration.getAllTriggerNoiseRejects().size();
			triggerHighFrequencyRejectCoordenates[3] = triggerHighFrequencyRejectCoordenates[2] + (triggerHighFrequencyRejectCoordenates[3] - triggerHighFrequencyRejectCoordenates[2]) * configuration.getAllTriggerHighFrequencyRejects().size();
			averageCoordenates[3] = averageCoordenates[2] + (averageCoordenates[3] - averageCoordenates[2]) * configuration.getAllAverages().size();
			if(state.getMeasuresButtonActive() && isIn(x, y, measuresMenuCoordenates))
			{
				vector<int> coordenates = state.getMeasuresMenuCoordenates();
				selectMeasure((Configuration::Measures)(configuration.getAllMeasures().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getMathematicsButtonActive() && isIn(x, y, mathematicsMenuCoordenates))
			{
				vector<int> coordenates = state.getMathematicsMenuCoordenates();
				selectMathematic((Configuration::Mathematics)(configuration.getAllMathematics().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getModeButtonActive() && isIn(x, y, modeMenuCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectMode((Configuration::Modes)(configuration.getAllModes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getTriggerModeActive() && isIn(x, y, triggerModeCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectTriggerMode((Configuration::TriggerModes)(configuration.getAllTriggerModes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getTriggerChannelActive() && isIn(x, y, triggerChannelCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectTriggerChannel((Configuration::Channels)(configuration.getAllChannels().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getTriggerSlopeActive() && isIn(x, y, triggerSlopeCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectTriggerSlope((Configuration::TriggerSlopes)(configuration.getAllTriggerSlopes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(state.getTriggerNoiseRejectActive() && isIn(x, y, triggerNoiseRejectCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectTriggerNoiseReject(((configuration.getAllTriggerModes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1) < 0.5) ? false : true);
			}
			else if(state.getTriggerHighFrequencyRejectActive() && isIn(x, y, triggerHighFrequencyRejectCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectTriggerHighFrequencyReject(((configuration.getAllTriggerModes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1) < 0.5) ? false : true);
			}
			else if(state.getAverageActive() && isIn(x, y, averageCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectAverage((Configuration::Averages)(configuration.getAllAverages().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			else if(!isIn(x, y, state.getMeasuresCoordenates()) && !isIn(x, y, state.getMathematicsCoordenates()) && !isIn(x, y, state.getModeCoordenates()))
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
	vector<double> cursor;
	cursor.push_back((double)(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
	cursor.push_back((double)(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
	cursor.push_back((double)(y - coordenates[2] - 4 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
	cursor.push_back((double)(y - coordenates[2] - 4 * state.getPixelsPerDivision()) / state.getPixelsPerDivision());
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
	vector<double> cursor = configuration.getCursor();
	cursor[1] = (double)(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision();
	cursor[3] = (double)(y - coordenates[2] - 4 * state.getPixelsPerDivision()) / state.getPixelsPerDivision();
	configuration.setCursor(cursor);
}

void Touch::dragOffset(int x, int y)
{
	vector<int> initialOffset = state.getInitialOffset();
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		configuration.setOffset(state.getSelectedChannel(), configuration.getOffset(state.getSelectedChannel()) + configuration.getVerticalScaleValue(state.getSelectedChannel()) * (y - initialOffset[1]) / state.getPixelsPerDivision());
		initialOffset[1] = y;
	}
	configuration.setDelay(configuration.getDelay() + (double)(x - initialOffset[0]) / state.getPixelsPerDivision());
	initialOffset[0] = x;
	state.setInitialOffset(initialOffset);
}

void Touch::dragVerticalScale(int y)
{
	int levels = (y - state.getInitialVerticalScale()) / state.getPixelsPerDivision();
	if((state.getSelectedChannel() != Configuration::NO_CHANNEL) && (levels != 0))
	{
		configuration.setVerticalScale(state.getSelectedChannel(), (Configuration::VerticalScales)(configuration.getVerticalScale(state.getSelectedChannel()) + levels));
		state.setInitialVerticalScale(y);
	}
}

void Touch::dragHorizontalScale(int x)
{
	int levels = (x - state.getInitialHorizontalScale()) / state.getPixelsPerDivision();
	if(levels != 0)
	{
		double oldScale = configuration.getHorizontalScaleValue();
		configuration.setHorizontalScale((Configuration::HorizontalScales)(configuration.getHorizontalScale() + levels));
		double newScale = configuration.getHorizontalScaleValue();
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
	configuration.setTriggerHoldOff(configuration.getHorizontalScaleValue() * ((double)(x - coordenates[0] - 5 * state.getPixelsPerDivision()) / state.getPixelsPerDivision() - configuration.getDelay()));
	configuration.setTriggerLevel(configuration.getVerticalScaleValue(state.getSelectedChannel()) * (y - coordenates[2] - 4 * state.getPixelsPerDivision()) / state.getPixelsPerDivision() - configuration.getOffset(state.getSelectedChannel()));
}

void Touch::resetButtons(void)
{
	state.setMeasuresButtonActive(false);
	state.setMathematicsButtonActive(false);
	state.setModeButtonActive(false);
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

void Touch::selectMode(Configuration::Modes mode)
{
	state.setModeButtonActive(false);
	configuration.setMode(mode);
	switch(mode)
	{
		case Configuration::RUN:
			state.setAverageActive(true);
			configuration.setDelay(0);
			configuration.setStep(1);
			break;
		case Configuration::STOP:
			break;
		case Configuration::SINGLE:
			state.setTriggerModeActive(true);
			configuration.setDelay(0);
			configuration.setStep(1);
			break;
		case Configuration::ROLL:
			configuration.setDelay(5 - configuration.getMemoryDepth() / (2.0 * state.getPixelsPerDivision()));
			configuration.setStep(1);
			break;
	}
}

void Touch::selectTriggerMode(Configuration::TriggerModes mode)
{
	state.setTriggerModeActive(false);
	configuration.setTriggerMode(mode);
	state.setTriggerChannelActive(true);
}

void Touch::selectTriggerChannel(Configuration::Channels channel)
{
	state.setTriggerChannelActive(false);
	configuration.setTriggerChannel(channel);
	state.setTriggerSlopeActive(true);
}

void Touch::selectTriggerSlope(Configuration::TriggerSlopes slope)
{
	state.setTriggerSlopeActive(false);
	configuration.setTriggerSlope(slope);
	state.setTriggerNoiseRejectActive(true);
}

void Touch::selectTriggerNoiseReject(bool reject)
{
	state.setTriggerNoiseRejectActive(false);
	configuration.setTriggerNoiseReject(reject);
	state.setTriggerHighFrequencyRejectActive(true);
}

void Touch::selectTriggerHighFrequencyReject(bool reject)
{
	state.setTriggerHighFrequencyRejectActive(false);
	configuration.setTriggerHighFrequencyReject(reject);
	state.setTriggerLevelActive(true);
}

void Touch::selectAverage(Configuration::Averages average)
{
	state.setAverageActive(false);
	configuration.setAverage(average);
	state.setTriggerModeActive(true);
}

bool Touch::isIn(int x, int y, vector<int> coordenates)
{
	return (x > coordenates[0]) && (x < coordenates[1]) && (y > coordenates[2]) && (y < coordenates[3]);
}

