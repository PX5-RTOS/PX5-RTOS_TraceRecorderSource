/*
 * Trace Recorder for Tracealyzer v4.8.1
 * Copyright 2023 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * The PX5 specific parts needed by the trace recorder
 */

#ifndef TRC_KERNEL_PORT_H
#define TRC_KERNEL_PORT_H

#include <trcRecorder.h>
#include "px5_time.h"

#if (TRC_USE_TRACEALYZER_RECORDER == 1)

#ifdef __cplusplus
extern "C" {
#endif

#if (TRC_CFG_RECORDER_BUFFER_ALLOCATION == TRC_RECORDER_BUFFER_ALLOCATION_DYNAMIC)
#error "Dynamic allocation not supported, only static."
#endif

/**
 * @def TRACE_KERNEL_VERSION
 * @brief This defines the kernel version/identity.
 */
#define TRACE_KERNEL_VERSION 0x1FF1
    
/**
 * @def TRC_TICK_RATE_HZ
 * @brief Trace RTOS tick rate in Hz.
 */
#define TRC_TICK_RATE_HZ PX5_TICKS_PER_SECOND

/**
 * @def TRACE_CPU_CLOCK_HZ
 * @brief Trace CPU clock speed in Hz.
 */
#define TRACE_CPU_CLOCK_HZ TRC_CFG_CPU_CLOCK_HZ

/**
 * @def TRC_PLATFORM_CFG
 * @brief This defines the basis for version specific lookup of
 * platform configuration files. If left empty the default
 * RTOS XML files are used.
 */
#define TRC_PLATFORM_CFG "PX5"

/**
 * @def TRC_PLATFORM_CFG_MAJOR
 * @brief Major release version for recorder.
 */
#define TRC_PLATFORM_CFG_MAJOR 1
    
/**
 * @def TRC_PLATFORM_CFG_MINOR
 * @brief Minor release version for recorder.
 */
#define TRC_PLATFORM_CFG_MINOR 0

/**
 * @def TRC_PLATFORM_CFG_PATCH
 * @brief Patchlevel release version for recorder.
 */
#define TRC_PLATFORM_CFG_PATCH 0

/**
 * @internal The kernel port data buffer
 */
typedef struct TraceKernelPortDataBuffer
{
	TraceUnsignedBaseType_t buffer;
} TraceKernelPortDataBuffer_t;

/**
 * @internal Initializes the kernel port
 * 
 * @param[in] pxBuffer Kernel port data buffer
 *
 * @retval TRC_FAIL Failure
 * @retval TRC_SUCCESS Success
 */
traceResult xTraceKernelPortInitialize(TraceKernelPortDataBuffer_t* const pxBuffer);

/**
 * @internal Enables the kernel port
 * 
 * @retval TRC_FAIL Failure
 * @retval TRC_SUCCESS Success
 */
traceResult xTraceKernelPortEnable(void);

/**
 * @internal Query if scheduler is suspended. For PX5 this will always be false.
 *
 * @retval 1 Scheduler suspended
 * @retval 0 Scheduler not suspended
 */
#define xTraceKernelPortIsSchedulerSuspended() (0U)

/******************************************************************************/
/*** Definitions for Streaming mode *******************************************/
/******************************************************************************/
#if (TRC_CFG_RECORDER_MODE == TRC_RECORDER_MODE_STREAMING)

/*******************************************************************************
 * PX5 extension function declarations.
 ******************************************************************************/

void px5_system_trace_thread_exit_extension();
void px5_system_trace_api_extension(int, void *, void *, void *);
int px5_trace_context_switch_pending_check();

/*******************************************************************************
 * PX5 extension macros.
 ******************************************************************************/

/* Determines if a context-switch is pending; to be passed to xTraceISREnd().  */
#define PX5_TRACE_CONTEXT_SWITCH_PENDING_CHECK \
    px5_trace_context_switch_pending_check()


#define PX5_PTHREAD_START_POST_EXTENSION \
    xTraceObjectRegisterWithoutHandle(PSF_EVENT_PTHREAD_CREATE, \
                                      &px5_globals.main_thread, \
                                      px5_globals.main_thread.name, \
                                      px5_globals.main_thread.priority); \
    xTraceTaskReady(&px5_globals.main_thread); \
    xTraceTaskSwitch(&px5_globals.main_thread, px5_globals.main_thread.priority);


#define PX5_SYSTEM_TRACE_THREAD_READY_EXTENSION(a, b, c, d) \
    xTraceTaskReady(b);


#define PX5_SYSTEM_TRACE_THREAD_ENTER_EXTENSION(a, b, c, d) \
    xTraceTaskSwitch((void *)b, b -> priority);


#define PX5_SYSTEM_TRACE_THREAD_EXIT_EXTENSION(a, b, c, d) \
    px5_system_trace_thread_exit_extension();


#define PX5_SYSTEM_TRACE_API_EXTENSION(a, b, c, d) \
    px5_system_trace_api_extension(a, (void *)b, (void *)c, (void *)d);


/*******************************************************************************
 * The event codes - should match the offline config file.
 ******************************************************************************/

/*** Event codes for streaming - should match the Tracealyzer config file *****/

/* Tracealyzer events. */

#define PSF_EVENT_NULL_EVENT								    0UL
#define PSF_EVENT_TRACE_START								    1UL
#define PSF_EVENT_TS_CONFIG								        2UL
#define PSF_EVENT_OBJ_NAME								        3UL
#define PSF_EVENT_TASK_PRIORITY								    4UL
#define PSF_EVENT_DEFINE_ISR								    5UL
#define PSF_EVENT_TASK_CREATE							        30UL
#define PSF_EVENT_TASK_DELETE							        31UL
#define PSF_EVENT_TASK_READY								    32UL
#define PSF_EVENT_ISR_BEGIN								        33UL
#define PSF_EVENT_ISR_RESUME							        34UL
#define PSF_EVENT_TS_BEGIN								        35UL
#define PSF_EVENT_TS_RESUME								        36UL
#define PSF_EVENT_TASK_ACTIVATE								    37UL
#define PSF_EVENT_MALLOC									    48UL
#define PSF_EVENT_FREE										    49UL
#define PSF_EVENT_MALLOC_FAILED								    50UL
#define PSF_EVENT_FREE_FAILED								    51UL
#define PSF_EVENT_LOWPOWER_BEGIN							    56UL
#define PSF_EVENT_LOWPOWER_END								    57UL
#define PSF_EVENT_STATEMACHINE_STATE_CREATE					    64UL
#define PSF_EVENT_STATEMACHINE_CREATE						    65UL
#define PSF_EVENT_STATEMACHINE_STATECHANGE					    66UL
#define PSF_EVENT_INTERVAL_CHANNEL_CREATE					    67UL
#define PSF_EVENT_INTERVAL_START							    68UL
#define PSF_EVENT_INTERVAL_STOP								    69UL
#define PSF_EVENT_INTERVAL_CHANNEL_SET_CREATE				    70UL
#define PSF_EVENT_EXTENSION_CREATE							    71UL
#define PSF_EVENT_HEAP_CREATE								    72UL
#define PSF_EVENT_COUNTER_CREATE							    73UL
#define PSF_EVENT_COUNTER_CHANGE							    74UL
#define PSF_EVENT_COUNTER_LIMIT_EXCEEDED					    75UL
#define PSF_EVENT_DEPENDENCY_REGISTER						    76UL
#define PSF_EVENT_RUNNABLE_REGISTER							    77UL
#define PSF_EVENT_RUNNABLE_START							    78UL
#define PSF_EVENT_RUNNABLE_STOP								    79UL
#define PSF_EVENT_USER_EVENT								    80UL
#define PSF_EVENT_USER_EVENT_FIXED							    88UL

/* PX5 API events.  */

#define PSF_EVENT_CLOCK_GETRES                                  1000UL
#define PSF_EVENT_CLOCK_GETTIME                                 1001UL
#define PSF_EVENT_CLOCK_SETTIME                                 1002UL
#define PSF_EVENT_MQ_CLOSE                                      1003UL
#define PSF_EVENT_MQ_GETATTR                                    1004UL
#define PSF_EVENT_MQ_OPEN                                       1005UL
#define PSF_EVENT_MQ_RECEIVE                                    1006UL
#define PSF_EVENT_MQ_SEND                                       1007UL
#define PSF_EVENT_MQ_SETATTR                                    1008UL
#define PSF_EVENT_MQ_TIMEDRECEIVE                               1009UL
#define PSF_EVENT_MQ_TIMEDSEND                                  1010UL
#define PSF_EVENT_NANOSLEEP                                     1011UL
#define PSF_EVENT_PTHREAD_ATTR_DESTROY                          1012UL
#define PSF_EVENT_PTHREAD_ATTR_GETDETACHSTATE                   1013UL
#define PSF_EVENT_PTHREAD_ATTR_GETSTACKADDR                     1014UL
#define PSF_EVENT_PTHREAD_ATTR_GETSTACKSIZE                     1015UL
#define PSF_EVENT_PTHREAD_ATTR_INIT                             1016UL
#define PSF_EVENT_PTHREAD_ATTR_SETDETACHSTATE                   1017UL
#define PSF_EVENT_PTHREAD_ATTR_SETSTACKADDR                     1018UL
#define PSF_EVENT_PTHREAD_ATTR_SETSTACKSIZE                     1019UL
#define PSF_EVENT_PTHREAD_CANCEL                                1020UL
#define PSF_EVENT_PTHREAD_CLEANUP_POP                           1021UL
#define PSF_EVENT_PTHREAD_CLEANUP_PUSH                          1022UL
#define PSF_EVENT_PTHREAD_COND_BROADCAST                        1023UL
#define PSF_EVENT_PTHREAD_COND_DESTROY                          1024UL
#define PSF_EVENT_PTHREAD_COND_INIT                             1025UL
#define PSF_EVENT_PTHREAD_COND_SIGNAL                           1026UL
#define PSF_EVENT_PTHREAD_COND_TIMEDWAIT                        1027UL
#define PSF_EVENT_PTHREAD_COND_WAIT                             1028UL
#define PSF_EVENT_PTHREAD_CONDATTR_DESTROY                      1029UL
#define PSF_EVENT_PTHREAD_CONDATTR_GETPSHARED                   1030UL
#define PSF_EVENT_PTHREAD_CONDATTR_INIT                         1031UL
#define PSF_EVENT_PTHREAD_CONDATTR_SETPSHARED                   1032UL
#define PSF_EVENT_PTHREAD_CREATE                                1033UL
#define PSF_EVENT_PTHREAD_DETACH                                1034UL
#define PSF_EVENT_PTHREAD_EQUAL                                 1035UL
#define PSF_EVENT_PTHREAD_EXIT                                  1036UL
#define PSF_EVENT_PTHREAD_GETAFFINITY_NP                        1037UL
#define PSF_EVENT_PTHREAD_JOIN                                  1038UL
#define PSF_EVENT_PTHREAD_KILL                                  1039UL
#define PSF_EVENT_PTHREAD_MUTEX_DESTROY                         1040UL
#define PSF_EVENT_PTHREAD_MUTEX_INIT                            1041UL
#define PSF_EVENT_PTHREAD_MUTEX_LOCK                            1042UL
#define PSF_EVENT_PTHREAD_MUTEX_TRYLOCK                         1043UL
#define PSF_EVENT_PTHREAD_MUTEX_UNLOCK                          1044UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_DESTROY                     1045UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_GETPROTOCOL                 1046UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_GETPSHARED                  1047UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_GETTYPE                     1048UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_INIT                        1049UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_SETPROTOCOL                 1050UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_SETPSHARED                  1051UL
#define PSF_EVENT_PTHREAD_MUTEXATTR_SETTYPE                     1052UL
#define PSF_EVENT_PTHREAD_SELF                                  1053UL
#define PSF_EVENT_PTHREAD_SETAFFINITY_NP                        1054UL
#define PSF_EVENT_PTHREAD_SETCANCELSTATE                        1055UL
#define PSF_EVENT_PTHREAD_SETCANCELTYPE                         1056UL
#define PSF_EVENT_PTHREAD_SIGMASK                               1057UL
#define PSF_EVENT_PTHREAD_TESTCANCEL                            1058UL
#define PSF_EVENT_PX5_ERRNO_GET                                 1059UL
#define PSF_EVENT_PX5_ERRNO_SET                                 1060UL
#define PSF_EVENT_PX5_MQ_EXTEND_OPEN                            1061UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_DESTROY                     1062UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_GETCONTROLADDR              1063UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_GETCONTROLSIZE              1064UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_GETQUEUEADDR                1065UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_GETQUEUESIZE                1066UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_INIT                        1067UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_SETCONTROLADDR              1068UL
#define PSF_EVENT_PX5_MQ_EXTENDATTR_SETQUEUEADDR                1069UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_GETCONTROLADDR               1070UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_GETCONTROLSIZE               1071UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_GETNAME                      1072UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_GETPRIORITY                  1073UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_GETTIMESLICE                 1074UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_SETCONTROLADDR               1075UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_SETNAME                      1076UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_SETPRIORITY                  1077UL
#define PSF_EVENT_PX5_PTHREAD_ATTR_SETTIMESLICE                 1078UL
#define PSF_EVENT_PX5_PTHREAD_CONDATTR_GETCONTROLADDR           1079UL
#define PSF_EVENT_PX5_PTHREAD_CONDATTR_GETCONTROLSIZE           1080UL
#define PSF_EVENT_PX5_PTHREAD_CONDATTR_GETNAME                  1081UL
#define PSF_EVENT_PX5_PTHREAD_CONDATTR_SETCONTROLADDR           1082UL
#define PSF_EVENT_PX5_PTHREAD_CONDATTR_SETNAME                  1083UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_CLEAR                 1084UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_CREATE                1085UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_DESTROY               1086UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_SET                   1087UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_TIMEDWAIT             1088UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_TRYWAIT               1089UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGS_WAIT                  1090UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_DESTROY           1091UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLADDR    1092UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETCONTROLSIZE    1093UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_GETNAME           1094UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_INIT              1095UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_SETCONTROLADDR    1096UL
#define PSF_EVENT_PX5_PTHREAD_EVENT_FLAGSATTR_SETNAME           1097UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_CREATE                  1098UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_DESTROY                 1099UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_RECEIVE                 1100UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_SEND                    1101UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TIMEDRECEIVE            1102UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TIMEDSEND               1103UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TRYRECEIVE              1104UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUE_TRYSEND                 1105UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_DESTROY             1106UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLADDR      1107UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETCONTROLSIZE      1108UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETNAME             1109UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETQUEUEADDR        1110UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_GETQUEUESIZE        1111UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_INIT                1112UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETCONTROLADDR      1113UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETNAME             1114UL
#define PSF_EVENT_PX5_PTHREAD_FASTQUEUEATTR_SETQUEUEADDR        1115UL
#define PSF_EVENT_PX5_PTHREAD_INFORMATION_GET                   1116UL
#define PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_ENABLE             1117UL
#define PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_GET                1118UL
#define PSF_EVENT_PX5_PTHREAD_MEMORY_MANAGER_SET                1119UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_ALLOCATE               1120UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_CREATE                 1121UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_DESTROY                1122UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_FREE                   1123UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_TIMEDALLOCATE          1124UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOL_TRYALLOCATE            1125UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_DESTROY            1126UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLADDR     1127UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETCONTROLSIZE     1128UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_GETNAME            1129UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_INIT               1130UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_SETCONTROLADDR     1131UL
#define PSF_EVENT_PX5_PTHREAD_MEMORYPOOLATTR_SETNAME            1132UL
#define PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETCONTROLADDR          1133UL
#define PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETCONTROLSIZE          1134UL
#define PSF_EVENT_PX5_PTHREAD_MUTEXATTR_GETNAME                 1135UL
#define PSF_EVENT_PX5_PTHREAD_MUTEXATTR_SETCONTROLADDR          1136UL
#define PSF_EVENT_PX5_PTHREAD_MUTEXATTR_SETNAME                 1137UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_ALLOCATE            1138UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_CREATE              1139UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_DESTROY             1140UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_FREE                1141UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_TIMEDALLOCATE       1142UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOL_TRYALLOCATE         1143UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_DESTROY         1144UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLADDR  1145UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETCONTROLSIZE  1146UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_GETNAME         1147UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_INIT            1148UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_SETCONTROLADDR  1149UL
#define PSF_EVENT_PX5_PTHREAD_PARTITIONPOOLATTR_SETNAME         1150UL
#define PSF_EVENT_PX5_PTHREAD_PRIORITY_CHANGE                   1151UL
#define PSF_EVENT_PX5_PTHREAD_RESUME                            1152UL
#define PSF_EVENT_PX5_PTHREAD_STACK_CHECK                       1153UL
#define PSF_EVENT_PX5_PTHREAD_START                             1154UL
#define PSF_EVENT_PX5_PTHREAD_SUSPEND                           1155UL
#define PSF_EVENT_PX5_PTHREAD_TICK_SLEEP                        1156UL
#define PSF_EVENT_PX5_PTHREAD_TICKS_GET                         1157UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMER_CREATE                  1158UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMER_DESTROY                 1159UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMER_START                   1160UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMER_STOP                    1161UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMER_UPDATE                  1162UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_DESTROY             1163UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETCONTROLADDR      1164UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETCONTROLSIZE      1165UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_GETNAME             1166UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_INIT                1167UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_SETCONTROLADDR      1168UL
#define PSF_EVENT_PX5_PTHREAD_TICKTIMERATTR_SETNAME             1169UL
#define PSF_EVENT_PX5_SEM_EXTEND_INIT                           1170UL
#define PSF_EVENT_PX5_SEM_TICKWAIT                              1171UL
#define PSF_EVENT_PX5_SEMATTR_DESTROY                           1172UL
#define PSF_EVENT_PX5_SEMATTR_GETCONTROLADDR                    1173UL
#define PSF_EVENT_PX5_SEMATTR_GETCONTROLSIZE                    1174UL
#define PSF_EVENT_PX5_SEMATTR_GETNAME                           1175UL
#define PSF_EVENT_PX5_SEMATTR_INIT                              1176UL
#define PSF_EVENT_PX5_SEMATTR_SETCONTROLADDR                    1177UL
#define PSF_EVENT_PX5_SEMATTR_SETNAME                           1178UL
#define PSF_EVENT_SCHED_YIELD                                   1179UL
#define PSF_EVENT_SEM_DESTROY                                   1180UL
#define PSF_EVENT_SEM_INIT                                      1181UL
#define PSF_EVENT_SEM_POST                                      1182UL
#define PSF_EVENT_SEM_TIMEDWAIT                                 1183UL
#define PSF_EVENT_SEM_TRYWAIT                                   1184UL
#define PSF_EVENT_SEM_WAIT                                      1185UL
#define PSF_EVENT_SIGACTION                                     1186UL
#define PSF_EVENT_SIGADDSET                                     1187UL
#define PSF_EVENT_SIGDELSET                                     1188UL
#define PSF_EVENT_SIGEMPTYSET                                   1189UL
#define PSF_EVENT_SIGFILLSET                                    1190UL
#define PSF_EVENT_SIGISMEMBER                                   1191UL
#define PSF_EVENT_SIGPENDING                                    1192UL
#define PSF_EVENT_SIGTIMEDWAIT                                  1193UL
#define PSF_EVENT_SIGWAIT                                       1194UL
#define PSF_EVENT_SIGWAITINFO                                   1195UL
#define PSF_EVENT_SLEEP                                         1196UL
#define PSF_EVENT_TIME                                          1197UL
#define PSF_EVENT_USLEEP                                        1198UL

#define TRC_EVENT_LAST_ID									    1199UL

#endif
    
#endif

#ifdef __cplusplus
}
#endif

#endif /* TRC_KERNEL_PORT_H */
