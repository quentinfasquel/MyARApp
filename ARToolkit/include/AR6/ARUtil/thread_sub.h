/*
 *  profile.h
 *  ARToolKit6
 *
 *  Implements a basic client-worker threading system.
 *
 *  This file is part of ARToolKit.
 *
 *  Copyright 2015-2016 Daqri, LLC.
 *  Copyright 2007-2015 ARToolworks, Inc.
 *
 *  Author(s): Hirokazu Kato, Philip Lamb
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */
/*
    thread_sub.c, thread_sub.h

    Written by Hirokazu Kato
    kato@is.naist.jp   Apr.24 2007
 */

#ifndef __AR6_ARUtil_thread_sub_h__
#define __AR6_ARUtil_thread_sub_h__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _THREAD_HANDLE_T THREAD_HANDLE_T;

//
// Client-side.
//

// Setup.
THREAD_HANDLE_T *threadInit( int ID, void *arg, void *(*start_routine)(THREAD_HANDLE_T*) ); // Create a new thread, and launch start_routine() on it. Returns NULL in case of failure.
int threadFree( THREAD_HANDLE_T **flag ); // Frees structures associated with the thread handle pointed to by the location pointed to by flag. Thread should already have terminated (i.e. threadWaitQuit() has returned). Location pointed to by flag is set to NULL. 

// Communication.
int threadStartSignal( THREAD_HANDLE_T *flag ); // Send the worker thread the "start processing" request.
int threadGetStatus( THREAD_HANDLE_T *flag );   // Find out (without waiting) whether a worker has ended. 0 = not started or started but not yet ended, 1 = ended.
int threadGetBusyStatus( THREAD_HANDLE_T *flag ); // Find out if a worker is currently busy. 0 = worker not started or worker ended, 1 = worker started but not yet ended.
int threadEndWait( THREAD_HANDLE_T *flag );     // Wait for thread to end processing.
int threadWaitQuit( THREAD_HANDLE_T *flag );    // Tell a thread waiting for the "start processing" request to quit (exit), and wait until this has happened.

// Example client structure:
//
//    THREAD_HANDLE_T *threadHandle = threadInit(0, NULL, worker);
//    if (!threadHandle) {
//        fprintf(stderr, "Error starting thread.\n");
//        exit(-1);
//    }
//
//    // Ready to do some work:
//    threadStartSignal(threadHandle);
//
//    // Wait for the results.
//    threadEndWait(threadHandle);
//
//    // If all done, quit and cleanup.
//    threadWaitQuit(threadHandle);
//    threadFree(&threadHandle);

//
// Worker-side.
//
    
int threadStartWait( THREAD_HANDLE_T *flag );   // Wait for the "start processing" request. Returns 0 if worker should start, or -1 if worker should quit (exit).
int threadEndSignal( THREAD_HANDLE_T *flag );   // Notify anyone waiting that the worker has ended.
int threadGetID( THREAD_HANDLE_T *flag );       // Get the 'ID' value passed to the thread's start routine.
void *threadGetArg( THREAD_HANDLE_T *flag );    // Get the 'arg' value passed to the thread's start routine.

// Example worker structure:
//
//    void *worker(THREAD_HANDLE_T *threadHandle)
//    {
//        void *arg = threadHandle->arg; // Get data passed to the worker.
//        while (threadStartWait(threadHandle) == 0) {
//            // Do work, probably on arg.
//            threadEndSignal(threadHandle);
//        }
//        // Do cleanup.
//        return (NULL);
//    }

int threadGetCPU(void); // Returns the number of online CPUs in the system.


#ifdef __cplusplus
}
#endif
#endif // !__AR6_ARUtil_thread_sub_h__
