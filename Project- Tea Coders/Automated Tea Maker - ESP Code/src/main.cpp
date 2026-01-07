#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char *ssid = "HUAWEI-2.4G-6qSe";
const char *password = "wyeRy2eZ";

IPAddress local_IP(192, 168, 18, 50);
IPAddress gateway(192, 168, 18, 1);
IPAddress subnet(255, 255, 255, 0);

const int RELAY1_PIN = 27; // Motor 1
const int RELAY2_PIN = 26; // Motor 2
const int STOVE_PIN = 23;
const int SERVO1_PIN = 18;
const int SERVO2_PIN = 19;

Servo servo1, servo2;
WebServer server(80);

// State management
enum State
{
  IDLE,
  MOTOR1_RUNNING,
  MOTOR2_RUNNING,
  SERVO_RUNNING,
  STOVE_RUNNING,
  COMPLETED
};
State currentState = IDLE;

unsigned long motor1EndTime = 0;
unsigned long motor2EndTime = 0;
unsigned long stoveEndTime = 0;

int motor1Duration = 0;
int motor2Duration = 0;
int servo1Rotations = 0;
int servo2Rotations = 0;
int stoveDuration = 0;

void startMotor1(int seconds)
{
  digitalWrite(RELAY1_PIN, LOW); // LOW = relay ON
  motor1EndTime = millis() + (seconds * 1000);
  currentState = MOTOR1_RUNNING;

  Serial.println("MOTOR 1 STARTED");
  Serial.print("Motor 1 duration: ");
  Serial.print(seconds);
  Serial.println(" seconds");
}

void stopMotor1()
{
  digitalWrite(RELAY1_PIN, HIGH); // HIGH = relay OFF
  Serial.println("MOTOR 1 STOPPED");
}

void startMotor2(int seconds)
{
  digitalWrite(RELAY2_PIN, LOW); // LOW = relay ON
  motor2EndTime = millis() + (seconds * 1000);
  currentState = MOTOR2_RUNNING;

  Serial.println("MOTOR 2 STARTED");
  Serial.print("Motor 2 duration: ");
  Serial.print(seconds);
  Serial.println(" seconds");
}

void stopMotor2()
{
  digitalWrite(RELAY2_PIN, HIGH); // HIGH = relay OFF
  Serial.println("MOTOR 2 STOPPED");
}

void startServos(int rotations1, int rotations2)
{
  currentState = SERVO_RUNNING;

  Serial.println("SERVOS STARTED");
  Serial.print("Servo 1 rotations: ");
  Serial.println(rotations1);
  Serial.print("Servo 2 rotations: ");
  Serial.println(rotations2);

  // Calculate max rotations to handle both servos
  int maxRotations = max(rotations1, rotations2);

  for (int i = 0; i < maxRotations; i++)
  {
    // Rotate servo 1 if it still has rotations remaining
    if (i < rotations1)
    {
      servo1.write(90);
    }
    // Rotate servo 2 if it still has rotations remaining
    if (i < rotations2)
    {
      servo2.write(90);
    }

    delay(500);

    // Return to 0 degrees
    if (i < rotations1)
    {
      servo1.write(0);
    }
    if (i < rotations2)
    {
      servo2.write(0);
    }

    delay(500);
  }

  servo1.write(0);
  servo2.write(0);
  Serial.println("SERVOS STOPPED");
}

void startStove(int seconds)
{
  digitalWrite(STOVE_PIN, HIGH);
  stoveEndTime = millis() + (seconds * 1000);
  currentState = STOVE_RUNNING;

  Serial.println("STOVE STARTED");
  Serial.print("Stove duration: ");
  Serial.print(seconds);
  Serial.println(" seconds");
}

void stopStove()
{
  digitalWrite(STOVE_PIN, LOW);
  Serial.println("STOVE STOPPED");
}

