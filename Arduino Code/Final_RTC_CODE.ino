/***================================================================================================================================================
Designer & Developer = Arpan Mukherjee.
Last mofified = 16/09/24
Project name = Real time clock using arduino. (Embedded Project)
Place = Durgapur, West Bengal, INDIA
Time = 10:30 AM.
*/

/*
 * Include the 16x2 LCD library
 */
#include<LiquidCrystal.h>


/*
 * Time Intervals relevant to the project put as macro.
 */
#define SECOND_PERIOD 1000
#define MINUTE_PERIOD 60
#define HOUR_PERIOD   60
#define DAY_PERIOD    24
String temp;


/*
 * To initialize red leds.
 */
#define LED_1 A0
#define LED_2 A1
#define LED_3 A2
#define LED_4 A3
#define TEMP  A4
#define BUZZER  8


/*
 * Freqeuency of the key acknowledgement tone put as macro.
 */
#define NOTE_C4  400
#define NOTE_C5  5000
/*
 * Key values put as macro.
 */
#define MODE_KEY    1
#define POS_KEY     2
#define EDT_KEY     3
#define OK_KEY      4

/*
 * Key read interval put as macro.
 * Experiment with duration
 */
#define KEY_READ_INTERVAL      140

/*
 * RTC modes put as macro.
 */
#define NORMAL_MODE   0
#define EDIT_MODE     1

/*
 * Intializing the LCD with arduino's pins associated  to the project.
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*
 * Global Variables for creating non blocking delay 
 */
unsigned long CurrentMillis=0; 
unsigned long StartMillis=0;
unsigned long KeyMillis=0; 
 

/*
 * Global Variables for running time
 */
unsigned char Hour=0;
unsigned char Minute=0;
unsigned char Second=0;

/*
 * Global Variables for creating editing time
 */
unsigned char tmpHour=0;
unsigned char tmpMinute=0;
unsigned char tmpSecond=0;

/*
 * Global Variables for testing time update interval
 */
//bool ToggleVal=LOW;

/*
 * Global Variables for RTC mode
 */
int Mode;
/*
 * Global Variables for LCD cursor  position
 */
int Xpos;
/*
 * Global Variables for key value
 */
int KeyVal=-1;

void setup()
{ 
 /*
  * Initialization Routines
  */
  InitializeLCD();
  InitializeKeys();   
  InitializeGlobalVars();
  InitializeAnalogPins();
  IrReceiver.begin(IR_RECEIVE_PIN);

  
 /*
  * Start Scheduling 
  */
  StartMillis=millis(); 
}

void loop()
{  
 /*
  * Load current millis() value and compare to check if second interval has elapsed.
  * If yes update time.Running time is displayed if it is NORMAL mode.
  */
  CurrentMillis = millis();  
  if ((CurrentMillis - StartMillis) >= SECOND_PERIOD)  
  {
      StartMillis=CurrentMillis;
      
      UpdateTime();

   /*
    * Toggling Pin 13 to check time update interval.
    */
      /*ToggleVal^=HIGH;
      digitalWrite(13,ToggleVal);*/

      if(Mode==NORMAL_MODE)
      {
        ShowTime();
        Tick_Tick();
        LedArray_normal();
      }
      else if (Mode==EDIT_MODE)
      {
        LedArray_edit();
      }

  }
 /*
  * Load current millis() value and compare to check if key read interval has elapsed.
  * If yes Read Key,
  */
  if ((CurrentMillis - KeyMillis) >= KEY_READ_INTERVAL)  
  {
    KeyMillis=CurrentMillis;
    
    ReadKey();
    
  }
}

/*
 * Initialize Global Variables of the project. 
 */
void InitializeGlobalVars(void)
{
  CurrentMillis=0; 
  StartMillis=0;
  KeyMillis=0; 

/*
 * Edit here to set initial vaues of time.
 */
  Hour=10;
  Minute=00;
  Second=50;
  

  tmpHour=0;
  tmpMinute=0;
  tmpSecond=0;
  
  Mode=NORMAL_MODE;
  Xpos=0;
  KeyVal=-1;
}

