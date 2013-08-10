#include <Display.hpp>
#include <cmath>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples) : configuration(configuration), state(state), samples(samples), measurer(configuration, state, samples), mathematician(configuration, state, samples), miniFB("/dev/fb0")
{
}

void Display::print(void)
{
   clearScreen();
   printGrid(state.getGridCoordenates());
   printTriggerLevel(state.getGridCoordenates(), state.getColor(configuration.getTriggerChannel()));
   printSliders(state.getGridCoordenates());
   if(configuration.getChannel(state.getUnselectedChannel()))
   {
      printSamples(samplesToPixels(samples.getSamples(state.getUnselectedChannel()), configuration.getVerticalScaleValue(state.getUnselectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getUnselectedChannel()), state.getGridCoordenates());
   }
   if(configuration.getChannel(state.getSelectedChannel()))
   {
      printSamples(samplesToPixels(samples.getSamples(state.getSelectedChannel()), configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
   }
   if(configuration.getMathematic() != Configuration::NOMATHEMATIC)
   {
      printSamples(samplesToPixels(mathematician.getSamples(), configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), 0, configuration.getMemoryDepth(), 1, state.getColorMathematics(), state.getGridCoordenates());
   }
   if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
   {
      printOffset((configuration.getOffset(state.getSelectedChannel()) / configuration.getVerticalScaleValue(state.getSelectedChannel()) * state.getPixelsPerDivision()).min(3.5f * state.getPixelsPerDivision()).max(-4.0f * state.getPixelsPerDivision()), configuration.getOffsetString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
      printVerticalScale(configuration.getVerticalScaleString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
   }
   printHorizontalScale(configuration.getHorizontalScaleString(), state.getGridCoordenates());
   printDelay((configuration.getDelay() * state.getPixelsPerDivision()).min(3.5f * state.getPixelsPerDivision()).max(-5.0f * state.getPixelsPerDivision()), configuration.getDelayString(), state.getGridCoordenates());
   printChannelButton("Channel A", configuration.getChannel(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, state.getColor(Configuration::CHANNEL_A), state.getChannelCoordenates(Configuration::CHANNEL_A));
   printChannelButton("Channel B", configuration.getChannel(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, state.getColor(Configuration::CHANNEL_B), state.getChannelCoordenates(Configuration::CHANNEL_B));
   printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_A), state.getColor(Configuration::CHANNEL_A), state.getCouplingCoordenates(Configuration::CHANNEL_A));
   printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_B), state.getColor(Configuration::CHANNEL_B), state.getCouplingCoordenates(Configuration::CHANNEL_B));
   printButton("Measures", measurer.getMeasure(), state.getMeasuresButtonActive(), state.getMeasuresCoordenates());
   printButton("Mathematics", configuration.getMathematicString(), state.getMathematicsButtonActive(), state.getMathematicsCoordenates());
   printButton("Mode", configuration.getModeString(), state.getModeButtonActive(), state.getModeCoordenates());
   if(configuration.getMeasure() == Configuration::CURSORS)
   {
      vector<fix> cursor = configuration.getCursor();
      vector<int> gridCoordenates = state.getGridCoordenates();
      vector<int> cursorCoordenates;
      cursorCoordenates.push_back(min(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
      cursorCoordenates.push_back(max(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
      cursorCoordenates.push_back(gridCoordenates[2] + 4 * state.getPixelsPerDivision() - max(cursor[2], cursor[3]) * state.getPixelsPerDivision());
      cursorCoordenates.push_back(gridCoordenates[2] + 4 * state.getPixelsPerDivision() - min(cursor[2], cursor[3]) * state.getPixelsPerDivision());
      printCursor(cursorCoordenates);
   }
   if(state.getMeasuresButtonActive())
   {
      printMenu(configuration.getAllMeasures(), state.getGridCoordenates());
   }
   if(state.getMathematicsButtonActive())
   {
      printMenu(configuration.getAllMathematics(), state.getGridCoordenates());
   }
   if(state.getModeButtonActive())
   {
      printMenu(state.getAllModes(), state.getGridCoordenates());
   }
   if(state.getModeActive())
   {
      printMenu(configuration.getAllModes(), state.getGridCoordenates());
   }
   if(state.getAverageActive())
   {
      printMenu(configuration.getAllAverages(), state.getGridCoordenates());
   }
   if(state.getTriggerModeActive())
   {
      printMenu(configuration.getAllTriggerModes(), state.getGridCoordenates());
   }
   if(state.getTriggerChannelActive())
   {
      printMenu(configuration.getAllChannels(), state.getGridCoordenates());
   }
   if(state.getTriggerSlopeActive())
   {
      printMenu(configuration.getAllTriggerSlopes(), state.getGridCoordenates());
   }
   if(state.getTriggerNoiseRejectActive())
   {
      printMenu(configuration.getAllTriggerNoiseRejects(), state.getGridCoordenates());
   }
   if(state.getTriggerHighFrequencyRejectActive())
   {
      printMenu(configuration.getAllTriggerHighFrequencyRejects(), state.getGridCoordenates());
   }
   if(state.getTriggerLevelActive())
   {
      printAlert("Select the trigger level and hold off", state.getGridCoordenates());
   }
   printMouse(state.getMouseX(), state.getMouseY());
   updateScreen();
}

vector<int> Display::samplesToPixels(const vector<fix>& samples, fix verticalScale, int pixelsPerDivision)
{
   vector<int> pixels(samples.size(), 0);
   for(int i = 0; i < samples.size(); i++)
   {
      pixels[i] = (int) (samples[i] * pixelsPerDivision / verticalScale);
   }
   return pixels;
}

void Display::clearScreen(void)
{
   miniFB.clearScreen();
}

void Display::updateScreen(void)
{
   miniFB.updateScreen();
}

void Display::printGrid(const vector<int>& coordenates)
{
   unsigned char color = miniFB.thinColor(state.getColorGeneral(), 1);
   for(int x = coordenates[0]; x <= coordenates[1]; x += state.getPixelsPerDivision())
   {
      miniFB.drawLine(x, coordenates[2], x, coordenates[3], color);
   }
   for(int y = coordenates[2]; y <= coordenates[3]; y += state.getPixelsPerDivision())
   {
      miniFB.drawLine(coordenates[0], y, coordenates[1], y, color);
   }
}

void Display::printTriggerLevel(const vector<int>& coordenates, unsigned char color)
{
   int y = coordenates[2] + (int) (state.getPixelsPerDivision() * (4 - configuration.getTriggerLevel()));
   miniFB.drawLine(coordenates[0], y, coordenates[1], y, miniFB.thinColor(color, 1));
}

void Display::printSliders(const vector<int>& coordenates)
{
   unsigned char color = miniFB.thinColor(state.getColorGeneral(), 1);
   miniFB.drawRectangleBorder(coordenates[0] + 2, coordenates[2] + 2, coordenates[1] - 2 * state.getPixelsPerDivision() - 2, coordenates[2] + 2 * state.getPixelsPerDivision() - 2, color);
   miniFB.drawRectangleBorder(coordenates[1] - 2 * state.getPixelsPerDivision() + 2, coordenates[2] + 2 * state.getPixelsPerDivision() + 2, coordenates[1] - 2, coordenates[3] - 2, color);
}

void Display::printOffset(int offsetValue, string offsetString, unsigned char color, const vector<int>& coordenates)
{
   miniFB.drawText(coordenates[0] + 5, (coordenates[2] + coordenates[3]) / 2 - offsetValue - miniFB.getTextHeight(offsetString), offsetString, color);
}

void Display::printVerticalScale(string verticalScale, unsigned char color, const vector<int>& coordenates)
{
   miniFB.drawText(coordenates[1] - miniFB.getTextWidth(verticalScale) - 5, (coordenates[2] + coordenates[3]) / 2 - miniFB.getTextHeight(verticalScale), verticalScale, color);
}

void Display::printDelay(int delayValue, std::string delayString, const vector<int>& coordenates)
{
   miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + delayValue, coordenates[3] - miniFB.getTextHeight(delayString) - 5, delayString, state.getColorGeneral());
}

void Display::printHorizontalScale(string horizontalScale, const vector<int>& coordenates)
{
   miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + 5, coordenates[2] + state.getPixelsPerDivision() - miniFB.getTextHeight(horizontalScale) - 5, horizontalScale, state.getColorGeneral());
}

void Display::printChannelButton(string channel, bool isActive, bool isSelected, unsigned char color, const vector<int>& coordenates)
{
   unsigned char fillColor;
   if(isSelected)
   {
      fillColor = miniFB.thinColor(color, 1);
   }
   else
   {
      fillColor = miniFB.thinColor(color, 3);
   }
   miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], fillColor, color);
   if(isActive)
   {
      fillColor = color;
   }
   else
   {
      fillColor = miniFB.thinColor(color, 3);
   }
   miniFB.drawRectangle(coordenates[0] + (coordenates[3] - coordenates[2]) / 8 , (3 * coordenates[2] + coordenates[3]) / 4, coordenates[0] + 3 * (coordenates[3] - coordenates[2]) / 8, (coordenates[2] + 3 * coordenates[3]) / 4, fillColor, color);
   miniFB.drawText(coordenates[0] + (coordenates[3] - coordenates[2]) / 2, (coordenates[2] + coordenates[3] - miniFB.getTextHeight(channel)) / 2, channel, color);
}

void Display::printCouplingButton(string text, unsigned char color, const vector<int>& coordenates)
{
   miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], miniFB.thinColor(color, 3), color);
   miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth("Coupling")) / 2, (2 * coordenates[2] + coordenates[3]) / 3 - miniFB.getTextHeight("Coupling") / 2, "Coupling", color);
   miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text)) / 2, (coordenates[2] + 2 * coordenates[3]) / 3 - miniFB.getTextHeight(text) / 2, text, color);
}

