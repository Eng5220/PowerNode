# DC Conveyor Water Filling Machine
### Real-Time Embedded Project

**Real-Time State Machine | Flow Meter | IR Bottle Detection | IoT Dashboard**  
**Platform:** Raspberry Pi 5 + C++  
**Components:** DC Motor | Solenoid Valve | YF-S201 Flow Meter | IR Sensor

---

| Field | Details |
|---|---|
| **Project Title** | DC Conveyor Water Filling Machine |
| **Platform** | Raspberry Pi 5 — C++ |
| **Core Mechanism** | Conveyor belt → bottle detection → fill to 500ml → advance/continue |
| **Key Sensors** | YF-S201 flow meter + IR obstacle sensor |
| **Control Logic** | Real-time state machine (20ms loop) |
| **Duration** | 4 Weeks |
| **Hardware Cost** | $78 – $117 USD (estimated) |

---

## 1. Executive Summary

This project designs and implements a real-time DC Conveyor Water Filling Machine on a Raspberry Pi 5 using C++. The system automatically detects bottles on a moving conveyor belt, stops the belt when a bottle is positioned under the nozzle, fills the bottle to a target volume using a flow meter, then restarts the belt to advance the next bottle. The entire process is controlled by a five-state real-time state machine running at a 20ms loop frequency under `SCHED_FIFO` scheduling.

The project is modelled directly on industrial bottling line automation — one of the most common real-world applications of embedded real-time systems.

> **Hard real-time consequence of missing a deadline:** At a flow rate of 500 ml/min, the solenoid valve dispenses ~8.3 ml/sec. If the valve-close ISR is delayed by more than 5 ms, the bottle overfills by ~41 ml — an 8% volume error that violates fill accuracy requirements and constitutes a hard real-time deadline miss.

---

## 2. Problem Statement & Motivation

Manual water bottling is slow, inconsistent in fill volume, and labour-intensive. Industrial bottling plants solve this with automated conveyor-based filling lines, but these systems cost millions of dollars and use proprietary controllers. This project demonstrates that the same fundamental automation concept — **detect, stop, fill, advance** — can be implemented on an affordable single-board computer using open-source real-time C++, achieving fill accuracy comparable to commercial systems.

The core engineering challenges are:
- Detecting a bottle in the correct position reliably using an IR sensor
- Measuring dispensed volume accurately using pulse counting from a flow meter
- Ensuring the solenoid valve closes at exactly the right moment to hit the target volume
- Coordinating the conveyor motor and valve as a coherent real-time system with no race conditions or timing errors

### The Complete Filling Cycle — One Bottle

| Step | Action |
|---|---|
| **Step 1** — Belt RUNNING | Conveyor motor ON, belt moving forward |
| **Step 2** — Bottle DETECTED | IR sensor fires GPIO interrupt → belt stops immediately |
| **Step 3** — FILLING begins | Solenoid valve opens, flow meter starts counting pulses |
| **Step 4** — Volume reached | Pulse count × 2.25ml >= 500ml → valve closes instantly |
| **Step 5** — SETTLE wait | 200ms pause — water stops flowing, no drip |
| **Step 6** — Belt RESTARTS | Motor ON, filled bottle moves away, next bottle arrives |
| **Step 7** | Repeat from Step 1 |

---

## 3. System Architecture

### 3.1 Physical Layout

```
Water Tank (elevated)
│
│ gravity / pump
┌────▼─────┐
│ Solenoid │ ← normally closed, opens to fill
│  Valve   │
└────┬─────┘
     │
┌────▼─────┐
│ YF-S201  │ ← counts pulses, each = 2.25ml
│Flow Meter│
└────┬─────┘
     │ nozzle
     ▼
═══════╪═══════════════════════════════════════ Belt
    [ BOTTLE ]──────────────────────────────────►
        ▲
     IR Sensor
     (detects bottle under nozzle → GPIO interrupt)

Belt direction: Empty bottles ──► Filled bottles
Belt driven by DC geared motor via L298N on left roller
```

### 3.2 Five-State Machine Diagram

