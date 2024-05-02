#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

/**
 *  Low pass filter class
 */
typedef struct
{
    /**
     * @param Tf - Low pass filter time constant
     */

    float Tf; //!< Low pass filter time constant

    float dt; // 0.0f ~ 0.3f(300ms)

    float y_prev; //!< filtered value in previous execution step
} LowPassFilter;

#endif // LOWPASS_FILTER_H