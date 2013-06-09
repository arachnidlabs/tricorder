/* ========================================
 *
 * Copyright Cypress Semiconductor, 2012
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Cypress Semiconductor.
 *
 * ========================================
*/
#include <device.h>
#include <math.h>
#include <stdio.h>

#include "glcdfont.h"

// initializes the hardware
void Init_Hardware(void);

// Loads global variables with the proper configuration information for the IDAC
void IDAC_DMA_Config(void);

// intializes the sinewave generation DMA channel
void Init_SineDMA(void);

// calibrates the offsets in the system for all gains
void Calibrate(void);

// wait for an ADC conversion to complete.  Result is stored in global
// variable ADC_Result
void WaitForADC(void);

// adjusts the ADC input stages to alter the gain
void SetADCGain(uint8 gain);

// choose slow (comment out this define) or high speed operation.  Slow speed has 10 x the numbers of points in the sinewave table, but tops out at 10 Khz limiting the range of the device
#define HIGH_SPEED

// number of samples in 1/4 of the wave table
#ifndef HIGH_SPEED
#define TABLE_SIZE 64
#else
#define TABLE_SIZE 13
#endif

// size and type of the samples, makes later calculations 
// easier if you need to change them
typedef uint8 SAMPLE_SIZE;

// Sine table, first 1/4 wave from 0 to pi/2
// to generate entire sine wave, run through first 1/4,then second 1/4, switch direction of IDAC (sink - source)
// then run through again first and second 1/4.
#ifndef HIGH_SPEED
SAMPLE_SIZE sine_tableq1q3[TABLE_SIZE] = {13,19,25,31,37,44,50,56,62,68,74,80,86,92,98,103,109,115,120,126,131,136,142,147,152,157,162,167,171,176,180,185,189,193,197,201,205,208,212,215,219,222,225,228,231,233,236,238,240,242,244,246,247,249,250,251,252,253,254,254,255,255,255,255};
#else
SAMPLE_SIZE sine_tableq1q3[TABLE_SIZE] = {31,61,90,119,145,169,191,210,226,238,248,253,255};
#endif

// Sine table, second 1/4 wave from pi/2 to pi
// to generate entire sine wave, run through first 1/4,then second 1/4, switch direction of IDAC (sink - source)
// then run through again first and second 1/4.
#ifndef HIGH_SPEED
SAMPLE_SIZE sine_tableq2q4[TABLE_SIZE] = {255,254,254,253,252,251,250,249,247,246,244,242,240,238,236,233,231,228,225,222,219,215,212,208,205,201,197,193,189,185,180,176,171,167,162,157,152,147,142,136,131,126,120,115,109,103,98,92,86,80,74,68,62,56,50,44,37,31,25,19,13,6,0,6};
#else
SAMPLE_SIZE sine_tableq2q4[TABLE_SIZE] = {253,248,238,226,210,191,169,145,119,90,61,31,0};
#endif

// determine the TERMOUT signal for each of the DMA channels
#define Sine_DMA_TermOut ((Sine_DMA__TERMOUT0_EN ? TD_TERMOUT0_EN : 0)| (Sine_DMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0))

// DMA variables
uint8 DMA_Channel; // DMA channel handle
uint8 tds_q1_sink, tds_q2_sink, tds_switch_IDAC_to_source, tds_source_cal, tds_q3_source, tds_q4_source, tds_switch_IDAC_to_sink, tds_sink_cal; // TD handles
// Variables to hold the IDAC configurations
uint8 IDAC_sink_config, IDAC_source_config;
// variabes to hold the calibration information for each IDAC direction
uint8 IDAC_sink_cal, IDAC_source_cal;

// TIA feedback resistances
float afFeedbackR[] = {995};//{994}; // {1000600};

// low and high limits on resistance measurements:
#ifndef HIGH_SPEED
#define RLOW_LIMIT 0 // 10 // for 1 K feedback //12000 // for 1 Meg feedback
#else
#define RLOW_LIMIT 0 // 10 // for 1 K feedback //12000 // for 1 Meg feedback
#endif
#define RHIGH_LIMIT 5000000 // 300000 // for 1 K feedback // 220000000 // for 1 Meg feedback

// low and high thresholds for gain switching
#define LOW_LIMIT 0.1

// I like pi
#define PI 3.141592

