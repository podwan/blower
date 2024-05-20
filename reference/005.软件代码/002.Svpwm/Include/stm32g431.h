/*********************************************************/
//
/*********************************************************/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions                */
#define     __IO    volatile             /*!< Defines 'read / write' permissions              */
/*********************************************************/
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;

/* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef struct
{
  __I  uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
  __IO uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
  __IO uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  __IO uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
  __IO uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  __IO uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  __IO uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  __IO uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  __IO uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
  __IO uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  __IO uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
  __IO uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
  __IO uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  __I  uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  __I  uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
       uint32_t RESERVED0[5];
  __IO uint32_t CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
  
} SCB_Type;
#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address  */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address  */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct           */
/*********************************************************/
typedef struct
{
  __IO uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  __IO uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  __IO uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  __IO uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  __IO uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  __IO uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  __O  uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_Type;

#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address                  */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct          */

/*********************************************************/
typedef struct
{
  __IO uint32_t ISR;          /*!< ADC interrupt and status register,             Address offset: 0x00 */
  __IO uint32_t IER;          /*!< ADC interrupt enable register,                 Address offset: 0x04 */
  __IO uint32_t CR;           /*!< ADC control register,                          Address offset: 0x08 */
  __IO uint32_t CFGR;         /*!< ADC configuration register 1,                  Address offset: 0x0C */
  __IO uint32_t CFGR2;        /*!< ADC configuration register 2,                  Address offset: 0x10 */
  __IO uint32_t SMPR1;        /*!< ADC sampling time register 1,                  Address offset: 0x14 */
  __IO uint32_t SMPR2;        /*!< ADC sampling time register 2,                  Address offset: 0x18 */
       uint32_t RESERVED1;    /*!< Reserved,                                                      0x1C */
  __IO uint32_t TR1;          /*!< ADC analog watchdog 1 threshold register,      Address offset: 0x20 */
  __IO uint32_t TR2;          /*!< ADC analog watchdog 2 threshold register,      Address offset: 0x24 */
  __IO uint32_t TR3;          /*!< ADC analog watchdog 3 threshold register,      Address offset: 0x28 */
       uint32_t RESERVED2;    /*!< Reserved,                                                      0x2C */
  __IO uint32_t SQR1;         /*!< ADC group regular sequencer register 1,        Address offset: 0x30 */
  __IO uint32_t SQR2;         /*!< ADC group regular sequencer register 2,        Address offset: 0x34 */
  __IO uint32_t SQR3;         /*!< ADC group regular sequencer register 3,        Address offset: 0x38 */
  __IO uint32_t SQR4;         /*!< ADC group regular sequencer register 4,        Address offset: 0x3C */
  __IO uint32_t DR;           /*!< ADC group regular data register,               Address offset: 0x40 */
       uint32_t RESERVED3;    /*!< Reserved,                                                      0x44 */
       uint32_t RESERVED4;    /*!< Reserved,                                                      0x48 */
  __IO uint32_t JSQR;         /*!< ADC group injected sequencer register,         Address offset: 0x4C */
       uint32_t RESERVED5[4]; /*!< Reserved,                                               0x50 - 0x5C */
  __IO uint32_t OFR1;         /*!< ADC offset register 1,                         Address offset: 0x60 */
  __IO uint32_t OFR2;         /*!< ADC offset register 2,                         Address offset: 0x64 */
  __IO uint32_t OFR3;         /*!< ADC offset register 3,                         Address offset: 0x68 */
  __IO uint32_t OFR4;         /*!< ADC offset register 4,                         Address offset: 0x6C */
       uint32_t RESERVED6[4]; /*!< Reserved,                                               0x70 - 0x7C */
  __IO uint32_t JDR1;         /*!< ADC group injected rank 1 data register,       Address offset: 0x80 */
  __IO uint32_t JDR2;         /*!< ADC group injected rank 2 data register,       Address offset: 0x84 */
  __IO uint32_t JDR3;         /*!< ADC group injected rank 3 data register,       Address offset: 0x88 */
  __IO uint32_t JDR4;         /*!< ADC group injected rank 4 data register,       Address offset: 0x8C */
       uint32_t RESERVED7[4]; /*!< Reserved,                                             0x090 - 0x09C */
  __IO uint32_t AWD2CR;       /*!< ADC analog watchdog 2 configuration register,  Address offset: 0xA0 */
  __IO uint32_t AWD3CR;       /*!< ADC analog watchdog 3 Configuration Register,  Address offset: 0xA4 */
       uint32_t RESERVED8;    /*!< Reserved,                                                     0x0A8 */
       uint32_t RESERVED9;    /*!< Reserved,                                                     0x0AC */
  __IO uint32_t DIFSEL;       /*!< ADC differential mode selection register,      Address offset: 0xB0 */
  __IO uint32_t CALFACT;      /*!< ADC calibration factors,                       Address offset: 0xB4 */
       uint32_t RESERVED10[2];/*!< Reserved,                                             0x0B8 - 0x0BC */
  __IO uint32_t GCOMP;        /*!< ADC calibration factors,                       Address offset: 0xC0 */
} ADC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;          /*!< ADC common status register,            Address offset: 0x300 + 0x00 */
  uint32_t      RESERVED1;    /*!< Reserved,                              Address offset: 0x300 + 0x04 */
  __IO uint32_t CCR;          /*!< ADC common configuration register,     Address offset: 0x300 + 0x08 */
  __IO uint32_t CDR;          /*!< ADC common group regular data register Address offset: 0x300 + 0x0C */
} ADC_Common_TypeDef;

