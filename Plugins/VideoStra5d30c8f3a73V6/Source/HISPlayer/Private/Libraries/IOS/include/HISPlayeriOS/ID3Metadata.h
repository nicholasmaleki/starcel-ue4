//
//  ID3Metadata.h
//
//  Created by Guille on 22/2/24.
//

#ifndef ID3Metadata_h
#define ID3Metadata_h

//Interfaz del Metadata

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>
#import <stdio.h>
@interface ID3Metadata : NSObject

@property(nonatomic, strong) NSString* text;
@property (nonatomic, strong) NSString* title;
@property(nonatomic, strong) NSString* album;
@property(nonatomic, strong) NSString* artist;
@property(nonatomic, strong) NSString* date;
@property(nonatomic, strong) NSString* genre;
@property(nonatomic, strong) NSString* sessionInfo;
@property(nonatomic, strong) NSString* track;
@property(nonatomic, strong) NSString* year;
@property(nonatomic, strong) NSString* attachedPicture;
@property(nonatomic, strong) NSString* lyric;
@property(nonatomic, strong) NSString* privateFrame;
@property(nonatomic, strong) NSString* comment;
@property(nonatomic, strong) NSString* time;
@property(nonatomic, strong) NSString* encapsulatedObject;
@property(nonatomic, strong) NSString* selectedMetadata;

//Properties
@property(nonatomic, strong) NSString* metadataMimeType;
@property(nonatomic, strong) NSString* metadataDescription;
@property(nonatomic, strong) NSString* metadataFileName;

-(int)checkMetadata: (NSString*)metadataTag checkValue : (AVMetadataItem*)metadataValue;

-(NSString*)GetMetadataInfoFromString: (int)metadataTagSelector;

-(NSString*)GetMetadataProps:(int)selector;
-(void)clean;

@end



#endif /* ID3Metadata_h */
