/// Created by HISPlayer © - 2024  

#pragma once

/// <summary>
/// This event ocurs when an asynchronous method of HISPlayer has completed successfully or failed
/// </summary>
enum class HISPlayerMobileNativeEvent : uint8 {

	NONE = 0,

	/// <summary>
	/// Complete Async. HISPlayer API
	/// </summary>
	/// <param name="param1">HISPlayerASYNC_EVENT_TYPE</param>
	/// <param name="param2">Result</param>
	ASYNC_COMPLETE = 1,

	/// <summary>
	/// Reached the end of content
	/// </summary>
	END_OF_CONTENT = 2,

	/// <summary>
	/// Content information is updated
	/// </summary>
	/// <param name="param1">Width</param>
	/// <param name="param2">Height</param>
	UPDATE_CONTENT_INFO = 3,

	/// <summary>
	/// Current playing time is updated 
	/// </summary>
	/// <param name="param1">Current playing time in miliseconds</param>
	/// <param name="param2">Buffer Info</param>
	TIME = 4,

	/// <summary>
	/// Buffer state is chaged 
	/// </summary>
	/// <param name="param1">Buffering status: 1 (buffering begin), 2 (buffering progress), 3 (buffering end)</param>
	/// <param name="param2">Buffering progress (percent)</param>
	BUFFERING = 5,

	/// <summary>
	/// Error happen at HISPlayer 
	/// </summary>
	/// <param name="param1">Error code</param>
	ERROR = 6,

	/// <summary>
	/// Load Start at HISPlayer
	/// </summary>
	LOADSTART = 7,

	/// <summary>
	/// New Metadata Detected
	/// </summary>
	TIMED_METADATA_RENDER = 100
};

/// <summary>
/// Possible values for command paramterer of onAsyncCmdComplete (under HISPlayerMobileNativeEvent::ASYNC_COMPLETE)
/// </summary>
enum class HISPlayerAsyncCMD : uint8 {

	NONE = 0,

	/// <summary>
	/// The player has initialized for local content
	/// </summary>
	OPEN_LOCAL = 1,

	/// <summary>
	/// The player has initialized for stream content
	/// </summary>
	OPEN_STREAMING = 2,

	/// <summary>
	/// The player has started playing a local video
	/// </summary>
	START_LOCAL = 5,

	/// <summary>
	/// The player has started playing a stream
	/// </summary>
	START_STREAMING = 6,

	/// <summary>
	/// The player has stopped
	/// </summary>
	STOP = 8,

	/// <summary>
	/// The player has paused
	/// </summary>
	PAUSE = 9,

	/// <summary>
	/// The player has resumed
	/// </summary>
	RESUME = 10,

	/// <summary>
	/// The player has seeked
	/// </summary>
	SEEK = 11,

	/// <summary>
	/// New Metadata Detected
	/// </summary>
	TIMED_METADATA_RENDERED = 12
};