typedef struct
{
  __IO uint32_t CSR;         /*!< COMP control and status register, Address offset: 0x00 */
} COMP_TypeDef;

typedef struct
{
  __IO uint32_t CR;          /*!< DAC control register,                                    Address offset: 0x00 */
  __IO uint32_t SWTRIGR;     /*!< DAC software trigger register,                           Address offset: 0x04 */
  __IO uint32_t DHR12R1;     /*!< DAC channel1 12-bit right-aligned data holding register, Address offset: 0x08 */
  __IO uint32_t DHR12L1;     /*!< DAC channel1 12-bit left aligned data holding register,  Address offset: 0x0C */
  __IO uint32_t DHR8R1;      /*!< DAC channel1 8-bit right aligned data holding register,  Address offset: 0x10 */
  __IO uint32_t DHR12R2;     /*!< DAC channel2 12-bit right aligned data holding register, Address offset: 0x14 */
  __IO uint32_t DHR12L2;     /*!< DAC channel2 12-bit left aligned data holding register,  Address offset: 0x18 */
  __IO uint32_t DHR8R2;      /*!< DAC channel2 8-bit right-aligned data holding register,  Address offset: 0x1C */
  __IO uint32_t DHR12RD;     /*!< Dual DAC 12-bit right-aligned data holding register,     Address offset: 0x20 */
  __IO uint32_t DHR12LD;     /*!< DUAL DAC 12-bit left aligned data holding register,      Address offset: 0x24 */
  __IO uint32_t DHR8RD;      /*!< DUAL DAC 8-bit right aligned data holding register,      Address offset: 0x28 */
  __IO uint32_t DOR1;        /*!< DAC channel1 data output register,                       Address offset: 0x2C */
  __IO uint32_t DOR2;        /*!< DAC channel2 data output register,                       Address offset: 0x30 */
  __IO uint32_t SR;          /*!< DAC status register,                                     Address offset: 0x34 */
  __IO uint32_t CCR;         /*!< DAC calibration control register,                        Address offset: 0x38 */
  __IO uint32_t MCR;         /*!< DAC mode control register,                               Address offset: 0x3C */
  __IO uint32_t SHSR1;       /*!< DAC Sample and Hold sample time register 1,              Address offset: 0x40 */
  __IO uint32_t SHSR2;       /*!< DAC Sample and Hold sample time register 2,              Address offset: 0x44 */
  __IO uint32_t SHHR;        /*!< DAC Sample and Hold hold time register,                  Address offset: 0x48 */
  __IO uint32_t SHRR;        /*!< DAC Sample and Hold refresh time register,               Address offset: 0x4C */
  __IO uint32_t RESERVED[2];
  __IO uint32_t STR1;        /*!< DAC Sawtooth register,                                   Address offset: 0x58 */
  __IO uint32_t STR2;        /*!< DAC Sawtooth register,                                   Address offset: 0x5C */
  __IO uint32_t STMODR;      /*!< DAC Sawtooth Mode register,                              Address offset: 0x60 */
} DAC_TypeDef;

