/*
  Sketch to read out and display the contents of a Mostek MK23xx Character Generatror ROM

  Mattis Lind 2025
*/

#define CLK PB0
#define CNT0 PA6
#define CNT1 PA7
#define CNT2 PA8
#define CARRY PB12
#define OUT0 PB5
#define OUT1 PB6
#define OUT2 PB7
#define OUT3 PB8
#define OUT4 PB9
#define OUT5 PB10
#define OUT6 PB11
#define IN0 PA0
#define IN1 PA1
#define IN2 PA2
#define IN3 PA3
#define IN4 PA4
#define IN5 PA5
#define SCROLL 0

void inOutput(int in) {
  digitalWrite(IN0, in & 1);
  digitalWrite(IN1, (in & 2)>>1);
  digitalWrite(IN2, (in & 4)>>2);
  digitalWrite(IN3, (in & 8)>>3);
  digitalWrite(IN4, (in & 16)>>4);
  digitalWrite(IN5, (in & 32)>>5);
}

int outRead() {
  return (digitalRead(OUT0)) | 
        ((digitalRead(OUT1)) << 1) |
        ((digitalRead(OUT2)) << 2) |
        ((digitalRead(OUT3)) << 3) |
        ((digitalRead(OUT4)) << 4) |
        ((digitalRead(OUT5)) << 5) |
        ((digitalRead(OUT6)) << 6);
}

void countOutput(int cnt) {
  int val;
  
  switch (cnt) {
    case 0:
      GPIOA ->ODR &= ~(GPIO_ODR_ODR6 | GPIO_ODR_ODR7 | GPIO_ODR_ODR8);
      break;
    case 1:
      GPIOA ->ODR &= ~(GPIO_ODR_ODR7 | GPIO_ODR_ODR8);
      GPIOA ->ODR |= (GPIO_ODR_ODR6);
      break;
    case 2:
      GPIOA ->ODR |= (GPIO_ODR_ODR7);
      GPIOA ->ODR &= ~(GPIO_ODR_ODR6 | GPIO_ODR_ODR8);   
      break;
    case 3:
      GPIOA ->ODR |= (GPIO_ODR_ODR6 | GPIO_ODR_ODR7);
      GPIOA ->ODR &= ~(GPIO_ODR_ODR8);    
      break;
    case 4:
      GPIOA ->ODR |= (GPIO_ODR_ODR8);
      GPIOA ->ODR &= ~(GPIO_ODR_ODR6  | GPIO_ODR_ODR7 );     
      break;
    case 5:
      GPIOA ->ODR |= (GPIO_ODR_ODR6  | GPIO_ODR_ODR8);
      GPIOA ->ODR &= ~(GPIO_ODR_ODR7 );    
      break;
    case 6:
      GPIOA ->ODR |= (GPIO_ODR_ODR7  | GPIO_ODR_ODR8);
      GPIOA ->ODR &= ~(GPIO_ODR_ODR6 );    
      break;      
    default:
      GPIOA ->ODR |= (GPIO_ODR_ODR6  | GPIO_ODR_ODR8 | GPIO_ODR_ODR7);   
      break;
  }
  
}

int i;
int j;
int character;
int k;
int start;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(CNT0, OUTPUT);
  pinMode(CNT1, OUTPUT);
  pinMode(CNT2, OUTPUT);  
  pinMode(IN0, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(OUT0, INPUT);     
  pinMode(OUT1, INPUT); 
  pinMode(OUT2, INPUT); 
  pinMode(OUT3, INPUT); 
  pinMode(OUT4, INPUT); 
  pinMode(OUT5, INPUT); 
  pinMode(OUT6, INPUT);   
  pinMode(CARRY, INPUT);
  pinMode(CLK, OUTPUT);      
  i=0;
  j=0;
  k=0;
  character = 0;
  start=5;
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("MK23XX CHAR GEN BIT MAP");
}


#define LEDPWM 100
#define CLK_LOW 500
#define CLK_HIGH 500
// the loop function runs over and over again forever
void loop() {
  //
  countOutput(7);
  digitalWrite(CLK, HIGH); 
  countOutput(7);
  delayMicroseconds(CLK_HIGH-LEDPWM); 
  countOutput(i);

  i++; 
  if (i>5) i=0; 
  if (k==0 && start == 0 && i > 0) {
    Serial.print("CHAR");
    Serial.print(character,HEX);
    Serial.print(" COLUMN ");
    Serial.print(((i-1)>=0)?(i-1):5);
    Serial.print(" VALUE ");
    Serial.print(outRead(), HEX);
    Serial.println();
  }

  delayMicroseconds(LEDPWM); 
  countOutput(6);
  digitalWrite(CLK, LOW);
  if (digitalRead(CARRY) == HIGH) {
    if (k>20) {
      start--;
      if (start<0) {
        start=5;
        if (character > 62) {
          character = 0;
        } else {
          character++;
        }
      }
      k=0;
    } else {
      k++;
    }
    if (SCROLL) {
      i = start;
    } else {
      i=0;
    }
  } 

  if (SCROLL) {
    if (i<start) {
      inOutput(~(character & 0x3f));  
    } else {
      inOutput(~((character+1) & 0x3f));  
    }
  } else {
    inOutput(~(character & 0x3f)); 
  } 

  delayMicroseconds(CLK_LOW);        
}
