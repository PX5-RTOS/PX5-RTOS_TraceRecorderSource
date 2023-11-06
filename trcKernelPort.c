/*
 * Trace Recorder for Tracealyzer v4.8.1
 * Copyright 2023 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * The PX5 specific parts of the trace recorder
 */

#include <stdint.h>
#include <trcRecorder.h>
#include "px5.h"

#if (TRC_USE_TRACEALYZER_RECORDER == 1)

/* Declare the dummy idle thread. This is not a real thread i.e. it is not
   registered with PX5; it is only registered with TraceRecorder for the purposes
   of displaying an idle context in Tracealyzer.  */
static char dummy_idle_thread;

traceResult xTraceKernelPortInitialize(TraceKernelPortDataBuffer_t* const pxBuffer)
{
	return TRC_SUCCESS;
}

traceResult xTraceKernelPortEnable(void)
{
    xTraceTaskRegisterWithoutHandle((void *)&dummy_idle_thread, "IDLE", 0);
	return TRC_SUCCESS;
}

void px5_system_trace_thread_exit_extension()
{
    xTraceTaskSwitch(&dummy_idle_thread, 0);
}

int px5_trace_context_switch_pending_check()
{
    return(px5_globals.executing_thread[PX5_EXECUTING_CORE] !=
           px5_globals.highest_priority_thread[PX5_EXECUTING_CORE] ? 1 : 0);
}