typedef struct
{
  __IO uint32_t CSR;           /*!< OPAMP control/status register,                     Address offset: 0x00 */
  __IO uint32_t RESERVED[5];   /*!< OPAMP offset trimming register for normal mode,    Address offset: 0x04 */
  __IO uint32_t TCMR;          /*!< OPAMP timer controlled mux mode register,          Address offset: 0x18 */
} OPAMP_TypeDef;


typedef struct
{
  __IO uint32_t IMR1;        /*!< EXTI Interrupt mask register 1,             Address offset: 0x00 */
  __IO uint32_t EMR1;        /*!< EXTI Event mask register 1,                 Address offset: 0x04 */
  __IO uint32_t RTSR1;       /*!< EXTI Rising trigger selection register 1,   Address offset: 0x08 */
  __IO uint32_t FTSR1;       /*!< EXTI Falling trigger selection register 1,  Address offset: 0x0C */
  __IO uint32_t SWIER1;      /*!< EXTI Software interrupt event register 1,   Address offset: 0x10 */
  __IO uint32_t PR1;         /*!< EXTI Pending register 1,                    Address offset: 0x14 */
  uint32_t      RESERVED1;   /*!< Reserved, 0x18                                                   */
  uint32_t      RESERVED2;   /*!< Reserved, 0x1C                                                   */
  __IO uint32_t IMR2;        /*!< EXTI Interrupt mask register 2,             Address offset: 0x20 */
  __IO uint32_t EMR2;        /*!< EXTI Event mask register 2,                 Address offset: 0x24 */
  __IO uint32_t RTSR2;       /*!< EXTI Rising trigger selection register 2,   Address offset: 0x28 */
  __IO uint32_t FTSR2;       /*!< EXTI Falling trigger selection register 2,  Address offset: 0x2C */
  __IO uint32_t SWIER2;      /*!< EXTI Software interrupt event register 2,   Address offset: 0x30 */
  __IO uint32_t PR2;         /*!< EXTI Pending register 2,                    Address offset: 0x34 */
} EXTI_TypeDef;

