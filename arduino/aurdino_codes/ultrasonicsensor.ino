/**
 * @brief This is arduino code that handles the distance sensor input feed and print it on serial monitor
 *
 * @author Rahulkumar Gupta <grahulkumar2002@gmail.com>
 *
 */

// define pins
#define echoPin 2
#define trigPin 3
#define led_pin 13

// define variables
long duration;
int distance;

/**
 * @brief Setup function of arduino that runs on in the start which sets the pinMode.
 * 
 */
void setup()
{

  // setting pinMode

  pinMode(led_pin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600); // in order to setup a serial communication and print on serial monitor
}

/**
 * @brief Loop function of arduino runs loops continuous till arduino is on 
 * 
 */
void loop()
{

  digitalWrite(trigPin, LOW); // set trigger pin LOW
  delayMicroseconds(2);       // let signal settle

  digitalWrite(trigPin, HIGH); // set trigger pin HIGH
  delayMicroseconds(10);       // duration in HIGH state

  digitalWrite(trigPin, LOW); // set back to LOW
  delayMicroseconds(2);
  duration = pulseIn(echoPin, HIGH); // returns time in Microseconds
  distance = duration * 0.034 / 2;   // Speed of sound 340m/s ,Divide it by 2(Since,single is transmits and reflects back=>covering same path in different directions)

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 50)
  {                              // if satisfy
    digitalWrite(led_pin, HIGH); // set to HIGH
    delay(10);                   // duration in HIGH state
    digitalWrite(led_pin, LOW);  // set back to LOW
  }

  if (distance < 10)
  {

    digitalWrite(led_pin, HIGH); // following in same manner as above
    delay(10);
    digitalWrite(led_pin, LOW);
  }
}
