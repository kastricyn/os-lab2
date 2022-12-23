import sys
"""
    В procfs выводим только числа, чтобы они влезли в буффер, а затем здесь всё будем парсить и добавлять пояснения в вывод
    task_cputime, можно либо прямо передать из файла или состолковать здесь из чисел, что лежат в signal_struct (или они дежат в другой структуре? task_struct)

"""
if __name__ =='__main__':
    with file():

    print("dfs")
    print(sys.argv)  

    maks_signal_struct_description = [
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
    ]