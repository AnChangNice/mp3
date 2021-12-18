#include "wm8988_sai.h"


static int SampleRate_Bits_To_DIV_FDL_Table[][10] = {
/*0-8000*/
{
	/* 8bits*/ 60, 50, //DIV, FDL
	/*16bits*/ 60, 50,
	/*20bits*/ 60, 50,
	/*24bits*/ 60, 50,
	/*32bits*/ 30, 100
},
/*1-11025*/
{
	/* 8bits*/ 34, 64,
	/*16bits*/ 34, 64,
	/*20bits*/ 34, 64,
	/*24bits*/ 34, 64,
	/*32bits*/ 34, 64,
},
/*2-12000*/
{
	/* 8bits*/ 50, 40,
	/*16bits*/ 50, 40,
	/*20bits*/ 50, 40,
	/*24bits*/ 40, 50,
	/*32bits*/ 25, 80
},
/*3-16000*/
{
	/* 8bits*/ 50, 30,
	/*16bits*/ 30, 50,
	/*20bits*/ 30, 50,
	/*24bits*/ 30, 50,
	/*32bits*/ 15, 100
},
/*4-22050*/
{
	/* 8bits*/ 34, 32,
	/*16bits*/ 34, 32,
	/*20bits*/ 17, 64,
	/*24bits*/ 17, 64,
	/*32bits*/ 17, 64
},
/*5-24000*/
{
	/* 8bits*/ 50, 20,
	/*16bits*/ 25, 40,
	/*20bits*/ 25, 40,
	/*24bits*/ 20, 50,
	/*32bits*/ 10, 100
},
/*6-32000*/
{
	/* 8bits*/ 25, 30,
	/*16bits*/ 15, 50,
	/*20bits*/ 15, 50,
	/*24bits*/ 15, 50,
	/*32bits*/ 5,  150
},
/*7-44100*/
{
	/* 8bits*/ 34, 16,
	/*16bits*/ 17, 32,
	/*20bits*/ 8,  68,
	/*24bits*/ 8,  68,
	/*32bits*/ 8,  68
},
/*8-48000*/
{
	/* 8bits*/ 25, 20,
	/*16bits*/ 10, 50,
	/*20bits*/ 10, 50,
	/*24bits*/ 10, 50,
	/*32bits*/ 5,  100
},
/*9-96000*/
{
	/* 8bits*/ 5, 50,
	/*16bits*/ 5, 50,
	/*20bits*/ 5, 50,
	/*24bits*/ 5, 50,
	/*32bits*/ 1, 250
}
};
void SAI2_SetSampleRateAndBits(int sampleRate, int bits)
{
	int DIV = 0, FRL = 0, DS = 0, DMA_DS = 0;
	int i, j;
	switch (sampleRate)
	{
	case  8000: i = 0; break;
	case 11025: i = 1; break;
	case 12000: i = 2; break;
	case 16000: i = 3; break;
	case 22050: i = 4; break;
	case 24000: i = 5; break;
	case 32000: i = 6; break;
	case 44100: i = 7; break;
	case 48000: i = 8; break;
	case 96000: i = 9; break;
	default:    i = 0; break;
	}
	switch (bits)
	{
	case  8: j = 0; DS = 2; DMA_DS = 0; break;
	case 16: j = 2; DS = 4; DMA_DS = 1; break;
	case 20: j = 4; DS = 5; DMA_DS = 2; break; //DMA only support 8,16,32bits transfer
	case 24: j = 6; DS = 6; DMA_DS = 2; break; //DMA only support 8,16,32bits transfer
	case 32: j = 8; DS = 7; DMA_DS = 2; break;
	default: j = 0; DS = 2; DMA_DS = 1; break;
	}

	DIV = SampleRate_Bits_To_DIV_FDL_Table[i][j];
	FRL = SampleRate_Bits_To_DIV_FDL_Table[i][j+1];

	//Set MCKDIV
	hsai_BlockA2.Instance->CR1 &= ~SAI_xCR1_MCKDIV_Msk; //Clear MCKDIV
	hsai_BlockA2.Instance->CR1 |= DIV << SAI_xCR1_MCKDIV_Pos;
	//Set FRL
	hsai_BlockA2.Instance->FRCR &= ~SAI_xFRCR_FRL_Msk; //Clear FRL
	hsai_BlockA2.Instance->FRCR |= (FRL-1) << SAI_xFRCR_FRL_Pos;
	//Set DS
	hsai_BlockA2.Instance->CR1 &= ~SAI_xCR1_DS_Msk; //Clear MCKDIV
	hsai_BlockA2.Instance->CR1 |= DS << SAI_xCR1_DS_Pos;
	//Set FSALL
	hsai_BlockA2.Instance->FRCR &= ~SAI_xFRCR_FSALL_Msk; //Clear FSALL
	hsai_BlockA2.Instance->FRCR |= ((FRL>>1)-1) << SAI_xFRCR_FSALL_Pos;

	//SAI DMA set to fit the bits.
	DMA_Stream_TypeDef *hdma_stream = hsai_BlockA2.hdmatx->Instance;
	uint32_t dma_control_val = hdma_stream->CR;
	
	dma_control_val &= (~DMA_SxCR_MSIZE); //Clear memory data size
	dma_control_val &= (~DMA_SxCR_PSIZE_Msk); //Clear peripheral data size

	dma_control_val |= (DMA_DS << DMA_SxCR_MSIZE_Pos); //Set memory data size
	dma_control_val |= (DMA_DS << DMA_SxCR_PSIZE_Pos); //Set peripheral data size

	//Write back to DMA channel.
	hdma_stream->CR = dma_control_val;
}