// possible sinewave freuencies
//uint16 aFreq[] = {10,20,50,100,200,500,1000,2000,5000,10000};
#ifndef HIGH_SPEED
uint16 aFreq[] = {100,200,500,1000,2000,5000,10000};
#else
uint32 aFreq[] = {100,200,500,1000,2000,5000,10000,20000,50000,94000};
#endif
// dividers for associated sinewave frequencies
//uint16 aDivider[] = {25780,12890,5155,2577,1288,515,257,128,51,25};
#ifndef HIGH_SPEED
uint16 aDivider[] = {2535,1267,633,253,124,62,24};
#else
uint16 aDivider[] = {12670,6340,2535,1267,633,253,124,62,24,12};
#endif
// ADC clock divider value for setting the ADC clock speed.  based on a 66 Mhz bus clk
//uint16 dDivider[] = {500,500,200,200,100,100,50,50,25,25};
#ifndef HIGH_SPEED
uint16 dDivider[] = {50,50,50,50,50,50,50};
#else
uint16 dDivider[] = {50,50,50,50,50,50,50,50,50,50};
#endif
// number of possible_frequencies
#ifndef HIGH_SPEED
#define FPOSSIBLE 7
#else
#define FPOSSIBLE 10
#endif

// operation mode, series, parallel, mag phase, D Q
// 0 series, 1 parallel, 2 mag phase, 3 D Q
typedef enum {SERIES = 0, PARALLEL = 1, MAG_PHASE = 2, Q_MODE = 3, D_MODE = 4} IMPEDANCE_MODE;
#define NUMBER_OF_MODES 5

// the number of gains implemented with the ADC input stage
#define ADC_GAINS 1
//	gain	1/4	1/2	1	2	4	8	16	32	64	128
//	index	0	1	2	3	4	5	6	7	8	9
// stores the signal chain offset for the TIA
int32 Offset_TIA_IP[FPOSSIBLE], Offset_TIA_IQ[FPOSSIBLE];
// stores the signal chain offset for the excitation drive
int32 Offset_Excitation_IP[FPOSSIBLE], Offset_Excitation_IQ[FPOSSIBLE];

// character string buffer for LCD display
char szBuffer[32];  

// enumerated types to improve readability of the code
typedef enum {IN_PHASE = 0, IN_QUADRATURE = 1} PHASE_SELECT;
typedef enum {EXCITATION = 0, TIA = 1} SOURCE_SELECT;

// end of conversion flag set by EOC interrupt
uint8 EOC_Flag = 0;

// for debugging to remove noise, mask off LSb's
// to reduce resolution, while maintaining oversample rate
#define RESULT_MASK 0xFFFFFFFF

// status register mask for the overload condition
#define CLIPPING_MASK 0x01

// status register mask for the button
#define BUTTON_F_MASK 0x02

// misc definitions for DMA
#define Sine_DMA_SRC_BASE (CYDEV_SRAM_BASE)
#define Sine_DMA_DST_BASE (CYDEV_PERIPH_BASE)

#define LCD_CUSTOM_0 '0'
#define LCD_CUSTOM_1 '1'
#define LCD_CUSTOM_2 '2'
#define LCD_CUSTOM_3 '3'
#define LCD_CUSTOM_4 '4'
#define LCD_CUSTOM_5 '5'
#define LCD_CUSTOM_6 '6'
#define LCD_CUSTOM_7 '7'