/*
 * Initialize LCD
 */
void InitializeLCD(void)
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Welcome Arpan !");
  lcd.setCursor(0,1);
  lcd.print("Real Time Clock");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("..Initializing..");
  delay(3000);

}

/*
 * Print running time on LCD.
 */
void ShowTime(void)
{ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time is:"); 

  lcd.setCursor(0,1);
  lcd.print("               ");
  
  //Divider for time and temperature printing
  lcd.setCursor(8, 0);
  lcd.print("|");
  lcd.setCursor(8, 1);
  lcd.print("|");
  
  lcd.setCursor(0,1);
  lcd.print(Hour);  
  lcd.setCursor(2,1);
  lcd.print(':');
  lcd.setCursor(3,1);
  lcd.print(Minute);
  lcd.setCursor(5,1);
  lcd.print(':');
  lcd.setCursor(6,1);
  lcd.print(Second);
  //printing the week days or day count
  /*switch(Day)
          {
            case 1: 
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("MON");
            break;
            }
            case 2:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("TUE");
            break;
            }
            case 3:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("WED");
            break;
            }
            case 4:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("THR");
            break;
            }
            case 5:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("FRI");
            break;
            }
            case 6:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("SAT");
            break;
            }
            case 7:
            {
            lcd.setCursor(10, 1);
            lcd.print(Day);
            lcd.setCursor(12, 1);
            lcd.print("SUN");
            break;
            }
          }*/

  ShowTemp(); //calling show temperature function within show time function  
}
void ShowTemp(void)
{
  temp = String(read_temperature()); // 0 is for no significant fields 27.536== 27 like that
  lcd.setCursor(9, 0);
  lcd.print("       ");
  lcd.setCursor(9, 0);
  lcd.print("Tmp:");
  lcd.setCursor(13,0);
  lcd.print(temp);
  lcd.setCursor(15,0);
  lcd.print((char)223); // (char)223 is for printing the degree symbol
}

/*
 * Print temporary for editing time on LCD.
 */
void ShowDummyTime()
{  
  lcd.noBlink();
  lcd.setCursor(0,1);
  lcd.print("        ");
  lcd.setCursor(0,1);
  lcd.print(tmpHour);  
  lcd.setCursor(2,1);
  lcd.print(':');
  lcd.setCursor(3,1);
  lcd.print(tmpMinute);
  lcd.setCursor(5,1);
  lcd.print(':');
  lcd.setCursor(6,1);
  lcd.print(tmpSecond);
  lcd.blink();  
  /*lcd.setCursor(10,1);
  lcd.print(tmpDay);*/
  lcd.blink();  
  switch(Xpos)
  {
    case  0:  lcd.setCursor(0,1);break;
    case  1:  lcd.setCursor(3,1);break;
    case  2:  lcd.setCursor(6,1);break;
    //case  3:  lcd.setCursor(10,1);break;
  }
}

/*
 * Manage time variables
 */
void UpdateTime(void)
{
    Second++;
    if(Second>=MINUTE_PERIOD)
    {
      Second=0;
      
      Minute++;
      if(Minute>=HOUR_PERIOD)
      {
        Minute=0;
        Hour++;
        if(Hour>=DAY_PERIOD)
        {
          Hour=0;
        }

      }
    }
    
    
}

/*
 * Buzzer routine for ackowledgement.
 * Experiment with duration
 */
void SoundBuzzer(void)
{
  tone(8, NOTE_C4, 15); 
  
}

/*
 * Set direction of pins connected to pushbuttons as input.
 * Set direction of pin 13 as output to test  Seconds Duration.
 */
