#include <TFT_eSPI.h> 
#include "compas.h"
#include "position.h"
#include "NotoSansMonoSCB20.h"
#include "NotoSansBold15.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite bck = TFT_eSprite(&tft);
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite sprite1 = TFT_eSprite(&tft);
TFT_eSprite data = TFT_eSprite(&tft);

#define gray 0x39C7
#define background1 0x29CC
#define background2 0x1928
#define left 0 //left button
#define right 14 //right button

void setup() {
  pinMode(left,INPUT_PULLUP);
  pinMode(right,INPUT_PULLUP);

  tft.init();
  tft.fillScreen(background1);
  tft.setSwapBytes(true);
  tft.drawString("LOCATION",10,300);
  tft.setTextColor(TFT_ORANGE, background1);
  tft.loadFont(NotoSansBold15);
  tft.drawString("43768554'",10,260);
  tft.loadFont(NotoSansBold15);
  tft.drawString("23758554'",10,280);
  tft.pushImage(100,260,48,48,position);
  
  data.createSprite(140,60);
  data.loadFont(NotoSansMonoSCB20);
  data.setTextColor(TFT_WHITE,background2);

  bck.createSprite(171,171);
  bck.setSwapBytes(true);
  
  sprite.createSprite(171,171);
  sprite.setSwapBytes(true);
  
  sprite1.createSprite(121,25);
  sprite.setPivot(85,85);
  
}
int angle=0;
int angle2=359;
int sx=60;
int sy=12;

void drawData()
{
data.fillSprite(background2);
data.drawString("needle: "+String(angle),10,8);
data.drawString("compas: "+String(angle2),10,34);
data.pushSprite(15,190);
}

void drawCompas()
{ 
  bck.fillSprite(0x29CC);
  bck.fillSmoothCircle(152, 5, 5, TFT_ORANGE);  
  sprite.fillSprite(0x29CC);
  sprite.pushImage(1,1,170,170,compas);
  sprite1.fillSprite(TFT_WHITE);
 
  sprite1.drawWedgeLine(6, sy, sx, sy, 1, 10, TFT_RED);
  sprite1.drawWedgeLine(sx, sy, 115, sy, 10, 1, TFT_BLUE);
  sprite1.fillSmoothCircle(sx, sy, 12, gray);
  sprite1.fillSmoothCircle(sx, sy, 6, TFT_WHITE);

  sprite.pushRotated(&bck,angle2,background1);
  sprite1.pushRotated(&bck,angle,TFT_WHITE);
  bck.pushSprite(0,8);}

void loop() {
 
  if(digitalRead(left)==0)
  angle=angle+4;
  if(angle==360)
  angle=0;
  if(digitalRead(right)==0)
   angle2=angle2-2;
  if(angle2<0)
  angle2=359;

drawCompas();
drawData();
}
