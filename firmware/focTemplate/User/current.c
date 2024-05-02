/**************************************************************************************************
 * 张飞实战电子
 * @project PLL_FOC
 * @file    Current.c
 * @author  张飞实战电子团队
 * @date    2024/03/28
 * @version V100
 * @Copyright  软件著作权张飞实战电子所有
 **************************************************************************************************/
#include "current.h"
#include "foc_utils.h"
#include "motor.h"
/**************************************************************************************************
 * Current
 **************************************************************************************************/
/*===============================================================================================*/
void currentInitialize(Currents *currents)
{
    currents->Ia = 0;
    currents->Ib = 0;
    currents->Ic = 0;

    currents->Ialpha = 0;
    currents->Ibeta = 0;

    currents->Id = 0;
    currents->Iq = 0;
}
/*===============================================================================================*/

/*============================================================================*/
// 检流电阻负压代表Ia的正向电流，即注入电机的电流为正向电流。
/*============================================================================*/
static void GetIabc(Currents *currents)
{
    signed short int Ia, Ib, Ic;

    Ia = currents->IoffsetA - tGlobal.IaValue;
    Ib = currents->IoffsetB - tGlobal.IbValue;
    Ic = 0 - Ia - Ib;

    currents->Ia = Ia;
    currents->Ib = Ib;
    currents->Ic = Ic;
}
/*============================================================================*/
// Clarke变换，计算公式
// Ialpha = Ia
// Ibeta = (Ia + 2Ib)/sqrt(3)
// Ibeta = 1/sqrt(3) * Ia + 1/sqrt(3) * 2Ib
/*============================================================================*/
static void GetIalphabeta(Currents *currents)
{
    currents->Ialpha = currents->Ia;
    // currents->Ibeta = (currents->Ia + 2.0f * currents->Ib) / _SQRT3;
    currents->Ibeta = _1_SQRT3 * currents->Ia + _1_SQRT3 * currents->Ib * 2.0f;
}
/*===============================================================================================*/
void GetCurrentOffset(Currents *currents)
{
    currents->IoffsetA = tGlobal.IaOffset;
    currents->IoffsetB = tGlobal.IbOffset;
}
/*============================================================================*/
// Park变换
// Id = Ialpha * Cosθr + Ibeta * Sinθr
// Iq = -Ialpha * Sinθr + Ibeta * Cosθr
/*============================================================================*/
static void GetIdq(Currents *currents)
{
    currents->Id = currents->Ialpha * _cos(currents->ParkAngle) + currents->Ibeta * _sin(currents->ParkAngle);
    currents->Iq = -(currents->Ialpha) * _sin(currents->ParkAngle) + currents->Ibeta * _cos(currents->ParkAngle);
}

/*===============================================================================================*/
void currentSample(Currents *currents)
{
    GetIabc(currents);
    GetIalphabeta(currents);
    GetIdq(currents);
}