//
//  HISPlayer.h
//
//  Created by Guille on 22/2/24.
//




#ifndef HISPlayer_h
#define HISPlayer_h

#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>

#import <stdio.h>
#import "ID3Metadata.h"
#import "Queue.h"

//Interfaz del Player
@interface HISPlayer : NSObject <AVPlayerItemMetadataOutputPushDelegate> {
    
}

@property (nonatomic, strong) AVPlayer *player;
@property (nonatomic, strong) AVURLAsset *sourceAsset;
@property (nonatomic, strong) AVPlayerItem *item;
@property (nonatomic, strong) AVPlayerItemVideoOutput *PlayerItemVideoOutput;
@property (nonatomic, strong) ID3Metadata* id3MetadataInfo;
@property (nonatomic, strong) AVPlayerItemMetadataOutput* itemMetadataOutput;
@property (nonatomic, strong) AVCaptureSession* session;
@property (nonatomic, strong) NSMutableArray* events;
@property (nonatomic, strong) Queue* eventQueue;

@property int tamBuffer;
@property int prevTamBuffer;
@property int playerIndex;
@property bool autoplay;

@property (nonatomic, strong) NSString* localAppID;
@property (nonatomic, strong) NSString* version;
@property (nonatomic, strong) NSString* currentURL;
@property (nonatomic, strong) NSString* licenseKey;

- (int) CreatePlayer: (NSString*) licenseKey : (NSString*) version : (int) playerIndex;
- (int) OpenURL:(NSString*) url;
- (void) Play;
- (void) Pause;
- (void) Stop;
- (void) Close;
- (void) Seek: (int)msec;
- (void) SetAutoplay: (bool) active;
- (void) SetMute: (bool) muted;
- (void) SetVolume: (float)vol;
- (void) EndOfContent;
- (int) GetVideoDuration;
- (int) GetCurrentPosition;
- (Boolean) GetWatermarkEnabled;
- (int) getLastEventID: (NSMutableArray*)queue;
- (int) getLastEventArg1: (NSMutableArray*)queue;
- (int) getLastEventArg2: (NSMutableArray*)queue;
- (void) pushEvent: (int)eventID : (int)arg1 : (int)arg2;
-(char*) GetMetadataText: (int)metadataTagSelector;
-(void) CleanMetadataText;
-(char*) GetMetadataProperties: (int)metadataPropInfo;
- (NSString*) debugType: (CVPixelBufferRef) pixelBuffer;
-(void) SetHISPlayerValues;
- (void) clean;



@end
#endif /* HISPlayer_h */


