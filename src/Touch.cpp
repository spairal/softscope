#include <Touch.hpp>

using namespace std;

Touch::Touch(Configuration& configuration, State& state) : configuration(configuration), state(state)
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
		if(!state.getMeasuresButtonActive() && !state.getMathematicsButtonActive() && !state.getModeButtonActive())
		{
			vector<int> coordenates = state.getGridCoordenates();
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
	if(buttonReleased)
	{
		buttonReleased = false;
		resetDrag();
		if(state.getMeasuresButtonActive() || state.getMathematicsButtonActive() || state.getModeButtonActive())
		{
			vector<int> measuresMenuCoordenates = state.getMeasuresMenuCoordenates();
			vector<int> mathematicsMenuCoordenates = state.getMathematicsMenuCoordenates();
			vector<int> modeMenuCoordenates = state.getModeMenuCoordenates();
			measuresMenuCoordenates[3] = measuresMenuCoordenates[2] + (measuresMenuCoordenates[3] - measuresMenuCoordenates[2]) * configuration.getAllMeasures().size();
			mathematicsMenuCoordenates[3] = mathematicsMenuCoordenates[2] + (mathematicsMenuCoordenates[3] - mathematicsMenuCoordenates[2]) * configuration.getAllMathematics().size();
			modeMenuCoordenates[3] = modeMenuCoordenates[2] + (modeMenuCoordenates[3] - modeMenuCoordenates[2]) * configuration.getAllModes().size();
			if(state.getMeasuresButtonActive() && isIn(x, y, measuresMenuCoordenates))
			{
				vector<int> coordenates = state.getMeasuresMenuCoordenates();
				selectMeasure((Configuration::Measures)(configuration.getAllMeasures().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			if(state.getMathematicsButtonActive() && isIn(x, y, mathematicsMenuCoordenates))
			{
				vector<int> coordenates = state.getMathematicsMenuCoordenates();
				selectMathematic((Configuration::Mathematics)(configuration.getAllMathematics().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			if(state.getModeButtonActive() && isIn(x, y, modeMenuCoordenates))
			{
				vector<int> coordenates = state.getModeMenuCoordenates();
				selectMode((Configuration::Modes)(configuration.getAllModes().size() - (y - coordenates[2]) / (coordenates[3] - coordenates[2]) - 1));
			}
			if(!isIn(x, y, state.getMeasuresCoordenates()) && !isIn(x, y, state.getMathematicsCoordenates()) && !isIn(x, y, state.getModeCoordenates()) && !isIn(x, y, measuresMenuCoordenates) && !isIn(x, y, mathematicsMenuCoordenates) && !isIn(x, y, modeMenuCoordenates))
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

void Touch::resetDrag(void)
{
	state.setOffsetDrag(false);
	state.setVerticalScaleDrag(false);
	state.setHorizontalScaleDrag(false);
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
		configuration.setHorizontalScale((Configuration::HorizontalScales)(configuration.getHorizontalScale() + levels));
		state.setInitialHorizontalScale(x);
	}
}

void Touch::resetButtons(void)
{
	state.setMeasuresButtonActive(false);
	state.setMathematicsButtonActive(false);
	state.setModeButtonActive(false);
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
}

bool Touch::isIn(int x, int y, vector<int> coordenates)
{
	return (x > coordenates[0]) && (x < coordenates[1]) && (y > coordenates[2]) && (y < coordenates[3]);
}

