/*
 * wm8988.c
 *
 *  Created on: Oct 12, 2021
 *      Author: AnChangNice
 */

 #include "wm8988.h"
 #include <string.h>

 /*
  * Internal Macros
  * */
 #define WM8988_BITS_MASK(bits, shift) (((0x01U << (bits)) - 0x01U)<<(shift))

 #define WM8988_IIC_ADDR (0x1A<<1U)

 #define WM8988_REG_WRITE(reg, value)

 #define WM8988_CHECK(val)  while (!(val))

 #define WM8988_WRITE_REG(n)  WM8988_CHECK(WM8988_OK == WM8988_IIC_Write(n, REG.R##n.val))

 /*
  *
  * Internal Variables
  * */
 static const uint16_t reg_init[] = {
 /*R00*/ 0x0097, // 010010111
 /*R01*/ 0x0097, // 010010111
 /*R02*/ 0x0079, // 001111001
 /*R03*/ 0x0079, // 001111001
 /*R04*/ //0x0000,// Reserved
 /*R05*/ 0x0008, // 000001000
 /*R06*/ //0x0000,// Reserved
 /*R07*/ 0x000A, // 000001010
 /*R08*/ 0x0000, // 000000000
 /*R09*/ //0x0000,// Reserved
 /*R10*/ 0x00FF, // 011111111
 /*R11*/ 0x00FF, // 011111111
 /*R12*/ 0x000F, // 000001111
 /*R13*/ 0x000F, // 000001111
 /*R15*/ 0x0000, // RESET
 /*R16*/ 0x0000, // 000000000
 /*R17*/ 0x007B, // 001111011
 /*R18*/ 0x0000, // 000000000
 /*R19*/ 0x0032, // 000110010
 /*R20*/ 0x0000, // 000000000
 /*R21*/ 0x00C3, // 011000011
 /*R22*/ 0x00C3, // 011000011
 /*R23*/ 0x00C0, // 011000000
 /*R24*/ 0x0000, // 000000000
 /*R25*/ 0x0000, // 000000000
 /*R26*/ 0x0000, // 000000000
 /*R27*/ 0x0000, // 000000000
 /*R31*/ 0x0000, // 000000000
 /*R32*/ 0x0000, // 000000000
 /*R33*/ 0x0000, // 000000000
 /*R34*/ 0x0050, // 001010000
 /*R35*/ 0x0050, // 001010000
 /*R36*/ 0x0050, // 001010000
 /*R37*/ 0x0050, // 001010000
 /*R38*/ //0x0050,// Reserved
 /*R39*/ //0x0050,// Reserved
 /*R40*/ 0x0079, // 001111001
 /*R41*/ 0x0079, // 001111001
 /*R42*/ //0x0079,// Reserved
 /*R67*/ 0x0000, // 000000000
 };

 /* This variable declared all registers and its bits. */
 static WM8988_REG_t REG;

 /* High Level API */
 int WM8988_Init(void)
 {
     // Reset all REG bits with its default value.
     memcpy((void *)&REG, (const void *)&reg_init, sizeof(WM8988_REG_t));

     //R15 - writing to this register resets all register to their default state.
     WM8988_WRITE_REG(15);

     //Left Input volume
     REG.R0.bits.LINVOL = 23; //0dB
     REG.R0.bits.LZCEN = 0;
     REG.R0.bits.LINMUTE = 1;
     REG.R0.bits.LIVU = 0;
     WM8988_WRITE_REG(0);

     //Right Input volume
     REG.R1.bits.RINVOL = 23; //0dB
     REG.R1.bits.RZCEN = 0;
     REG.R1.bits.RINMUTE = 1;
     REG.R1.bits.RIVU = 0;
     WM8988_WRITE_REG(1);

     //LOUT1 volume
     REG.R2.bits.LOUT1VOL = 121; //0dB
     REG.R2.bits.LO1ZC = 0;
     REG.R2.bits.LO1VU = 1;
     WM8988_WRITE_REG(2);

     //ROUT1 volume
     REG.R3.bits.ROUT1VOL = 121;
     REG.R3.bits.RO1ZC = 0;
     REG.R3.bits.RO1VU = 1;
     WM8988_WRITE_REG(3);

     //ADC & DAC Control
     REG.R5.bits.ADCHPD = 1;
     REG.R5.bits.DEEMP = 0;
     REG.R5.bits.DACMU = 0;
     REG.R5.bits.HPOR = 0;
     REG.R5.bits.ADCPOL = 0;
     REG.R5.bits.DACDIV2 = 0;
     REG.R5.bits.ADCDIV2 = 0;
     WM8988_WRITE_REG(5);

     //Audio Interface
     REG.R7.bits.FORMAT = 2;    //I2S Format
     REG.R7.bits.WL = 0;        //16 bits
     REG.R7.bits.LRP = 0;       //normal LRCLK polarity
     REG.R7.bits.LRSWAP = 0;    //output left and right data as normal
     REG.R7.bits.MS = 0;        //Enable Slave Mode
     REG.R7.bits.BCLKINV = 0;   //BCLK not inverted
     WM8988_WRITE_REG(7);

     //Sample rate
     REG.R8.bits.USB = 1;     //USB Mode
     REG.R8.bits.SR = 17;     //44100
     REG.R8.bits.CLKDIV2 = 1; //MCLK is divided by 2
     REG.R8.bits.BCM = 0;     // BCM function disabled
     WM8988_WRITE_REG(8);

     //Left DAC volume
     REG.R10.bits.LDACVOL = 255;
     REG.R10.bits.LDVU = 0;
     WM8988_WRITE_REG(10);

     //Right DAC volume
     REG.R11.bits.RDACVOL = 255;
     REG.R11.bits.RDVU = 0;
     WM8988_WRITE_REG(11);

     //Bass control
     REG.R12.bits.BASS = 15;
     REG.R12.bits.REV = 0;
     REG.R12.bits.BC = 0;
     REG.R12.bits.BB = 0;
     WM8988_WRITE_REG(12);

     //Treble control
     REG.R13.bits.TRBL = 15;
     REG.R13.bits.REV = 0;
     REG.R13.bits.TC = 0;
     WM8988_WRITE_REG(13);

#if 0
     //Reset
     REG.R15.bits.RESET = XX;
     WM8988_WRITE_REG(15);
#endif

     //3D control
     REG.R16.bits._3DEN = 0;
     REG.R16.bits._3DDEPTH = 0;
     REG.R16.bits._3DLC = 0;
     REG.R16.bits._3DUC = 0;
     REG.R16.bits.MODE3D = 0;
     WM8988_WRITE_REG(16);

     //ALC1
     REG.R17.bits.ALCL = 11;
     REG.R17.bits.MAXGAIN = 7;
     REG.R17.bits.ALCSEL = 0;
     WM8988_WRITE_REG(17);

     //ALC2
     REG.R18.bits.HLD = 0;
     REG.R18.bits.REV = 0;
     REG.R18.bits.ALCZC = 0;
     WM8988_WRITE_REG(18);

     //ALC3
     REG.R19.bits.ATK = 2;
     REG.R19.bits.DCY = 3;
     WM8988_WRITE_REG(19);

     //Noise Gate
     REG.R20.bits.NGAT = 0;
     REG.R20.bits.NGG = 1;
     REG.R20.bits.NGTH = 0;
     WM8988_WRITE_REG(20);

     //Left ADC volume
     REG.R21.bits.LADCVOL = 195;
     REG.R21.bits.LAVU = 1;
     WM8988_WRITE_REG(21);

     //Right ADC volume
     REG.R22.bits.RADCVOL = 195;
     REG.R22.bits.RAVU = 1;
     WM8988_WRITE_REG(22);

     //Additional control(1)
     REG.R23.bits.TOEN = 0;
     REG.R23.bits.DACINV = 0;
     REG.R23.bits.DATSEL = 0;
     REG.R23.bits.DMONOMIX = 0;
     REG.R23.bits.VSEL = 2;
     REG.R23.bits.TSDEN = 1;
     WM8988_WRITE_REG(23);

     //Additional control(2)
     REG.R24.bits.DACOSR = 1;
     REG.R24.bits.ADCOSR = 1;
     REG.R24.bits.LRCM = 0;
     REG.R24.bits.TRI = 0;
     REG.R24.bits.REV = 0;
     REG.R24.bits.HPCOMEN = 1;
     REG.R24.bits.LCOMEN = 1;
     WM8988_WRITE_REG(24);

     //Pwr Mgmt (1)
     REG.R25.bits.DIGENB = 0;
     REG.R25.bits.REV = 0;
     REG.R25.bits.ADCR = 0;
     REG.R25.bits.ADCL = 0;
     REG.R25.bits.AINR = 0;
     REG.R25.bits.AINL = 0;
     REG.R25.bits.VREF = 1;
     REG.R25.bits.VMIDSEL = 1;
     WM8988_WRITE_REG(25);

     //Pwr Mgmt (2)
     REG.R26.bits.REV = 0;
     REG.R26.bits.ROUT2 = 1;
     REG.R26.bits.LOUT2 = 1;
     REG.R26.bits.ROUT1 = 1;
     REG.R26.bits.LOUT1 = 1;
     REG.R26.bits.DACR = 1;
     REG.R26.bits.DACL = 1;
     WM8988_WRITE_REG(26);

     //Additional Control (3)
     REG.R27.bits.REV = 0;
     REG.R27.bits.HPFLREN = 1;
     REG.R27.bits.VROI = 0;
     WM8988_WRITE_REG(27);

     //ADC input mode
     REG.R31.bits.REV = 0;
     REG.R31.bits.LDCM = 0;
     REG.R31.bits.RDCM = 0;
     REG.R31.bits.MONOMIX = 0;
     REG.R31.bits.DS = 0;
     WM8988_WRITE_REG(31);

     //ADCL signal path
     REG.R32.bits.REV = 0;
     REG.R32.bits.LMICBOOST = 0;
     REG.R32.bits.LINSEL = 0;
     WM8988_WRITE_REG(32);

     //ADCR signal path
     REG.R33.bits.REV = 0;
     REG.R33.bits.RMICBOOST = 0;
     REG.R33.bits.RINSEL = 0;
     WM8988_WRITE_REG(33);

     //Left out Mix (1)
     REG.R34.bits.LMIXSEL = 0;
     REG.R34.bits.REV = 0;
     REG.R34.bits.LI2LOVOL = 0;
     REG.R34.bits.LI2LO = 0;
     REG.R34.bits.LD2LO = 1;
     WM8988_WRITE_REG(34);

     //Left out Mix (2)
     REG.R35.bits.REV = 0;
     REG.R35.bits.RI2LOVOL = 0;
     REG.R35.bits.RI2LO = 0;
     REG.R35.bits.RD2LO = 0;
     WM8988_WRITE_REG(35);

     //Right out Mix (1)
     REG.R36.bits.RMIXSEL = 0;
     REG.R36.bits.REV = 0;
     REG.R36.bits.LI2ROVOL = 0;
     REG.R36.bits.LI2RO = 0;
     REG.R36.bits.LD2RO = 0;
     WM8988_WRITE_REG(36);

     //Right out Mix (2)
     REG.R37.bits.REV = 0;
     REG.R37.bits.RI2ROVOL = 0;
     REG.R37.bits.RI2RO = 0;
     REG.R37.bits.RD2RO = 1;
     WM8988_WRITE_REG(37);

     //LOUT2 volume
     REG.R40.bits.LOUT2VOL = 121;
     REG.R40.bits.LO2ZC = 0;
     REG.R40.bits.LO2VU = 1;
     WM8988_WRITE_REG(40);

     //ROUT2 volume
     REG.R41.bits.ROUT2VOL = 121;
     REG.R41.bits.RO2ZC = 0;
     REG.R41.bits.RO2VU = 1;
     WM8988_WRITE_REG(41);

     //Low Power Playback
     REG.R67.bits.REV = 0;
     REG.R67.bits.DACMIX_BIAS = 0;
     WM8988_WRITE_REG(67);

     return WM8988_OK;
 }

 int WM8988_SetSampleRate(int sampleRate)
 {
     /*
      * Here we use USB mode in order to support more sample rate.
      * */
     REG.R8.bits.CLKDIV2 = 1;
     REG.R8.bits.USB = 1;

     switch (sampleRate)
     {
     case 8000:
         REG.R8.bits.SR = 6;
         break;
     case 11025:
         REG.R8.bits.SR = 25;
         break;
     case 12000:
         REG.R8.bits.SR = 8;
         break;
     case 16000:
         REG.R8.bits.SR = 10;
         break;
     case 22050:
         REG.R8.bits.SR = 27;
         break;
     case 24000:
         REG.R8.bits.SR = 28;
         break;
     case 32000:
         REG.R8.bits.SR = 12;
         break;
     case 44100:
         REG.R8.bits.SR = 17;
         break;
     case 48000:
         REG.R8.bits.SR = 0;
         break;
     case 96000:
         REG.R8.bits.SR = 14;
         break;
     default:
         return WM8988_ERROR;
     }

     WM8988_WRITE_REG(8);

     return WM8988_OK;
 }
 int WM8988_SetChannels(int channels)
 {
     return WM8988_OK;
 }
 int WM8988_SetBits(int bits)
 {
     switch (bits)
     {
     case 8:
         REG.R7.bits.WL = 0;
         break;
     case 16:
         REG.R7.bits.WL = 0;
         break;
     case 20:
         REG.R7.bits.WL = 1;
         break;
     case 24:
         REG.R7.bits.WL = 2;
         break;
     case 32:
         REG.R7.bits.WL = 3;
         break;
     default:
         return WM8988_ERROR;
     }

     WM8988_WRITE_REG(7);

     return WM8988_OK;
 }
 int WM8988_SetVolume(int volume)
 {
     /*
      * 0-100 .bits. 0-255 .bits. -127-0dB
      * */
     int db = 255 * volume / 100;

     REG.R10.bits.LDACVOL = db;
     REG.R10.bits.LDVU    = 1;
     REG.R11.bits.RDACVOL = db;
     REG.R11.bits.RDVU    = 1;

     WM8988_WRITE_REG(10);
     WM8988_WRITE_REG(11);

     return WM8988_OK;
 }

 /* Low Level API */
 extern I2C_HandleTypeDef hi2c4;
 int WM8988_IIC_Write(uint8_t reg, uint16_t reg_val)
 {
     uint8_t mem = (reg<<1U) | ((reg_val & 0x100) >> 8U);
     uint8_t value = (uint8_t)(reg_val & 0xff);

     if (HAL_OK != HAL_I2C_Mem_Write(&hi2c4, (uint16_t)WM8988_IIC_ADDR, (uint16_t)mem, 1U, &value, 1U, HAL_MAX_DELAY))
     {
         return WM8988_ERROR;
     }

     return WM8988_OK;
 }

