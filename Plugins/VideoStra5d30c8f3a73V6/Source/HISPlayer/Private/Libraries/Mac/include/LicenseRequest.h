//
//  LicenseRequest.h
//  HISPlayerMac
//
//  Created by Guille on 28/2/24.
//

#import <JavaScriptCore/JavaScriptCore.h>
#include <dlfcn.h>
#import "HISPlayerMac.h"

#ifndef LicenseRequest_h
#define LicenseRequest_h

@interface LicenseRequest:NSObject{}

@property bool isWatermarkNeeded;
@property int playbackDurationLimit;
@property int result;
@property int responseCode;
 
- (NSString *)getJSONObject : (NSString *)licenseKey :(NSString *)appID :(NSString *)sdkVersion :(NSString *)Content;
- (int)requestLicense: (NSString*) licenseKey :(NSString*) appID : (NSString*) sdkVersion : (NSString *)Content : (int) playerIndex : (HISPlayer*) manager : (bool) isEditor;
- (int)sendPostRequestWithEncryptedData:(NSString *)encryptedMessage : (HISPlayer*) manager;
- (NSString*) GetLibraryPath;

@end
#endif /* LicenseRequest_h */