void handleStart()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");

  if (currentState != IDLE)
  {
    server.send(400, "application/json", "{\"error\":\"Device already running\"}");
    return;
  }

  if (server.hasArg("motor1") && server.hasArg("motor2") &&
      server.hasArg("servo1") && server.hasArg("servo2") &&
      server.hasArg("stove"))
  {

    motor1Duration = server.arg("motor1").toInt();
    motor2Duration = server.arg("motor2").toInt();
    servo1Rotations = server.arg("servo1").toInt();
    servo2Rotations = server.arg("servo2").toInt();
    stoveDuration = server.arg("stove").toInt();

    if (motor1Duration > 0 && motor1Duration <= 20 &&
        motor2Duration > 0 && motor2Duration <= 20 &&
        servo1Rotations > 0 && servo2Rotations > 0 &&
        stoveDuration > 0)
    {

      startMotor1(motor1Duration);

      String response = "{\"status\":\"Sequence started\",\"motor1\":" + String(motor1Duration) +
                        ",\"motor2\":" + String(motor2Duration) +
                        ",\"servo1\":" + String(servo1Rotations) +
                        ",\"servo2\":" + String(servo2Rotations) +
                        ",\"stove\":" + String(stoveDuration) + "}";
      server.send(200, "application/json", response);
    }
    else
    {
      server.send(400, "application/json", "{\"error\":\"Invalid parameters\"}");
    }
  }
  else
  {
    server.send(400, "application/json", "{\"error\":\"Missing parameters\"}");
  }
}

void handleStop()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");

  if (currentState == MOTOR1_RUNNING)
  {
    stopMotor1();
  }
  else if (currentState == MOTOR2_RUNNING)
  {
    stopMotor2();
  }
  else if (currentState == SERVO_RUNNING)
  {
    servo1.write(0);
    servo2.write(0);
  }
  else if (currentState == STOVE_RUNNING)
  {
    stopStove();
  }

  currentState = IDLE;
  Serial.println("Sequence stopped manually");
  server.send(200, "application/json", "{\"status\":\"Stopped\"}");
}

void handleStatus()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");

  String stateStr = "idle";
  unsigned long remaining = 0;

  if (currentState == MOTOR1_RUNNING)
  {
    stateStr = "motor1";
    remaining = (motor1EndTime - millis()) / 1000;
  }
  else if (currentState == MOTOR2_RUNNING)
  {
    stateStr = "motor2";
    remaining = (motor2EndTime - millis()) / 1000;
  }
  else if (currentState == SERVO_RUNNING)
  {
    stateStr = "servo";
    remaining = 0;
  }
  else if (currentState == STOVE_RUNNING)
  {
    stateStr = "stove";
    remaining = (stoveEndTime - millis()) / 1000;
  }
  else if (currentState == COMPLETED)
  {
    stateStr = "completed";
    remaining = 0;
  }

  String response = "{\"state\":\"" + stateStr + "\",\"remaining\":" + String(remaining) + "}";
  server.send(200, "application/json", response);
}

void setup()
{
  Serial.begin(115200);
  delay(2000);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(STOVE_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(STOVE_PIN, LOW);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo1.write(0);
  servo2.write(0);

  Serial.println("All systems OFF");

  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    delay(500);
    attempts++;
  }

  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());

  server.on("/start", HTTP_POST, handleStart);
  server.on("/stop", HTTP_POST, handleStop);
  server.on("/status", HTTP_GET, handleStatus);
  server.begin();

  Serial.println("Ready!");
}

void loop()
{
  server.handleClient();

  // Sequential state machine
  if (currentState == MOTOR1_RUNNING && millis() >= motor1EndTime)
  {
    stopMotor1();
    startMotor2(motor2Duration);
  }

  if (currentState == MOTOR2_RUNNING && millis() >= motor2EndTime)
  {
    stopMotor2();
    startServos(servo1Rotations, servo2Rotations);
    startStove(stoveDuration);
  }

  if (currentState == STOVE_RUNNING && millis() >= stoveEndTime)
  {
    stopStove();
    currentState = COMPLETED;
    Serial.println("SEQUENCE COMPLETED");
  }
}