#ifndef __CONFIG__H_
#define __CONFIG__H_

 /*=============================================================================
  *                Supported STM32F411xx/STM32F410xx devices
  *-----------------------------------------------------------------------------
  *        System Clock source                    | PLL (HSI)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 100000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 100000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                         | 2
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        HSI Frequency(Hz)                      | 16000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 16
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 400
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 4
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 3
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *----------------------------------------------------------------------------- */

#define DEBUG_PORT_BAUDRATE 9600
#define HCLK_FREQUENCY 100000000UL
#define APB2_FREQUENCY 100000000UL

#endif