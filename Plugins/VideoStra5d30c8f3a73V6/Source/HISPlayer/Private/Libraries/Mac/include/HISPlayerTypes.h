//
//  HISPlayerTypes.h
//  HISPlayerMac
//
//  Created by UnrealMac on 24/4/24.
//

#ifndef HISPlayerTypes_h
#define HISPlayerTypes_h

enum HISPlayerMimeTypes
{
    HISPLAYER_MIME_TYPE_URL_EXTENSION = 0,
    HISPLAYER_MIME_TYPE_HLS = 1,
    HISPLAYER_MIME_TYPE_DASH = 2
};

// String Mime Types
static NSString *const STRING_MIME_TYPE_HLS= @"application/x-mpegURL";
static NSString *const STRING_MIME_TYPE_DASH = @"application/dash+xml";

#endif /* HISPlayerTypes_h */
