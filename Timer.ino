#include<Adafruit_GFX.h>
#include<Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(6, 5, 4, 3, 2);

boolean backlight = true;
int d = 137, h = 2, m = 20, s = 30;
int t = 0, sep = 962;
char sec[9];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  
  display.begin();
  display.clearDisplay();
  display.setContrast(60);
  display.setTextColor(BLACK);
}

void loop() {
  set();
  display.clearDisplay();
  
  display.setTextSize(4);
  if (d >= 10){
    display.print(d);
  }else {
    display.print("0");
    display.print(d);
  }
  display.println();
  display.display();

  display.setTextSize(1);
  Display();
  Judge();
  display.display();
  
  delay(sep);
}

void Display(){
  if (h >= 10){
    display.print(h);
  }else {
    display.print("0");
    display.print(h);
  }
  
  display.print(":");

  if (m >= 10){
    display.print(m);
  }else {
    display.print("0");
    display.print(m);
  }
  
  display.print(":");

  if (s >= 10){
    display.print(s);
  }else {
    display.print("0");
    display.print(s);
  }
}

void Judge(){
  if (s > 0){
    s -= 1;
  }
  else if(s <= 0 && m > 0){
    s = 59;
    m -= 1;
  }
  else if(m <= 0 && h > 0){
    s = 59;
    m = 59;
    h -= 1;
  }
  else if(h <= 0 && d > 0){
    s = 59;
    m = 59;
    h = 23;
    d -= 1;
  }
}

void set(){
  if (Serial.available()){
    Serial.readBytes(sec, 9);
    Serial.println(atoi(sec));
    t = atoi(sec);
    convert();
  }
}
void convert(){
  int option = t / 1000;
  if (option == 1){
    d = t - option*1000;
  }
  else if (option == 2){
    h = t - option*1000;
  }
  else if (option == 3){
    m = t - option*1000;
  }
  else if (option == 4){
    s = t - option*1000;
  }
  else if (option == 5){
    sep = t - option*1000;
  }
  Serial.print(d);
  Serial.print(":");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.print(s);
  Serial.print(" ");
  Serial.println(sep);
}
