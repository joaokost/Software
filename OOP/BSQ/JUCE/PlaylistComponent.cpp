/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 26 Jul 2022 8:48:16pm
    Author:  Andres Beregovich

  ==============================================================================
*/

#include <JuceHeader.h>
#include <iostream>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(URL url, String filename, String trackname, String trackartist, String tracklength, String trackalbum, String trackyear, String tracknumber)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	trackUrl = url;
	fileName = filename;
	trackName = trackname;
	trackArtist = trackartist;
	trackLength = tracklength;
	trackAlbum = trackalbum;
	trackYear = trackyear;
	trackNumber = tracknumber;

}

PlaylistComponent::PlaylistComponent()
{
	
}

PlaylistComponent::~PlaylistComponent()
{
}

URL PlaylistComponent::getTrackUrl() {
	return trackUrl;
}

String PlaylistComponent::getFileName() {
	return fileName;
}

String PlaylistComponent::getTrackArtist() {
	return trackArtist;
}

String PlaylistComponent::getTrackName() {
	return trackName;
}

String PlaylistComponent::getTrackLength() {
	return trackLength;
}

String PlaylistComponent::getTrackAlbum() {
	return trackAlbum;
}

String PlaylistComponent::getTrackYear() {
	return trackYear;
}

String PlaylistComponent::getTrackNumber() {
	return trackNumber;
}