typedef struct
{
  __IO uint32_t ACR;              /*!< FLASH access control register,            Address offset: 0x00 */
  __IO uint32_t PDKEYR;           /*!< FLASH power down key register,            Address offset: 0x04 */
  __IO uint32_t KEYR;             /*!< FLASH key register,                       Address offset: 0x08 */
  __IO uint32_t OPTKEYR;          /*!< FLASH option key register,                Address offset: 0x0C */
  __IO uint32_t SR;               /*!< FLASH status register,                    Address offset: 0x10 */
  __IO uint32_t CR;               /*!< FLASH control register,                   Address offset: 0x14 */
  __IO uint32_t ECCR;             /*!< FLASH ECC register,                       Address offset: 0x18 */
       uint32_t RESERVED1;        /*!< Reserved1,                                Address offset: 0x1C */
  __IO uint32_t OPTR;             /*!< FLASH option register,                    Address offset: 0x20 */
  __IO uint32_t PCROP1SR;         /*!< FLASH bank1 PCROP start address register, Address offset: 0x24 */
  __IO uint32_t PCROP1ER;         /*!< FLASH bank1 PCROP end address register,   Address offset: 0x28 */
  __IO uint32_t WRP1AR;           /*!< FLASH bank1 WRP area A address register,  Address offset: 0x2C */
  __IO uint32_t WRP1BR;           /*!< FLASH bank1 WRP area B address register,  Address offset: 0x30 */
       uint32_t RESERVED2[15];    /*!< Reserved2,                                Address offset: 0x34 */
  __IO uint32_t SEC1R;            /*!< FLASH Securable memory register bank1,    Address offset: 0x70 */
} FLASH_TypeDef;
/*********************************************************/
typedef struct
{
  __IO uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  __IO uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  __IO uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */
} GPIO_TypeDef;
/*********************************************************/
typedef struct
{
  __IO uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
  __IO uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
  __IO uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
  __IO uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
  uint32_t      RESERVED0;   /*!< Reserved,                                                                Address offset: 0x10 */
  uint32_t      RESERVED1;   /*!< Reserved,                                                                Address offset: 0x14 */
  __IO uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
  __IO uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
  __IO uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
  uint32_t      RESERVED2;   /*!< Reserved,                                                                Address offset: 0x24 */
  __IO uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  __IO uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  __IO uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  uint32_t      RESERVED3;   /*!< Reserved,                                                                Address offset: 0x34 */
  __IO uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
  __IO uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
  __IO uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
  uint32_t      RESERVED4;   /*!< Reserved,                                                                Address offset: 0x44 */
  __IO uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
  __IO uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
  __IO uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
  uint32_t      RESERVED5;   /*!< Reserved,                                                                Address offset: 0x54 */
  __IO uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
  __IO uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
  __IO uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
  uint32_t      RESERVED6;   /*!< Reserved,                                                                Address offset: 0x64 */
  __IO uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
  __IO uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
  __IO uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
  uint32_t      RESERVED7;   /*!< Reserved,                                                                Address offset: 0x74 */
  __IO uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
  __IO uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
  __IO uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
  uint32_t      RESERVED8;   /*!< Reserved,                                                                Address offset: 0x84 */
  __IO uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
  uint32_t      RESERVED9;   /*!< Reserved,                                                                Address offset: 0x8C */
  __IO uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
  __IO uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
  __IO uint32_t CRRCR;       /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
  __IO uint32_t CCIPR2;      /*!< RCC peripherals independent clock configuration register 2,              Address offset: 0x9C */
} RCC_TypeDef;

typedef struct
{
  __IO uint32_t MEMRMP;      /*!< SYSCFG memory remap register,                        Address offset: 0x00      */
  __IO uint32_t CFGR1;       /*!< SYSCFG configuration register 1,                     Address offset: 0x04      */
  __IO uint32_t EXTICR[4];   /*!< SYSCFG external interrupt configuration registers,   Address offset: 0x08-0x14 */
  __IO uint32_t SCSR;        /*!< SYSCFG CCMSRAM control and status register,          Address offset: 0x18      */
  __IO uint32_t CFGR2;       /*!< SYSCFG configuration register 2,                     Address offset: 0x1C      */
  __IO uint32_t SWPR;        /*!< SYSCFG CCMSRAM write protection register,            Address offset: 0x20      */
  __IO uint32_t SKR;         /*!< SYSCFG CCMSRAM Key Register,                         Address offset: 0x24      */
} SYSCFG_TypeDef;

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register 5,           Address offset: 0x48 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register 6,           Address offset: 0x4C */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x50 */
  __IO uint32_t DTR2;        /*!< TIM deadtime register 2,                  Address offset: 0x54 */
  __IO uint32_t ECR;         /*!< TIM encoder control register,             Address offset: 0x58 */
  __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  __IO uint32_t OR ;         /*!< TIM option register,                      Address offset: 0x68 */
       uint32_t RESERVED0[220];/*!< Reserved,                               Address offset: 0x6C */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x3DC */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x3E0 */
} TIM_TypeDef;

