/*
MKLCDBuf v1.0
Author: Mateusz Kozicki "Kozaluss"
Date: 2023.11.05
*/

#include "MKLCDBuf.h"

MKLCDBuf::MKLCDBuf(int pWidth,int pHeight){
  Width = pWidth;
  Height = pHeight;
  BufSize = Width * Height;
  WrapX = false;
  WrapY = false;
  ClearChar = ' ';
  Buffer.remove(0);
  Buffer.reserve(BufSize + 1);
  char lcc[2] = "\0";
  lcc[0] = ClearChar;
  for(int i=0;i<BufSize;i++) Buffer.concat(lcc);
}

inline size_t MKLCDBuf::write(uint8_t value) {
  int c2p = Cursor2Position();
  if(c2p<0) return 1; // bad position->exit
  Buffer.setCharAt(c2p,value);
  cursorMove(1,0);
  return 1;
}

void MKLCDBuf::SetLCD(LiquidCrystal_I2C *pLCD){
  ThisLCD = pLCD;
}

void MKLCDBuf::clear(){
  char *cstr = (char *)Buffer.c_str();
  memset(cstr,ClearChar,BufSize);
  memset(cstr+BufSize,0,1);
}

void MKLCDBuf::setClearChar(char pChar){
  ClearChar = pChar;
}

void MKLCDBuf::setCursor(int pX,int pY){
  CursorX = pX;
  CursorY = pY;
}

void MKLCDBuf::cursorMove(int pX,int pY){
  CursorX += pX;
  if(WrapX){
    do{
      bool Zmiana = false;
      if(CursorX<0){
        CursorX += Width;
        CursorY -= 1;
        Zmiana = true;
      }else if(CursorX>(Width-1)){
        CursorX -= Width;
        CursorY += 1;
        Zmiana = true;
      }
      if(!Zmiana)break;
    }while(true);
  }
  CursorY += pY;
  if(WrapY){
    do{
      bool Zmiana = false;
      if(CursorY<0){
        CursorY += Height;
        Zmiana = true;
      }else if(CursorY>(Height-1)){
        CursorY -= Height;
        Zmiana = true;
      }
      if(!Zmiana)break;
    }while(true);
  }
}

void MKLCDBuf::setWrapX(bool pWrap){
  WrapX = pWrap;
}

void MKLCDBuf::setWrapY(bool pWrap){
  WrapY = pWrap;
}

int MKLCDBuf::Cursor2Position(){
  if(CursorY<0) return -1;
  if(CursorY>(Height-1)) return -1;
  if(CursorX<0) return -1;
  if(CursorX>(Width-1)) return -1;
  return CursorY * Width + CursorX;
}

void MKLCDBuf::ToLCD(){
  String linia;
  linia.reserve(Width+1);
  char *dst = (char *)linia.c_str();
  char *src = (char *)Buffer.c_str();
  // Zeruj bufor linii
  memset(dst,0,Width+1);
  // Kopiuj linie na ekran
  for(int i=0;i<4;i++){
    memcpy(dst,src,Width);
    ThisLCD->setCursor(0,i);
    ThisLCD->print(dst);
    src += Width;
  }
}