void main()
{
	uint16 divider;  // varaible that holds the clock divider index for driving the DMA
	PHASE_SELECT phase;  // selects the phase clock for the up mixer
	SOURCE_SELECT source; // selects the source for the mixer, either the excitation or the TIA
	IMPEDANCE_MODE Op_Mode = SERIES;
	uint8 ADC_Gain = 0; // variable that holds the present ADC gain
	uint8 IDAC_Range = 0; // variable to hold the present setting of the IDAC: 0 -> 32 uA, 1 -> 255 uA, 2 -> 2 mA
	uint8 status = 0; // copy of the status register
	uint8 toss = 0; // variable to indicate the current sample should be thrown away
	
	int32 Excite_In_Phase;		// 32 bit variables to hold ADC results for each input
	int32 Excite_In_Quadrature;
	int32 Measured_In_Phase;
	int32 Measured_In_Quadrature;
	
	float Mag_Excite;  // floats for holding magnitude and phase of the excitation voltage
	float Phase_Excite;
	
	float Mag_TIA;	// floats for holding magnitude and phase of the TIA voltage
	float Phase_TIA;
	
	float Omega; // frequency in radians
	float Mag_Z;  // magnitude of impedance
	float Phi_Z;  // angle of impedance
	float X;  // imaginary impedance
	float R;  // equivalent resistance
	float C;  // equivalent capacitence
	float L;  // equivalent inductance
	float Q;  // quality factor
	float D;  // dissapation factor
	char scale_R;  // stores the scale of the resistance (K, M)
	char scale_X;  // stores the scale of the inductance / capacitence (m, u, n)
	char scale_Mag; 
	
	Init_Hardware();
	
	// update the user on the status
	sprintf(szBuffer,"Open circuit cal");
    
	LCD_Position(0,0);
	LCD_PrintString(szBuffer);
	
	Init_SineDMA();
	// cannot call calibrate unless you have initialized the Sine DMA
	// since the sine DMA hardware generates important signals for the system
	// to operate
	Calibrate();
	
	// set the inititial divider index to FPOSSIBLE - 1 (highest frequency)
	divider = FPOSSIBLE-1;
	Divider_WritePeriod(aDivider[divider]);
	ADC_Clock_Ext_SetDividerRegister(dDivider[divider],0);
	
	LCD_ClearDisplay();
		
    for(;;)
    {
		status = Status_Reg_Read();
		
		// begin by measuring the in phase result of the TIA voltage
		source = TIA;
		Measure_Mux_Select(source);
		phase = IN_PHASE;
		Phase_Write(phase);
		
		// setting this bit arms the Start Of Conversion (SOC)
		// state machine to trigger on the next rising edge
		// of the in-phase clock. Starting conversions on the
		// rising edge of the in phase clock ensures that
		// the samples will be averaged over the same part of 
		// the cycle every time
		SOC_Go_Write(1);
		
		// waits for the End Of Conversion (EOC) flag to be
		// set by the EOC ISR
		WaitForADC();
		// get the result of the conversion and mask out RESULT_MASK bits
		Measured_In_Phase = -ADC_GetResult32();
		
		// clearing the SOC_Go bit resets the SOC state machine
		SOC_Go_Write(0);
		
		// measure the in quadrature part of the TIA voltage
		source = TIA;
		Measure_Mux_Select(source);
		phase = IN_QUADRATURE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);

		WaitForADC();
		Measured_In_Quadrature = -ADC_GetResult32();

		SOC_Go_Write(0);
		
		// calculate the magnitude of the TIA voltage by taking the
		// square root of the sum of the squares.  The offset determined during calibration is removed
		Mag_TIA = PI/2*sqrt(pow(ADC_CountsTo_Volts(Measured_In_Phase-Offset_TIA_IP[divider]),2) + pow(ADC_CountsTo_Volts(Measured_In_Quadrature-Offset_TIA_IQ[divider]),2));
		
		// calculate the phase of the TIA voltage by taking the ArcTangent of the in quadrature value
		// over the in phase value.
		Phase_TIA = 180.0/PI*atan2(ADC_CountsTo_Volts(Measured_In_Quadrature-Offset_TIA_IQ[divider]),ADC_CountsTo_Volts(Measured_In_Phase-Offset_TIA_IP[divider]));
		//Phase_TIA = 180.0/PI*atan(ADC_CountsTo_Volts(Measured_In_Quadrature-Offset_TIA_IQ[divider])/ADC_CountsTo_Volts(Measured_In_Phase-Offset_TIA_IP[divider]));
		
		// repeat the above process for the excitation voltage
		source = EXCITATION;
		Measure_Mux_Select(source);
		phase = IN_PHASE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);
		
		WaitForADC();
		Excite_In_Phase = ADC_GetResult32();

		SOC_Go_Write(0);
		
		source = EXCITATION;
		Measure_Mux_Select(source);
		phase = IN_QUADRATURE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);

		WaitForADC();
		Excite_In_Quadrature = ADC_GetResult32();

		SOC_Go_Write(0);
		
		Mag_Excite = PI/2*sqrt(pow(ADC_CountsTo_Volts(Excite_In_Phase-Offset_Excitation_IP[divider]),2) + pow(ADC_CountsTo_Volts(Excite_In_Quadrature-Offset_Excitation_IQ[divider]),2));
		Phase_Excite = 180.0/PI*atan2(ADC_CountsTo_Volts(Excite_In_Quadrature-Offset_Excitation_IQ[divider]),ADC_CountsTo_Volts(Excite_In_Phase-Offset_Excitation_IP[divider]));
		//Phase_Excite = 180.0/PI*atan(ADC_CountsTo_Volts(Excite_In_Quadrature-Offset_Excitation_IQ[ADC_Gain])/ADC_CountsTo_Volts(Excite_In_Phase-Offset_Excitation_IP[ADC_Gain]));
		
		// calculate the equivalent impedance magnitude
		// R = Vexcite/VTIA*RFeedback
		Mag_Z = Mag_Excite/Mag_TIA*afFeedbackR[0];
		Phi_Z = Phase_TIA - Phase_Excite;
		
		Q = 1/tan(PI/2-Phi_Z*PI/180.0);
		D = 1/Q;
		
		// if the button is pressed, cycle through the different
		// frequencies of the sine wave
		/*if(Button_Freq_Read() ==  0)
		{
			divider++;
			divider %= FPOSSIBLE;
			Divider_WritePeriod(aDivider[divider]);
			ADC_Clock_Ext_SetDividerRegister(dDivider[divider],0);
		}
		
		if(Button_Mode_Read() == 0)
		{
			Op_Mode++;
			Op_Mode %= NUMBER_OF_MODES;
			LCD_ClearDisplay();
		}*/
		
		// equivalent circuit calculations
		// equivalent series calculation
		R = fabs(Mag_Z*cos(Phi_Z*PI/180.0));
		X = Mag_Z*sin(Phi_Z*PI/180.0);
		Omega = (2*PI*((float) aFreq[divider]));
		
		if(Op_Mode == PARALLEL)
		{
			// equivalent parallel calculation
			R = R*(1.0+1.0/pow(D,2));
			X = X*(1.0+pow(D,2));
		}
		
		// L C and D Q calculations
		if(X >= 0)
		{
			L = fabs(X)/Omega;
			C= 0;
		}
		else
		{
			L = 0;
			C = 1.0/(fabs(X)*Omega);
		}
		
		scale_X = ' ';
		if(((L < 1) && (L >= 0.001)) || ((C < 1) && (C >= 0.001)))
		{
			L = L * 1000.0;
			C = C * 1000.0;
			scale_X = 'm';
		}
		else if(((L < 0.001) && (L >= 0.000001)) || ((C < 0.001) && (C >= 0.000001)))
		{
			L = L * 1000000.0;
			C = C * 1000000.0;
			scale_X = 'u';
		}
		else if(((L < 0.000001) && (L >= 0.000000001)) || ((C < 0.000001) && (C >= 0.000000001)))
		{
			L = L * 1000000000.0;
			C = C * 1000000000.0;
			scale_X = 'n';
		}
		else if(((L < 0.000000001) && (L >= 0.000000000001)) || ((C < 0.000000001) && (C >= 0.000000000001)))
		{
			L = L * 1000000000000.0;
			C = C * 1000000000000.0;
			scale_X = 'p';
		}
		
		scale_R = ' ';
		if((R >= 1000) && (R < 1000000))
		{
			R = R / 1000.0;
			scale_R = 'K';
		}
		else if(R >= 1000000)
		{
			R = R / 1000000.0;
			scale_R = 'M';
		}
		
		scale_Mag = ' ';
		if((Mag_Z >= 1000) && (Mag_Z < 1000000))
		{
			scale_Mag = 'K';
		}
		else if(Mag_Z >= 1000000)
		{
			scale_Mag = 'M';
		}
		
		toss = 0;
		// adjust the Drive signal if the TIA output is too high or too low
		if((Mag_TIA < LOW_LIMIT) && (IDAC_Range == 0))
		{
			IDAC_Range = 1;
			Divider_Stop();
			IDrive_SetRange(IDrive_RANGE_255uA);
			IDAC_DMA_Config();
			Divider_Start();
			CyDelay(20);
			Status_Reg_Read();
			toss = 1;
		}
		else if((Mag_TIA < LOW_LIMIT) && (IDAC_Range == 1))
		{
			IDAC_Range = 2;
			Divider_Stop();
			IDrive_SetRange(IDrive_RANGE_2mA);
			IDAC_DMA_Config();
			Divider_Start();
			CyDelay(20);
			Status_Reg_Read();
			toss = 1;
		}
		else if(((status & CLIPPING_MASK) > 0) && (IDAC_Range == 2))
		{
			IDAC_Range = 1;
			Divider_Stop();
			IDrive_SetRange(IDrive_RANGE_255uA);
			IDAC_DMA_Config();
			Divider_Start();
			CyDelay(20);
			Status_Reg_Read();
			toss = 1;
		}
		else if(((status & CLIPPING_MASK) > 0) && (IDAC_Range == 1))
		{
			IDAC_Range = 0;
			Divider_Stop();
			IDrive_SetRange(IDrive_RANGE_32uA);
			IDAC_DMA_Config();
			Divider_Start();
			CyDelay(20);
			Status_Reg_Read();
			toss = 1;
		}
		
		
		if((status & CLIPPING_MASK) > 0 && IDAC_Range == 0) 
		{
			sprintf(szBuffer,"    CLIPPING    ");
			LCD_Position(0,0);
			LCD_PrintString(szBuffer);
		}
		else if(toss == 1) 
		{
			sprintf(szBuffer,"  AUTO RANGING  ");
			LCD_Position(0,0);
			LCD_PrintString(szBuffer);
		}
		else if((Mag_Z < RHIGH_LIMIT) && (Mag_Z > RLOW_LIMIT))
		{
			switch(Op_Mode)
			{
				case SERIES:	
					// equivalent series circuit
					sprintf(szBuffer,"%3.2f%c%c    ", R, scale_R, 0xf4);
					LCD_Position(0,0);
					LCD_PrintString(szBuffer);
							
					sprintf(szBuffer,"%3.1f%c%c   ", C == 0 ? L : C , scale_X, X >= 0 ? 'H' : 'F');
					LCD_Position(0,9);
					LCD_PrintString(szBuffer);
					break;
				case PARALLEL:
					// equivalent series circuit
					sprintf(szBuffer,"%3.2f%c%c     ", R, scale_R, 0xf4);
					LCD_Position(0,0);
					LCD_PrintString(szBuffer);
							
					sprintf(szBuffer,"%3.1f%c%c    ", C == 0 ? L : C , scale_X, X >= 0 ? 'H' : 'F');
					LCD_Position(0,9);
					LCD_PrintString(szBuffer);
					break;
				case MAG_PHASE:
					// magnitude and phase
					sprintf(szBuffer,"%3.2f%c  ", scale_Mag == 'K' ? Mag_Z / 1000.0 : scale_R == 'M' ? Mag_Z / 1000000.0 : Mag_Z, scale_Mag );
					LCD_Position(0,0);
					LCD_PrintString(szBuffer);
							
					sprintf(szBuffer,"%2.1f%c ", Phase_TIA - Phase_Excite > 180 ? 180 - (Phase_TIA - Phase_Excite) : Phase_TIA - Phase_Excite, 0xdf);
					//sprintf(szBuffer,"%2.1f%c ", Phase_TIA - Phase_Excite, 0xdf);
					LCD_Position(0,8);
					LCD_PrintString(szBuffer);
					break;
				case Q_MODE:
					// magnitude and phase
					sprintf(szBuffer,"Q: %3.1f      " , fabs(Q));
					LCD_Position(0,0);
					LCD_PrintString(szBuffer);
					break;
				case D_MODE:
					// magnitude and phase
					sprintf(szBuffer,"D: %3.1f      " , fabs(D));
					LCD_Position(0,0);
					LCD_PrintString(szBuffer);
					break;
			}
		}
		else if(Mag_Z >= RHIGH_LIMIT) 
		{
			sprintf(szBuffer,"   OVER RANGE    ");
			LCD_Position(0,0);
			LCD_PrintString(szBuffer);
		}
		else if(Mag_Z < RLOW_LIMIT) 
		{
			sprintf(szBuffer,"  UNDER RANGE    ");
			LCD_Position(0,0);
			LCD_PrintString(szBuffer);
		}
		
		sprintf(szBuffer,"F: %ld Hz   ",aFreq[divider]);
		LCD_Position(1,0);
		LCD_PrintString(szBuffer);
		
		LCD_Position(1,12);
		switch(Op_Mode)
		{
		case SERIES:	
			// display series connection
			LCD_PutChar(LCD_CUSTOM_1);
			LCD_PutChar(LCD_CUSTOM_0);
			LCD_PutChar(LCD_CUSTOM_2);
			LCD_PutChar(LCD_CUSTOM_1);
			break;
		case PARALLEL:
			// display parallel connection
			LCD_PutChar(' ');
			LCD_PutChar(LCD_CUSTOM_4);
			LCD_PutChar(LCD_CUSTOM_3);
			LCD_PutChar(LCD_CUSTOM_5);
			break;
		case MAG_PHASE:
			// magnitude and phase
			LCD_PutChar(' ');
			LCD_PutChar(LCD_CUSTOM_7);
			LCD_PutChar(' ');
			LCD_PutChar(LCD_CUSTOM_6);
			break;
		case Q_MODE:
			LCD_PutChar(' ');
			LCD_PutChar(' ');
			LCD_PutChar('Q');
			LCD_PutChar(' ');
			break;
		case D_MODE:
			LCD_PutChar(' ');
			LCD_PutChar(' ');
			LCD_PutChar('D');
			LCD_PutChar(' ');
			break;
		}
    }
}

