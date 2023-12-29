#define BLYNK_TEMPLATE_ID "TMPL27GHEVvQ4"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "kZY6OfDmvgDwzOgl9hMgvDr9ydc_81gv"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

const int ledPin = 2;  // Built-in LED pin on most ESP32 boards

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "X";
char pass[] = "X";

BlynkTimer timer;

BLYNK_WRITE(V6)
{
  // Set incoming value from pin V6 to a variable
  int switchValue = param.asInt();

  // Check the state of the switch
  if (switchValue == 1)
  {
    Serial.println("Switch is ON");
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    Serial.println("Switch is OFF");
    digitalWrite(ledPin, LOW);  // Turn off LED
  }
}


// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  //sensors.requestTemperatures(); 
  //float temperatureC = sensors.getTempCByIndex(0);
  //Serial.print(temperatureC);
  //Serial.println("ºC");
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int randomNumber = random(101);
  
  Blynk.virtualWrite(V2, randomNumber);
  //Blynk.virtualWrite(V4, temperatureC);
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
    // Start the DS18B20 sensor
  //sensors.begin();
  Serial.println("Setup started");

  pinMode(ledPin, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
