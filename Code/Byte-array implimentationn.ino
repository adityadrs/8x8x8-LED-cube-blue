/*LED 8x8x8 blue cube 
based on switiching by transistors which are controled by shift registor arrays.
common annode architecture (positive termimnal)


*/

//attmpt to use an array of byte to shift data to the registers and emplor multiplexing
#define latchPin 33 //this will shift the stored data out (can be considered as enable out put but is not exactly like enable output)
#define clockPin 50 //look for wave diagram as to how data is pushed in a shiftregister
//in this case 74hc595d the smd brother of the standard 74hc595 dip
#define dataPin 51 //this pushes data out 
#define blankPin 32 // this can be toggled high to low to remove aall the data that was stored in the shift registors
//here the byte array is set up
byte Anodes[8]; // this will contain the data that is to be shifted out to the 8 shift registers that control the 64 anode pillars
byte Cathodes[1]; //this will contain the data that is to be  shifted to the last shift register that controles the levels

void setup(){

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(blankPin, OUTPUT);

}

void loop(){

	LED(7,7,7);
	//AllOn();
  	//Edges();
	Diagnols();
	EdgesAndDiagnols();

}


void LED(int level, int row, int column){
  //adding some constraints to level, row and column
  if(level<0)
    level=0;

  if(level>7)
    level=7;

  if(row<0)
    row=0;

  if(row>7)
    row=7;

  if(column<0)
    column=0;

  if(column>7)
    column=7;

//since we have devided the input as row column and level, 
//it makes things quite easy for us
  
Anodes[row]=(1<<(column-1)); //what is happening here is we are shifting a high at the position in the byte that maps to that perticular column 

Cathodes[1]=(1<<level); //here the 
push();

}
void push(){

// setlatch pin low so the LEDs don't change while sending in bits
	digitalWrite(latchPin, LOW); 

// shift out the bits of dataToSend to the 74HC595
	for(int i=0; i<8; i++)
	{
		shiftOut(dataPin, clockPin, LSBFIRST, Anodes[i]);
	}

	shiftOut(dataPin, clockPin, MSBFIRST, Cathodes);
	digitalWrite(latchPin, HIGH);

}

/********************ANIMATIONS***************************************ANIMATIONS***************************************ANIMATIONS*******************/
/********************ANIMATIONS***************************************ANIMATIONS***************************************ANIMATIONS*******************/
/********************ANIMATIONS***************************************ANIMATIONS*****************************	**********ANIMATIONS*******************/

void Edges(){

  for(int i=0; i<8;i++)
  {
	
	LED(7,i,0);
    LED(7,i,7);
    LED(7,1,i);
    LED(7,7,i);



  }
    
}

void AllOn(){

  for(int i=0; i<8;i++)
  {
    for(int j =0; j<8 ;j++)
    {
      for(int k =0; k<8 ; k++)
      {
        LED(i,j,k);
      } 
    }



  }
    
}

void Diagnols(){

  //diagnoal 1
  for(int i = 0; i<8; i++)
  {
    LED(i,i,i);
    LED(i,7-i,i);
    LED(i,7-i,7-i);
    LED(i,i,7-i);
  }
}

void EdgesAndDiagnols(){
  Diagnols();
  Edges();
}