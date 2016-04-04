//
//  PMHTTPManagerTaskStateBox.h
//  PostmatesNetworking
//
//  Created by Kevin Ballard on 1/5/16.
//  Copyright © 2016 Postmates. All rights reserved.
//

@import Foundation;

typedef NS_ENUM(unsigned char, PMHTTPManagerTaskStateBoxState) {
    /// The Running state. This state can transition into Processing and Canceled.
    PMHTTPManagerTaskStateBoxStateRunning = 0,
    /// The Processing state. This state can transition into any state. Transitioning
    /// back into Running occurs when the task fails and is automatically retried.
    PMHTTPManagerTaskStateBoxStateProcessing = 1,
    /// The Canceled state. This state cannot transition anywhere.
    PMHTTPManagerTaskStateBoxStateCanceled = 2,
    /// The Completed state. This state cannot transition anywhere.
    PMHTTPManagerTaskStateBoxStateCompleted = 3
};

typedef struct PMHTTPManagerTaskStateBoxResult {
    /// `true` if the state is now in the desired state, whether
    /// or not a transition actually happened.
    _Bool completed;
    /// The state that it was in before.
    PMHTTPManagerTaskStateBoxState oldState;
} PMHTTPManagerTaskStateBoxResult;

__attribute__((objc_subclassing_restricted))
@interface PMHTTPManagerTaskStateBox : NSObject
@property (atomic, readonly) PMHTTPManagerTaskStateBoxState state;
@property (atomic, nonnull) NSURLSessionTask *networkTask;
- (nonnull instancetype)initWithState:(PMHTTPManagerTaskStateBoxState)state networkTask:(nonnull NSURLSessionTask *)task NS_DESIGNATED_INITIALIZER;
- (nonnull instancetype)init NS_UNAVAILABLE;
/// Transitions the state to \c newState if possible.
- (PMHTTPManagerTaskStateBoxResult)transitionStateTo:(PMHTTPManagerTaskStateBoxState)newState;
@end
