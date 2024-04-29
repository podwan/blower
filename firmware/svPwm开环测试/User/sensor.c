

#include "sensor.h"
// #include "beeper.h"

static unsigned int ntcTemp;
static char ntcErr;
static unsigned char adcChannels[CHN_NUM];

#if PULL_UP
// 上拉10K
const unsigned int rtTable[] = {
    3973,
    3967,
    3961,
    3954,
    3947,
    3940,
    3932,
    3925,
    3917,
    3908,
    3899,
    3890,
    3881,
    3871,
    3861,
    3850,
    3839,
    3828,
    3816,
    3804,
    3792,
    3779,
    3765,
    3752,
    3737,
    3723,
    3708,
    3692,
    3676,
    3660,
    3643,
    3625,
    3607,
    3589,
    3570,
    3551,
    3531,
    3511,
    3490,
    3468,
    3447,
    3424,
    3402,
    3378,
    3355,
    3330,
    3306,
    3281,
    3255,
    3229,
    3203,
    3176,
    3148,
    3120,
    3092,
    3064,
    3035,
    3005,
    2976,
    2946,
    2915,
    2885,
    2854,
    2823,
    2791,
    2759,
    2727,
    2695,
    2663,
    2630,
    2597,
    2565,
    2532,
    2499,
    2465,
    2432,
    2399,
    2365,
    2332,
    2299,
    2265,
    2232,
    2199,
    2166,
    2133,
    2100,
    2067,
    2034,
    2002,
    1970,
    1938,
    1906,
    1874,
    1842,
    1811,
    1780,
    1750,
    1719,
    1689,
    1659,
    1630,
    1600,
    1571,
    1543,
    1515,
    1487,
    1459,
    1432,
    1405,
    1379,
    1353,
    1327,
    1301,
    1276,
    1252,
    1227,
    1204,
    1180,
    1157,
    1134,
    1112,
    1090,
    1068,
    1047,
    1026,
    1005,
    985,
    965,
    946,
    927,
    908,
    890,
    872,
    854,
    837,
    820,
    803,
    787,
    771,
    755,
    739,
    724,
    709,
    695,
    681,
    667,
    653,
    640,
    627,
    614,
    601,
    589,
    577,
    565,
    554,
    543,
    531,
    521,
    510,
    500,
    490,
    480,
    470,
    461,
    451,
    442,
    433,
    425,
    416,
    408,
    400,
    392,
    384,
    376,
    369,
    361,
    354,
    347,
    340,
    334,
    327,
    321,
    315,
    308,
    302,
    297,
    291,
    285,
    280,
    274,
    269,
    264,
    259,
    254,
    249,
    244,
    240,
    235,
    231,
    227,
    222,
    218,
    214,
    210,
    206,
    202,
    199,
    195,
    191,
    188,
    185,
    181,
    178,
    175,
    172,
    168,
    165,
    162,
    160,
    157,
    154,
    151,
    149,
    146,
    143,
    141,
    138,
    136,
    134,
    131,
    129,
    127,
    125,
    123,
    121,
    118,
    116,
    115,
    113,
    111,
    109,
    107,
    105,
    104,
    102,
    100,
    99,
    97,
    95,
    94,
    92,
    91,
    89,
    88,
    86,
    85,
    84,
    82,
    81,
    80,
    79,
    77,
    76,
    75,
    74,
    73,
    72,
    70,
    69,
    68,
    67,
    66,
    65,
};
#else
// 下拉10K
code unsigned int rtTable[] = {
    122,
    128,
    134,
    141,
    148,
    155,
    163,
    170,
    178,
    187,
    196,
    205,
    214,
    224,
    234,
    245,
    256,
    267,
    279,
    291,
    303,
    316,
    330,
    343,
    358,
    372,
    387,
    403,
    419,
    435,
    452,
    470,
    488,
    506,
    525,
    544,
    564,
    584,
    605,
    627,
    648,
    671,
    693,
    717,
    740,
    765,
    789,
    814,
    840,
    866,
    892,
    919,
    947,
    975,
    1003,
    1031,
    1060,
    1090,
    1119,
    1149,
    1180,
    1210,
    1241,
    1272,
    1304,
    1336,
    1368,
    1400,
    1432,
    1465,
    1498,
    1530,
    1563,
    1596,
    1630,
    1663,
    1696,
    1730,
    1763,
    1796,
    1830,
    1863,
    1896,
    1929,
    1962,
    1995,
    2028,
    2061,
    2093,
    2125,
    2157,
    2189,
    2221,
    2253,
    2284,
    2315,
    2345,
    2376,
    2406,
    2436,
    2465,
    2495,
    2524,
    2552,
    2580,
    2608,
    2636,
    2663,
    2690,
    2716,
    2742,
    2768,
    2794,
    2819,
    2843,
    2868,
    2891,
    2915,
    2938,
    2961,
    2983,
    3005,
    3027,
    3048,
    3069,
    3090,
    3110,
    3130,
    3149,
    3168,
    3187,
    3205,
    3223,
    3241,
    3258,
    3275,
    3292,
    3308,
    3324,
    3340,
    3356,
    3371,
    3386,
    3400,
    3414,
    3428,
    3442,
    3455,
    3468,
    3481,
    3494,
    3506,
    3518,
    3530,
    3541,
    3552,
    3564,
    3574,
    3585,
    3595,
    3605,
    3615,
    3625,
    3634,
    3644,
    3653,
    3662,
    3670,
    3679,
    3687,
    3695,
    3703,
    3711,
    3719,
    3726,
    3734,
    3741,
    3748,
    3755,
    3761,
    3768,
    3774,
    3780,
    3787,
    3793,
    3798,
    3804,
    3810,
    3815,
    3821,
    3826,
    3831,
    3836,
    3841,
    3846,
    3851,
    3855,
    3860,
    3864,
    3868,
    3873,
    3877,
    3881,
    3885,
    3889,
    3893,
    3896,
    3900,
    3904,
    3907,
    3910,
    3914,
    3917,
    3920,
    3923,
    3927,
    3930,
    3933,
    3935,
    3938,
    3941,
    3944,
    3946,
    3949,
    3952,
    3954,
    3957,
    3959,
    3961,
    3964,
    3966,
    3968,
    3970,
    3972,
    3974,
    3977,
    3979,
    3980,
    3982,
    3984,
    3986,
    3988,
    3990,
    3991,
    3993,
    3995,
    3996,
    3998,
    4000,
    4001,
    4003,
};
#endif