void Display::printButton(string title, string text, bool isActive, const vector<int>& coordenates)
{
   unsigned char color = state.getColorGeneral();
   unsigned char fillColor;
   if(isActive)
   {
      fillColor = miniFB.thinColor(color, 1);
   }
   else
   {
      fillColor = miniFB.thinColor(color, 3);
   }
   miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], fillColor, color);
   miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(title)) / 2, (6 * coordenates[2] + coordenates[3]) / 7 - miniFB.getTextHeight(title) / 2, title, color);
   miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text)) / 2, (3 * coordenates[2] + 4 * coordenates[3]) / 7 - miniFB.getTextHeight(text) / 2, text, color);
}

void Display::printMenu(const vector<string>& options, const vector<int>& coordenates)
{
   unsigned char color = state.getColorGeneral();
   int ppd = state.getPixelsPerDivision();
   int n = 0;
   int m = 0;
   for(int i = 0; i < options.size(); i++)
   {
      miniFB.drawRectangle(coordenates[0] + 3 * n * ppd, coordenates[2] + 2 * m * ppd, coordenates[0] + 3 * (n + 1) * ppd - 1, coordenates[2] + 2 * (m + 1) * ppd - 1, miniFB.thinColor(color, 3), color);
      miniFB.drawText(coordenates[0] + 3 * n * ppd + (3 * ppd - miniFB.getTextWidth(options[i])) / 2, coordenates[2] + 2 * m * ppd + (2 * ppd - miniFB.getTextHeight(options[i])) / 2, options[i], color);
      n++;
      if(n >= 3)
      {
         n = 0;
         m++;
      }
   }
}