LCD_buffer lcd_buf;

void Init_Hardware(void)
{
	CYGlobalIntEnable
	
	Phase_Write(0);
//	Button_Freq_Write(1);
//	Button_Mode_Write(1);
	SOC_Go_Write(0);
	
	Divider_Start();
	Divider_WritePeriod(aDivider[0]);
	
    IDrive_Start();
    Drive_Start();
	
	TIA_Start();
	
    Measure_Mux_Start();
	Measure_Mux_Select(0);
	
    ADC_Start();
	ADC_IRQ_Enable();
	
	Clipping_Sense_Start();
	
	LCD_Start();
    LCD_Update(&lcd_buf, 0, 0); // Give the LCD a buffer to use.
	LCD_ClearDisplay(); 
	
    PWM_1_Start();
    
	return;
}

void IDAC_DMA_Config(void)
{
	IDAC_sink_config  = IDrive_CR1;  // get current configuration for the IDrive IDAC
	IDAC_source_config  = IDAC_sink_config;
	
	IDAC_sink_config &= ~IDrive_IDIR_MASK; // clear the direction bit
	IDAC_sink_config |= IDrive_IDIR_SINK;  // prepare the configuration for sinking
	
	IDAC_source_config &= ~IDrive_IDIR_MASK; // clear the direction bit
	IDAC_source_config |= IDrive_IDIR_SRC;  // prepare the configuration for sourcing
		
	// retrieve calibration for source mode
	IDrive_SetPolarity(IDrive_SOURCE);
	IDAC_source_cal = IDrive_TR; 
	
	// retrieve calibration for sink mode
	IDrive_SetPolarity(IDrive_SINK);
	IDAC_sink_cal = IDrive_TR;  
}

