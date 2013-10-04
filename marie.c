/********************************************************************
* 		MARIE Assembler				       	                        *
* 	Date:26-07-2013					       	                        *
*	version:1.0					       	                            *
*	By: Mostafa ELbakly				       	                        *
*	Email: elbakly@gmail.com                                        *
*   Editor: Vim         			    	                        *
*********************************************************************
*								                                    *
* This program accepts MARIE Instruction set as File 		        *
*	Input: Binary or Hex or MARIE                                   *
*	Output: One table displaying the three language as below        *
*                                     				                *
* _______________________________________________________________   *
*| Addr |    Hexcode	| Instructions	| Binary		|           *
*----------------------------------------------------------------   *
*| 100	|   1104	| Load 104	| 000100010000100	|               *
*----------------------------------------------------------------   *
*                						                            *
*								                                    *
*   For proper display of output please use fullscreen terminal on  *
*	ubuntu                					                        *
*                     						                        *
*********************************************************************/
//including need libs

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//function prototype
char* BinToHex(char*);

//defining parallel arrays
const char * const binary[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};

const char* hex[16]= {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
//temp variable for calcutations
char tempfull[4];
//function prototype
const char * HexToBin(char);

/*
The main program runs and ask in which mode is wanted 
*/

int main() {
//defining marie instructions array
const char * instr[13]={"JnS","Load","Store","Add","Subt","Input","Output","Halt","Skipcond","Jump","Clear","AddI","JumpI"};

//Defining variables
char bline1[100];
char bline2[4];
char bline3[4];
char bline4[4];
char choice;
char filename[256];
char   action[6];
char  counter[6];
char linecode[6];
char  lineread[100];
FILE * inputf;
int i;
char res[24];
char result[50];
int linehex;
char * blinehex;
char slinehex;
int bineq,blinelen;
int flag=1;
// Choosing mode
printf("\nplease choose file code you are inserting\na. Hex Code (This option is N/A) \nb. Binary language \nc. Marie Language \n\n Choose a,b,c ?");
scanf("%c",&choice);
//getting the file name
printf("Enter .txt file name : ");
scanf("%s",filename);

printf("\n");

//reading the file

 inputf=fopen(filename,"r");
 //preform file check
if(inputf==NULL){
        printf("\nCould not read file\n");
        exit(0);
        }
// start output header
printf("\nFile name was %s\n",filename);

printf("----------------------------------------------------------------------------------------\n");
printf("|\tAddr\t|\tHexCode\t|\t  MARIE  \t|\tBinary\t\t|\n");
printf("----------------------------------------------------------------------------------------\n");

//interpert the input file line by line

while(fgets(lineread,256,inputf)!= NULL){


//in Case of choosing marie file
if(choice=='c'){
//reseting variable for each line
action[0]='\0';
counter[0]='\0';
result[0]='\0';
linehex=0;


sscanf(lineread,"%s%s%s",counter,linecode,action);

for(i=0;i<13;i++){

	if( linecode[0] == instr[i][0] && linecode[3]==instr[i][3] ){
 		linehex = i;
		
	break;
	}
}
if(linehex!=0){

	strcat(result,HexToBin((char)(((int)'0')+linehex)));
}else{
for(i=0;i<strlen(linecode);i++){
	strcat(result,HexToBin(linecode[i]));
}

}
for(i=0;i<strlen(action);i++){
	strcat(result,HexToBin(action[i]));
}
if(linehex!=0){
printf("|\t%s\t|\t%d%s\t|\t%s %s   \t|\t%s\t|\n",counter,linehex,action,linecode,action,result);
}else{
printf("|\t%s\t|\t%s\t|\t%s %s     \t|\t%s\t|\n",counter,linecode,linecode,action,result);
}
printf("----------------------------------------------------------------------------------------\n");
} //end of choosing marie file


//in case of choosing binary file
if(choice=='b'){
//resetting variables for each line
tempfull[0]=NULL;
tempfull[1]=NULL;
tempfull[2]=NULL;
tempfull[3]=NULL;
sscanf(lineread,"%s",bline1);
linecode[0]="\0";
bineq=0;
blinelen=strlen(bline1);
for(i=0;i<13;i++){
	if(binary[i][0]==bline1[0] &&binary[i][1]==bline1[1]&&binary[i][2]==bline1[2]&& binary[i][3]==bline1[3]){
	bineq=i;
}
}




if(flag==0){
	blinehex= BinToHex(bline1);
	printf("|\t\t|\t%s\t|\t%s   \t|\t%s\t|\n",blinehex,blinehex,bline1);
}else{
	blinehex=BinToHex(bline1);
printf("|\t\t|\t%s\t|\t%s %c%c%c  \t|\t%s\t|\n",blinehex,instr[bineq],blinehex[1],blinehex[2],blinehex[3],bline1);}
if(bineq==7){
flag=0;
}
} //end of choosing binary file
printf("----------------------------------------------------------------------------------------\n");


// in case of choosing HEXCode file
if(choice=='a'){
printf("This is a option is not yet available\n");
}

} 
// end of inserted file and the while

//close the file
fclose(inputf);
return 0;

//end of main
}


//function to convert from hexadecimal to binary digit by digit
const char * HexToBin( char c){



  	if (c >= '0' && c <= '9') return binary[     c - '0'];
  	if (c >= 'A' && c <= 'F') return binary[10 + c - 'A'];
  	if (c >= 'a' && c <= 'f') return binary[10 + c - 'a'];
 	 return "1";
	
}


//function to convert form binary to hexadecimal fullnumber
char* BinToHex(char* BinData){
	char* full;
	char tempbin[4];

	int i,j,bytecounter=0;
	int k=0;
	
		
	for(i=0;i<strlen(BinData);i++){
	
	    
		tempbin[bytecounter]=BinData[i];
		bytecounter++;
		if(bytecounter==4){
		   
			bytecounter=0;
			for(j=0;j<16;j++){
			  
				if(tempbin[0]==binary[j][0]
				&&tempbin[1]==binary[j][1]
				&&tempbin[2]==binary[j][2]
				&&tempbin[3]==binary[j][3]){
				
				tempfull[k]=*hex[j];
				k++;
				
				}
			}
		
		}
	}
	
	return tempfull;
}

