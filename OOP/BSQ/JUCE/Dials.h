/*
  ==============================================================================

    Dials.h
    Created: 1 Aug 2022 4:41:24pm
    Author:  Andres Beregovich

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Dials.h"

using namespace juce;

//==============================================================================
/*
*/
class Dials  : public Component,
               public LookAndFeel_V4
{
public:
    
    Dials();
    ~Dials() override;

    void paint (Graphics&) override;
    void resized() override;

private:
    
    Slider dialMaster;
    Label dialLabel;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dials)
};
