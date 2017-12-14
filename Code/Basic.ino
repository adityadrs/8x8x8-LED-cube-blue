int DS_pin =51;
int LATCH_pin = 33;
int Clock_pin = 52;
boolean registers[72];

void setup()
{
  pinMode(DS_pin, OUTPUT);
  pinMode(LATCH_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  writereg();
}


void writereg()
{
  digitalWrite(LATCH_pin, LOW);

  for (int i = 72 ; i>=0 ; i--)
  {
    digitalWrite(Clock_pin, LOW);
    digitalWrite(DS_pin, registers[i]);
    //dela(10);
    digitalWrite(Clock_pin, HIGH);
   // delay(10);
  }

  digitalWrite(LATCH_pin, HIGH);

}
//Single Led Function
void LED(int level, int row, int column){
 registers[7-level] = HIGH;
 registers[((8*column)+row)+8] = HIGH;
   for(int i =71 ; i>0 ; i--)
  {
    if(i==(7-level)||i==(((8*column)+row)+8))
    continue;
    registers[i] = LOW;
    //delay(100);
    writereg();
  }

}

void loop()
{
  //uncomment the animations to enable
  //NOTE: MULTIPLEXING HAS BE SOME WHAT IMPLIMENTED AT FUNCTION LEVEL. BUT WHEN YOU CALL LED(A,B,C) THINGS WILL NOT WORK AS OU THINK  THEY WOULD
  //      A CONJUGATE LED WILL BE AUTOMATICALLY SWITCHED ON
  


  //OnOnebyOne();
  //OffOnebyOne();
  //Flicker();
  //OnLayerwise();
  //OffLayerwise();
  //RandomRain();
  //Boundaries();
  //Walls();
  Spiral();
}

void EveryOn()
{
  for(int i=0;i<72;i++)
    {
      registers[i]=HIGH;
      //delay(100);
      writereg();
    }
}
void EveryOff()
{
  for(int i=0;i<72;i++)
    {
      registers[i]=LOW;
      //delay(100);
      writereg();
    }  
}
void OnOnebyOne()
{ EveryOff();
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      for(int k=0;k<8;k++)
      {
        registers[7-i] = HIGH;
        registers[((8*k)+j)+8] = HIGH;
        writereg();
        delay(100);
      }
    }
  }
}
void OffOnebyOne()
{ EveryOn();
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
      for(int k=0;k<8;k++)
      {
        registers[7-i] = LOW;
        registers[((8*k)+j)+8] = LOW;
        writereg();
        delay(100);
      }
    }
  }
}
void Flicker()
{ EveryOff();
  for(int i=0;i<10;i++)
  {
    EveryOn();
    delay(10);
    EveryOff();
    delay(10);
  }
}
void OnLayerwise()
{ EveryOff();
  for(int i=8;i<72;i++)
  {
    registers[i]=HIGH;
    writereg();
  }
  for(int i=0;i<8;i++)
  {
    registers[i]=HIGH;
    writereg();
    delay(100);
  }
}
void OffLayerwise()
{ EveryOn();
  for(int i=0;i<8;i++)
  {
    registers[i]=LOW;
    writereg();
    delay(100);
  }
}
void OnColumnwise()
{ EveryOff();
  for(int i=0;i<8;i++)
  {
    registers[i]=HIGH;
    writereg();
  }
  for(int i=8;i<72;i++)
  {
    registers[i]=HIGH;
    writereg();
    delay(100);
  }
}
void OffColumnwise()
{ EveryOn();
  for(int i=8;i<72;i++)
  {
    registers[i]=LOW;
    writereg();
    delay(100);
  }
}
void RandomRain()
{ EveryOff();
  for(int i=0;i<30;i++)
  {
    int rand=random(8,71);
    registers[rand]=HIGH;
    writereg();
  }
  for(int i=7;i>=0;i--)
  {
    registers[i]=HIGH;
    writereg();
    delay(100);
    registers[i]=LOW;
    writereg();
    delay(10);
  }
}
void Boundaries()
{ //EveryOff();
  registers[0]=HIGH;
  registers[7]=HIGH;  
  for(int i=8;i<72;i++)
  { if((i<16&i>7)||(i<72&i>63)||(i%8==0)||(i%8==7))
    {registers[i]=HIGH;
    writereg();
    delay(50);
    }
    else
    {registers[i]=LOW;
      writereg();}
  }
}
void Walls()
{
  for(int i=0;i<8;i++)
    {registers[i]=HIGH;
     writereg();
    }
  for(int i=8;i<72;i++)
  { if((i<16&i>7)||(i<72&i>63)||(i%8==0)||(i%8==7))
    {registers[i]=HIGH;
    writereg();
    delay(50);
    }
    else
    {registers[i]=LOW;
      writereg();}
  }
}
void Spiral()
{ for(int j=0;j<8;j++)
  { 
    if(j%2==0)
    {for(int i=0;i<8;i++)
    { //EveryOff();
      LED(0,i,j);
      registers[8*j+i+8]=LOW;
      writereg();
    } 
    }
    else
      { 
        for(int i=7;i>=0;i--)
        { //EveryOff();
          LED(0,i,j);
          registers[8*j+i+8]=LOW;
          writereg();
        }
      }
  }
}