/*
  ==============================================================================

	PlayList.h
	Created: 26 Jul 2022 8:48:16pm
	Author:  Andres Beregovich

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlayList : public juce::Component,
	public TableListBoxModel,
	public Button::Listener
{
public:
	PlayList();
	PlayList(DeckGUI* deck1, DeckGUI* deck2);
	~PlayList() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	int getNumRows() override;

	void paintRowBackground(Graphics &,
		int rowNumber,
		int width,
		int height,
		bool rowIsSelected
	) override;


	void paintCell(Graphics &,
		int rowNumber,
		int columnId,
		int width,
		int height,
		bool rowIsSelected
	) override;

	Component* refreshComponentForCell(int rowNumber,
		int columnId,
		bool isRowSelected,
		Component *  existingComponentToUpdate
	) override;

	void buttonClicked(Button* button) override;

private:

	//Reference to DECKs
	DeckGUI* deckRef1;
	DeckGUI* deckRef2;
	
	//Buttons
	TextButton loadButton{ "LOAD" };
	TextButton deleteButton{ "DELETE" };
	TextButton loadDeck1Button{ "TO DECK 1" };
	TextButton loadDeck2Button{ "TO DECK 2" };
	TextButton searchButton{ "SEARCH" };

	//Test Buttons
	TextButton xmlButton{ "XML Test" };

	//Text Editor
	TextEditor searchText;

	//Table
	TableListBox tableBox;

	//Tracks Array
	Array<PlaylistComponent> tracks;

	
	FileChooser fChooser {"Select a file...", File::getCurrentWorkingDirectory(), "*.mp3, *.xml"};
	//FileChooser fChooser{ "Select a file...", File::getSpecialLocation(File::userHomeDirectory) ,"*.mp3, *.xml"};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayList)
};
