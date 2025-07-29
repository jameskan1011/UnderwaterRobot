# AquaVise: Underwater Inspection Robot

AquaVise is a compact and intelligent underwater Remotely Operated Vehicle (ROV) developed for corrosion inspection and monitoring tasks, specifically within nuclear reactor pools. It combines mechanical agility, advanced sensing, and intelligent software to detect corrosion visually and maintain stable maneuverability in challenging underwater environments.

> 🏆 **Capstone Theme Award** at Universiti Teknologi Malaysia  
> 🏆 **Gold Award** in International Virtual Competition of Creative & Innovative Idea (IVCCII 2025)
---
![WhatsApp Image 2025-03-29 at 11 39 36 PM (1) (1)](https://github.com/user-attachments/assets/c5f30906-900e-454f-88ee-cfb0cc5afcda)
![WhatsApp Image 2025-03-29 at 11 39 37 PM](https://github.com/user-attachments/assets/25cc38fa-0910-417d-a6c5-3fb00c2d68e7)


## 📽️ Demonstration

- **Test in Aquarium:**  
https://github.com/user-attachments/assets/d291c60b-21bb-4c5e-aba0-56c1710979f3

- **Pipe Corrosion Detected:**  
<img width="809" height="654" alt="corrosion2_crop" src="https://github.com/user-attachments/assets/e504461e-245e-4bd7-a238-9ed83fb6b39e" />
<img width="817" height="661" alt="corrosion1_crop" src="https://github.com/user-attachments/assets/bde0b57b-7522-478f-b653-d45948cfe81d" />

- **Adjustable Camera:**
[ezgif-14e0a4dfad839b.webm](https://github.com/user-attachments/assets/6dd5c388-9fd7-4827-bece-901261d9a31d)


---

## 🚀 Features

- **Corrosion Detection**  
  Utilizes OpenCV-based color thresholding to detect yellow-hued corrosion spots.

- **IMU Stabilization**  
  The MPU6050 IMU ensures stability through real-time pitch and roll correction.

- **Compact 3D-Printed Design**  
  The PLA body with epoxy coating is lightweight, waterproof, and environmentally conscious.

- **Four Thruster System**  
  Ensures 6-DOF movement for optimal maneuverability in confined or dynamic underwater spaces.

- **Integrated Control**  
  Arduino Mega and Raspberry Pi Pico combination enables seamless control and sensor data handling.

- **Real-Time Monitoring**  
  Camera feed with corrosion highlight overlay, live water temperature display, and adjustable servo-driven camera angle.

---

## 🛠️ Hardware Overview

| Component             | Description                            |
|----------------------|----------------------------------------|
| MCU                  | Arduino Mega + Raspberry Pi Pico       |
| Sensors              | MPU6050 IMU, Waterproof Thermometer    |
| Camera               | Endoscope with servo for angle control |
| Motors               | 4 Brushed Motors with Propellers       |
| Motor Drivers        | Dual-channel H-bridge drivers          |
| Power Supply         | 12.6V 9800mAh Li-Po Battery             |
| Chassis              | PLA 3D Printed, Coated with Epoxy Resin|

---

## 💻 Software Components

- **Python (Raspberry Pi):**  
  - IMU data processing  
  - Corrosion detection using HSV filtering  
  - UART serial communication to Arduino

- **Arduino C++ (Arduino Mega):**  
  - Joystick handling  
  - Thruster control based on IMU commands  
  - Servo motor positioning for camera

---

## 🧪 Test Highlights

- **Lab Testing:** Corrosion detection software detects yellow regions on test surfaces with adjustable HSV trackbars.
- **On-Site Testing:**  
  - Conducted in aquarium with variable lighting and water clarity.  
  - Detection accuracy improved with real-time HSV tuning via GUI sliders.

---

## ⚙️ System Architecture

<img width="712" height="262" alt="image" src="https://github.com/user-attachments/assets/7a6fb173-3955-40f8-b272-6960f7693c36" />

---

## 🗺️ Future Improvements

- Replace current thrusters with high-torque waterproof models.
- Use modular ballast containers for adjustable buoyancy.
- Add leak detection sensors with moisture-triggered failsafe shutoff.
- Refine body design for easier maintenance and internal access.
- Upgrade to wireless control with robust data transmission.

---

## 📅 Project Timeline

- Week 1–2: Planning, research & user analysis  
- Week 3–4: Design & CAD modeling  
- Week 5–8: Assembly, coding, integration  
- Week 9–10: Testing, optimization  
- Week 11: Presentation & award recognition  

---

## 👨‍🔧 Authors

- **Aina Nuha Binti Che Mahadzir**  
- **Kan Chang Fei**  
- **Nourhan Hatem Mohammed**  
- **Supervisor:** Assoc. Prof. Ts. Dr. Anita Binti Ahmad  
- Faculty of Electrical Engineering, Universiti Teknologi Malaysia

---

## 📜 License

This project is for academic use. Please contact the authors for permissions on reproduction or distribution.

---

## 📎 References

1. [Motherboard: Engineering the Ultimate Robotic Fish](https://www.youtube.com/watch?v=9ISGXe0Vl5A)  
2. [Science Buddies: Build an Underwater ROV](https://www.youtube.com/watch?v=wRco4tGXrzw)  
3. [CPSdrone: 3D Printed Submarine DIY](https://www.youtube.com/watch?v=arTLho86huQ)

---

