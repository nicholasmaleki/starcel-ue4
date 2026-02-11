/// Created by HISPlayer � - 2024  

#pragma once
#include <string>
#include <vector>
#include "HISPlayerTypes/HISPlayerPlaybackProperties.h"
#include "HISPlayerTypes/HISPlayerTrack.h"
#include "HISPlayerTypes/HISPlayerStatus.h"
#include "Engine/LatentActionManager.h"

#include "HISPlayerFunctions.generated.h"



UCLASS(NotBlueprintable, meta = (DisplayName = "HISPlayer Unreal"))
class UHISPlayerFunctions : public UObject {
	GENERATED_BODY()

public:

	/**
	* This function is called automatically
	*/
	static void StartupModule();
	/**
	* This function is called automatically
	*/
	static void ShutdownModule();

	/**
	* Pre-initialize HISPlayer, minimal code needed to be called on BeginPlay
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer BeginPlay"))
	static void BeginPlay(int numStreams);

	/**
	* Initialize HISPlayer, needed before using the player. It internally creates a texture in runtime.
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Setup", Latent, LatentInfo = "LatentInfo", DefaultToSelf = "WorldContextObject"))
	static void Setup(int streamIndex, UObject* WorldContextObject, UTexture2D*& outputTexture, struct FLatentActionInfo LatentInfo);
	/**
	 * Create a new texture of a new resolution
	 * @param Stream index
	 * @param FIntPoint for resolution. X value for Width, Y value for Height.
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Create New Texture"))
	static void CreateNewTexture(int streamIndex, FIntPoint resolution, UTexture2D*& outputTexture);

	/**
	 * Start HISPlayer
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Open Player"))
	static int OpenPlayer(int streamIndex, const FString& url);

	/**
	 * Update each frame, needs to be called every frame
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Update"))
	static void Update(int streamIndex);

	/**
	 * Resume the paused or stopped video.
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Resume"))
	static void Resume(int streamIndex);

	/**
	 * Pause the video
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Pause"))
	static void Pause(int streamIndex);

	/**
	 * Stops the video and next time you press play, it begins from start
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Stop"))
	static void Stop(int streamIndex);

	/**
	 * Seeks the video to a certain position
	 * @param Stream index
	 * @param msec
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Seek"))
	static void Seek(int streamIndex, int msec);

	/**
	 * Set a new value for the volume of the player
	 * @param Stream index
	 * @param newVolume - must be included in the range [0.0f,1.0f]
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer SetVolume"))
	static void SetVolume(int streamIndex, float newVolume);

	/**
	* Set Playback Speed Rate
	*
	* @param Stream index
	* @param Playback Speed Rate. (Example: 1.0 = 100% speed, 1.5 = 150% speed, 0.75 = 75% speed)
	* .
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Set Playback Rate"))
	static void SetPlaybackRate(int streamIndex, float rate);

	/**
	* Get Current Playback Speed Rate
	*
	* @param Stream index
	* @return Current Playback Rate
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Playback Rate"))
	static float GetPlaybackRate(int streamIndex);

	/**
	 * Mute the player
	 * @param Stream index
	 * @param isMute
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer SetMute"))
	static void SetMute(int streamIndex, bool isMute);

	/**
	 * Returns the current time position of the current track
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer GetCurrentPosition"))
	static int GetCurrentPosition(int streamIndex);

	/**
	 * Returns the total time of the current track
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer GetTotalTime"))
	static int GetTotalTime(int streamIndex);

	/**
	 * Method for closing and releasing HISPlayer
	 * @param Stream index
	 */
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Close"))
	static void Close(int streamIndex);

	/**
	* Get the player status
	* @param Stream index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Player Status"))
	static HISPlayerStatus GetPlayerStatus(int streamIndex);

	/**
	* Get the Delegate Manager
	* @param Stream index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Delegate Manager"))
	static UDelegateManager* GetDelegateManager(int streamIndex);

	/**
	* Set the current playback properties of the stream
	* @param Stream index
	* @param PlayerPlaybackProperties type.
	* @return PlayerPlaybackProperties type.
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Set PlayBack Properties"))
	static void SetPlaybackProperties(int streamIndex, const FHISPlayerPlaybackProperties& Properties);

	/**
	* Get the height of the current track of a certain stream
	* @param Stream index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Video Height"))
	static int GetVideoHeight(int streamIndex);

	/**
	* Get the width of the current track of a certain stream
	* @param Stream index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Video Width"))
	static int GetVideoWidth(int streamIndex);

	/**
	* Get the number of tracks of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track Count"))
	static int GetTrackCount(int streamIndex);

	/**
	* Provides information about the tracks of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Tracks"))
	static TArray<FHISPlayerTrack> GetTracks(int streamIndex);

	/**
	* Get the bitrate of a certain track of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track Bitrate"))
	static int GetTrackBitrate(int streamIndex, int trackIndex);

	/**
	* Get the framerate of a certain track of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track Framerate"))
	static float GetTrackFramerate(int streamIndex, int trackIndex);

	/**
	* Get the width of a certain track of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track Width"))
	static int GetTrackWidth(int streamIndex, int trackIndex);

	/**
	* Get the width of a certain track of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track Height"))
	static int GetTrackHeight(int streamIndex, int trackIndex);

	/**
	* Get the ID of a certain track of a certain stream
	* @param Stream index
	* @param Track index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Get Track ID"))
	static FString GetTrackID(int streamIndex, int trackIndex);

	/**
	* Select a certain track of a certain stream to be used as the main track. The possible tracks can be obtained from the tracks returned from the method GetTracks.
	* The playerIndex is associated with the index of the element of Multi Stream Properties
	* @param Stream index
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Select Track"))
	static void SelectTrack(int streamIndex, int trackIndex);

	/**
	* Change Video Content
	*
	* Use this method to change the content of a Stream at runtime.
	* @param Stream Index
	* @param Content URL
	*/
	UFUNCTION(BlueprintCallable, Category = "HISPlayer", meta = (DisplayName = "HISPlayer Change Video Content"))
	static void ChangeVideoContent(int streamIndex, const FString& url);

	// Internal

	/**
	* Internal. Check if the player has been initialized.
	*/
	static bool IsPlayerInit();

};