void Display::printAlert(string text, const vector<int>& coordenates)
{
   miniFB.drawText(coordenates[0] + state.getPixelsPerDivision(), coordenates[2] + state.getPixelsPerDivision() - miniFB.getTextHeight(text), text, state.getColorGeneral());
}

void Display::printSamples(const std::vector<int>& samples, int delay, int memoryDepth, fix step, unsigned char color, const vector<int>& coordenates)
{
   int upStep = max(1.0, round(step));
   int start = (delay - memoryDepth / 2) * step + memoryDepth / 2;
   for(int i = max(start, 0); i < min((int) (start + round((coordenates[1] - coordenates[0]) * step)), memoryDepth - upStep); i += upStep)
   {
      int ya = (coordenates[2] + coordenates[3]) / 2 - samples[i];
      int yb = (coordenates[2] + coordenates[3]) / 2 - samples[i + upStep];
      if(ya < coordenates[2])
      {
         ya = coordenates[2];
      }
      else if(ya > coordenates[3])
      {
         ya = coordenates[3];
      }
      if(yb < coordenates[2])
      {
         yb = coordenates[2];
      }
      else if(yb > coordenates[3])
      {
         yb = coordenates[3];
      }
      miniFB.drawLine(round(coordenates[0] + (i - start) / step), ya, round(coordenates[0] + (i - start + upStep) / step), yb, color);
   }
}

void Display::printCursor(const vector<int>& coordenates)
{
   miniFB.drawRectangleBorder(coordenates[0], coordenates[2], coordenates[1], coordenates[3], state.getColorGeneral());
}

void Display::printMouse(int x, int y)
{
   //miniFB.drawText(x - miniFB.getTextWidth("X") / 2, y - miniFB.getTextHeight("X") / 2, "X", 0xE);
}

