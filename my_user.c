#include <stdio.h>

#include "maks.h"

void print_structs(const struct maks_transfer_struct * trans) {
    printf("\nData of signal_struct:\n"); 
    printf("sigcnt: %d\n", trans->sigcnt);
    printf("nr_threads: %d\n", trans->nr_threads);
    printf("group_exit_code: %d\n", trans->group_exit_code);
    printf("notify_count: %d\n", trans->notify_count);
    printf("group_stop_count: %d\n", trans->group_stop_count);
    printf("flags: %u\n", trans->flags);
    printf("leader: %d\n", trans->leader);
    printf("utime: %ld\n", trans->utime);
    printf("stime: %ld\n", trans->stime);
    printf("cutime: %ld\n", trans->cutime);
    printf("cstime: %ld\n", trans->cstime);
    printf("gtime: %ld\n", trans->gtime);
    printf("cgtime: %ld\n", trans->cgtime);
    printf("sum_sched_runtime: %llu\n", trans->sum_sched_runtime);

    printf("\nData of task_cputime:\n\n"); 
    printf("utime: %ld\n", trans->task_cpu_time_utime);
    printf("stime: %ld\n", trans->task_cpu_time_stime);
    unsigned long long sum_exec_runtime = 
    (unsigned long long) trans->task_cpu_time_utime + trans->task_cpu_time_stime;
    printf("sum_exec_runtime: %llu\n", sum_exec_runtime);

}

int main(int argc, char **argv) {
    struct maks_transfer_struct trans;

    if (argc != 2){
        printf("Program need 1 argument: pid.\n");
        return -1;
    }

    char fproc_name[] = "/proc/maks_module";

    FILE * fproc;
    if ( (fproc = fopen( fproc_name, "w+" )) == NULL ) {
        fprintf( stderr, "Error: can't open file %s for writing", fproc_name );
        return -1;
    }

    fprintf( fproc, "%s", argv[1] );
    printf( "PID: %s\n", argv[1] );
    
    fclose( fproc );
    if ( (fproc = fopen( fproc_name, "r+" )) == NULL ) {
        fprintf( stderr, "Error: can't open file %s for reading", fproc_name );
        return -1;
    }

    uint8_t c = 0;
    uint8_t * address = (uint8_t *) &trans;
    for (int i = 0; i < sizeof(struct maks_transfer_struct) && c != EOF; i++){
        c = getc(fproc);
        * (address + i) = c;
    }

    fclose( fproc );

    print_structs(&trans);
    return 0;
}