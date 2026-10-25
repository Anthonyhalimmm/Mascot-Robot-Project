
# 🐧💃 Penguin Mascot Robot

A penguin mascot for our family business that greets customers, talks, and dances.

<img width="1080" height="1096" alt="1000400101" src="https://github.com/user-attachments/assets/2dcb5601-47fb-4e87-9b6e-4df20e6c21b7" />

## What it does
- **Notices people.** Wave your hand close to it, or walk past, and it reacts
- **Moves** its arms, head, and body with 4 servos
- **Talks** with pre-recorded voice lines
- **Shows emotions** with 2 LCD eyes

## How it works
1. The ultrasonic sensor measures how far away someone is
2. Walk past (80–150 cm) and the penguin waves hello
3. Wave your hand close (under 15 cm) and the Arduino picks a random move
4. The Arduino plays a voice line and tells the ESP32 which eyes to show
5. The ESP32 loads the eye images from the SD card onto the two screens

## Hardware
- Arduino Mega (servos, sensor, audio)
- ESP32 (eyes)
- 4 servos (left arm, right arm, head, body)
- Ultrasonic sensor
- DFPlayer Mini + speaker
- 2 x 1.8" TFT screens (ST7735)
- 2 x microSD cards (one for audio, one for eye images)

| Move | Eyes |
|--------|--------|
| 👋 Wave | 😊 Happy |
| 💃 Dance | 🤩 Excited |
| 🎉 Excited | 🤩 Excited |
| 😠 Angry | 😠 Angry |
| 😢 Sad | 😢 Sad |

## Future upgrades
- Smoother servo movements
- More voice lines and dances
- Use a PCB to neaten the wiring

---
Built by Anton 🤖
