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



/*============================================================================*/
// 检流电阻负压代表Ia的正向电流，即注入电机的电流为正向电流。
/*============================================================================*/
// static void getPhaseCurrents(Currents *currents, uint32_t adc_a, uint32_t adc_b)
// {
//     currents->A = (adc_a - currents->offset_ia) * VLOTS_AMPS_RATIO; // amps
//     currents->B = (adc_b - currents->offset_ib) * VLOTS_AMPS_RATIO; // amps
// }
/*============================================================================*/
// Clarke变换，计算公式
// Ialpha = Ia
// Ibeta = (Ia + 2Ib)/sqrt(3)
// Ibeta = 1/sqrt(3) * Ia + 1/sqrt(3) * 2Ib
/*============================================================================*/
// static void getABCurrents(Currents *currents)
// {
//     currents->alpha = currents->A;
//     // currents->Ibeta = (currents->Ia + 2.0f * currents->Ib) / _SQRT3;
//     currents->beta = _1_SQRT3 * currents->A + _2_SQRT3 * currents->B;
// }

/*============================================================================*/
// Park变换
// Id = Ialpha * Cosθr + Ibeta * Sinθr
// Iq =   Ibeta * Cosθr -Ialpha * Sinθr
/*============================================================================*/
// static void getDQCurrents(Currents *currents)
// {
//     float ct;
//     float st;
//     //_sincos(currents->eAngle, &st, &ct);
//     currents->D = currents->alpha * ct + currents->beta * st;
//     currents->Q = currents->beta * ct - currents->alpha * st;
// }

/*===============================================================================================*/
void currentSample(Currents *currents)
{
    //    GetIabc(currents);
  //  GetIalphabeta(currents);
   // GetIdq(currents);
}
