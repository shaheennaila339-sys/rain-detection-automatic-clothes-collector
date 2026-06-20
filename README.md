# Rain Detection Based Automatic Clothes Collector using NodeMCU

An IoT-based home automation project that automatically detects rainfall and moves a servo motor to pull clothes indoors — protecting them from unexpected rain — and moves them back out once the rain stops.

---

## 📌 Project Overview

This project uses a **NodeMCU (ESP8266)** along with a **rain sensor** to continuously monitor weather conditions. When rain is detected, a **servo motor** is triggered to rotate smoothly from 0° to 180°, simulating the action of pulling a clothesline indoors. Once the rain stops, the servo rotates back from 180° to 0°, returning the clothes outdoors.

The servo movement is controlled gradually (step-by-step rotation with delay) instead of an instant jump, making the motion smooth and realistic — closer to how a real mechanical system would behave.

---

## 🔧 Components Used

| Component         | Quantity |
|--------------------|----------|
| NodeMCU (ESP8266)  | 1        |
| Rain Sensor Module | 1        |
| Servo Motor (SG90 or similar) | 1 |
| Breadboard         | 1        |
| Jumper Wires       | As needed |
| Power Source (USB/Adapter) | 1 |

---

## 🔌 Circuit Connections

| Component        | Pin on Component | Connected to NodeMCU Pin |
|-------------------|------------------|---------------------------|
| Rain Sensor (Digital Out) | D0/OUT  | D1 |
| Servo Motor (Signal)      | Signal  | D2 |
| Servo Motor (VCC)         | VCC     | 5V / VIN |
| Servo Motor (GND)         | GND     | GND |
| Rain Sensor (VCC)         | VCC     | 3.3V |
| Rain Sensor (GND)         | GND     | GND |

> ⚠️ Note: Update this table according to your exact wiring if it differs.

---

## ⚙️ How It Works

1. The rain sensor continuously monitors moisture/rainfall on its surface.
2. The digital output pin (connected to **D1** on NodeMCU) reads:
   - **LOW (0)** → Rain detected
   - **HIGH (1)** → No rain / surface dry
3. Based on this reading:
   - If rain is detected and the clothesline is currently outdoors (`currentPos == 0`), the servo smoothly rotates from **0° to 180°**, pulling clothes indoors.
   - If rain stops and the clothesline is currently indoors (`currentPos == 180`), the servo smoothly rotates back from **180° to 0°**, moving clothes back outdoors.
4. The `moveSlowly()` function ensures the servo moves gradually (1° at a time with a 15ms delay) instead of snapping instantly, for smoother and safer mechanical movement.
5. Status updates are printed to the Serial Monitor at each stage (e.g., *"BARISH! Kapre Andar Ho Rahe Hain..."*) for easy debugging and monitoring.

---

## 💻 Code

The full Arduino/NodeMCU code is available here: [`rain_detector.ino`](./rain_detector.ino)

```cpp
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
```

---

## 🚀 Features

- ✅ Real-time automatic rain detection
- ✅ Smooth, gradual servo movement (not abrupt)
- ✅ Automatic two-way control (indoors on rain, outdoors when clear)
- ✅ Serial Monitor status logging for debugging
- ✅ Low-cost, beginner-friendly IoT solution
- ✅ Practical home automation application

---

## 🛠️ Tools & Technologies

- Arduino IDE
- NodeMCU (ESP8266) board package
- Embedded C/C++ (Arduino framework)
- Servo Library

---

## 📷 Project Demo

*(Add photos or a short GIF/video link of your working setup here)*

---

## 🔮 Future Improvements

- Add a buzzer/notification alert when rain is detected
- Integrate with a mobile app (via Blynk or Firebase) for remote monitoring
- Add a light sensor to detect sunny conditions for better automation
- Use a more robust motor/mechanism for real-world clothesline sizes
- Add Wi-Fi based notifications (e.g., to a phone) instead of only Serial Monitor logs

---

## 👤 Author

**[Naila Shaheen]**  
Feel free to connect with me on [LinkedIn](#) or check out more projects on my [GitHub](#).

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
