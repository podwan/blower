# 2024/4/26

接入市电电前待确认项目：

1. 三路PWM是否正常输出（25kHz)
2. 死区是否为2.4us
3. 能否正常出发ADC采样

# 2024/4/27

![扇区作用时间汇总](G:\workSpace\KX\121_blower\doc\扇区作用时间汇总.jpg)

![](G:\workSpace\KX\121_blower\doc\公因式.png)

![M项](G:\workSpace\KX\121_blower\doc\M项.png)

![扇区1](G:\workSpace\KX\121_blower\doc\扇区1.jpg)

![扇区2](G:\workSpace\KX\121_blower\doc\扇区2.jpg)

![扇区3](G:\workSpace\KX\121_blower\doc\扇区3.jpg)

![扇区4](G:\workSpace\KX\121_blower\doc\扇区4.jpg)

![扇区5](G:\workSpace\KX\121_blower\doc\扇区5.jpg)

![扇区6](G:\workSpace\KX\121_blower\doc\扇区6.jpg)

![M项](G:\workSpace\KX\121_blower\doc\M项.png)

# 2024/4/28

1. 先用烧录提供的代码验证硬件
2. 将编写的应用代码替换验证
3. 将初始化代码替换验证

# 2024/5/2

电机控制以控制三相相电流为目的

涉及三大模块：

1. 电流：

   根据采集到的相电流和电角度，进行clark\park转换得到直流电流

2. PID

   将直流电流和期望电流输入到PID计算得到直流电压，输入到电压模块

3. 电压

   将直流电压

# 2024/5/20

![矢量的合成与分解](C:\Users\18575\Desktop\blower\doc\矢量的合成与分解.jpg)

1. 用PI控制器算出Ud, Uq
2. 根据Ud, Uq 算出Us, 和 θsd后SVPWM
3. Ualpha和Ubeta用于电角度的估算

# 2024/5/21

同样的二级制数据，根据不同的运算规则可以代表不同的数据



![image-20240521200616932](C:\Users\18575\AppData\Roaming\Typora\typora-user-images\image-20240521200616932.png)

# 2024/5/24

![锁相环位置估算1](C:\Users\18575\Desktop\blower\doc\锁相环位置估算1.jpg)

1. 根据电机方程， 由Ualpha, Ubeta, Ialpha和Ibeta  得到反电动势Ealpha, Ebeta
2. 由Ealpha和Ebeta结合角度得到Ed, Eq， 即得到角度θ和Ed的方程式：
3. 如果theta估算正确则Ed始终为零

![](C:\Users\18575\Desktop\blower\doc\锁相环位置估算2.jpg)

将0-Ed为误差量输入PI控制器，用反馈得到的量对θest进行修正，

逆时针： Δθ∝-Ed  顺时针： Δθ∝Ed