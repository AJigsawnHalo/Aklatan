//This code was adapted from the ChangeUID example code from the MFRC522 libraries.
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 9
#define SS_PIN 10
const int buzzer = 4; //buzzer to arduino pin 4
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
MFRC522::MIFARE_Key key;
void setup() {
// put your setup code here, to run once:
Serial.begin(9600); // Initialize serial communications with the PC
while (!Serial); // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
SPI.begin(); // Init SPI bus
mfrc522.PCD_Init(); // Init MFRC522 card
Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));
}
void loop() {
// put your main code here, to run repeatedly:
// Look for new cards, and select one if present
if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
delay(1500);
return;
}
// Now a card is selected. The UID and SAK is in mfrc522.uid.
//Serial.print(F("Card UID:"));
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
tone(buzzer, 4000); // Send 1KHz sound signal...
delay(100); // ...for 1 sec
noTone(buzzer); // Stop sound...
delay(100); // ...for 1sec
// Serial.println();
}
