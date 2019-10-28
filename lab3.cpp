#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <x86intrin.h>
#include <climits>
#include <sys/time.h>
long long int p_count;
static const long double e = 2.72;

/* gettimeofday */
struct timeval tv1,tv2,dtv;
struct timezone tz;

// func's prototypes
/* calc func */
long double einx(unsigned long long int &x);

/* time realizing for gettimeofday() */
void time_start(void);
long double time_stop(void);

/* main time funcs */
long double first_time_check(unsigned long long int &x);  /* clock() */
long double second_time_check(unsigned long long int &x); /* gettimeofday() */
//unsigned int rdtsc(); /* tsc */
long double third_time_check(unsigned long long int &x);

int main(void)
{
    unsigned long long int x = 1488.0;
    while(1)
    {
        std::cin >> p_count;
        if(p_count == 0)
            break;
        first_time_check(x); // clock()
        second_time_check(x); // gettimeofday()
        third_time_check(x);
        std::cout << std::endl;
    }
    return 0;
}

long double einx(unsigned long long int &x)
{
    long double value = 1;
    for(auto i = 1; i <= x; i++)
        value *= e;
    return value;
}

long double first_time_check(unsigned long long int &x)
{
    srand(time(nullptr));
    long double clock_time_start, clock_time_end = 0;
    clock_time_start = clock();
    for(auto i = 0; i < p_count; i++)
        einx(x);
    clock_time_end = clock();
    std::cout <</* "Time(clock) - " <<*/ std::fixed << std::setprecision(10) << (double)(clock_time_end - clock_time_start) / CLOCKS_PER_SEC << "\t";
    return 0;
}

void time_start(void)
{
    gettimeofday(&tv1, &tz);
}

long double time_stop(void)
{
    gettimeofday(&tv2, &tz);
    dtv.tv_sec =  tv2.tv_sec - tv1.tv_sec;
    dtv.tv_usec = tv2.tv_usec- tv1.tv_usec;
    if(dtv.tv_usec < 0)
    {
        dtv.tv_sec--;
        dtv.tv_usec += 1000000;
    }
    return dtv.tv_sec * 1000 + dtv.tv_usec / 1000.0;
}

long double second_time_check(unsigned long long int &x)
{
    time_start();
    for(auto i = 0; i < p_count; i++)
        einx(x);
    std::cout <</* "\t\tTime(gettimeofday) - " <<*/ std::fixed << std::setprecision(10) << (double)time_stop() / 1000.0 << "\t";
    return 0;
}

long double third_time_check(unsigned long long int &x)
{
    __uint64_t start = __rdtsc();
    for(auto i = 0; i < p_count; i++)
        einx(x);
    std::cout <</* "\t\tTime(TSC) - " <<*/ std::fixed << std::setprecision(10) << (double)(__rdtsc() - start) / 2200000000;
    return 0;
}