typedef struct
{
  __IO uint32_t CR1;         /*!< USART Control register 1,                 Address offset: 0x00  */
  __IO uint32_t CR2;         /*!< USART Control register 2,                 Address offset: 0x04  */
  __IO uint32_t CR3;         /*!< USART Control register 3,                 Address offset: 0x08  */
  __IO uint32_t BRR;         /*!< USART Baud rate register,                 Address offset: 0x0C  */
  __IO uint32_t GTPR;        /*!< USART Guard time and prescaler register,  Address offset: 0x10  */
  __IO uint32_t RTOR;        /*!< USART Receiver Timeout register,          Address offset: 0x14  */
  __IO uint32_t RQR;         /*!< USART Request register,                   Address offset: 0x18  */
  __IO uint32_t ISR;         /*!< USART Interrupt and status register,      Address offset: 0x1C  */
  __IO uint32_t ICR;         /*!< USART Interrupt flag Clear register,      Address offset: 0x20  */
  __IO uint32_t RDR;         /*!< USART Receive Data register,              Address offset: 0x24  */
  __IO uint32_t TDR;         /*!< USART Transmit Data register,             Address offset: 0x28  */
  __IO uint32_t PRESC;       /*!< USART Prescaler register,                 Address offset: 0x2C  */
} USART_TypeDef;

typedef struct
{
  __IO uint32_t CSR;          /*!< CORDIC control and status register,        Address offset: 0x00 */
  __IO uint32_t WDATA;        /*!< CORDIC argument register,                  Address offset: 0x04 */
  __IO uint32_t RDATA;        /*!< CORDIC result register,                    Address offset: 0x08 */
} CORDIC_TypeDef;


#define FLASH_BASE            (0x08000000UL) /*!< FLASH (up to 128 kB) base address */
#define SRAM1_BASE            (0x20000000UL) /*!< SRAM1(up to 16 KB) base address */
#define SRAM2_BASE            (0x20004000UL) /*!< SRAM2(6 KB) base address */
#define CCMSRAM_BASE          (0x10000000UL) /*!< CCMSRAM(10 KB) base address */
#define PERIPH_BASE           (0x40000000UL) /*!< Peripheral base address */

#define SRAM1_BB_BASE         (0x22000000UL) /*!< SRAM1(16 KB) base address in the bit-band region */
#define SRAM2_BB_BASE         (0x22080000UL) /*!< SRAM2(6 KB) base address in the bit-band region */
#define CCMSRAM_BB_BASE       (0x220B0000UL) /*!< CCMSRAM(10 KB) base address in the bit-band region */
#define PERIPH_BB_BASE        (0x42000000UL) /*!< Peripheral base address in the bit-band region */
/* Legacy defines */
#define SRAM_BASE             SRAM1_BASE
#define SRAM_BB_BASE          SRAM1_BB_BASE

#define SRAM1_SIZE_MAX        (0x00004000UL) /*!< maximum SRAM1 size (up to 16 KBytes) */
#define SRAM2_SIZE            (0x00001800UL) /*!< SRAM2 size (6 KBytes) */
#define CCMSRAM_SIZE          (0x00002800UL) /*!< CCMSRAM size (10 KBytes) */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE        PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)


/*!< APB1 peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800UL)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000UL)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400UL)
#define CRS_BASE              (APB1PERIPH_BASE + 0x2000UL)
#define TAMP_BASE             (APB1PERIPH_BASE + 0x2400UL)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800UL)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00UL)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000UL)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800UL)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00UL)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL)
#define USB_BASE              (APB1PERIPH_BASE + 0x5C00UL)  /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x6000UL)  /*!< USB_IP Packet Memory Area base address */
#define FDCAN1_BASE           (APB1PERIPH_BASE + 0x6400UL)
#define FDCAN_CONFIG_BASE     (APB1PERIPH_BASE + 0x6500UL)  /*!< FDCAN configuration registers base address */
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)
#define I2C3_BASE             (APB1PERIPH_BASE + 0x7800UL)
#define LPTIM1_BASE           (APB1PERIPH_BASE + 0x7C00UL)
#define LPUART1_BASE          (APB1PERIPH_BASE + 0x8000UL)
#define UCPD1_BASE            (APB1PERIPH_BASE + 0xA000UL)
#define SRAMCAN_BASE          (APB1PERIPH_BASE + 0xA400UL)

