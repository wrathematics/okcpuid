// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Copyright 2013, Schmidt


#include <stdio.h>

#define SINGLE 0
#define DOUBLE 1

#define PLATFORM_SUPPORTED 0
#define PLATFORM_ERROR 1



// Linux
#ifdef __linux__
    #include <sys/sysinfo.h>
    #include <unistd.h>
    
    static int get_ncores(void)
    {
        return sysconf(_SC_NPROCESSORS_ONLN);
    }
    
    #define PLATFORM PLATFORM_SUPPORTED
    
#else
    #define PLATFORM PLATFORM_ERROR
    
#endif



int cpu_hardware_info(double *clock, int *ncpus, int *ncores, int *nthreads)
{
    *ncores = get_ncores();
    
    // these do nothing atm
    *clock = 0.0;
    *ncpus = 0;
    *nthreads = 0;
	
    return PLATFORM;
}


// todo
/*double machine_theoretical_peak(int type)*/
/*{*/
/*    int check;*/
/*    int ncpus, ncores, nthreads, ops_per_cycle;*/
/*    double clock, peak;*/

/*    if (type == SINGLE)*/
/*        ops_per_cycle = 4;*/
/*    else if (type == DOUBLE)*/
/*        ops_per_cycle = 2;*/

/*    check = cpu_hardware_info(&clock, &ncpus, &ncores, &nthreads);*/

/*    if (check == PLATFORM_ERROR)*/
/*        return -1.0;*/

/*    // peak = ncpus * (operand/cycle) * (# cores) * (SSE/core) * (cycles/second)*/
/*    peak = ((double) ncpus * ops_per_cycle * ncores * (nthreads/ncores)) * clock;*/

/*    return peak;*/
/*}*/




int main()
{
    int support;
    int ncpus, ncores, nthreads;
    double clock;
    
    support = cpu_hardware_info(&clock, &ncpus, &ncores, &nthreads);
     
    if (support == PLATFORM_SUPPORTED)
      printf("clock=%f, cpus=%d, ncores=%d, nthreads=%d\n", clock, ncpus, ncores, nthreads);
    else
      printf("platform not supported\n");
    
    return 0;
}