void px5_system_trace_api_extension(int event_id, void *param0, void *param1, void *param2)
{
    switch (event_id)
    {
        case PX5_PTHREAD_START_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_START,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_CLOCK_GETRES_ID:
        xTraceEventCreate2(PSF_EVENT_CLOCK_GETRES,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_CLOCK_GETTIME_ID:
        xTraceEventCreate2(PSF_EVENT_CLOCK_GETTIME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_CLOCK_SETTIME_ID:
        xTraceEventCreate2(PSF_EVENT_CLOCK_SETTIME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_TIME_ID:
        xTraceEventCreate1(PSF_EVENT_TIME,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICKS_GET_ID:
        xTraceEventCreate0(PSF_EVENT_PX5_PTHREAD_TICKS_GET);
        break;

        case PX5_ERRNO_GET_ID:
        xTraceEventCreate0(PSF_EVENT_PX5_ERRNO_GET);
        break;

        case PX5_ERRNO_SET_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_ERRNO_SET,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_ATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETDETACHSTATE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_GETDETACHSTATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETPRIORITY_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_GETPRIORITY,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETSTACKADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_GETSTACKADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETSTACKSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_GETSTACKSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_GETTIMESLICE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_GETTIMESLICE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_ATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_ATTR_SETDETACHSTATE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_SETDETACHSTATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_SETPRIORITY_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_SETPRIORITY,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_SETSTACKADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_SETSTACKADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_SETSTACKSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_ATTR_SETSTACKSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_ATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_ATTR_SETTIMESLICE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_ATTR_SETTIMESLICE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_ATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_ATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PTHREAD_CREATE,
                                          (px5_thread_control *)(*(pthread_t *)param0),
                                          ((px5_thread_control *)(*(pthread_t *)param0)) -> name,
                                          ((px5_thread_control *)(*(pthread_t *)param0)) -> priority);
        break;

        case PX5_PTHREAD_DETACH_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_DETACH,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_CANCEL_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_CANCEL,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_EXIT_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PTHREAD_EXIT,
                                            px5_globals.executing_thread[PX5_EXECUTING_CORE],
                                            (uint32_t)param0);
        break;

        case PX5_PTHREAD_INFORMATION_GET_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_INFORMATION_GET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_JOIN_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_JOIN,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_KILL_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_KILL,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_RESUME_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_RESUME,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_SELF_ID:
        xTraceEventCreate0(PSF_EVENT_PTHREAD_SELF);
        break;

        case PX5_PTHREAD_PRIORITY_CHANGE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_PRIORITY_CHANGE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_SETCANCELSTATE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_SETCANCELSTATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_SETCANCELTYPE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_SETCANCELTYPE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_SIGMASK_ID:
        xTraceEventCreate3(PSF_EVENT_PTHREAD_SIGMASK,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_STACK_CHECK_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_STACK_CHECK,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_SUSPEND_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_SUSPEND,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TESTCANCEL_ID:
        xTraceEventCreate0(PSF_EVENT_PTHREAD_TESTCANCEL);
        break;

        case PX5_PTHREAD_EQUAL_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_EQUAL,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CLEANUP_POP_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_CLEANUP_POP,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_CLEANUP_PUSH_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_CLEANUP_PUSH,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_COND_BROADCAST_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_COND_BROADCAST,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_COND_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PTHREAD_COND_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_COND_INIT_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PTHREAD_COND_INIT,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_condattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_COND_SIGNAL_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_COND_SIGNAL,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_COND_TIMEDWAIT_ID:
        xTraceEventCreate3(PSF_EVENT_PTHREAD_COND_TIMEDWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_COND_WAIT_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_COND_WAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_CONDATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_CONDATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_CONDATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_CONDATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_CONDATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_GETPSHARED_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_CONDATTR_GETPSHARED,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_CONDATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_CONDATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_CONDATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_CONDATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_CONDATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_CONDATTR_SETPSHARED_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_CONDATTR_SETPSHARED,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_CLEAR_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_CLEAR,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_CREATE,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_event_flagsattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_SET_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_SET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_TIMEDWAIT_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_TIMEDWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_TRYWAIT_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_TRYWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_EVENT_FLAGS_WAIT_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_WAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_EVENT_FLAGSATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUE_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_CREATE,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_event_flagsattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUE_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_FASTQUEUE_RECEIVE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_RECEIVE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUE_SEND_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_SEND,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUE_TIMEDRECEIVE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TIMEDRECEIVE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUE_TIMEDSEND_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TIMEDSEND,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUE_TRYRECEIVE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TRYRECEIVE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUE_TRYSEND_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TRYSEND,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_GETQUEUEADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETQUEUEADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_GETQUEUESIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETQUEUESIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_FASTQUEUEATTR_SETQUEUEADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETQUEUEADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MEMORYPOOL_ALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_ALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MEMORYPOOL_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_CREATE,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_event_flagsattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MEMORYPOOL_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_MEMORYPOOL_FREE_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_FREE,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MEMORYPOOL_TRYALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_TRYALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MEMORYPOOLATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEX_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PTHREAD_MUTEX_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_MUTEX_INIT_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PTHREAD_MUTEX_INIT,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_event_flagsattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEX_LOCK_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_MUTEX_LOCK,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MUTEX_TRYLOCK_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_MUTEX_TRYLOCK,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MUTEX_UNLOCK_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_MUTEX_UNLOCK,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MUTEXATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_MUTEXATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETPROTOCOL_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_GETPROTOCOL,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETPSHARED_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_GETPSHARED,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_GETTYPE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_GETTYPE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PTHREAD_MUTEXATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MUTEXATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_MUTEXATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_MUTEXATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MUTEXATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_SETPROTOCOL_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_SETPROTOCOL,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_SETPSHARED_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_SETPSHARED,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MUTEXATTR_SETTYPE_ID:
        xTraceEventCreate2(PSF_EVENT_PTHREAD_MUTEXATTR_SETTYPE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_ALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_ALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_CREATE,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_event_flagsattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_FREE_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_FREE,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_TIMEDALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_TIMEDALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_PARTITIONPOOL_TRYALLOCATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_TRYALLOCATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_PARTITIONPOOLATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_TICKTIMER_CREATE_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_TICKTIMER_CREATE,
                                          param0,
                                          param1 == 0 ? (void *)0 : ((pthread_ticktimerattr_t *)param1) -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_TICKTIMER_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_PX5_PTHREAD_TICKTIMER_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_PTHREAD_TICKTIMER_START_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_TICKTIMER_START,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICKTIMER_STOP_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_TICKTIMER_STOP,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICKTIMER_UPDATE_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_TICKTIMER_UPDATE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_PTHREAD_TICKTIMERATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEM_DESTROY_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_SEM_DESTROY,
                                            param0,
                                            0);
        break;

        case PX5_SEM_EXTEND_INIT_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_SEM_EXTEND_INIT,
                                          param0,
                                          ((sem_t *)param0) -> internal_semaphore_control -> name,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEM_INIT_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_SEM_INIT,
                                          param0,
                                          NULL,
                                          (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEM_POST_ID:
        xTraceEventCreate1(PSF_EVENT_SEM_POST,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SEM_TICKWAIT_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_SEM_TICKWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEM_TIMEDWAIT_ID:
        xTraceEventCreate2(PSF_EVENT_SEM_TIMEDWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEM_TRYWAIT_ID:
        xTraceEventCreate1(PSF_EVENT_SEM_TRYWAIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SEM_WAIT_ID:
        xTraceEventCreate1(PSF_EVENT_SEM_WAIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SEMATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_SEMATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SEMATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_SEMATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEMATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_SEMATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEMATTR_GETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_SEMATTR_GETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SEMATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_SEMATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SEMATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_SEMATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_SEMATTR_SETNAME_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_SEMATTR_SETNAME,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SIGACTION_ID:
        xTraceEventCreate3(PSF_EVENT_SIGACTION,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_SIGADDSET_ID:
        xTraceEventCreate2(PSF_EVENT_SIGADDSET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SIGDELSET_ID:
        xTraceEventCreate2(PSF_EVENT_SIGDELSET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SIGEMPTYSET_ID:
        xTraceEventCreate1(PSF_EVENT_SIGEMPTYSET,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SIGFILLSET_ID:
        xTraceEventCreate1(PSF_EVENT_SIGFILLSET,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SIGISMEMBER_ID:
        xTraceEventCreate2(PSF_EVENT_SIGISMEMBER,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SIGPENDING_ID:
        xTraceEventCreate1(PSF_EVENT_SIGPENDING,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_SIGTIMEDWAIT_ID:
        xTraceEventCreate3(PSF_EVENT_SIGTIMEDWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_SIGWAIT_ID:
        xTraceEventCreate2(PSF_EVENT_SIGWAIT,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SIGWAITINFO_ID:
        xTraceEventCreate2(PSF_EVENT_SIGWAITINFO,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_CLOSE_ID:
        xTraceObjectUnregisterWithoutHandle(PSF_EVENT_MQ_CLOSE,
                                            param0,
                                            0);
        break;

        case PX5_MQ_EXTEND_OPEN_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_PX5_MQ_EXTEND_OPEN,
                                          param0,
                                          (char *)param1,
                                          (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_EXTENDATTR_DESTROY_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_MQ_EXTENDATTR_DESTROY,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_MQ_EXTENDATTR_GETCONTROLADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_MQ_EXTENDATTR_GETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_EXTENDATTR_GETCONTROLSIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_MQ_EXTENDATTR_GETCONTROLSIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_EXTENDATTR_GETQUEUEADDR_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_MQ_EXTENDATTR_GETQUEUEADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_EXTENDATTR_GETQUEUESIZE_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_MQ_EXTENDATTR_GETQUEUESIZE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_EXTENDATTR_INIT_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_MQ_EXTENDATTR_INIT,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_MQ_EXTENDATTR_SETCONTROLADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_MQ_EXTENDATTR_SETCONTROLADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_EXTENDATTR_SETQUEUEADDR_ID:
        xTraceEventCreate3(PSF_EVENT_PX5_MQ_EXTENDATTR_SETQUEUEADDR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_GETATTR_ID:
        xTraceEventCreate2(PSF_EVENT_MQ_GETATTR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_MQ_OPEN_ID:
        xTraceObjectRegisterWithoutHandle(PSF_EVENT_MQ_OPEN,
                                          param0,
                                          (char *)param1,
                                          (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_RECEIVE_ID:
        xTraceEventCreate3(PSF_EVENT_MQ_RECEIVE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_SEND_ID:
        xTraceEventCreate3(PSF_EVENT_MQ_SEND,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_SETATTR_ID:
        xTraceEventCreate3(PSF_EVENT_MQ_SETATTR,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_TIMEDRECEIVE_ID:
        xTraceEventCreate3(PSF_EVENT_MQ_TIMEDRECEIVE,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_MQ_TIMEDSEND_ID:
        xTraceEventCreate3(PSF_EVENT_MQ_TIMEDSEND,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1,
                           (TraceUnsignedBaseType_t)param2);
        break;

        case PX5_NANOSLEEP_ID:
        xTraceEventCreate2(PSF_EVENT_NANOSLEEP,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SLEEP_ID:
        xTraceEventCreate1(PSF_EVENT_SLEEP,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_USLEEP_ID:
        xTraceEventCreate1(PSF_EVENT_USLEEP,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_TICK_SLEEP_ID:
        xTraceEventCreate1(PSF_EVENT_PX5_PTHREAD_TICK_SLEEP,
                           (TraceUnsignedBaseType_t)param0);
        break;

        case PX5_PTHREAD_MEMORY_MANAGER_ENABLE_ID:
        xTraceEventCreate0(PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_ENABLE);
        break;

        case PX5_PTHREAD_MEMORY_MANAGER_GET_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_GET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_PTHREAD_MEMORY_MANAGER_SET_ID:
        xTraceEventCreate2(PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_SET,
                           (TraceUnsignedBaseType_t)param0,
                           (TraceUnsignedBaseType_t)param1);
        break;

        case PX5_SCHED_YIELD_ID:
        xTraceEventCreate0(PSF_EVENT_SCHED_YIELD);
        break;
    }
}

#endif