/*!< APB2 peripherals */
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x0000UL)
#define VREFBUF_BASE          (APB2PERIPH_BASE + 0x0030UL)
#define COMP1_BASE            (APB2PERIPH_BASE + 0x0200UL)
#define COMP2_BASE            (APB2PERIPH_BASE + 0x0204UL)
#define COMP3_BASE            (APB2PERIPH_BASE + 0x0208UL)
#define COMP4_BASE            (APB2PERIPH_BASE + 0x020CUL)
#define OPAMP_BASE            (APB2PERIPH_BASE + 0x0300UL)
#define OPAMP1_BASE           (APB2PERIPH_BASE + 0x0300UL)
#define OPAMP2_BASE           (APB2PERIPH_BASE + 0x0304UL)
#define OPAMP3_BASE           (APB2PERIPH_BASE + 0x0308UL)

#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400UL)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00UL)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x3400UL)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800UL)
#define TIM15_BASE            (APB2PERIPH_BASE + 0x4000UL)
#define TIM16_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define TIM17_BASE            (APB2PERIPH_BASE + 0x4800UL)
#define SAI1_BASE             (APB2PERIPH_BASE + 0x5400UL)
#define SAI1_Block_A_BASE     (SAI1_BASE + 0x0004UL)
#define SAI1_Block_B_BASE     (SAI1_BASE + 0x0024UL)

/*!< AHB1 peripherals */
#define DMA1_BASE             (AHB1PERIPH_BASE)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x0400UL)
#define DMAMUX1_BASE          (AHB1PERIPH_BASE + 0x0800UL)
#define CORDIC_BASE           (AHB1PERIPH_BASE + 0x0C00UL)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x1000UL)
#define FMAC_BASE             (AHB1PERIPH_BASE + 0x1400UL)
#define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x2000UL)
#define CRC_BASE              (AHB1PERIPH_BASE + 0x3000UL)

#define DMA1_Channel1_BASE    (DMA1_BASE + 0x0008UL)
#define DMA1_Channel2_BASE    (DMA1_BASE + 0x001CUL)
#define DMA1_Channel3_BASE    (DMA1_BASE + 0x0030UL)
#define DMA1_Channel4_BASE    (DMA1_BASE + 0x0044UL)
#define DMA1_Channel5_BASE    (DMA1_BASE + 0x0058UL)
#define DMA1_Channel6_BASE    (DMA1_BASE + 0x006CUL)

#define DMA2_Channel1_BASE    (DMA2_BASE + 0x0008UL)
#define DMA2_Channel2_BASE    (DMA2_BASE + 0x001CUL)
#define DMA2_Channel3_BASE    (DMA2_BASE + 0x0030UL)
#define DMA2_Channel4_BASE    (DMA2_BASE + 0x0044UL)
#define DMA2_Channel5_BASE    (DMA2_BASE + 0x0058UL)
#define DMA2_Channel6_BASE    (DMA2_BASE + 0x006CUL)

#define DMAMUX1_Channel0_BASE    (DMAMUX1_BASE)
#define DMAMUX1_Channel1_BASE    (DMAMUX1_BASE + 0x0004UL)
#define DMAMUX1_Channel2_BASE    (DMAMUX1_BASE + 0x0008UL)
#define DMAMUX1_Channel3_BASE    (DMAMUX1_BASE + 0x000CUL)
#define DMAMUX1_Channel4_BASE    (DMAMUX1_BASE + 0x0010UL)
#define DMAMUX1_Channel5_BASE    (DMAMUX1_BASE + 0x0014UL)
#define DMAMUX1_Channel6_BASE    (DMAMUX1_BASE + 0x0020UL)
#define DMAMUX1_Channel7_BASE    (DMAMUX1_BASE + 0x0024UL)
#define DMAMUX1_Channel8_BASE    (DMAMUX1_BASE + 0x0028UL)
#define DMAMUX1_Channel9_BASE    (DMAMUX1_BASE + 0x002CUL)
#define DMAMUX1_Channel10_BASE   (DMAMUX1_BASE + 0x0030UL)
#define DMAMUX1_Channel11_BASE   (DMAMUX1_BASE + 0x0034UL)
#define DMAMUX1_RequestGenerator0_BASE  (DMAMUX1_BASE + 0x0100UL)
#define DMAMUX1_RequestGenerator1_BASE  (DMAMUX1_BASE + 0x0104UL)
#define DMAMUX1_RequestGenerator2_BASE  (DMAMUX1_BASE + 0x0108UL)
#define DMAMUX1_RequestGenerator3_BASE  (DMAMUX1_BASE + 0x010CUL)

