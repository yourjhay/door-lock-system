#include <Password.h>
#include <Keypad.h>

const byte numRows= 4;
const byte numCols= 4;
int led = 10;
int lock = 11;
const int btn = A0;
int btnState = 0;
bool permaLock = true;

char keys[numRows][numCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keys), rowPins, colPins, numRows, numCols);

Password passwd = Password("2519");

void setup() { 
pinMode(lock, OUTPUT);
pinMode(led, OUTPUT);
pinMode(btn, INPUT);
digitalWrite(lock, HIGH);
Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable //If key is not equal to 'NO_KEY', then this key is printed out //if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process

void loop() {
char keypressed = myKeypad.getKey();

  if (keypressed != NO_KEY)
  {
  Serial.print(keypressed);
  blinkLed();
   delay(60); 
      switch (keypressed){     
      case '#': 
        checkpasswd(); break;
      case '*': 
        passwd.reset(); break;
      case 'A':
        semiLock();
        break;
      case 'D':
        if(permaLock == 0) {
          unlock();
        }
        break;
      default: 
        passwd.append(keypressed);        
      }
  }
  
  Serial.print(permaLock);
  btnState = digitalRead(btn);

  if(btnState == HIGH ){
    unlock();
  }
  
}

void semiLock(){
  if(permaLock == true) {
    if(passwd.evaluate()){
      permaLock = false;
      semiLockActivated(500);
      Serial.println("semi lock activated");
    }
  } else {
    permaLock = true;
    semiLockActivated(100);
  }
  passwd.reset();
 }

void checkpasswd() {

   if (passwd.evaluate()){
      Serial.println(" OK.");
      unlock();
   } else {
      Serial.println(" Wrong password!");
      wrongLed();
   } 
   passwd.reset();
}

void blinkLed(){
  int delay_ = 200;
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
}

void wrongLed()
{
  int delay_ = 200;
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
}

void semiLockActivated(int delay_)
{  
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
  digitalWrite(led, HIGH);
  delay(delay_);
  digitalWrite(led, LOW);
  delay(delay_);
}
void unlock()
{
  digitalWrite(led, HIGH);
  digitalWrite(lock, LOW)  ;
  delay(5000);
  digitalWrite(lock, HIGH);
  digitalWrite(led, LOW);
}