```
System Start
│
▼
┌──────────────────┐
│      IDLE        │
│  Start button    │
│    pressed       │
└────────┬─────────┘
         │ Start pressed
         ▼
┌─────────────────────────────────────┐
│           BELT_RUNNING              │◄──────────────────┐
│  Conveyor motor ON                  │                   │
│  Waiting for IR sensor to fire      │                   │
└────────────────┬────────────────────┘                   │
                 │ IR interrupt: bottle detected           │
                 ▼                                        │
┌─────────────────────────────────────┐                   │
│             FILLING                 │                   │
│  Belt stopped                       │                   │
│  Valve open                         │                   │
│  Flow meter counting pulses         │                   │
│  LCD: '247ml / 500ml'               │                   │
└────────────────┬────────────────────┘                   │
                 │ flow >= TARGET_ML                      │
                 ▼                                        │
┌─────────────────────────────────────┐                   │
│          FILL_COMPLETE              │                   │
│  Valve closed                       │                   │
│  Buzzer beep                        │                   │
│  200ms settle wait                  │                   │
│  bottle_count++                     │                   │
└────────────────┬────────────────────┘                   │
                 │ settle done                            │
                 └────────────────────────────────────────┘
                         Belt restarts → BELT_RUNNING
```

### 3.3 Complete Block Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                  RASPBERRY PI 5 (C++)                       │
│                                                             │
│  Main Thread (SCHED_FIFO 80, 20ms loop):                    │
│    State machine: IDLE → BELT_RUNNING → FILLING →           │
│    FILL_COMPLETE → BELT_RUNNING                             │
│                                                             │
│  Monitor Thread (normal priority, 500ms):                   │
│    LCD update + MQTT publish + CSV log                      │
│                                                             │
│  ISR 1 — GPIO 23 (YF-S201): pulse++ per 2.25ml             │
│  ISR 2 — GPIO 24 (IR sensor): bottleDetected = true        │
└──────┬──────────┬───────────┬──────────┬────────────────────┘
       │          │           │          │
 ┌────▼───┐ ┌────▼───┐ ┌────▼───┐ ┌────▼───────────────────┐
 │ L298N  │ │ Relay  │ │  IR    │ │       YF-S201           │
 │ Motor  │ │ Module │ │ Sensor │ │      Flow Meter         │
 │ Driver │ │        │ │        │ │     (pulse ISR)         │
 └────┬───┘ └────┬───┘ └────────┘ └────────────────────────┘
      │          │
 ┌────▼───┐ ┌────▼──────────┐
 │Conveyor│ │   Solenoid    │
 │  Belt  │ │  Valve (NC)   │
 │  Motor │ └───────────────┘
 └────────┘
