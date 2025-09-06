/*
 * Copyright 2019-2020 VMware, Inc.
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once
#include <linux/version.h>
#ifdef __KERNEL__
#include <linux/time.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
#include <linux/time64.h>
#include <linux/ktime.h>
#include <linux/types.h>
#endif
#else
#include <sys/types.h>
#include <time.h>
#endif


#pragma pack(push, 1)
struct CB_EVENT_PROCESS_INFO {
	pid_t pid; // Process id for this event

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,18,0)
	time64_t process_start_time; // Windows time the process at 'pid' started
	time64_t event_time; // Windows time this event occurred
	struct timespec64 process_start_time_unix; // Unix time that the process
		// at 'pid' started
	struct timespec64 event_time_unix; // Unix time that this event occurred
#else
	time_t process_start_time; // Windows time the process at 'pid' started
	time_t event_time; // Windows time this event occurred
	struct timespec process_start_time_unix; // Unix time that the process
		// at 'pid' started
	struct timespec event_time_unix; // Unix time that this event occurred
#endif
};
#pragma pack(pop)
