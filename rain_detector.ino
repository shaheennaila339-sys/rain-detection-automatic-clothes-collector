#include <Servo.h>
Servo s1;
int val = 0;
int currentPos = 0;  // Current position track karne ke liye

void setup()
{
    Serial.begin(115200);
    pinMode(D1, INPUT_PULLUP);
    s1.attach(D2);
    s1.write(0);
    Serial.println("Wheather's Clear!");
}

void moveSlowly(int startPos, int endPos) 
{
    if (startPos < endPos)  
    {
        for (int i = startPos; i <= endPos; i++) 
        {
            s1.write(i);
            delay(15);  
        }
    } 
    else  
    {
        for (int i = startPos; i >= endPos; i--) 
        {
            s1.write(i);
            delay(15);
        }
    }
    currentPos = endPos;
}

void loop() 
{
    val = digitalRead(D1);
    delay(100);
    
    if(val == 0 && currentPos == 0)      // BARISH
    {
        Serial.println("BARISH! Kapre Andar Ho Rahe Hain...");
        moveSlowly(0, 180);
        Serial.println("Kapre Andar Ho Gaye!");
    }
    else if(val == 1 && currentPos == 180)  // SAAF
    {
        Serial.println("Rain Has Stopped! Kapre Bahar Ja Rahe Hain...");
        moveSlowly(180, 0);
        Serial.println("Kapre Bahar Ho Gaye!");
    }
}
