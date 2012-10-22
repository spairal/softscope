#include <Touch.hpp>

using namespace std;

Touch::Touch(Configuration& configuration, State& state) : configuration(configuration), state(state)
{
	buttonPressed = false;
}

void Touch::setButtonPressed(bool pressed)
{
	buttonPressed = pressed;
}

void Touch::parseScreen(int x, int y)
{
	if(buttonPressed)
	{
		buttonPressed = false;
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
				state.setMeasuresButtonActive(false);
				state.setMathematicsButtonActive(false);
				state.setModeButtonActive(false);
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