void Init_SineDMA(void)
{

	// prep the data for the first use
	IDAC_DMA_Config();
	
	/* Configure and report channel number of DMA hardware - Perform dma transaction in bursts of sizeof(SAMPLE_SIZE) bytes, Do Not Automaticaly 
	request carry out bursts (1), upper address bits of source are zero (0), upper address bits of 
	destination are zero (0) since all work will be done in SRAM */
	DMA_Channel = Sine_DMA_DmaInitialize((uint8) sizeof(SAMPLE_SIZE), 1, HI16(Sine_DMA_SRC_BASE), HI16(Sine_DMA_DST_BASE));	
	
	//	 Allocate Transaction Descriptors for the DMA channel
    tds_q1_sink = CyDmaTdAllocate();
	tds_q2_sink = CyDmaTdAllocate();
	tds_switch_IDAC_to_source = CyDmaTdAllocate();
	tds_source_cal = CyDmaTdAllocate();
	tds_q3_source = CyDmaTdAllocate();
	tds_q4_source = CyDmaTdAllocate();
	tds_switch_IDAC_to_sink = CyDmaTdAllocate();
	tds_sink_cal = CyDmaTdAllocate();
	
	
	// v
    // configure the forward sine table transaction discriptor (tds_forward_sink)
    // transmit (for this TD) a total of BUFFER_SIZE*sizeof(SAMPLE_SIZE) bytes.
    // When this TD is complete, move on to the TD tds_backward_sink
    // Enable the TD complete signal (TD_TERMOUT0_EN)
    // Enable increment source address (TD_INC_SRC_ADR)
	CyDmaTdSetConfiguration(tds_q1_sink, TABLE_SIZE*sizeof(SAMPLE_SIZE), tds_q2_sink, Sine_DMA_TermOut | TD_INC_SRC_ADR);
	
	// Configure the source and destination addresses
    // grab data from the sine table, start writing it
    // into the IExcite IDAC
	CyDmaTdSetAddress(tds_q1_sink, LO16((uint32) &(sine_tableq1q3[0])), LO16((uint32) &IDrive_Data));
	// ^
	
	
	// v
    // configure the backward sine table transaction discriptor (tds_backward_sink)
    // transmit (for this TD) a total of BUFFER_SIZE*sizeof(SAMPLE_SIZE) bytes.
    // When this TD is complete, move on to the TD tds_switch_IDAC_to_Source
    // Enable the TD complete signal (TD_TERMOUT0_EN)
    // Enable increment source address (TD_INC_SRC_ADR)
	// Automatically execute the next TD in the chain (TD_AUTO_EXEC_NEXT) when this TD completes
	CyDmaTdSetConfiguration(tds_q2_sink, TABLE_SIZE*sizeof(SAMPLE_SIZE), tds_switch_IDAC_to_source, Sine_DMA_TermOut | TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
	
	// Configure the source and destination addresses
    // grab data from the sine table, start writing it
    // into the IExcite IDAC
	CyDmaTdSetAddress(tds_q2_sink, LO16((uint32) &(sine_tableq2q4[0])), LO16((uint32) &IDrive_Data));
	// ^
	
	
	// v
    // configure the IDAC change mode transaction discriptor (tds_switch_IDAC_to_source)
    // transmit (for this TD) a total of sizeof(uint8) bytes.
    // When this TD is complete, move on to the TD tds_forward_source
	CyDmaTdSetConfiguration(tds_switch_IDAC_to_source, sizeof(uint8), tds_source_cal, TD_AUTO_EXEC_NEXT);
	
	// Configure the source and destination addresses
    // grab data from the comfiguration byte, write it into
    // IExcite_CR1
	CyDmaTdSetAddress(tds_switch_IDAC_to_source, LO16((uint32) &IDAC_source_config), LO16((uint32) &IDrive_CR1));
	// ^
	
	
	// v
    // configure the IDAC change mode transaction discriptor (tds_switch_IDAC_to_source)
    // transmit (for this TD) a total of sizeof(uint8) bytes.
    // When this TD is complete, move on to the TD tds_forward_source
	CyDmaTdSetConfiguration(tds_source_cal, sizeof(uint8), tds_q3_source, 0);
	
	// Configure the source and destination addresses
    // grab data from the comfiguration byte, write it into
    // IExcite_CR1
	CyDmaTdSetAddress(tds_source_cal, LO16((uint32) &IDAC_source_cal), LO16((uint32) &IDrive_TR));
	// ^
	

	// v
    // configure the forward sine table transaction discriptor (tds_forward_source)
    // transmit (for this TD) a total of BUFFER_SIZE*sizeof(SAMPLE_SIZE) bytes.
    // When this TD is complete, move on to the TD tds_backward_source
    // Enable the TD complete signal (TD_TERMOUT0_EN)
    // Enable increment source address (TD_INC_SRC_ADR)
	CyDmaTdSetConfiguration(tds_q3_source, TABLE_SIZE*sizeof(SAMPLE_SIZE), tds_q4_source, Sine_DMA_TermOut | TD_INC_SRC_ADR);
	
	// Configure the source and destination addresses
    // grab data from the sine table, start writing it
    // into the IExcite IDAC
	CyDmaTdSetAddress(tds_q3_source, LO16((uint32) &(sine_tableq1q3[0])), LO16((uint32) &IDrive_Data));
	// ^
	
	
	// v
    // configure the backward sine table transaction discriptor (tds_backward_source)
    // transmit (for this TD) a total of BUFFER_SIZE*sizeof(SAMPLE_SIZE) bytes.
    // When this TD is complete, move on to the TD tds_switch_IDAC_to_sink
    // Enable the TD complete signal (TD_TERMOUT0_EN)
    // Enable increment source address (TD_INC_SRC_ADR
	// Automatically execute the next TD in the chain (TD_AUTO_EXEC_NEXT) when this TD completes
	CyDmaTdSetConfiguration(tds_q4_source, TABLE_SIZE*sizeof(SAMPLE_SIZE), tds_switch_IDAC_to_sink, Sine_DMA_TermOut | TD_INC_SRC_ADR | TD_AUTO_EXEC_NEXT);
	
	// Configure the source and destination addresses
    // grab data from the sine table, start writing it
    // into the IExcite IDAC
	CyDmaTdSetAddress(tds_q4_source, LO16((uint32) &(sine_tableq2q4[0])), LO16((uint32) &IDrive_Data));
	// ^
	
	
	// v
    // configure the IDAC change mode transaction discriptor (tds_switch_IDAC_to_sink)
    // transmit (for this TD) a total of sizeof(uint8) bytes.
    // When this TD is complete, move on to the TD tds_forward_sink
	CyDmaTdSetConfiguration(tds_switch_IDAC_to_sink, sizeof(uint8), tds_sink_cal, TD_AUTO_EXEC_NEXT);
	
	// Configure the source and destination addresses
    // grab data from the comfiguration byte, write it into
    // IExcite_CR1
	CyDmaTdSetAddress(tds_switch_IDAC_to_sink, LO16((uint32) &IDAC_sink_config), LO16((uint32) &IDrive_CR1));
	// ^
	
	
	// v
    // configure the IDAC change mode transaction discriptor (tds_switch_IDAC_to_source)
    // transmit (for this TD) a total of sizeof(uint8) bytes.
    // When this TD is complete, move on to the TD tds_forward_source
	CyDmaTdSetConfiguration(tds_sink_cal, sizeof(uint8), tds_q1_sink, 0);
	
	// Configure the source and destination addresses
    // grab data from the comfiguration byte, write it into
    // IExcite_CR1
	CyDmaTdSetAddress(tds_sink_cal, LO16((uint32) &IDAC_sink_cal), LO16((uint32) &IDrive_TR));
	// ^
	
	
	// set the initial TD to tds
    CyDmaChSetInitialTd(DMA_Channel, tds_q1_sink);
	
	// enable the DMA channel, do not alter the source and destination addresses (1)
    CyDmaChEnable(DMA_Channel, 1);
	
	return;
}

void Calibrate(void)
{
	SOURCE_SELECT source;
	PHASE_SELECT phase;
	uint8 i = 0;
		
//	 disconnect IDAC for calibration
	IDrive_SW3 = IDrive_SW3 & ~0x80; 
	
	for(i = 0; i < FPOSSIBLE; i++)
	{
		// change the frequency
		Divider_WritePeriod(aDivider[i]);
		ADC_Clock_Ext_SetDividerRegister(dDivider[i],0);
		
		// measure offset for TIA in Phase
		
		source = TIA;
		Measure_Mux_Select(source);
		phase = IN_PHASE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);
		
		WaitForADC();
		Offset_TIA_IP[i] = -ADC_GetResult32();
		
		SOC_Go_Write(0);
		
		// measure offset for TIA in Quadrature
		
		source = TIA;
		Measure_Mux_Select(source);
		phase = IN_QUADRATURE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);
		
		WaitForADC();
		Offset_TIA_IQ[i] = -ADC_GetResult32();
		
		SOC_Go_Write(0);
		
		// measure offset for EXCITATION in Phase
		
		source = EXCITATION;
		Measure_Mux_Select(source);
		phase = IN_PHASE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);
		
		WaitForADC();
		Offset_Excitation_IP[i] = ADC_GetResult32();
		
		SOC_Go_Write(0);
		
		// measure offset for EXCITATION in Quadrature	
		
		source = EXCITATION;
		Measure_Mux_Select(source);
		phase = IN_QUADRATURE;
		Phase_Write(phase);
		
		SOC_Go_Write(1);
		
		WaitForADC();
		Offset_Excitation_IQ[i] = ADC_GetResult32();
	
		SOC_Go_Write(0);
	}
		
//	 reconnect IDAC to pin
	IDrive_SW3 = IDrive_SW3 | 0x80; 

	return;
}

void WaitForADC(void)
{
	while(EOC_Flag == 0)
	{
	}
	
	EOC_Flag = 0;
}


/* [] END OF FILE */
