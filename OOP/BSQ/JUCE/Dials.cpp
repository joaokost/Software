/*
  ==============================================================================

    Dials.cpp
    Created: 1 Aug 2022 4:41:24pm
    Author:  Andres Beregovich

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Dials.h"
using namespace juce;

//==============================================================================
Dials::Dials()
{
    
    
    addAndMakeVisible(dialMaster);
    addAndMakeVisible(dialLabel);
    
    dialLabel.setText("Frequency", dontSendNotification);
    dialLabel.attachToComponent(&dialMaster, true);
    
    dialMaster.setSliderStyle(Slider::SliderStyle::ThreeValueHorizontal );
    dialMaster.setTextBoxStyle(Slider::TextBoxAbove, false, 100, 25);
    dialMaster.setTextValueSuffix(" Hz");
    
    
    dialMaster.setRange(0.0, 2.0);
    
}

Dials::~Dials()
{
	
}

void Dials::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::lightgreen);
    g.setFont (14.0f);
    g.drawText("Multiple Adjustments", 5, 5, 100, 25, Justification::centred);
    g.setColour (juce::Colours::red);
    
    g.drawRect (getLocalBounds(), 3);   // draw an outline around the component
    
}

void Dials::resized()
{
    dialMaster.setBounds(getLocalBounds());
}

