
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>



// Environmental sensors
#define DHT_PIN       D0
#define DHT_TYPE      DHT11
#define LDR_PIN       D1

// Buttons
#define BUTTON_1      D2
#define BUTTON_2      D3

// I2C connections
#define OLED_SDA      D5
#define OLED_SCL      D4

// RGB LED outputs
#define LED_RED       D6
#define LED_GREEN     D7
#define LED_BLUE      D8

// Buzzer driver
#define BUZZER_PIN    D10


#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_MPU6050 mpu;



bool oledReady = false;
bool mpuReady = false;

int lightLevel = 0;
int currentScreen = 0;

float temperature = NAN;
float humidity = NAN;



void setLED(bool red, bool green, bool blue) {
  digitalWrite(LED_RED, red ? HIGH : LOW);
  digitalWrite(LED_GREEN, green ? HIGH : LOW);
  digitalWrite(LED_BLUE, blue ? HIGH : LOW);
}


void beep(unsigned int duration = 100) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(duration);
  digitalWrite(BUZZER_PIN, LOW);
}

void showStatus(const char* message) {
  if (!oledReady) return;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("StudyBuddy");
  display.println("----------------");

  display.println(message);

  display.display();
}



void initialiseSensors() {
  dht.begin();

  mpuReady = mpu.begin();

  Serial.print("MPU6050 status: ");
  Serial.println(mpuReady ? "Connected" : "Not detected");
}


void initialiseDisplay() {
  oledReady = display.begin(
    SSD1306_SWITCHCAPVCC,
    OLED_ADDRESS
  );

  if (oledReady) {
    showStatus("Initialising...");
    Serial.println("OLED initialised.");
  } else {
    Serial.println("OLED not detected.");
  }
}


void setup() {
  Serial.begin(115200);

  // Configure user input pins.
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Configure RGB LED pins.
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // Configure buzzer driver.
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Start I2C using the PCB pin assignments.
  Wire.begin(OLED_SDA, OLED_SCL);

  // Start the display and sensors.
  initialiseDisplay();
  initialiseSensors();

  // Start the DHT11 and MPU6050 setup is complete.
  setLED(false, true, false);

  Serial.println();
  Serial.println("================================");
  Serial.println("    StudyBuddy Firmware");
  Serial.println("================================");
  Serial.println("Microcontroller: XIAO ESP32-C3");
  Serial.println("Initialisation complete.");

  if (oledReady) {
    showStatus("System ready!");
  }

  beep(80);
}


void readSensors() {
  lightLevel = analogRead(LDR_PIN);

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}



void printSensorData() {
  Serial.print("Light level: ");
  Serial.println(lightLevel);

  Serial.print("Temperature: ");

  if (isnan(temperature)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(temperature);
    Serial.println(" C");
  }

  Serial.print("Humidity: ");

  if (isnan(humidity)) {
    Serial.println("Unavailable");
  } else {
    Serial.print(humidity);
    Serial.println(" %");
  }

  if (mpuReady) {
    sensors_event_t acceleration;
    sensors_event_t gyroscope;
    sensors_event_t sensorTemperature;

    mpu.getEvent(
      &acceleration,
      &gyroscope,
      &sensorTemperature
    );

    Serial.print("Acceleration X: ");
    Serial.println(acceleration.acceleration.x);
  }

  Serial.println("------------------------------");
}



void showSensorScreen() {
  if (!oledReady) return;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("Environmental Data");
  display.println("------------------");

  display.print("Light: ");
  display.println(lightLevel);

  display.print("Temp: ");

  if (isnan(temperature)) {
    display.println("--");
  } else {
    display.print(temperature, 1);
    display.println(" C");
  }

  display.print("Humidity: ");

  if (isnan(humidity)) {
    display.println("--");
  } else {
    display.print(humidity, 0);
    display.println("%");
  }

  display.display();
}



void handleButtons() {
  if (digitalRead(BUTTON_1) == LOW) {
    currentScreen = (currentScreen + 1) % 3;

    beep(50);

    Serial.print("Screen changed to: ");
    Serial.println(currentScreen);

    delay(200);
  }

  if (digitalRead(BUTTON_2) == LOW) {
    beep(50);

    Serial.println("Button 2 pressed.");

    delay(200);
  }
}


void updateLED() {
  // Basic demonstration using the ambient light reading.
  if (lightLevel < 1000) {
    setLED(false, true, false);
  } else {
    setLED(true, false, false);
  }
}



void loop() {
  handleButtons();

  readSensors();

  printSensorData();

  updateLED();

  if (currentScreen == 0) {
    showStatus("StudyBuddy ready");
  } else if (currentScreen == 1) {
    showSensorScreen();
  } else {
    showStatus("Study mode planned");
  }

  delay(500);
}


 * PLANNED BUILD WEEK 6
 * 1. Add study/break countdown timer.
 * 2. Add pause, resume and reset controls.
 * 3. Make a OLED menu and settings interface.
 * 4. Add MPU6050 tilt and gesture recognition.
 * 5. Calibrate the LDR readings for ambient light detection.
 * 6. Add RGB LED states for studying, breaks and alerts.
 * 7. Add buzzer notifications when sessions end.
 * 8. Improve button debouncing and remove blocking delays.
 * 9. Test all components on the assembled PCB.
 *
