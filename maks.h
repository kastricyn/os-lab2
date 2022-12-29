#ifndef maks_h
#define maks_h

#ifndef maks_kernel_build
#include<stdint.h>

typedef uint32_t u32;
typedef uint64_t u64;
#endif //maks_kernel_build

struct maks_transfer_struct{
//	int nop; //only for simple serialization
    int		sigcnt;
    int			nr_threads;
    /* thread group exit support */
	int			group_exit_code;
	/* overloaded:
	 * - notify group_exit_task when ->count is equal to notify_count
	 * - everyone except group_exit_task is stopped during signal delivery
	 *   of fatal signals, group_exit_task processes the signal.
	 */
	int			notify_count;
    /* thread group stop support, overloads group_exit_code too */
	int			group_stop_count;
	unsigned int		flags; /* see SIGNAL_* flags below */
    /* boolean value for session group leader */
	int leader;
    	/*
	 * Cumulative resource counters for dead threads in the group,
	 * and for reaped dead child processes forked by this group.
	 * Live threads maintain their own counters and add to these
	 * in __exit_signal, except for the group leader.
	 */
	u64 utime, stime, cutime, cstime;
	u64 gtime;
	u64 cgtime;
    /*
	 * Cumulative ns of schedule CPU time fo dead threads in the
	 * group, not including a zombie group leader, (This only differs
	 * from jiffies_to_ns(utime + stime) if sched_clock uses something
	 * other than jiffies.)
	 */
	unsigned long long sum_sched_runtime;

	u64 task_cpu_time_stime;
	u64 task_cpu_time_utime;
};

/**
 * struct task_cputime - collected CPU time counts
 * @stime:		time spent in kernel mode, in nanoseconds
 * @utime:		time spent in user mode, in nanoseconds
 * @sum_exec_runtime:	total time spent on the CPU, in nanoseconds
 *
 * This structure groups together three kinds of CPU time that are tracked for
 * threads and thread groups.  Most things considering CPU time want to group
 * these counts together and treat all three of them in parallel.
 */
struct maks_task_cputime{
    u64				stime;
	u64				utime;
	unsigned long long		sum_exec_runtime;
};

#endif // maks_h