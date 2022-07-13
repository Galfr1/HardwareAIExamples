#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64);
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
int bird_x = 1;
int bird_y = 63;
int score = 0;
int velocity = 100;
int linepx[50];
bool gameRunning = false;
void setup(){
  delay(100);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setRotation(0);
  display.setTextWrap(false);
  display.dim(0);
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(8,OUTPUT);
  display.clearDisplay();
  display.display();
}

void loop() {
  String command = "";
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();
    }
  if(command.equals("start")){
    gameRunning = true;
    }
  if(gameRunning == true){
  display.clearDisplay();
  bird_x ++;
  if(digitalRead(2) == HIGH){
    bird_y ++;
    }
  if(digitalRead(2) == LOW){
    bird_y --;
    }
  if(bird_y > 55){
    bird_y = 55;
    }
  if(bird_y < 8){
    bird_y = 8;
    }
  if(bird_x == 120){
    bird_x = 1;
    tone(8, 120, 100);
    if(velocity != 0){
      velocity  = velocity - 20;
      }
    score ++;

    
    int spaceY = random(5, 50);
    int i = 0;
    int i2 = 1;
    while(i < 50){
      if(i2 < spaceY){
        linepx[i] = i2;
        }
      if(i2 == spaceY){
        i2 = i2 + random(5, 14);
        }
      if(i2 > spaceY){
        linepx[i] = i2;
        }
      i ++;
      i2 ++;
      }


      
    }
  int draw_x = bird_x;
  int draw_y = bird_y;
  display.setCursor(draw_x, draw_y);
  display.println(".");
  draw_x ++;
  display.setCursor(draw_x, draw_y);
  display.println(".");
  draw_y --;
  display.setCursor(draw_x, draw_y);
  display.println(".");
  draw_x --;
  display.setCursor(draw_x, draw_y);
  display.println(".");


  
  int drawLoop = 0;
  while(drawLoop < 50){
    display.setCursor(90, linepx[drawLoop]);
    display.println(".");
    drawLoop ++;
    }


    
  display.display();
  delay(velocity);

  int howMany = 0;
  while(howMany < 50){
    if(bird_y == linepx[howMany] && bird_x == 90){
      tone(8, 220, 100);
      Serial.println(score);
      score = 0;
      display.clearDisplay();
      display.display();
      velocity = 200;
      bird_x = 1;
      bird_y = 63;
      int howManyTimes = 0;
      while(howManyTimes < 50){
        linepx[howManyTimes] = 0;
        howManyTimes ++;
        }
      gameRunning = false;
      }
     howMany ++;
    }
  if(command.equals("end")){
    tone(8, 220, 100);
      Serial.println(score);
      score = 0;
      display.clearDisplay();
      display.display();
      velocity = 200;
      bird_x = 1;
      bird_y = 63;
      int howManyTimes = 0;
      while(howManyTimes < 50){
        linepx[howManyTimes] = 0;
        howManyTimes ++;
        }
      gameRunning = false;
    }
}
}
