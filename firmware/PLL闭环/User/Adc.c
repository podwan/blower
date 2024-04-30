#include "motor.h"
#include "Adc.h"

tAdc_Type tAdc;

/*===============================================================================================*/
void AdcSample(void)
{
    tAdc.An11.ValueInstant = (unsigned short int)ADC1->JDR1; // Ia
    tAdc.An12.ValueInstant = (unsigned short int)ADC1->JDR2; // Vbus
    tAdc.An13.ValueInstant = (unsigned short int)ADC1->JDR3; // HT
    tAdc.An14.ValueInstant = (unsigned short int)ADC1->JDR4; // NTC

    tAdc.An21.ValueInstant = (unsigned short int)ADC2->JDR1; // Ib
    tAdc.An22.ValueInstant = (unsigned short int)ADC2->JDR2; // V15
    tAdc.An23.ValueInstant = (unsigned short int)ADC2->JDR3; // VTS-B
    tAdc.An24.ValueInstant = (unsigned short int)ADC2->JDR4; // OPAMP3

    tGlobal.IaValue = tAdc.An11.ValueInstant;
    tGlobal.IbValue = tAdc.An21.ValueInstant;

    tGlobal.VbusInstant = tAdc.An12.ValueInstant;
    tGlobal.OPAMP3Instant = tAdc.An24.ValueInstant;
}
/*===============================================================================================*/
void InitAdcOffset(void)
{
    tAdc.An11.ValueSum32 = 0;
    tAdc.An11.ValueNum = 0;
    tAdc.An21.ValueSum32 = 0;
    tAdc.An21.ValueNum = 0;
    tAdc.An12.ValueSum32 = 0;
    tAdc.An12.ValueNum = 0;
}
/*===============================================================================================*/
void CalAdcOffset(void)
{
    if (tGlobal.OffsetReq)
    {
        tAdc.An11.ValueSum32 += tAdc.An11.ValueInstant;
        tAdc.An11.ValueNum++;
        if (tAdc.An11.ValueNum >= 64)
        {
            tAdc.An11.ValueAverage = (unsigned short int)(tAdc.An11.ValueSum32 >> 6);
            tAdc.An11.ValueSum32 = 0;
            tAdc.An11.ValueNum = 0;
        }

        tAdc.An21.ValueSum32 += tAdc.An21.ValueInstant;
        tAdc.An21.ValueNum++;
        if (tAdc.An21.ValueNum >= 64)
        {
            tAdc.An21.ValueAverage = (unsigned short int)(tAdc.An21.ValueSum32 >> 6);
            tAdc.An21.ValueSum32 = 0;
            tAdc.An21.ValueNum = 0;
            tGlobal.IaOffset = tAdc.An11.ValueAverage;
            tGlobal.IbOffset = tAdc.An21.ValueAverage;
        }

        tAdc.An12.ValueSum32 += tAdc.An12.ValueInstant;
        tAdc.An12.ValueNum++;
        if (tAdc.An12.ValueNum >= 64)
        {
            tAdc.An12.ValueAverage = (unsigned short int)(tAdc.An12.ValueSum32 >> 6);
            tAdc.An12.ValueSum32 = 0;
            tAdc.An12.ValueNum = 0;
            tGlobal.TargetVbus = tAdc.An12.ValueAverage;
            tGlobal.OffsetReq = 0;
        }
    }
}
