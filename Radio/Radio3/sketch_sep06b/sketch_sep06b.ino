//This is the function called when the interrupt occurs (pin 2 goes high)
//this is often referred to as the interrupt service routine or ISR
//This cannot take any input arguments or return anything
void interruptFunction() {
  count++; //up the receive counter
  while (wirelessSPI.available()) { //get data sent from transmit
    wirelessSPI.read( &gotByte, 1 ); //read one byte of data and store it in gotByte variable
  }

}


#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
byte counter = 1; //used to count the packets sent
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t pAddress = 0xB00B1E5000LL;              // Radio pipe addresses for the 2 nodes to communicate.

void setup()
{
  Serial.begin(57600);   //start serial to communicate process
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setAutoAck(1);                    // Ensure autoACK is enabled so rec sends ack packet to let you know it got the transmit packet payload
  wirelessSPI.enableAckPayload();               // Allow optional ack payloads
  wirelessSPI.setPALevel(RF24_PA_LOW);
  wirelessSPI.openWritingPipe(pAddress);        // pipe address that we will communicate over, must be the same for each nRF24 module
  wirelessSPI.stopListening();        //transmitter so stop listening for data
  randomSeed(analogRead(0));    //use random ADC value to seed random number algorithm
}

void loop() {
  delay(random(100, 5000)); //Generate delay time between 100msec and 5 sec
  Serial.println("Sending packet");
  if (!wirelessSPI.write( &counter, 1 )) { //if the send fails let the user know over serial monitor
    Serial.println("packet delivery failed");
  }
  Serial.println();
}
