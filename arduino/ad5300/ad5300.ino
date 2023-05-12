#include <SPI.h>

// Define the chip select pin for the AD5300 chip
const int CS_PIN = 10;

//Arduino UNO
//SLK PIN 13
//MOSI PIN 11


void setup() {
  // Initialize SPI communication
  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set the chip select pin to inactive/high
}

void loop() {
  unsigned char hexValue = 0x00;

  for (int i = 0; hexValue <= 0x0F; i++, hexValue++) {
    digitalWrite(CS_PIN, LOW); // Select the AD5300 chip
    SPI.transfer(hexValue); // Send the write and update DAC register command
    SPI.transfer(0xC0); // Send the MSB of the 12-bit data word
    digitalWrite(CS_PIN, HIGH); // Deselect the AD5300 chip

    // Delay for a short period of time (e.g. 100ms)
    delay(1000);
  }

}