```

---

## 4. Software Architecture — Class Design (SOLID Principles)

All Raspberry Pi code is written in C++ following SOLID design principles. Each hardware subsystem is encapsulated in its own class with a well-defined public interface.

| Class | Responsibility | Key Methods |
|---|---|---|
| `ConveyorMotor` | Wraps L298N GPIO; drives belt | `start()`, `stop()`, `setSpeed(pwm)` |
| `SolenoidValve` | Wraps relay GPIO; controls water flow | `open()`, `close()` |
| `FlowMeter` | Owns pulse ISR; converts pulses to ml | `getVolumeML()`, `resetCount()`, `registerCallback(fn)` |
| `IRSensor` | Owns GPIO interrupt; notifies on bottle | `registerCallback(fn)`, ISR handler |
| `FillingStateMachine` | Orchestrates state transitions using the above classes | `tick()`, `getState()` |
| `MonitorThread` | Normal-priority thread: LCD, MQTT, CSV log | `start()`, `stop()`, `publish()` |

**SOLID mapping:**
- **S** — Each class owns exactly one subsystem (no god-object)
- **O** — `IRSensor` and `FlowMeter` accept callbacks so the state machine does not need to be modified to change event handling
- **L** — All hardware classes share a common `IHardwareDevice` interface for testability with mocks
- **I** — `MonitorThread` depends only on a read-only `StatusProvider` interface, not the full state machine
- **D** — `FillingStateMachine` depends on abstractions (`IValve`, `IMotor`, `ISensor`), not concrete GPIO classes — enabling unit testing without hardware

---

## 5. Real-Time Latency Budget

All timing decisions are derived from measured or calculated worst-case latencies.

| Event | Latency Target | Consequence of Miss | Mechanism |
|---|---|---|---|
| IR trigger → belt stop | < 5 ms | Bottle misaligned under nozzle | GPIO interrupt → `SCHED_FIFO` 80 state machine tick |
| Flow meter pulse ISR response | < 1 ms | Pulse lost → volume miscounted | `SCHED_FIFO` 90 ISR thread (highest priority) |
| Valve close at target volume | < 2 ms | Overfill by ~16 ml per ms of delay | ISR directly writes GPIO via `close()` |
| LCD / MQTT update | < 500 ms | No user-visible impact | Normal-priority `MonitorThread` (non-RT) |
| State machine loop period | 20 ms | Delayed response to sensor events | `SCHED_FIFO`, `clock_nanosleep` periodic wake |

**Why `SCHED_FIFO` priority 80?** This places the control loop above standard Linux processes (priority 0–20) while reserving priority 99 for kernel interrupt threads and priority 90 for the pulse ISR, ensuring the flow meter ISR always pre-empts the state machine rather than the reverse.

**Settle wait implementation (non-blocking):** The 200 ms post-fill settle delay is implemented as a **non-blocking timed state** — the state machine records the `FILL_COMPLETE` timestamp using `clock_gettime(CLOCK_MONOTONIC)` and transitions to `BELT_RUNNING` only when the elapsed time exceeds 200 ms on a subsequent 20 ms tick. No `sleep()` or blocking wait is used anywhere in the real-time thread.

---

## 6. Hardware Components & Cost

| Component | Specification | Purpose | Est. Cost |
|---|---|---|---|
| Raspberry Pi 5 | 2GB RAM, ARM Cortex-A76 | Main real-time controller | $35–45 |
| DC Geared Motor | 12V, 60–100 RPM | Drive conveyor belt | $5–8 |
| L298N Motor Driver | 2A, 12V H-bridge | Belt motor PWM + direction | $2–3 |
| 12V Solenoid Valve | Normally closed, food-grade | Water flow ON/OFF | $5–8 |
| Relay Module | 1-channel, 5V coil, 10A NO | Switch 12V solenoid valve | $2–3 |
| YF-S201 Flow Meter | Hall-effect, 1–30 L/min | Measure fill volume in ml | $3–5 |
| IR Obstacle Sensor | FC-51, adjustable range | Detect bottle under nozzle | $1–2 |
| 16×2 LCD (I2C) | HD44780 + PCF8574 @0x27 | State and fill volume display | $4–6 |
| Conveyor Frame | Small belt + 2 rollers | Move bottles under nozzle | $10–20 |
| 12V 2A PSU | Regulated DC | Motor + valve + system power | $8–12 |
| Green/Blue/Red LEDs | 5mm standard + 470Ω resistors | Status indicators | $1–2 |
| Active Buzzer | 5V 85dB + 2N2222 transistor | Fill complete audio feedback | $1–2 |
| 1N4007 Diodes ×2 | 1A rectifier | Flyback on motor + solenoid | $1 |
| Water Tubing | Food-grade silicone 8mm ID | Tank → valve → flow meter → nozzle | $2–3 |
| Misc (resistors, wire, breadboard) | 470Ω, 1kΩ, jumper wires | Wiring and assembly | $3–5 |
| **Total Estimated** | | | **$78–117** |

---

## 7. Project Methodology — 4-Week Plan

### Week 1 — Foundation

| Category | Tasks |
|---|---|
| **Hardware** | Wire L298N + DC motor. Build or mount conveyor frame. Test belt running at correct slow speed. Wire IR sensor and verify detection range with potentiometer adjustment. |
| **Software** | Write conveyor motor driver (start/stop/speed). Write IR sensor GPIO interrupt handler. Implement basic IDLE → BELT_RUNNING → BOTTLE_DETECTED states. Verify ISR fires on bottle placement. |
| **Milestone** | Belt running. IR sensor detecting bottles reliably. State machine transitioning correctly between first three states. |

### Week 2 — Filling System

| Category | Tasks |
|---|---|
| **Hardware** | Wire solenoid valve + relay. Wire YF-S201 flow meter in water line between tank and nozzle. Test water flow end-to-end with bucket. Calibrate `ML_PER_PULSE` with measured volumes. |
| **Software** | Write flow meter pulse counting ISR. Implement FILLING state with valve open and pulse counting. Implement FILL_COMPLETE state with valve close. Calibrate `ML_PER_PULSE` constant. |
| **Milestone** | Complete fill cycle working: bottle detected → valve opens → pulses counted → valve closes at target. Fill accuracy ±10ml initially. |

### Week 3 — Full Integration

| Category | Tasks |
|---|---|
| **Hardware** | Wire LCD + LEDs + buzzer. Mount nozzle over belt at correct height. Run full automatic cycle with real bottles. Adjust IR sensor position and belt speed for reliable detection. |
| **Software** | Wire all outputs (LCD, LEDs, buzzer). Implement monitor thread for LCD + MQTT. Add CSV data logger. Fine-tune `ML_PER_PULSE` calibration. Add fault detection (IR timeout, flow timeout). |
| **Milestone** | Full automatic cycle running continuously. LCD showing state and fill volume. MQTT dashboard live. CSV logging every fill. Fill accuracy ±5ml. |

### Week 4 — Validation & Report

| Category | Tasks |
|---|---|
| **Hardware** | Run 20-bottle accuracy test. Measure each fill volume on kitchen scale. Test fault detection by blocking belt or sensor. Demo for supervisor. |
| **Software** | Final calibration from 20-bottle test data. Generate report graphs (fill accuracy histogram, fill time chart). Code cleanup and comments. Final report writing. |
| **Milestone** | Fill accuracy ±3ml over 20 bottles. All states tested. Fault detection working. Report complete with graphs. |

---

## 8. Revision Control, Team Structure & Testing

### 8.1 Git Workflow

| Practice | Detail |
|---|---|
| **Branching** | `main` (stable releases only), `develop` (integration), feature branches per subsystem (e.g., `feature/flow-meter-isr`, `feature/state-machine`) |
| **Commits** | Atomic, descriptive — one logical change per commit |
| **Releases** | GitHub Releases tagged at end of each weekly milestone (v0.1 → v1.0) |
| **Issue Tracker** | GitHub Issues for all bugs and feature tasks; linked to commits via `Closes #N` |
| **Code Review** | All PRs require at least one peer review before merge to `develop` |

