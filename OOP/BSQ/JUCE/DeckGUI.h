/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Dials.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener,
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 

	void loadURLToPlayer(URL url);
	void loadURLToWaveform(URL url);

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};

	TextButton defaultButton{ "DEFAULT" };
    
    
    Slider dialSpeed;
    Slider dialVolume;
    Slider dialPos;

    Dials dialMaster;

    FileChooser fChooser{"Select a file..."};

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player; 

    LookAndFeel_V4 dialVolLook;
    LookAndFeel_V4 dialSpeedLook;
    LookAndFeel_V4 dialPosLook;
    
    Label volLabel;
    Label speedLabel;
    Label posLabel;
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};



