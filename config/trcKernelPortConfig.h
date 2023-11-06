/*
 * Trace Recorder for Tracealyzer v4.8.1
 * Copyright 2023 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Configuration parameters for the kernel port.
 * More settings can be found in trcKernelPortStreamingConfig.h.
 */

#ifndef TRC_KERNEL_PORT_CONFIG_H
#define TRC_KERNEL_PORT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def TRC_USE_TRACEALYZER_RECORDER
 * @brief Enables/Disables the recorder.
 */
#define TRC_USE_TRACEALYZER_RECORDER 1

/**
 * @brief Board CPU clock frequency in Hz. Must be changed from 0.
 */
#define TRC_CFG_CPU_CLOCK_HZ 0

#if(TRC_CFG_CPU_CLOCK_HZ == 0)
#error "TRC_CFG_CPU_CLOCK_HZ needs to be set to the CPU frequency."
#endif

#ifdef __cplusplus
}
#endif

#endif /* TRC_KERNEL_PORT_CONFIG_H */
