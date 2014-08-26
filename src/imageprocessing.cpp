#include "imageprocessing.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#define FALSE 0;
#define TRUE 1;

using namespace std;

void print(){
	cout<<"Hello world!";
}

void ImageProcessing::readImage(char **argv){
	FILE * fpIn;
	char * string;
	int doneReading = FALSE;
	char c;

	fpIn = fopen(argv[1], "rb");
	if(fpIn == NULL){
		cerr<<"Such a file does not exist...";
		exit;
	}
	string = (char *) calloc(256,1);
	while(!doneReading && (c = (char) fgetc(fpIn)) != '\0')
		switch(c){
			case 'P':
				c = (char) fgetc(fpIn);
				switch(c){
					case '2':
						this->numberOfBands = 1;
						//pgm plain
					break;
					case '5':
						this->numberOfBands = 1;
						//pgm Normal
					break;
					case '3':
						this->numberOfBands = 3;
						//ppm plain
					break;
					case '6':
						this->numberOfBands = 3;
						//ppm Normal
					break;
				}
				c = (char) fgetc(fpIn);
				if(c != 0x0A){
					ungetc(c, fpIn);
				}
				else{
					ungetc(c, fpIn);
					fgets(string, 256, fpIn);
					cout<<"File you entered is "<<string<<"\n";
				}
			break;
			case '#':
			fgets(string, 256, fpIn);
			cout<<"File you entered is "<<string<<"\n";
			break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				ungetc(c, fpIn);
				fscanf(fpIn,"%d %d %d", &(this->numberOfColumns), &(this->numberOfRows), &(this->highVal));
				doneReading = TRUE;
				fgetc(fpIn);
			break;
		}
	this->totalPixels = this->numberOfRows*this->numberOfColumns*this->numberOfBands;
	this->image = (unsigned char *) malloc (this->totalPixels);
	fread(this->image,1,this->totalPixels,fpIn);
}