#define DMAMUX1_ChannelStatus_BASE      (DMAMUX1_BASE + 0x0080UL)
#define DMAMUX1_RequestGenStatus_BASE   (DMAMUX1_BASE + 0x0140UL)

/*!< AHB2 peripherals */
#define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400UL)
#define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800UL)
#define GPIOD_BASE            (AHB2PERIPH_BASE + 0x0C00UL)
#define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000UL)
#define GPIOF_BASE            (AHB2PERIPH_BASE + 0x1400UL)
#define GPIOG_BASE            (AHB2PERIPH_BASE + 0x1800UL)

#define ADC1_BASE             (AHB2PERIPH_BASE + 0x08000000UL)
#define ADC2_BASE             (AHB2PERIPH_BASE + 0x08000100UL)
#define ADC12_COMMON_BASE     (AHB2PERIPH_BASE + 0x08000300UL)

#define DAC_BASE              (AHB2PERIPH_BASE + 0x08000800UL)
#define DAC1_BASE             (AHB2PERIPH_BASE + 0x08000800UL)
#define DAC3_BASE             (AHB2PERIPH_BASE + 0x08001000UL)

#define RNG_BASE              (AHB2PERIPH_BASE + 0x08060800UL)
/* Debug MCU registers base address */
#define DBGMCU_BASE           (0xE0042000UL)

#define PACKAGE_BASE          (0x1FFF7500UL)        /*!< Package data register base address     */
#define UID_BASE              (0x1FFF7590UL)        /*!< Unique device ID register base address */
#define FLASHSIZE_BASE        (0x1FFF75E0UL)        /*!< Flash size data register base address  */
/**
  * @}
  */

/** @addtogroup Peripheral_declaration
  * @{
  */
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define CRS                 ((CRS_TypeDef *) CRS_BASE)
#define TAMP                ((TAMP_TypeDef *) TAMP_BASE)
#define RTC                 ((RTC_TypeDef *) RTC_BASE)
#define WWDG                ((WWDG_TypeDef *) WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)
#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                ((I2C_TypeDef *) I2C2_BASE)
#define USB                 ((USB_TypeDef *) USB_BASE)
#define FDCAN1              ((FDCAN_GlobalTypeDef *) FDCAN1_BASE)
#define FDCAN_CONFIG        ((FDCAN_Config_TypeDef *) FDCAN_CONFIG_BASE)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)
#define I2C3                ((I2C_TypeDef *) I2C3_BASE)
#define LPTIM1              ((LPTIM_TypeDef *) LPTIM1_BASE)
#define LPUART1             ((USART_TypeDef *) LPUART1_BASE)
#define UCPD1              ((UCPD_TypeDef *) UCPD1_BASE)

#define SYSCFG              ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define VREFBUF             ((VREFBUF_TypeDef *) VREFBUF_BASE)
#define COMP1               ((COMP_TypeDef *) COMP1_BASE)
#define COMP2               ((COMP_TypeDef *) COMP2_BASE)
#define COMP3               ((COMP_TypeDef *) COMP3_BASE)
#define COMP4               ((COMP_TypeDef *) COMP4_BASE)

