//
//  TrackInfo.h
//
//  Created by Guille on 24/4/24.
//

#ifndef TrackInfo_h
#define TrackInfo_h
#import <AVFoundation/AVFoundation.h>

@interface TrackInfo : NSObject

@property (nonatomic, strong) NSString* id;
@property int bitRate;
@property float frameRate;
@property int videoWidth;
@property int videoHeight;

@end

#endif /* TrackInfo_h */
