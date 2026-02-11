/// Created by HISPlayer © - 2024  

#pragma once
#include "HISPlayerEvent.generated.h"

UENUM(BlueprintType, Category = "HISPlayer|Types")
enum class HISPlayerEvent : uint8 {

	NONE = 0				UMETA(DisplayName = "None"),				// No or unknown event
	
	INIT_COMPLETE = 1		UMETA(DisplayName = "Init complete"),		// The Player has been initialized, but it's not playing 

	PLAYBACK_STARTED = 2	UMETA(DisplayName = "Started"),				// The player has started playing the video
	
	END_OF_CONTENT = 3		UMETA(DisplayName = "End of content"),		// The player has reached the end of the video playback
	
	BUFFERING_ENDED = 6		UMETA(DisplayName = "Ended"),				// The player has buffered enough content and has resume the playback. Wait for this event before starting playback.
	
	TEXTURE_CHANGED = 7		UMETA(DisplayName = "Texture Changed"),		// The internal texture has changed
	
	TRACK_CHANGED = 8		UMETA(DisplayName = "Track Changed"),		// The track of the playback has changed. This is especially useful for protocols with several resolution tracks (ABR)

	PLAYBACK_PAUSED = 9		UMETA(DisplayName = "Paused"),				// The playback has been paused
	
	STOPPED = 12			UMETA(DisplayName = "Stopped"),				// The player has been closed
	
	SEEKED = 13				UMETA(DisplayName = "Seeked"),				// The player has seeked

	BUFFERING = 14			UMETA(DisplayName = "Buffering"),			// The player is buffering

	EXTERNAL_PCM = 15		UMETA(DisplayName = "On External PCM received"),	// The player is buffering
	
	LOADING = 157			UMETA(DisplayName = "Loading"),				// The player is loading a video

	/**
	 * This event is called when new timed metadata is ready for display in HLS.
	 * 
	 * Timed metadata includes additional information about the playing content that may be displayed
	 * to the user and this information may change at different times throughout the content.
	 * Each time new metadata is available for display, this event occurs.
	 */
	TIMED_METADATA_RENDER = 101		UMETA(DisplayName = "Timed Metadata Render"),

	SERVER_CONNECTION = 100			UMETA(DisplayName = "Server Connection")
	
};
