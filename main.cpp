/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: iqgonzalez
 *
 * Created on 4 de abril de 2017, 10:42
 */

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



/*
 * 
 */

float halfFloat_to_singleFloat(uint16_t h) ;

int main() {
	uint16_t valores;
	float singleFloat;
	for(valores=0;valores<65535;valores++){
		singleFloat= halfFloat_to_singleFloat(valores);
		printf("\n El valor entero %hd se corresponde con %.50f",valores,singleFloat);
	}
	
	valores = 65535;
	singleFloat =halfFloat_to_singleFloat(valores);
	printf("\n El valor entero %hd se corresponde con el float16 %.50f",valores,singleFloat);
	
	return 0;
}
float halfFloat_to_singleFloat(uint16_t h) {
 uint16_t h_exp, h_sig;
 uint32_t f_sgn, f_exp, f_sig;
 float result;
 h_exp = (h & 0x7c00u);
 f_sgn = ((uint32_t) h & 0x8000u) << 16;
 switch (h_exp) {
 case 0x0000u: /* 0 or subnormal */
 h_sig = (h & 0x03ffu);
 /* Signed zero */
 if (h_sig == 0) {
 return *((float *) (&f_sgn));
 }
 /* Subnormal */
 h_sig <<= 1;
 while ((h_sig & 0x0400u) == 0) {
 h_sig <<= 1;
 h_exp++;
 }
 f_exp = ((uint32_t) (127 - 15 - h_exp)) << 23;
 f_sig = ((uint32_t) (h_sig & 0x03ffu)) << 13;
 f_sgn = f_sgn + f_exp + f_sig;
 return *((float *) (&f_sgn));
 case 0x7c00u: /* inf or NaN */
 /* All-ones exponent and a copy of the significand */
 f_sgn = f_sgn + 0x7f800000u + (((uint32_t) (h & 0x03ffu)) << 13);
 return *((float *) (&f_sgn));
 default: /* normalized */
 /* Just need to adjust the exponent and shift */
 f_sgn = f_sgn + (((uint32_t) (h & 0x7fffu) + 0x1c000u) << 13);
 return *((float *) (&f_sgn));
 }
}



