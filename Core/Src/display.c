/*
 * display.c
 *
 *  Created on: 13. 12. 2021
 *      Author: Molnar & Nyiri
 */

#include "display.h"
uint8_t updateDigit = 1;
uint8_t displayTextPos = 0;
uint8_t direction = 0;

void updateDisplay(){
	char displayString[] = "MICHAL_MOLnAr_98352";
	for(int i = 1; i<5; i++){
		switch(updateDigit){
				case 1:
					DIGIT_1_ON;
					resetAllSegments();
					displayLetter(displayString[displayTextPos]);
					break;
				case 2:
					DIGIT_2_ON;
					resetAllSegments();
					displayLetter(displayString[displayTextPos+1]);
					break;
				case 3:
					DIGIT_3_ON;
					resetAllSegments();
					displayLetter(displayString[displayTextPos+2]);
					break;
				case 4:
					DIGIT_4_ON;
					resetAllSegments();
					displayLetter(displayString[displayTextPos+3]);
					break;
			}
			updateDigit = (updateDigit < 4) ? updateDigit+1 : 1;
			LL_mDelay(2);
			resetAllDigits();
	}

}

void shiftDisplayText(){
	if(displayTextPos < (20-4-1) && direction == 0){
		displayTextPos = displayTextPos+1;
	}
	else if(displayTextPos >= (20-4-1) && direction == 0){
		direction = 1;
		displayTextPos = displayTextPos-1;
	}
	else if(displayTextPos <= 0 && direction == 1){
		direction = 0;
		displayTextPos = displayTextPos+1;
	}
	else if(displayTextPos > 0 && direction == 1){
		displayTextPos = displayTextPos-1;
	}
}

void displayLetter(char letter){
	switch(letter){
		case 'A':
			setA();
			break;
		case 'a':
			seta();
			break;
		case 'b':
			setb();
			break;
		case 'C':
			setC();
			break;
		case 'c':
			setc();
			break;
		case 'd':
			setd();
			break;
		case 'E':
			setE();
			break;
		case 'F':
			setF();
			break;
		case 'G':
			setG();
			break;
		case 'H':
			setH();
			break;
		case 'h':
			seth();
			break;
		case 'I':
			setI();
			break;
		case 'J':
			setJ();
			break;
		case 'K':
			setK();
			break;
		case 'L':
			setL();
			break;
		case 'M':
			setM();
			break;
		case 'n':
			setn();
			break;
		case 'O':
			setO();
			break;
		case 'o':
			seto();
			break;
		case 'P':
			setP();
			break;
		case 'q':
			setq();
			break;
		case 'r':
			setr();
			break;
		case 'S':
			setS();
			break;
		case 't':
			sett();
			break;
		case 'U':
			setU();
			break;
		case 'u':
			setu();
			break;
		case 'V':
			setV();
			break;
		case 'W':
			setW();
			break;
		case 'X':
			setX();
			break;
		case 'y':
			sety();
			break;
		case 'Z':
			setZ();
			break;
		case ' ':
			resetAllSegments();
			break;
		case '_':
			setLine();
			break;


		case '1':
			setOne();
			break;
		case '2':
			setTwo();
			break;
		case '3':
			setThree();
			break;
		case '4':
			setFour();
			break;
		case '5':
			setFive();
			break;
		case '6':
			setSix();
			break;
		case '7':
			setSeven();
			break;
		case '8':
			setEight();
			break;
		case '9':
			setNine();
			break;
		case '0':
			setZero();
			break;
		default:
			setDot();
			break;
	}
}

void setAllSegments(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentDP_Pin);
}

void resetAllSegments(void){
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentDP_Pin);
}

void resetAllDigits(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);
}

void setA(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	// reset D
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);

}
void seta(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	// reset f
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);

}
void setb(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	// reset a,b
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
}
void setC(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	// reset B,C,G
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setc(void){
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setd(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setE(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
}
void setF(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
}
void setG(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setH(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
}
void seth(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);

}
void setI(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setJ(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setL(void){
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setn(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setO(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void seto(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setP(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
}
void setq(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void setr(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setS(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void sett(void){
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
}
void setU(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setu(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void sety(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}


// Disgusting letters :D
void setK(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);

}
void setM(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void setV(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);

}
void setW(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
}
void setX(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setZ(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}

// numbers
void setOne(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setTwo(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setThree(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
}
void setFour(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void setFive(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void setSix(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
}
void setSeven(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}
void setEight(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
}
void setNine(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentG_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
}
void setZero(void){
	LL_GPIO_ResetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_ResetOutputPin(GPIOA, segmentF_Pin);
	//reset
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
}

void setLine(void){
	LL_GPIO_ResetOutputPin(GPIOB, segmentD_Pin);

	LL_GPIO_SetOutputPin(GPIOA, segmentA_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentB_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentC_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentE_Pin);
	LL_GPIO_SetOutputPin(GPIOA, segmentF_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentG_Pin);
	LL_GPIO_SetOutputPin(GPIOB, segmentDP_Pin);
}
// and dot to end
void setDot(void){
	LL_GPIO_ResetOutputPin(GPIOB, segmentDP_Pin);
}
