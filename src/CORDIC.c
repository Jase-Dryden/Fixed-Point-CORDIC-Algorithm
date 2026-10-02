/*
 ============================================================================
 Name        : CORDIC.c
 Author      : Jase
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) {

	float num;
	printf("Enter in an angle in degrees\n");

	scanf("%f",&num); // Promps the user for an angle

	int angle = num * (1 << 16); // transforms a float into fixed point
	int x = 0b1001101101100100; // 0.607 in fixed point
	int y = 0b0000000000000000;
	int z = 0b0000000000000000;
	int d = 0;

	// atan 2^-i converted to fixed point to increase run speed
	int atan[16] = {0b1011010000000000000000,
				        0b110101001000010100111,
				        0b11100000100101000111,
				        0b1110010000000000001,
				        0b111001001110001011,
				        0b11100101000111000,
				        0b1110010100101010,
				        0b111001010010111,
				        0b11100101001100,
				        0b1110010100110,
				        0b111001010011,
				        0b11100101001,
				        0b1110010101,
				        0b111001010,
				        0b11100101,
				        0b1110011};
	int xnew = 0;
	int ynew = 0;
	int znew = 0;
	// Iterates trough the array of atan to find the sin and cos.
	for(int i = 0; i < 16; i++){
		// Determines if the predicted angle is above or below the true angle
		if(z < angle){
			d = 1;
		}
		else{
			d = -1;
		}
		xnew = x - ((y*d) >> i);
		ynew = y + ((x*d) >> i);
		znew = z + d * atan[i];

		x = xnew;
		y = ynew;
		z = znew;
	}
	//converts the fixed point back to floating point
	float xfinal = x / (float)(1 << 16);
	float yfinal = y / (float)(1 << 16);
	float zfinal = z / (float)(1 << 16);

	// displays the results
	printf("Cosine %f\n", xfinal);
	printf("Sine %f\n", yfinal);
	printf("final angle %f\n", zfinal);
	return EXIT_SUCCESS;

}
