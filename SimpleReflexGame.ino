/**
 * @author af Rasmus F. Knudsen
 * SimpleReflexGame
 */

#include <EEPROM.h>
#include <SimpleFIFO.h>
#include <MsTimer2.h>

#define KNAP 2
#define LED 13

SimpleFIFO<char, 16> KeyBuffer; /// Keybuffer med 16 elementer

/// Classen af knappen 
class Knap {
  private:
    byte _btn;
  public:
    Knap(byte button) {
      _btn = button;
      init();
    }
    void init() {
      pinMode(_btn, INPUT);
    }
};

/// Classen af LEDen 
class Led {
  private:
    byte _led;
  public:
    Led(byte lys) {
      _led = lys;
      init();
    }
    void init() {
      pinMode(_led, OUTPUT);
    }
};

Knap button (KNAP);
Led lys (LED);


int long gameDelay = 0;
int sensValue = 0;
float realTid;
float gennemsnitsTid;
float endeligTid;
int bedsteTid = 0;

struct Tider {
  char tid;
};

void setup() {
  Serial.begin(115200);

}

/// Spillet sættes op, med forklaring til spilleren
void loop() {
  Serial.println("Nu skal vi måle din reaktionstid");
  Serial.println("Tryk på knappen når lampen lyser \n\n");
  delay(2000);
  Serial.println("Tryk på knappen for at starte spillet\n\n");
  while (digitalRead(KNAP) == 0) {
  }
  Serial.println("Er du klar! \n");
  delay(1000);
  Serial.println("Parat! \n");
  delay(1000);
  Serial.println("Kig på LEDen! \n");
  delay(1000);
  
/// Spillet går igang
  for (int i = 1; i <= 30; i++) {

    gameDelay = random(3000);
    delay(gameDelay);

    realTid = millis();
    digitalWrite(LED, HIGH);

    while (digitalRead(KNAP) == 0) {
    }
    digitalWrite(LED, LOW);
    realTid = millis() - realTid;
    Serial.print("Tid: ");
    Serial.print(realTid / 1000, 2);
    Serial.println(" sekunder\n\n");

    gennemsnitsTid += realTid; /// realTid skal lægges til gennemsnitsTid
  }  
  
  //Serial.println(gennemsnitsTid);
  endeligTid = gennemsnitsTid / 30;

  /// Spillets afslutning, og oplysning om spillerens tid
  while (digitalRead(KNAP) == 0) {
  }
  digitalWrite(LED, LOW);



  Serial.print("Din endelige tid er: ");
  Serial.print(endeligTid / 1000, 2);
  Serial.println(" sekunder\n\n");


  /// Tiderne lægges ind i EEPROM
  EEPROM.put(bedsteTid, endeligTid); /// Tiderne puttes ind
  //EEPROM.get(bedsteTid, endeligTid); /// Tiderne hentes
  
  Serial.println("**************************************< Spillet er slut >************************************\n\n\n");
  delay(7000);
}
