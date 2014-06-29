#include "colour.h"
#include "FlashingLight.h"
#include "NoteLight.h"
#include "BreatheLight.h"
#include "Settings.h"

Settings settings;
BreatheLight breatheLight;
NoteLight noteLight;
FlashingLight flashingLight;

int func(String);
int stringToInt(String);

/* "exposed" functions */
int ping(String);
int setLED(String);
int setLode(String);
int setLED(String);
int setFlashRate(String);
int setBreatheRate(String);

void setup() {
    Spark.function("func", func);
    
    settings = Settings();
    noteLight = NoteLight();
    breatheLight = BreatheLight();
    flashingLight = FlashingLight();
    
    RGB.control(true);
}

void loop() {
    if (settings.isSolid() == true){
        RGB.color(noteLight.getRed(), noteLight.getGreen(), noteLight.getBlue());
    } else if (settings.isFlashing() == true) {
        flashingLight.flash();
    } else if (settings.isBreathing() == true) {
        breatheLight.breathe();
    }
}

int setMode(String args) {
    if (args == "solid"){
        settings.setMode(1);
    } else if (args == "flashing") {
        settings.setMode(2);
    } else if (args == "breathing") {
        settings.setMode(3);
    }
    return 0;
}

int setLED(String args) {
    if (args != NULL){
        char hex[8];
        args.toCharArray(hex, 8);
        int rgb[3];
        hextorgb(hex, rgb);
        int r = rgb[0];
        int g = rgb[1];
        int b = rgb[2];
        noteLight.setColours(r,g,b);
    }
    return 0;
}

int setFlashRate(String args) {
    int range = stringToInt(args);
    flashingLight.setFlashRate(range);
    return 0;
}

int setBreatheRate(String args) {
    int range = stringToInt(args);
    breatheLight.setBreatheRate(range);
    return 0;
}

int ping(String args) {
    return 0;
}

int stringToInt(String str) {
    char ch[256];
    str.toCharArray(ch, 256);
    return atoi(ch);
}

/* prototype -- proof of concept function. development use only */
int func(String args) {
    int i = args.indexOf("|");
    String func_name = args.substring(0, i);
    String argv = args.substring(i + 1);
    
    if(func_name.equals("setLED")) return setLED(argv);
    if(func_name.equals("setMode")) return setMode(argv);
    if(func_name.equals("setFlashRate")) return setFlashRate(argv);
    if(func_name.equals("setBreatheRate")) return setBreatheRate(argv);
    if(func_name.equals("ping")) return ping(argv);
    
    return 0x77358008; // ha
}