/*
  ==============================================================================

    PlaylistComponent.h
    Created: 26 Jul 2022 8:48:16pm
    Author:  Andres Beregovich

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <iostream>
#include <string>

//==============================================================================
/*
*/
class PlaylistComponent   
{
public:

	PlaylistComponent(URL url, String filename, String trackname, String trackartist, String tracklength, String trackalbum, String trackyear, String tracknumber);
	PlaylistComponent();
    ~PlaylistComponent();

	//Public Methods
	URL getTrackUrl();
	String getFileName();
	String getTrackName();
	String getTrackArtist();
	String getTrackLength();
	String getTrackAlbum();
	String getTrackYear();
	String getTrackNumber();
	

private:
    
	URL trackUrl;
	String fileName;
	String trackName;
	String trackLength;
	String trackArtist;
	String trackAlbum;
	String trackYear;
	String trackNumber;
    
};