void InitializeKeys(void)
{
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(13, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    digitalWrite(13,HIGH);
}
/*
 * Read and process Key press. 
 */
void ReadKey(void)
{
  if(digitalRead(7)==HIGH)
  {
      KeyVal=MODE_KEY;  
  }
  else if(digitalRead(6)==HIGH)
  {
      KeyVal=POS_KEY;    
  }
  else if(digitalRead(10)==HIGH)
  {
      KeyVal=EDT_KEY;   
  }
  else if(digitalRead(9)==HIGH)
  {
      KeyVal=OK_KEY;   
  }
  else
  {
    KeyVal=-1;
  }
 
  if(KeyVal!=-1)
  {
    SoundBuzzer();
  }
  ProcessKey();
  
}

/*
 *Invoking the correct action routine related to each key press.
 */
void ProcessKey(void)
{
  switch(KeyVal)
  {
    case  MODE_KEY  : ModeKeyTask();break;  
    case  POS_KEY   : PosKeyTask();break;
    case  EDT_KEY   : EditKeyTask();break;
    case  OK_KEY    : OkKeyTask();break;
  }
  KeyVal=-1;
}

/*
 *MOD key actions
 */
void ModeKeyTask(void)
{
  Xpos=0;
  lcd.setCursor(0,1);
  
  if(Mode==NORMAL_MODE)
  {
    Mode=EDIT_MODE;
    lcd.blink();

    tmpHour=Hour;
    tmpMinute=Minute;
    tmpSecond=Second;
    //tmpDay=Day;
  }
  else
  {    
    Mode=NORMAL_MODE;
    lcd.noBlink();
  }  
}

/*
 *POS key actions
 */
void PosKeyTask(void)
{
  if(Mode==EDIT_MODE)
  {
    Xpos++;
    if(Xpos>2)
    {
      Xpos=0;
    }
    switch(Xpos)
    {
      case  0:  lcd.setCursor(0,1);break;
      case  1:  lcd.setCursor(3,1);break;
      case  2:  lcd.setCursor(6,1);break;
    }
  }
}
/*
 *EDT key actions
 */
void EditKeyTask(void)
{
  if(Mode==EDIT_MODE)
  {
    switch(Xpos)
    {
      case  0:  lcd.print("  ");
                lcd.setCursor(0,1);
                tmpHour++;
                if(tmpHour>23)
                {
                  tmpHour=0;
                }
                break;
      case  1:  lcd.print("  ");
                lcd.setCursor(3,1);
                tmpMinute++;
                if(tmpMinute>59)
                {
                  tmpMinute=0;
                }
                break;
      case  2:  lcd.print("  ");
                lcd.setCursor(6,1);
                tmpSecond++;
                if(tmpSecond>59)
                {
                  tmpSecond=0;
                }
                break;
      /*case  3:  lcd.print("  ");
                lcd.setCursor(10,1);
                tmpDay++;
                if(tmpDay>7)
                {
                  tmpDay=1;
                }
                break;*/
    }
    ShowDummyTime();
  }
}
/*
 *OK key actions
 */
void OkKeyTask(void)
{
  if(Mode==EDIT_MODE)
  {
    Hour=tmpHour;
    Minute=tmpMinute;
    Second=tmpSecond;
    //Day=tmpDay;
    Xpos=0;
    lcd.setCursor(0,1);
    Mode=NORMAL_MODE;
    lcd.noBlink();
  }
}

/*
* Led array operation
*/
void LedArray_normal(void)
{
  unsigned int arr[4]={LED_1,LED_2,LED_3,LED_4};
  unsigned int i;
  for(i=0;i<4;i++)
  {
   analogWrite(arr[i],255);
   delay(50);
   analogWrite(arr[i],0);
  }
}

void LedArray_edit(void)
{
  unsigned int arr[4]={LED_4,LED_3,LED_2,LED_1};
  unsigned int i;
  for(i=0;i<4;i++)
  {
   analogWrite(arr[i],255);
   delay(50);
   analogWrite(arr[i],0);
  }
}

void InitializeAnalogPins(void)
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, INPUT);
}

float read_temperature(void)
{
  float temperature;
  temperature =(((analogRead(TEMP) *(float) 5/1024))  /  (float) 0.01);
  return temperature;
}

void Tick_Tick(void)
{
  tone(8, NOTE_C5, 60); 
  
}

