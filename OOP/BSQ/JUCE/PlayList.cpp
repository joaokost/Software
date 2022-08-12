/*
  ==============================================================================

	PlayList.cpp
	Created: 26 Jul 2022 8:48:16pm
	Author:  Andres Beregovich

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>
#include "PlayList.h"
#include "PlaylistComponent.h"

//==============================================================================
//Standard Contructor
PlayList::PlayList()
{
}

PlayList::PlayList(DeckGUI* deck1, DeckGUI* deck2)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	deckRef1 = deck1;
	deckRef2 = deck2;

	//Button LOAD
	loadButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
	loadButton.setColour(TextButton::textColourOffId, Colours::white);
	loadButton.addListener(this);
	addAndMakeVisible(loadButton);

	//Button DELETE
	deleteButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
	deleteButton.setColour(TextButton::textColourOffId, Colours::white);
	deleteButton.addListener(this);
	addAndMakeVisible(deleteButton);

	//Button loadDeck1
	loadDeck1Button.setColour(TextButton::buttonColourId, Colours::darkgrey);
	loadDeck1Button.setColour(TextButton::textColourOffId, Colours::white);
	loadDeck1Button.addListener(this);
	addAndMakeVisible(loadDeck1Button);

	//Button loadDeck2
	loadDeck2Button.setColour(TextButton::buttonColourId, Colours::darkgrey);
	loadDeck2Button.setColour(TextButton::textColourOffId, Colours::white);
	loadDeck2Button.addListener(this);
	addAndMakeVisible(loadDeck2Button);

	//Button SEARCH
	searchButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
	searchButton.setColour(TextButton::textColourOffId, Colours::white);
	searchButton.addListener(this);
	addAndMakeVisible(searchButton);

	//TextEditor 
	searchText.setColour(TextButton::buttonColourId, Colours::darkgrey);
	searchText.setColour(TextButton::textColourOffId, Colours::white);
	addAndMakeVisible(searchText);

	//Table Box
	tableBox.setHeaderHeight(20);
	tableBox.getHeader().addColumn("File", 1, 150);
	tableBox.getHeader().addColumn("Title", 2, 150);
	tableBox.getHeader().addColumn("Artist", 3, 150);
	tableBox.getHeader().addColumn("Length", 4, 80);
	tableBox.getHeader().addColumn("Album", 5, 150);
	tableBox.getHeader().addColumn("Year", 6, 80);
	tableBox.getHeader().addColumn("Track", 7, 80);
	tableBox.setModel(this);
	addAndMakeVisible(tableBox);


	//Check if there is a saved File an load tracks
	xmlButton.setColour(TextButton::buttonColourId, Colours::darkgrey);
	xmlButton.setColour(TextButton::textColourOffId, Colours::white);
	xmlButton.addListener(this);
	addAndMakeVisible(xmlButton);

	File xmlFile = File::getCurrentWorkingDirectory().getChildFile("MyTrackLibrary.xml");
	if (xmlFile.existsAsFile())
	{
		XmlDocument xmlDoc(xmlFile);
		std::unique_ptr<XmlElement> xmlRoot = xmlDoc.getDocumentElement();
		if (xmlRoot->hasTagName("MyTrackLibrary")) {
			String trackurl = "";
			String filename = "";
			String trackname = "";
			String artist = "";
			String length = "";
			String album = "";
			String year = "";
			String tracknumber = "";

			forEachXmlChildElement(*xmlRoot, child) {
				if (child->hasTagName("track")) {
					forEachXmlChildElement(*child, attr) {
						if (attr->hasTagName("trackurl")) {
							trackurl = attr->getAllSubText();
						}
						if (attr->hasTagName("filename")) {
							filename = attr->getAllSubText();
						}
						if (attr->hasTagName("trackname")) {
							trackname = attr->getAllSubText();
						}
						if (attr->hasTagName("artist")) {
							artist = attr->getAllSubText();
						}
						if (attr->hasTagName("length")) {
							length = attr->getAllSubText();
						}
						if (attr->hasTagName("album")) {
							album = attr->getAllSubText();
						}
						if (attr->hasTagName("year")) {
							year = attr->getAllSubText();
						}
						if (attr->hasTagName("tracknumber")) {
							tracknumber = attr->getAllSubText();
						}
					}
					PlaylistComponent nC(trackurl, filename, trackname, artist, length, album, year, tracknumber);
					tracks.add(nC);
				}
			}
		}
	}
}

PlayList::~PlayList()
{
	//Destructor
	//Save Library in our XML File
	File xmlFile = File::getCurrentWorkingDirectory().getChildFile("MyTrackLibrary.xml");
	if (!xmlFile.existsAsFile())
	{
		auto result = xmlFile.create();
		if (!result.wasOk())
		{
			return;
		}
	}
	String xmlString = "<MyTrackLibrary>\n";
	for (PlaylistComponent plC : tracks) {
		xmlString += "\t<track>\n";
		xmlString += "\t\t<trackurl>" + plC.getTrackUrl().toString(false) + "</trackurl>\n";
		xmlString += "\t\t<filename>" + plC.getFileName() + "</filename>\n";
		xmlString += "\t\t<trackname>" + plC.getTrackName() + "</trackname>\n";
		xmlString += "\t\t<artist>" + plC.getTrackArtist() + "</artist>\n";
		xmlString += "\t\t<length>" + plC.getTrackLength() + "</length>\n";
		xmlString += "\t\t<album>" + plC.getTrackAlbum() + "</album>\n";
		xmlString += "\t\t<year>" + plC.getTrackYear() + "</year>\n";
		xmlString += "\t\t<tracknumber>" + plC.getTrackNumber() + "</tracknumber>\n";
		xmlString += "\t</track>\n";
	}
	xmlString += "</MyTrackLibrary>";
	xmlFile.replaceWithText(xmlString);
}

void PlayList::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
	g.setColour(juce::Colours::darkgrey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void PlayList::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..

	//Buttons
	int wB = 7;
	int hB = 20;
	loadButton.setBounds(0, 0, getWidth()/ wB, hB);
	deleteButton.setBounds(getWidth()/ wB, 0, getWidth() / wB, hB);
	loadDeck1Button.setBounds((getWidth() / wB) * 2, 0, getWidth() / wB, hB);
	loadDeck2Button.setBounds((getWidth() / wB) * 3, 0, getWidth() / wB, hB);
	searchButton.setBounds((getWidth() / wB) * 6, 0, getWidth() / wB, hB);
	xmlButton.setBounds((getWidth() / wB) * 6, 20, getWidth() / wB, hB);

	//Text Editor
	searchText.setBounds((getWidth() / wB) * 4, 0, (getWidth() / wB) * 2, hB);

	//Table
	tableBox.setBounds(0, 20, getWidth(), getHeight());
}

int PlayList::getNumRows()
{
	return tracks.size();
}

void PlayList::paintRowBackground(Graphics & g,
	int     rowNumber,
	int     width,
	int     height,
	bool    rowIsSelected
) 
{
	if (rowIsSelected)
	{
		g.fillAll(Colours::orange);
	}
	else
	{
		g.fillAll(Colours::darkgrey);
	}
}


void PlayList::paintCell(Graphics & g,
	int     rowNumber,
	int     columnId,
	int     width,
	int     height,
	bool    rowIsSelected
)
{
	//Draw Track Information
	if (columnId == 1) {
		g.drawText(tracks[rowNumber].getFileName(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 2) {
		g.drawText(tracks[rowNumber].getTrackName(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 3) {
		g.drawText(tracks[rowNumber].getTrackArtist(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 4) {
		g.drawText(tracks[rowNumber].getTrackLength(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 5) {
		g.drawText(tracks[rowNumber].getTrackAlbum(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 6) {
		g.drawText(tracks[rowNumber].getTrackYear(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	if (columnId == 7) {
		g.drawText(tracks[rowNumber].getTrackNumber(), 2, 0, width - 4, height, Justification::centredLeft, true);
	}
	
}


Component* PlayList::refreshComponentForCell(int rowNumber,
	int columnId,
	bool isRowSelected,
	Component *existingComponentToUpdate
)
{

	return existingComponentToUpdate;
}

void PlayList::buttonClicked(Button* button)
{

	/* LOAD BUTTON */
	//Select new File to load
	if (button == &loadButton)
	{
		//File Dialog
		auto fileChooserFlags = FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
		{
			//Get the File
			File mp3File { chooser.getResult() };

			//If a File was chosen, save it in the list
			if (mp3File.getSize() > 0) {
				//Get URL of File
				URL url = URL{ mp3File };

				//Check if File is already in our list
				bool FileInList = false;
				for (int i = 0; i < tracks.size(); i++) {
					if ((tracks[i].getFileName() == mp3File.getFileName()) && (tracks[i].getTrackUrl() == url)) {
						FileInList = true;
						tableBox.selectRow(i);
						break;
					}
				}
				
				if (!FileInList) {
					String fileName = mp3File.getFileName();
					String trackName = "Unknown";
					String trackArtist = "Unknown";
					String trackArtist2 = "Unknown";
					String trackLength = "Unknown";
					String trackAlbum = "Unknown";
					String trackYear = "Unknown";
					String trackNumber = "Unknown";

					//Get a Input Stream from File
					FileInputStream inputStream(mp3File);

					//Read first 10000 Bytes
					char fileBytes[10000];
					inputStream.read(fileBytes, 10000);

					//Read First 3 Bytes of File (mp3 id), filter ID3 mp3 Files
					if ((fileBytes[0] == 'I') && (fileBytes[1] == 'D') && (fileBytes[2] == '3')) {
						//Check if we have Correct Data
						if ((fileBytes[10] == 'T') && (fileBytes[11] == 'I') && (fileBytes[12] == 'T') && (fileBytes[13] == '2')) {
							//Get TIT2 (Starts at Byte 24)
							String str = "";
							int i = 23;
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'P') && (fileBytes[i + 3] == 'E') && (fileBytes[i + 4] == '1')) {
									trackName = str;
									i += 14; //Offset of 5 (for TAG) + 9 (Where the next word starts) in MP3 File
									break;
								}
							}

							//Get TPE1
							str = "";
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'P') && (fileBytes[i + 3] == 'E') && (fileBytes[i + 4] == '2')) {
									trackArtist = str;
									i += 14; //Offset of 5 (for TAG) + 9 (Where the next word starts) in MP3 File
									break;
								}
							}

							//Get TPE2
							str = "";
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'A') && (fileBytes[i + 3] == 'L') && (fileBytes[i + 4] == 'B')) {
									trackArtist2 = str;
									i += 14; //Offset of 5 (for TAG) + 9 (Where the next word starts) in MP3 File
									break;
								}
							}

							//Get TALB
							str = "";
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'Y') && (fileBytes[i + 3] == 'E') && (fileBytes[i + 4] == 'R')) {
									trackAlbum = str;
									i += 12; //Offset of 5 (for TAG) + 7 (Where the next word starts) in MP3 File
									break;
								}
							}

							//Get TYER
							str = "";
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'R') && (fileBytes[i + 3] == 'C') && (fileBytes[i + 4] == 'K')) {
									trackYear = str;
									i += 14; //Offset of 5 (for TAG) + 9 (Where the next word starts) in MP3 File
									break;
								}
							}

							//Get TRCK
							str = "";
							for (i; i < 10000; i++) {
								//Get rid of NULL characters
								if ((fileBytes[i] > 31) && (fileBytes[i] < 255)) {
									str = str + fileBytes[i];
								}
								if ((fileBytes[i + 1] == 'T') && (fileBytes[i + 2] == 'P') && (fileBytes[i + 3] == 'O') && (fileBytes[i + 4] == 'S')) {
									trackNumber = str;
									break;
								}
							}
						}
					} 

					//Set new PlaylistComponent for our tracks
					PlaylistComponent nC(url, fileName, trackName, trackArtist, trackLength, trackAlbum, trackYear, trackNumber);
					tracks.add(nC);
					
					//Update table
					tableBox.updateContent();

					//Update XML Library File (Create one if it does not exist)
					//Open the File
					
					File flib = File::getCurrentWorkingDirectory().getChildFile("MyTrackLibrary.xml");
					if (!flib.existsAsFile())
					{
						auto result = flib.create();
						if (!result.wasOk())
						{
							return;  
						}

						//Set the Frame

					}

				}
			}
		});


	}

	/* DELETE BUTTON */
	if (button == &deleteButton) {
		//Check if a row is selected
		int row = tableBox.getSelectedRow();
		if (row > -1) {
			tracks.remove(row);
			tableBox.updateContent();
			//Update XML Library File 

		}
	}

	/* LOAD DECK 1 BUTTON */
	if (button == &loadDeck1Button) {
		//Check if a row is selected
		int row = tableBox.getSelectedRow();
		if (row > -1) {
			deckRef1->loadURLToPlayer(tracks[row].getTrackUrl());
			deckRef1->loadURLToWaveform(tracks[row].getTrackUrl());
		}
	}

	/* LOAD DECK 2 BUTTON */
	if (button == &loadDeck2Button) {
		//Check if a row is selected
		int row = tableBox.getSelectedRow();
		if (row > -1) {
			deckRef2->loadURLToPlayer(tracks[row].getTrackUrl());
			deckRef2->loadURLToWaveform(tracks[row].getTrackUrl());
		}
	}

	/* SEARCH BUTTON */
	if (button == &searchButton) {
		//Check if search field is not empty
		String srT = searchText.getText();
		if (!(srT == "")) {
			//Search in our track list
			for (int i = 0; i < tracks.size(); i++) {
				if (tracks[i].getTrackName() == srT) {
					tableBox.selectRow(i);
					break;
				}
			}
		}
	}

	/* XML BUTTON */
	if (button == &xmlButton) {
		File xmlFile = File::getCurrentWorkingDirectory().getChildFile("MyTrackLibrary.xml");
		if (!xmlFile.existsAsFile())
		{
			auto result = xmlFile.create();
			if (!result.wasOk())
			{
				return;
			}
		}
		String xmlString = "<MyTrackLibrary>\n";
		for(PlaylistComponent plC : tracks) {
			xmlString += "\t<track>\n";
			xmlString += "\t\t<trackurl>" + plC.getTrackUrl().toString(false) +"</trackurl>\n";
			xmlString += "\t\t<filename>" + plC.getFileName() + "</filename>\n";
			xmlString += "\t\t<trackname>" + plC.getTrackName() + "</trackname>\n";
			xmlString += "\t\t<artist>" + plC.getTrackArtist() + "</artist>\n";
			xmlString += "\t\t<length>" + plC.getTrackLength() + "</length>\n";
			xmlString += "\t\t<album>" + plC.getTrackAlbum() + "</album>\n";
			xmlString += "\t\t<year>" + plC.getTrackYear() + "</year>\n";
			xmlString += "\t\t<tracknumber>" + plC.getTrackNumber() + "</tracknumber>\n";
			xmlString += "\t</track>\n";
		}
		xmlString += "</MyTrackLibrary>";
		xmlFile.replaceWithText(xmlString);
	}

}

