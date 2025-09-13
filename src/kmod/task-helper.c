/*
 * Copyright 2016-2020 VMware, Inc.
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#define DS_MYSUBSYS (DS_PROC)
#include "priv.h"

pid_t gettid(struct task_struct *task)
{
	return task->pid; // this is the thread id
}

pid_t getpid(struct task_struct *task)
{
	return task->tgid;
}

pid_t getppid(struct task_struct *task)
{
	if (task->real_parent) // @@review: use parent?
	{
		return getpid(task->real_parent);
	}
	PR_DEBUG("no parent for task %d", getpid(task));
	return -1;
}

struct task_struct *cb_find_task(pid_t pid)
{
	struct task_struct *task = NULL;

	rcu_read_lock();
	task = CB_RESOLVED(find_task_by_vpid)(pid);
	rcu_read_unlock();

	return task;
}
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,0,0)
void get_starttime(struct timespec *start_time)

{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,18,0)
    struct timespec64 current_time64;
    
    // 内核 4.18+ 使用新的 API
    ktime_get_real_ts64(&current_time64);
    
    // 转换 timespec64 到 timespec（如果需要保持兼容）
    start_time->tv_sec = current_time64.tv_sec;
    start_time->tv_nsec = current_time64.tv_nsec;
#else
    struct timespec current_time;
    
    // 旧内核使用传统 API
    getnstimeofday(&current_time);
    set_normalized_timespec(start_time, current_time.tv_sec,
                          current_time.tv_nsec);
#endif
}
#endif