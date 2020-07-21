#include <LiquidCrystal.h>
#include <DS3231.h>
DS3231  rtc(SDA, SCL);
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pset = 6;
int phour = 9;
int pmin = 13;
int pexit = 10;
//int buz = 0; //uncomment to connect buzzer
int set = 0;
int h = 0;
int m = 0;
int e = 0;
int H, M;
int Hour, Min;
int activate = 0;
Time t;
void setup()
{
  //tone(0,0,100); //uncomment if buzzer connected
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  pinMode(pset, INPUT);
  pinMode(phour, INPUT);
  pinMode(pmin, INPUT);
  pinMode(pexit, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(0, 1);
  lcd.print("Date: ");
  rtc.begin();   
  
 // If using RTC for first time, uncomment below lines and 
 // set current time and date, upload to arduino, again comment and upload
 //rtc.setTime(18 ,37 ,00); 
 //rtc.setDate(3, 6, 2019);  
}

void loop()
{
  if (activate == 0)
  { 
    lcd.setCursor(6, 1);
    lcd.println(rtc.getDateStr()); 
    lcd.setCursor(8, 0);
    lcd.println(rtc.getTimeStr());
    delay (1000);
    t = rtc.getTime();
    Hour = t.hour;
    Min = t.min;
    set = digitalRead(pset);
  }
  if (set == HIGH)
  {
    activate = 1;
    lcd.clear();}
    while (activate == 1)
    {
      lcd.setCursor(0,0);
      lcd.print("set alarm");
      lcd.setCursor(0,1);
      lcd.print("hour:");
      lcd.setCursor(9,1);
      lcd.print("min:");
      h = digitalRead(phour);
      if(h == HIGH)
      {
        H = H+1;
        lcd.setCursor(5,1);
        lcd.print(H);
        if(H > 23)
        {
          H = 0;
          lcd.clear();
        }
        delay(100);
      }
      m = digitalRead(pmin);
      if(m == HIGH)
      {
        M = M+1;
        lcd.setCursor(13,1);
        lcd.print(M);
        if(M > 59)
        {
          M = 0;
          lcd.clear();
        }
        delay(100);
      }
      lcd.setCursor(5,1);
      lcd.print(H);
      lcd.setCursor(13,1);
      lcd.print(M);
      e = digitalRead(pexit);
      if(e == HIGH)
      {
        activate = 0;
        lcd.clear();
      }
    }
    if (Hour == H && Min == M)
    {
      lcd.setCursor(0, 0);
      lcd.print("WAKE UP"); 
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      //tone(0,400,300); //uncomment if buzzer connected
      //delay(1000);
      //tone(0,400,300); 
      //tone(0,400,300); 
    }      
}
      
  
    

