/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    /* Render Buttons */
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
	addAndMakeVisible(defaultButton);

    /* Render Dials */
    addAndMakeVisible(dialSpeed);
    addAndMakeVisible(dialVolume);
    addAndMakeVisible(dialPos);
    addAndMakeVisible(dialMaster);

    /* Define Dial Type */
    dialSpeed.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    dialVolume.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    dialPos.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    
    /* Define Text for Dials*/
    dialVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    dialSpeed.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    dialPos.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);

    /* Renders Waveform */
    addAndMakeVisible(waveformDisplay);

    /* Add Event Listeners */
    //Buttons
	playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
	defaultButton.addListener(this);

	//Dials
    dialSpeed.addListener(this);
    dialVolume.addListener(this);
    dialPos.addListener(this);

    /* Define Component Range */
    dialSpeed.setRange(0.0, 2.0);
    dialVolume.setRange(0.0, 1.0);
    dialPos.setRange(0.0, 1.0);
    startTimer(500);
    
    /* Set styles for rotary sliders */
	dialSpeedLook.setColour(Slider::thumbColourId, Colours::darkblue);
	dialSpeedLook.setColour(Slider::rotarySliderFillColourId, Colours::blue);
	dialSpeed.setLookAndFeel(&dialSpeedLook);

    dialVolLook.setColour(Slider::thumbColourId, Colours::darkblue);
    dialVolLook.setColour(Slider::rotarySliderFillColourId, Colours::blue);
    dialVolume.setLookAndFeel(&dialVolLook);
    
    dialPosLook.setColour(Slider::thumbColourId, Colours::darkblue);
    dialPosLook.setColour(Slider::rotarySliderFillColourId, Colours::blue);
    dialPos.setLookAndFeel(&dialPosLook);
    
    playButton.setColour (TextButton::buttonColourId, Colours::green);
    playButton.setColour (TextButton::textColourOffId , Colours::black);
    stopButton.setColour (TextButton::buttonColourId, Colours::red);
    stopButton.setColour (TextButton::textColourOffId , Colours::black);
    loadButton.setColour (TextButton::buttonColourId, Colours::grey);
    loadButton.setColour (TextButton::textColourOffId , Colours::black);
	defaultButton.setColour(TextButton::buttonColourId, Colours::blue);
	defaultButton.setColour(TextButton::textColourOffId, Colours::black);
    
    speedLabel.attachToComponent(&dialSpeed, true);
    dialSpeed.setTextValueSuffix(" bpm");
    
    posLabel.attachToComponent(&dialPos, true);
    dialPos.setTextValueSuffix(" sec");
    
    volLabel.attachToComponent(&dialVolume, true);
    dialVolume.setTextValueSuffix(" dB");

	//Set Defaults
	dialSpeed.setValue(1.0, sendNotificationAsync);
	dialVolume.setValue(1.0, sendNotificationAsync);
	dialPos.setValue(0.0, sendNotificationAsync);

}

DeckGUI::~DeckGUI()
{
    stopTimer();
	dialSpeed.setLookAndFeel(nullptr);
	dialVolume.setLookAndFeel(nullptr);
	dialPos.setLookAndFeel(nullptr);
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::white);
    g.setFont (14.0f);
    
}

void DeckGUI::resized()
{
    /* Styling variables */
    const int dialWidth = getWidth() / 3;
    const int dialHeight = getHeight() / 7;
    double rowH = getHeight() / 16;
    
    /* Bounds for components */
    
	//Buttons
    playButton.setBounds(0, 0, getWidth() / 2, rowH);
    stopButton.setBounds(getWidth() / 2, 0, getWidth() / 2, rowH);
	loadButton.setBounds(0, rowH * 6, getWidth()/2, rowH);
	defaultButton.setBounds(getWidth() / 2, rowH * 6, getWidth()/2, rowH);

	//Dials
    dialSpeed.setBounds(0, rowH * 1.25, dialWidth, dialHeight);
    dialVolume.setBounds(dialWidth, rowH * 1.25, dialWidth, dialHeight);
    dialPos.setBounds(dialWidth * 2, rowH * 1.25, dialWidth, dialHeight);

	//Waveform
    waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);
    
    dialMaster.setBounds(0, rowH * 7, getWidth() , rowH * 2);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()}); 
        });
    }
	   if (button == &defaultButton) {
		   //Set all Dials to Default
		   std::cout << "Default button was clicked " << std::endl;
		   dialSpeed.setValue(1.0, sendNotificationAsync);
		   dialVolume.setValue(1.0, sendNotificationAsync);
		   dialPos.setValue(0.0, sendNotificationAsync);

	}
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &dialVolume)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &dialSpeed)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &dialPos)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}

void DeckGUI::loadURLToPlayer(URL url) {
	player->loadURL(url);
}

void DeckGUI::loadURLToWaveform(URL url) {
	waveformDisplay.loadURL(url);
}



