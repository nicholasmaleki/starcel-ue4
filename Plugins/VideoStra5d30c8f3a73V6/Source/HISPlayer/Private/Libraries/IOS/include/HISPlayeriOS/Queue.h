//
//  Queue.h
//  HISPlayeriOS
//
//  Created by Guille on 27/2/24.
//

#ifndef Queue_h
#define Queue_h
__attribute__((visibility("default"))) @interface Queue:NSObject{}
@property(nonatomic, strong) NSMutableArray* queue;
@property int eventID;
@property int arg1;
@property int arg2;
- (id)init;
- (void) pushToQueue: (id)obj;
- (int) popFromEventQueue;
- (int) eventQueueCount;
- (int)getLastEventID;
-(int)getLastEventArg1;
-(int)getLastEventArg2;
@end
#endif /* Queue_h */
