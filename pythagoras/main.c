#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_INPUT_ARGS 4

const char* outputtext = "A triangle with given lengths has the following properties: %s%s\n";


/******************swap two numbers***************************/
void swap(int* x,int* y){
	int t;
	t = *y;
	*y = *x;
	*x = t;
}
/******************sort a array from biggest to lowest***************************/
void sort(int x[],int size){
	
	for (int i=0; i<(size-1);i++ ){
		if(x[i]<x[i+1]){
			swap(&x[i],&x[i+1]);
			sort(x,size);
		}
    }

}


/******************main***************************/
int main(int argc, char* argv[]){

	int loclargc;
	loclargc = argc;

	char* buff[MAX_INPUT_ARGS];

	for (int i=0; i<loclargc;i++ ){	
		buff[i] = argv[i];
	}

			
	if (loclargc != MAX_INPUT_ARGS){
		//handle more than MAX_INPUT_ARGS-1 args
		if (loclargc > MAX_INPUT_ARGS){
			printf("Invalid number of arguments. Maximum %d are allowed.\n",MAX_INPUT_ARGS-1);
			return -1;
		}
		//init random on each startup
		srand(time(0));
		char tempbuf[MAX_INPUT_ARGS][5];
						
		//do until the random number is greater than 0
		for (int i=loclargc; i<MAX_INPUT_ARGS;i++ ){
			uint8_t randomnum;														
			randomnum = (uint8_t)255*((float)(rand())/(float)65535);
			sprintf(tempbuf[i],"%d",randomnum);
	
		}	
		//copy over random args	
		for (int i=loclargc; i<MAX_INPUT_ARGS;i++ ){
			buff[i] = tempbuf[i];
		}
		
		char* argtext = "";		
		argtext = (MAX_INPUT_ARGS-loclargc==1) ? "argument" : "arguments";
		//inform about random args	
		printf("%d %s chosen randomly, because not given:\n",MAX_INPUT_ARGS-loclargc,argtext);
		printf("The new set of arguments is: %s, %s, %s \n",buff[1],buff[2],buff[3]);
		loclargc = MAX_INPUT_ARGS;	
	
	}
	
	/******************main triangle identification***************************/	
				
	//convert to integer
	int numargv[argc];
	
	for (int i=1; i<(loclargc);i++ ){
		numargv[i] = atoi(buff[i]);	
		
		if (numargv[i] <= 0)
		{
			printf("Invalid argument(s): positive and greater 0 expected as length.\n");		
			return -1;
		}
	}
			
	//equilateral, isosceles
	
	bool isIsoscele;
	if ((numargv[1]==numargv[2]) && (numargv[2] == numargv[3])){
		printf(outputtext,"","equilateral");
		return 0;
	//if two sides are equal, isosceles = true 
	}else if((numargv[1]==numargv[2]) || (numargv[2] == numargv[3]) || (numargv[1] == numargv[3]) ){
		isIsoscele = true;
	}
	else{
		isIsoscele = false;
	}
		
	
	//invalid
	int sum=0;
	for (int i=1; i<loclargc;i++ ){
		sum += numargv[i];
	}
	for (int i=1; i<loclargc;i++ ){
		if ((sum - numargv[i]) <= numargv[i]){	
			printf(outputtext, "","invalid");
			return 0;
			break;
		}	
	}
	
	int numargtemp[loclargc-1];
	for (int i=0; i<loclargc-1;i++ ){
		numargtemp[i] = numargv[i+1];
	}
	//find longest side		
	sort(numargtemp,loclargc-1);
	
	//blunt, rectangular
	float gamma = 0.0f;
    
	//calculate angle opposite of longest side
	gamma = (180.0f*acos((pow(numargtemp[0],2) - pow(numargtemp[1],2) 
	-pow (numargtemp[2],2))/(-2*numargtemp[1]*numargtemp[2])))/acos(-1);
	//triangle is rectangular
	if (gamma == 90.0f){
		char*isoscelesText;			
		isoscelesText = isIsoscele ? "isosceles, " : "";
		printf(outputtext, isoscelesText,"rectangular");
	//triangle is blunt
	}else if(gamma > 90.0f){
		char*isoscelesText;			
		isoscelesText = isIsoscele ? "isosceles, " : "";
		
		printf(outputtext, isoscelesText,"blunt");
		
	}else{
		if(isIsoscele == true){
			printf(outputtext, "","isosceles");
		}	
	}
	
	
	return 0;
}