### 8.2 Division of Labour

| Member | Primary Responsibility |
|---|---|
| Member 1 | Hardware assembly — conveyor frame, wiring, motor driver |
| Member 2 | Real-time software — state machine, ISR handlers, SCHED_FIFO threading |
| Member 3 | Sensor integration — flow meter calibration, IR sensor tuning |
| Member 4 | Monitoring & data — LCD driver, MQTT dashboard, CSV logging |
| Member 5 | Testing, documentation & promotion — unit tests, GitHub Pages, social media |

### 8.3 Unit Testing Plan

All core classes are tested against the `IHardwareDevice` mock interface without requiring physical hardware:

| Test | What It Verifies |
|---|---|
| `FlowMeterTest` | `getVolumeML()` returns correct ml for N simulated pulses |
| `StateMachineTest` | Correct state transitions for all valid and invalid input sequences |
| `ValveCloseTest` | Valve closes within one tick of target volume being reached |
| `SettleTimerTest` | Belt does not restart before 200 ms elapsed; does restart after |
| `IRTimeoutTest` | Fault state triggered if no bottle detected within timeout window |

Testing framework: **Google Test (gtest)** — runs on host machine via CI (GitHub Actions) without Pi hardware.

---

## 9. Promotion & Documentation Strategy

| Channel | Plan |
|---|---|
| **GitHub Pages** | Project landing page with architecture overview, wiring diagrams, build instructions, and demo video embed |
| **Hackaday** | Article submission targeting the embedded systems / automation community |
| **Instagram / TikTok** | Short-form video of the machine filling bottles automatically — target maker/engineering audience |
| **YouTube** | Full demo + build walkthrough video (< 5 min) |
| **License** | MIT License — permissive open-source, maximises reproducibility and reach |
| **Documentation** | Full `README.md` covering: prerequisites, wiring diagram, build steps, calibration procedure, and how to run |

---

## 10. Conclusion

The DC Conveyor Water Filling Machine is modelled directly on real industrial bottling automation — immediately understandable to any audience, straightforward to build within four weeks, and rich in real-time embedded systems content.

- The **flow meter ISR** demonstrates interrupt-driven measurement
- The **20ms `SCHED_FIFO` control loop** with hard valve-close deadline demonstrates real-time scheduling
- The **multi-threaded architecture** with atomic shared variables demonstrates thread-safe embedded C++ design

---

*DC Conveyor Water Filling Machine — Raspberry Pi 5 + C++*
