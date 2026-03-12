# Automatice Water DC Filling Machine
### Real-Time Embedded Project

**Real-Time State Machine | Flow Meter | Ultrasonic Detection | Embedded Control**  
**Platform:** Raspberry Pi 5 and C++  
**Components:** DC Water Pump | YF-S401 Flow Meter | HC-SR04 Ultrasonic Sensor  

---

## Project Overview

This project implements a small automatic bottle filling system using a Raspberry Pi 5 programmed in C++. The goal is to demonstrate how a low-cost embedded system can automate a water dispensing process similar to those used in industrial filling systems.

The system detects when a bottle is placed under the filling nozzle using an ultrasonic sensor. Once the bottle is detected and remains in place for a short confirmation period, the Raspberry Pi activates a small DC water pump.

Water flows through a flow sensor that produces electrical pulses proportional to the water volume. The Raspberry Pi counts these pulses in real time to determine how much water has been dispensed. When the target volume is reached, the pump is switched off automatically.

The complete automated cycle is:

detect → pump → measure → stop
---

# Project Details

| Field | Details |
|------|------|
| **Project Title** | Automatic Bottle Water Filling System |
| **Platform** | Raspberry Pi 5 — C++ |
| **Core Mechanism** | Bottle detection → automatic filling → stop at target volume |
| **Key Sensors** | YF-S401 flow meter + HC-SR04 ultrasonic sensor |
| **Control Logic** | Real-time state machine |
| **Hardware Cost** | £35 – £60 |

---

# Problem Statement

Manually filling bottles is slow and inconsistent. Human error often causes bottles to be overfilled or underfilled. Industrial bottling plants solve this using automated filling machines, but these systems are expensive.

This project explores whether a similar concept can be implemented using a Raspberry Pi and low-cost sensors.

The main challenges are:

- Detecting when a bottle is positioned correctly
- Measuring water volume accurately
- Turning the pump on and off at the correct moment
- Coordinating sensors and actuators reliably

---

# System Architecture

## Physical Layout
```
The water path is simple. A small pump pushes water from a container through the flow sensor and out through the filling nozzle.

Water Tank / Container
│
│
┌────▼─────┐
│ DC Pump │
└────┬─────┘
│
┌────▼─────┐
│ YF-S401 │
│Flow Meter│
└────┬─────┘
│
▼
Nozzle
│
▼
[Bottle]
▲
│
HC-SR04 Ultrasonic Sensor
(detects bottle under nozzle)

```
---

# System Operation

The system works through a simple automated cycle.

| Step | Action |
|----|----|
| Step 1 | System waits for bottle |
| Step 2 | Ultrasonic sensor detects bottle |
| Step 3 | Bottle position confirmed |
| Step 4 | Pump starts |
| Step 5 | Flow sensor pulses counted |
| Step 6 | Target volume reached |
| Step 7 | Pump stops and system resets |

---

# Complete Block Diagram
                +----------------------+
                |    Raspberry Pi 5    |
                |                      |
                |  Control State Machine
                |                      |
                |  Flow Pulse Counter  |
                +----+------------+----+
                     |            |
                     |            |
          Distance   |            | Pulse Signal
                     |            |
           +---------v----+   +---v----------+
           | Ultrasonic   |   |   YF-S401    |
           |    Sensor    |   | Flow Sensor  |
           +--------------+   +--------------+

                       Pump control
                            |
                            v
                     +-------------+
                     | TIP121      |
                     | Transistor  |
                     +------+------+
                            |
                            v
                     +-------------+
                     |  DC Pump    |
                     +------+------+
                            |
                            v
                      Water Output


---

# Water Flow Architecture
Water Container
│
▼
DC Pump
│
▼
YF-S401 Flow Sensor
│
▼
Filling Nozzle
│
▼
Bottle


---

# Software Architecture

The project is written in **C++** using modular classes so that each hardware component is handled independently.

| Class | Responsibility |
|------|------|
| `UltrasonicSensor` | Measures bottle distance |
| `PumpController` | Controls pump operation |
| `FlowMeter` | Counts pulses and calculates volume |
| `FillingController` | Controls system logic |
| `Monitor` | Displays system status |

---

# Control Logic

The system operates using a simple **state machine**.

## Control Logic

The system operates using a simple state machine.

```text
System Start
     │
     ▼
┌───────────────┐
│   WAITING     │
│ No bottle yet │
└───────┬───────┘
        │ bottle detected
        ▼
┌───────────────┐
│ CONFIRMATION  │
│ Bottle stable │
└───────┬───────┘
        │ confirmed
        ▼
┌───────────────┐
│   FILLING     │
│ Pump ON       │
│ Count pulses  │
└───────┬───────┘
        │ volume reached
        ▼
┌───────────────┐
│ FILL COMPLETE │
│ Pump OFF      │
└───────┬───────┘
        │
        ▼
      WAITING

---
```
# Hardware Components

| Component | Purpose | Estimated Cost |
|------|------|------|
| Raspberry Pi 5 | Main controller | £35–45 |
| Mini DC Water Pump | Moves water | £5–8 |
| TIP121 Transistor | Switch pump power | £1 |
| YF-S401 Flow Sensor | Measures water flow | £3–5 |
| HC-SR04 Ultrasonic Sensor | Detects bottle presence | £2–3 |
| 1N4007 Diode | Protects transistor | £1 |
| Resistors (1kΩ, 2kΩ) | Voltage divider & base resistor | £1 |
| Breadboard & wires | Assembly | £3–5 |
| Water tubing | Water transport | £2–3 |

Estimated total cost: **£45–60**

---

# Development Plan

### Week 1
Set up Raspberry Pi GPIO and test ultrasonic sensor.

### Week 2
Integrate pump and transistor driver.

### Week 3
Add flow sensor and pulse counting logic.

### Week 4
Combine all components and test full filling cycle.

---

# Conclusion

This project demonstrates how a simple embedded system can automate a practical task such as filling bottles with water. By combining sensor feedback, real-time control, and a structured state machine, the Raspberry Pi manages the entire process automatically.

Although the system is relatively simple, it reflects the same principles used in real industrial automation systems: sensor input, actuator control, and reliable timing.

The project provides hands-on experience with:

- Embedded C++
- Raspberry Pi GPIO control
- Sensor integration
- Real-time system design

---

# License

MIT License
