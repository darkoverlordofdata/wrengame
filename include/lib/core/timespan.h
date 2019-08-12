#pragma once
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define TicksPerMillisecond  10000.0
#define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
#define TicksPerMinute TicksPerSecond * 60.0         // 600,000,000
#define TicksPerHour TicksPerMinute * 60.0        // 36,000,000,000
#define TicksPerDay TicksPerHour * 24.0          // 864,000,000,000

#define MillisecondsPerTick 1.0 / (TicksPerMillisecond)
#define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001
#define MinutesPerTick 1.0 / (TicksPerMinute) // 1.6666666666667e-9
#define HoursPerTick 1.0 / (TicksPerHour) // 2.77777777777777778e-11
#define DaysPerTick 1.0 / (TicksPerDay) // 1.1574074074074074074e-12
#define MillisPerSecond 1000.0
#define MillisPerMinute (MillisPerSecond) * 60.0 //     60,000
#define MillisPerHour (MillisPerMinute) * 60.0   //  3,600,000
#define MillisPerDay (MillisPerHour) * 24.0      // 86,400,000

#define MaxSeconds INT64_MAX / (TicksPerSecond)
#define MinSeconds INT64_MIN / (TicksPerSecond)
#define MaxMilliSeconds INT64_MAX / TicksPerMillisecond
#define MinMilliSeconds INT64_MIN / TicksPerMillisecond
#define TicksPerTenthSecond (TicksPerMillisecond * 100)


typedef struct TimeSpan TimeSpan;

typedef struct TimeSpan
{
    int64_t ticks;
} TimeSpan;

static inline 
int Days(TimeSpan* this) {
    return (int)((this->ticks / TicksPerDay));
}

static inline 
int Hours(TimeSpan* this) {
    return (int)((this->ticks / TicksPerHour)) % 24;
}

static inline 
int Milliseconds(TimeSpan* this) {
    return (int)((this->ticks / TicksPerMillisecond)) % 1000;
}

static inline 
int Minutes(TimeSpan* this) {
    return (int)((this->ticks / TicksPerMinute)) % 60;
}

static inline 
int Seconds(TimeSpan* this) {
    return (int)((this->ticks / TicksPerSecond)) % 60;
}

static inline 
double TotalDays(TimeSpan* this) {
    return (double)((this->ticks * DaysPerTick));
}


static inline 
double TotalHours(TimeSpan* this) {
    return (double)((this->ticks * HoursPerTick));
}

static inline 
double TotalMilliseconds(TimeSpan this) {
    double temp = (double)(this.ticks * MillisecondsPerTick);
    if (temp > MaxMilliSeconds)
        return (double)MaxMilliSeconds;

    if (temp < MinMilliSeconds)
        return (double)MinMilliSeconds;

    return temp;
}

static inline 
double TotalMinutes(TimeSpan* this) {
    return (double)((this->ticks * MinutesPerTick));
}

static inline 
double TotalSeconds(TimeSpan* this) {
    return (double)((this->ticks * SecondsPerTick));
}

static inline 
void Plus(TimeSpan * this, TimeSpan * rhs) { this->ticks += rhs->ticks; }

static inline
void Minus(TimeSpan* this, TimeSpan * rhs) { this->ticks -= rhs->ticks; }

static inline
TimeSpan Add(TimeSpan * this, TimeSpan * rhs) {
    TimeSpan value = { .ticks = this->ticks + rhs->ticks };
    return value;
}

static inline
TimeSpan Sub(TimeSpan* this, TimeSpan * rhs) { 
    TimeSpan value = { .ticks = this->ticks - rhs->ticks };
    return value;
}

static inline
bool LT(TimeSpan* this, TimeSpan * rhs) {  return this->ticks < rhs->ticks; }

static inline
bool LE(TimeSpan* this, TimeSpan * rhs) { return this->ticks <= rhs->ticks; }

static inline
bool GT(TimeSpan* this, TimeSpan * rhs) { return this->ticks > rhs->ticks; }

static inline
bool GE(TimeSpan* this, TimeSpan * rhs) { return this->ticks >= rhs->ticks; }

static inline
bool NE(TimeSpan* this, TimeSpan * rhs) { return this->ticks != rhs->ticks; }

static inline
bool EQ(TimeSpan* this, TimeSpan * rhs) { return this->ticks == rhs->ticks; }

static inline
TimeSpan Interval(double value, int scale) 
{
    double tmp = value * scale;
    double millis = tmp + (value >= 0? 0.5: -0.5);
    TimeSpan retval = { .ticks = (long)millis * TicksPerMillisecond };
    return retval;
}

static inline
TimeSpan FromHours(double value) 
{
    return Interval(value, MillisPerHour);
}

static inline
TimeSpan FromMinutes(double value) 
{
    return Interval(value, MillisPerMinute);
}

static inline
TimeSpan FromSeconds(double value) 
{
    return Interval(value, MillisPerSecond);
}

static inline
TimeSpan FromMilliseconds(double value) 
{
    return Interval(value, 1);
}

static inline
TimeSpan FromTicks(int64_t value) 
{
    TimeSpan retval = { .ticks = value };
    return retval;
}

static inline 
TimeSpan FromTimeSpec(struct timespec ts)
{
    TimeSpan retval = { .ticks = ts.tv_sec * TicksPerMillisecond + ts.tv_nsec/1000000 };
    return retval;
}

static inline
TimeSpan Duration(TimeSpan* this) {
    // if (this->ticks==MinValue.ticks)
    //     throw exceptions::OverflowException();
    TimeSpan retval = { .ticks = this->ticks >= 0? this->ticks: -this->ticks };
    return retval;
}

static inline
TimeSpan Negate(TimeSpan* this) 
{
    // if (this->ticks==MinValue.ticks)
    //     throw exceptions::OverflowException();
    TimeSpan retval = { .ticks = -this->ticks };
    return retval;
}

static inline 
int64_t Ticks(TimeSpan* this) 
{
    return this->ticks;
}

static inline 
TimeSpan* NewTimeSpan(int64_t ticks) 
{
    TimeSpan* this = malloc(sizeof(TimeSpan));
    this->ticks = ticks;
    return this;
}


static const struct TimeSpan MaxValue = { .ticks = INT64_MAX }; // = new TimeSpan(INT64_MAX);
static const struct TimeSpan MinValue = { .ticks = INT64_MIN }; // = new TimeSpan(INT64_MIN);
static const struct TimeSpan TimeSpan_Zero = { .ticks = 0 }; // = new TimeSpan(0);
