;*******************************************************************************
;* @File Name          : startup_stm32g431xx.s
;* @Author             : MCD Application Team
;* @Brief              : Vector table for MDK-ARM toolchain
;*******************************************************************************
				EXPORT  __Vectors
				EXPORT  Reset_Handler
				EXTERN  ADC1_2_IRQHandler
				EXTERN  Main
					

Stack_Size      EQU     0x400;				;1K

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


Heap_Size       EQU     0x200;				;0.5K

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                
				;0x08000000
__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     0                ; NMI Handler
                DCD     0          ; Hard Fault Handler
                DCD     0          ; MPU Fault Handler
                DCD     0           ; Bus Fault Handler
                DCD     0         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                ; SVCall Handler
                DCD     0           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     0             ; PendSV Handler
                DCD     0            ; SysTick Handler

                ; External Interrupts
                DCD     0			;0 Window WatchDog
                DCD     0           ;1 PVD/PVM1/PVM2/PVM3/PVM4 through EXTI Line detection
                DCD     0        	;2 RTC, TAMP and RCC LSE_CSS through the EXTI line
                DCD     0           ;3 RTC Wakeup through the EXTI line
                DCD     0           ;4 FLASH
                DCD     0           ;5 RCC
                DCD     0           ;6 EXTI Line0
                DCD     0           ;7 EXTI Line1
                DCD     0           ;8 EXTI Line2
                DCD     0           ;9 EXTI Line3
                DCD     0           ;10 EXTI Line4
                DCD     0          	;11 DMA1 Channel 1
                DCD     0          	;12 DMA1 Channel 2
                DCD     0          	;13 DMA1 Channel 3
                DCD     0          	;14 DMA1 Channel 4
                DCD     0          	;15 DMA1 Channel 5
                DCD     0          	;16 DMA1 Channel 6
                DCD     0           ;17 Reserved
                DCD     ADC1_2_IRQHandler ;18 ADC1 and ADC2
                DCD     0                 ;19 USB Device High Priority
                DCD     0                 ;20 USB Device Low Priority
                DCD     0             ;21 FDCAN1 interrupt line 0
                DCD     0             ;22 FDCAN1 interrupt line 1
                DCD     0    		  ;23 External Line[9:5]s
                DCD     0         	  ;24 TIM1 Break, Transition error, Index error and TIM15
                DCD     0          	  ;25 TIM1 Update and TIM16
                DCD     0     		  ;26 TIM1 Trigger, Commutation, Direction change, Index and TIM17
                DCD     0			  ;27 TIM1 Capture Compare
                DCD     0                   ; TIM2
                DCD     0                   ; TIM3
                DCD     0                   ; TIM4
                DCD     0                ; I2C1 Event
                DCD     0                ; I2C1 Error
                DCD     0                ; I2C2 Event
                DCD     0                ; I2C2 Error
                DCD     0                   ; SPI1
                DCD     0                   ; SPI2
                DCD     0                 ; USART1
                DCD     0                 ; USART2
                DCD     0                 ; USART3
                DCD     0              ; External Line[15:10]
                DCD     0              ; RTC Alarm (A and B) through EXTI Line
                DCD     0              ; USB Wakeup through EXTI line
                DCD     0               ; TIM8 Break, Transition error and Index error Interrupt
                DCD     0                ; TIM8 Update Interrupt
                DCD     0           ; TIM8 Trigger, Commutation, Direction change and Index Interrupt
                DCD     0                ; TIM8 Capture Compare Interrupt
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                 ; LP TIM1 interrupt
                DCD     0                                 ; Reserved
                DCD     0                   ; SPI3
                DCD     0                  ; UART4
                DCD     0                                 ; Reserved
                DCD     0               ; TIM6 and DAC1&3 underrun errors
                DCD     0               ; TIM7 and DAC2&4 underrun errors
                DCD     0          ; DMA2 Channel 1
                DCD     0          ; DMA2 Channel 2
                DCD     0          ; DMA2 Channel 3
                DCD     0          ; DMA2 Channel 4
                DCD     0          ; DMA2 Channel 5
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                  ; UCPD1
                DCD     0              ; COMP1, COMP2 and COMP3
                DCD     0                  ; COMP4
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                    ; CRS Interrupt
                DCD     0                   ; Serial Audio Interface 1 global interrupt
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                    ; FPU
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                    ; RNG global interrupt
                DCD     0                ; LP UART 1 interrupt
                DCD     0                ; I2C3 Event
                DCD     0                ; I2C3 Error
                DCD     0             ; DMAMUX overrun global interrupt
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0          ; DMA2 Channel 6
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                 ; CORDIC
                DCD     0                   ; FMAC

                AREA    |.text|, CODE, READONLY
				
; Reset handler
Reset_Handler    PROC                  
				 
				 LDR 	R0,=0xe000ed08			;SCB->VTOR
				 LDR	R1,=0x08000000			;FLASH_BASE
				 STR	R1,[R0]
				 
				 LDR	R0,=0x10000000			;CCM_SRAM
				 LDR	R1,=0
				 LDR	R2,=0x10002800			;10K
Ccm_Ram_Clear
				 STR	R1,[R0]
				 ADDS	R0,#4
				 CMP	R0,R2
				 BNE	Ccm_Ram_Clear
				 	
				 LDR	R0,=0x20000000			;SRAM1 + SRAM2
				 LDR	R1,=0
				 LDR	R2,=0x20005800			;16K + 6K
Sram_Clear
				 STR	R1,[R0]
				 ADDS	R0,#4
				 CMP	R0,R2
				 BNE	Sram_Clear
				 
                 LDR    R0, =Main
                 BX     R0
                 ENDP

				 END					
;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