static unsigned int search4temp(unsigned int adcValue, const unsigned int *table, unsigned int size);

// 每30ms调用
void sensoring()
{

    static unsigned char sampledTimes = 0;
    static unsigned int adcValues[CHN_NUM][4];
    static bool adcChannelsInited = 0;

    // if (ntcSampleLock)
    //     return;

    if (!adcChannelsInited)
    {
        adcChannelsInited = 1;
        adcChannels[0] = 0;
    }

    if (++sampledTimes <= SAMPLE_PERIOD)
    {
        unsigned int value;
        unsigned char i;

        for (i = 0; i < CHN_NUM; i++)
        {
            if (sampledTimes == 1) // 初始化
            {
                adcValues[i][MIN_INDEX] = 0xFFFF;
                adcValues[i][MAX_INDEX] = 0;
                adcValues[i][SUM_INDEX] = 0;
            }

           // value = ADC_SAMPLE_START(adcChannels[i]); // AIN0-P06

            if (adcValues[i][MIN_INDEX] > value)
                adcValues[i][MIN_INDEX] = value;
            if (adcValues[i][MAX_INDEX] < value)
                adcValues[i][MAX_INDEX] = value;
            adcValues[i][SUM_INDEX] += value;
        }

        if (sampledTimes == SAMPLE_PERIOD) // 300ms
        {

            sampledTimes = 0;

            for (i = 0; i < CHN_NUM; i++)
            {

#if SAMPLE_PERIOD == 10
                adcValues[i][AVERAGE_INDEX] = (adcValues[i][SUM_INDEX] - adcValues[i][MIN_INDEX] - adcValues[i][MAX_INDEX]) / 8; // AIN0-P06
#elif SAMPLE_PERIOD == 6
                adcValues[i][AVERAGE_INDEX] = (adcValues[i][SUM_INDEX] - adcValues[i][MIN_INDEX] - adcValues[i][MAX_INDEX]) / 4; // AIN0-P06
#endif
                if (i == 0) // CHN_1
                {
                    static unsigned int recordedTemp = 0;
                    static unsigned int detectedTemp = 0;
                    static unsigned char ntcShortCnt = 0;
                    static unsigned char ntcOpenCnt = 0;
#if PULL_UP
                    if (adcValues[i][AVERAGE_INDEX] > 4090)
                    {
                        ntcShortCnt = 0;
                        if (ntcErr != NTC_OPEN && ++ntcOpenCnt >= 4)
                        {
                            ntcErr = NTC_OPEN;
                        }
                    }
                    else if (adcValues[i][AVERAGE_INDEX] < 23)
                    {
                        ntcOpenCnt = 0;
                        if (ntcErr != NTC_SHORT && ++ntcShortCnt >= 4)
                        {
                            ntcErr = NTC_SHORT;
                        }
                    }

#else
                    if (adcValues[i][AVERAGE_INDEX] > 4041)
                    {
                        ntcOpenCnt = 0;
                        if (ntcErr != NTC_SHORT && ++ntcShortCnt >= 4)
                        {
                            ntcErr = NTC_SHORT;
                        }
                    }
                    else if (adcValues[i][AVERAGE_INDEX] < 23)
                    {
                        ntcShortCnt = 0;
                        if (ntcErr != NTC_OPEN && ++ntcOpenCnt >= 4)
                        {
                            ntcErr = NTC_OPEN;
                        }
                    }
#endif
                    else
                    {
                        static unsigned char filterCnt = 0;

                        ntcShortCnt = 0;
                        ntcOpenCnt = 0;
                        ntcErr = 0;
#if PULL_UP
                        if (adcValues[i][AVERAGE_INDEX] >= rtTable[0])
                            detectedTemp = 0;
                        else if (adcValues[i][AVERAGE_INDEX] <= rtTable[sizeof(rtTable) / sizeof(*rtTable) - 1])
                            detectedTemp = sizeof(rtTable) / sizeof(*rtTable) - 1;
#else
                        if (adcValues[i][AVERAGE_INDEX] <= rtTable[0])
                            detectedTemp = 0;
                        else if (adcValues[i][AVERAGE_INDEX] >= rtTable[sizeof(rtTable) / sizeof(*rtTable) - 1])
                            detectedTemp = sizeof(rtTable) / sizeof(*rtTable) - 1;
#endif
                        else
                            detectedTemp = search4temp(adcValues[i][AVERAGE_INDEX], rtTable, sizeof(rtTable) / sizeof(*rtTable) - 1);

                        if (recordedTemp != detectedTemp)
                        {
                            if (++filterCnt >= MIN_FRESH_INTEVAL)
                            {
                                filterCnt = 0;
                                ntcTemp = detectedTemp;
                                recordedTemp = detectedTemp;
                            }
                        }
                        else
                            filterCnt = 0;
                    }
                }
                else if (i == 1) // CHN_2
                {
                }
            }
        }
    }
}

#if PULL_UP
static unsigned int search4temp(unsigned int adcValue, const unsigned int *table, unsigned int size)
{

    unsigned int i = 0, k = size, j;
    while (1)
    {
        j = (i + k) / 2;
        if (adcValue == table[j])
            return j;
        else if (i == j)
            return table[i] - adcValue < adcValue - table[k] ? i : k;
        else if (adcValue > table[j])
            k = j;
        else
            i = j;
    }
}
#else
static unsigned int search4temp(unsigned int adcValue, const unsigned int *table, unsigned int size)
{

    xdata unsigned int i = 0, k = size, j;
    while (1)
    {
        j = (i + k) / 2;
        if (adcValue == table[j])
            return j;
        else if (i == j)
            return adcValue - table[i] < table[k] - adcValue ? i : k;
        else if (adcValue < table[j])
            k = j;
        else
            i = j;
    }
}
#endif

char getTemp(unsigned int *temp)
{
    *temp = ntcTemp;
    return ntcErr;
}
