# MKLCDBuf

Offscreen buffer for LiquidCrystal_I2C (Arduino C)

Author: Mateusz Kozicki "Kozaluss"
https://kozaluss.pl

Date: 2023.11.05

## What is this?

It is a companion class adding backbuffer capability for LiquidCrystal_I2C.
It depends on existence of LiquidCrystal_I2C library.
Similarly as LCD library - this one extends Print class - therefore all print flavors are available.

## How to use:

1. Include MKLCDBuf.h:

```
  #include "MKLCDBuf.h"
```

2. Declare object giving width and height of the LCD display:

```
  MKLCDBuf lcd(20,4);
```

3. Initialize in setup() with address of LiquidCrystal_I2C object:

```
  lcd.SetLCD(&i2clcd);
```

4. Usage similar to regular LiquidCrystal_I2C object:

```
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
```

5. When done printing, copy to LiquidCrystal_I2C object:

```
  lcd.ToLCD();
```

## Class functions reference:

`MKLCDBuf(int pWidth,int pHeight);`

>Construct giving width and height in characters.

`void SetLCD(LiquidCrystal_I2C *pLCD);`

>Initialize in setup to point where buffer should be copied when ready.

`void clear();`

>Clear buffer using ClearChar character.

`void setClearChar(char pChar);`

>Set the ClearChar character - used by clear() function.

`void setCursor(int pX,int pY);`

>Set cursor position to X,Y.

`void cursorMove(int pX,int pY);`

>Move cursor in given axis by given number of characters. Behaviour of this function depends on wrapping settings.

`void setWrapX(bool pWrap);`
`void setWrapY(bool pWrap);`

>Set wrapping settings on a given axis. Default is off.
X wrapping makes the text continue writing on next line.
Y wrapping makes text continue from last row to first row.
If wrapping is off, it does not make any errors when writing beyond the boundaries - characters will simply be ignored.

`void ToLCD();`

>Copy buffer to actual LCD display.

---
