#pragma once
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include "timespan.h"

#define TicksPerMillisecond 10000
#define TicksPerSecond TicksPerMillisecond * 1000

// "Frequency" stores the frequency of the high-resolution performance counter, 
// if one exists. Otherwise it will store TicksPerSecond. 
// The frequency cannot change while the system is running,
// so we only need to initialize it once. 
#define Frequency 1000000L
static bool IsHighResolution = true;
// performance-counter frequency, in counts per ticks.
// This can speed up conversion from high frequency performance-counter 
// to ticks. 
static double tickFrequency = TicksPerSecond / Frequency;

typedef struct Stopwatch Stopwatch;

typedef struct Stopwatch
{
    long elapsed;
    uint64_t startTimeStamp;
    bool isRunning;
    
} Stopwatch;

static inline 
uint64_t GetTimestamp() {

    struct timeval t;     
    gettimeofday(&t, nullptr);

    uint64_t ts = t.tv_sec;
    uint64_t us = t.tv_usec;
    return (ts * 1000000L) + us;
}

/**
 * Start
 */
static inline
void Stopwatch_Start(Stopwatch* this) {
    if (!this->isRunning) {
        this->startTimeStamp = GetTimestamp();
        this->isRunning = true;
    }
}

/**
 * GetRawElapsedTicks
 * 
 * Get the elapsed ticks.
 */
static inline
long Stopwatch_GetRawElapsedTicks(Stopwatch* this) {
    long timeElapsed = this->elapsed;

    if (this->isRunning) {
        // If the Stopwatch is running, add elapsed time since
        // the Stopwatch is started last time. 
        uint64_t currentTimeStamp = GetTimestamp();                 
        uint64_t elapsedUntilNow = currentTimeStamp - this->startTimeStamp;
        timeElapsed += (long)elapsedUntilNow;
    }
    return timeElapsed;
}   

/**
 * GetElapsedDateTimeTicks
 * 
 * Get the elapsed ticks.
 */         
static inline
long Stopwatch_GetElapsedDateTimeTicks(Stopwatch* this) {
    long rawTicks = Stopwatch_GetRawElapsedTicks(this);
    if( IsHighResolution) {
        // convert high resolution perf counter to DateTime ticks
        double dticks = rawTicks;
        dticks *= tickFrequency;
        return (long)dticks;                        
    }
    else {
        return rawTicks;
    }
}   

/**
 * Reset
 */
static inline
void Stopwatch_Reset(Stopwatch* this)
{
    this->elapsed = 0;
    this->startTimeStamp = 0;
    this->isRunning = false;
}

/**
 * Restart
 */
static inline
void Stopwatch_Restart(Stopwatch* this)
{
    this->elapsed = 0;
    this->startTimeStamp = GetTimestamp();
    this->isRunning = true;
}

/**
 * IsRunnin
 */
static inline
bool Stopwatch_IsRunning(Stopwatch* this) 
{   
    return this->isRunning;
}

/**
 * Elapsed
 */
static inline
TimeSpan Stopwatch_Elapsed(Stopwatch* this)
{
    TimeSpan value = { .ticks = Stopwatch_GetElapsedDateTimeTicks(this) };
    return value;
}

/**
 * ElapsedMilliseconds
 */
static inline
long Stopwatch_ElapsedMilliseconds(Stopwatch* this) 
{
    return Stopwatch_GetElapsedDateTimeTicks(this)/TicksPerMillisecond;
}

/**
 * ElapsedTicks
 */
static inline
long Stopwatch_ElapsedTicks(Stopwatch* this)
{
    return Stopwatch_GetRawElapsedTicks(this);
}

static inline 
Stopwatch* NewStopwatch() 
{
    Stopwatch* this = malloc(sizeof(Stopwatch));
    Stopwatch_Reset(this);
    return this;
}

static inline
Stopwatch* Stopwatch_StartNew()
{   
    Stopwatch* s = NewStopwatch();
    Stopwatch_Start(s);
    return s;
}