#define OPAMP               ((OPAMP_TypeDef *) OPAMP_BASE)
#define OPAMP1              ((OPAMP_TypeDef *) OPAMP1_BASE)
#define OPAMP2              ((OPAMP_TypeDef *) OPAMP2_BASE)
#define OPAMP3              ((OPAMP_TypeDef *) OPAMP3_BASE)

#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define SPI1                ((SPI_TypeDef *) SPI1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define TIM15               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17               ((TIM_TypeDef *) TIM17_BASE)
#define SAI1                ((SAI_TypeDef *) SAI1_BASE)
#define SAI1_Block_A        ((SAI_Block_TypeDef *)SAI1_Block_A_BASE)
#define SAI1_Block_B        ((SAI_Block_TypeDef *)SAI1_Block_B_BASE)
#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMAMUX1             ((DMAMUX_Channel_TypeDef *) DMAMUX1_BASE)
#define CORDIC              ((CORDIC_TypeDef *) CORDIC_BASE)
#define RCC                 ((RCC_TypeDef *) RCC_BASE)
#define FMAC                ((FMAC_TypeDef *) FMAC_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)
#define CRC                 ((CRC_TypeDef *) CRC_BASE)

#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define ADC1                ((ADC_TypeDef *) ADC1_BASE)
#define ADC2                ((ADC_TypeDef *) ADC2_BASE)
#define ADC12_COMMON        ((ADC_Common_TypeDef *) ADC12_COMMON_BASE)
#define DAC                 ((DAC_TypeDef *) DAC_BASE)
#define DAC1                ((DAC_TypeDef *) DAC1_BASE)
#define DAC3                ((DAC_TypeDef *) DAC3_BASE)
#define RNG                 ((RNG_TypeDef *) RNG_BASE)

#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)

#define DMA2_Channel1       ((DMA_Channel_TypeDef *) DMA2_Channel1_BASE)
#define DMA2_Channel2       ((DMA_Channel_TypeDef *) DMA2_Channel2_BASE)
#define DMA2_Channel3       ((DMA_Channel_TypeDef *) DMA2_Channel3_BASE)
#define DMA2_Channel4       ((DMA_Channel_TypeDef *) DMA2_Channel4_BASE)
#define DMA2_Channel5       ((DMA_Channel_TypeDef *) DMA2_Channel5_BASE)
#define DMA2_Channel6       ((DMA_Channel_TypeDef *) DMA2_Channel6_BASE)

#define DMAMUX1_Channel0    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel0_BASE)
#define DMAMUX1_Channel1    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel1_BASE)
#define DMAMUX1_Channel2    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel2_BASE)
#define DMAMUX1_Channel3    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel3_BASE)
#define DMAMUX1_Channel4    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel4_BASE)
#define DMAMUX1_Channel5    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel5_BASE)
#define DMAMUX1_Channel6    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel6_BASE)
#define DMAMUX1_Channel7    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel7_BASE)
#define DMAMUX1_Channel8    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel8_BASE)
#define DMAMUX1_Channel9    ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel9_BASE)
#define DMAMUX1_Channel10   ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel10_BASE)
#define DMAMUX1_Channel11   ((DMAMUX_Channel_TypeDef *) DMAMUX1_Channel11_BASE)

#define DMAMUX1_RequestGenerator0  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator0_BASE)
#define DMAMUX1_RequestGenerator1  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator1_BASE)
#define DMAMUX1_RequestGenerator2  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator2_BASE)
#define DMAMUX1_RequestGenerator3  ((DMAMUX_RequestGen_TypeDef *) DMAMUX1_RequestGenerator3_BASE)

#define DMAMUX1_ChannelStatus      ((DMAMUX_ChannelStatus_TypeDef *) DMAMUX1_ChannelStatus_BASE)
#define DMAMUX1_RequestGenStatus   ((DMAMUX_RequestGenStatus_TypeDef *) DMAMUX1_RequestGenStatus_BASE)



#define DBGMCU              ((DBGMCU_TypeDef *) DBGMCU_BASE)
