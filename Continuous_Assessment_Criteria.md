# Real-time Embedded Programming Assignment

## Course Information

**Course Code:** ENG 5220

**Course Name:** Real Time Embedded Programming

**Type:** Technical Report, Oral Presentation & Public Relations

**Title:** Development, design, construction and promotion of a product requiring realtime operation

**Weight:** 100% of final course mark

**Lecturers:** Bernd Porr & Chongfeng Wei

---

## Marking Breakdown

### 1. Initial Pitch (10%)

Assessment of the initial project pitch (5 minutes, two slides) and initial GitHub pages setup. Evaluates:

* Originality/usefulness of the work
* Solid realtime requirement
* Quality of presentation

### 2. Code Structure (25%)

Assessment of code organization including:

* Division into classes with proper encapsulation
* Safe data structures
* Safe data receiving and releasing
* High reliability and ease of maintenance

### 3. Realtime Coding (30%)

Assessment of realtime software implementation including:

* Event-driven processing through thread waking
* Use of callbacks, timers, signals, threads
* Kernel space interrupt-driven coding
* Preference for non-polling methods

### 4. Revision Control & Project Management (25%)

Assessment based on:

* Use of version control (commits, branching, releases)
* Testing practices
* Project planning
* Clear division of labour
* Documentation
* Issue tracker usage
* Unit testing

### 5. Promotion & Documentation (10%)

Assessment of project presentation including:

* GitHub presentation quality
* Hardware/software documentation for reproducibility
* Social media presence
* Online publication pickup (e.g., Hackaday)
* Project licensing

All items are marked on the 22-point scale according to performance indicators.

---

## Submission & Return

**Submission Method:** Online via Moodle with link to GitHub page containing report, code, hardware details, and social media links.

**Submission Deadline:** 20 April 2026, 9am

**Important Notes:**

* Latest release from team's GitHub repository will be downloaded and marked on the deadline
* Team responsibility to create a release on GitHub by deadline
* Each group member's area of responsibility must be clearly marked
* Late submissions penalized by two secondary bands per working day (e.g., B1 → B3)
* Submissions more than five days late receive an 'H' grade
* Contact instructors immediately if unable to submit on time due to good cause

**Feedback:**

* Initial pitch feedback available after presentation
* Final work feedback via email, structured according to marking criteria

---

## Marking Criteria Details

### 1. Presentation

| Grade Range     | A1, A2 | A3, A4, A5 | B1, B2, B3 | C1, C2, C3 | D1, D2, D3 | E1, E2, E3 | F, G, H |
| --------------- | ------ | ---------- | ---------- | ---------- | ---------- | ---------- | ------- |
| **Score** | 22, 21 | 20–18     | 17–15     | 14–12     | 11–9      | 8–6       | 5–0    |

**Delivery Criteria:**

* **A1-A2:** Conference-ready presentation
* **A3-A5:** Confident delivery, clear speech, engaging
* **B1-B3:** Good delivery with minor flaws
* **C1-C3:** Significant lapses but satisfactory
* **D1-D3:** Hard to follow in parts
* **E1-E3:** Difficult to understand
* **F-H:** Impossible to learn from

**Slides Criteria:**

* **A1-A2:** Professional conference quality
* **A3-A5:** Excellent, attractive, well-presented
* **B1-B3:** Good with minor flaws
* **C1-C3:** Some illegible text or incomprehensible illustrations
* **D1-D3:** Poor, hard to read
* **E1-E3:** No effort made
* **F-H:** No slides

**Originality Criteria:**

* **A1-A2:** Novel product with clear market appeal
* **A3-A5:** Genuinely novel and impressive
* **B1-B3:** Appropriate to brief
* **C1-C3:** Satisfactory but originality unclear
* **D1-D3:** Idea not clear
* **E1-E3:** Inadequate content
* **F-H:** No worthwhile idea

**Realtime Criteria:**

* **A1-A2:** Professional, quantitative assessment
* **A3-A5:** Clear case for realtime processing
* **B1-B3:** Satisfactory, mostly qualitative
* **C1-C3:** Realtime demands not completely clear
* **D1-D3:** Poor case, lacking aspects
* **E1-E3:** Minimal understanding
* **F-H:** No understanding

**Response to Questions:**

* **A1-A2:** Supervisor learned from responses
* **A3-A5:** Confident, informed responses
* **B1-B3:** Good but occasionally unconvincing
* **C1-C3:** Satisfactory for most questions
* **D1-D3:** Difficulty with most questions
* **E1-E3:** Required prompting
* **F-H:** Unable to answer satisfactorily

### 2. Structure of the Code

| Grade Range     | A1, A2 | A3, A4, A5 | B1, B2, B3 | C1, C2, C3 | D1, D2, D3 | E1, E2, E3 | F, G, H |
| --------------- | ------ | ---------- | ---------- | ---------- | ---------- | ---------- | ------- |
| **Score** | 22, 21 | 20–18     | 17–15     | 14–12     | 11–9      | 8–6       | 5–0    |

**Optimal Choice of Classes (SOLID Principles):**

* **A1-A2:** SOLID clearly guides all class choices, professionally evaluated
* **A3-A5:** SOLID almost always guides choices with minor issues
* **B1-B3:** Mostly SOLID-guided but rationale unclear
* **C1-C3:** SOLID applied but no explicit explanations
* **D1-D3:** Serious implementation flaws, little documentation
* **E1-E3:** Unclear if SOLID applied, no documentation
* **F-H:** No SOLID application

**Encapsulation:**

* **A1-A2:** Clear public interfaces, private data, safe getters/setters/callbacks, efficient structures
* **A3-A5:** Good encapsulation with minor flaws in safety/timing
* **B1-B3:** Generally encapsulated with smaller issues
* **C1-C3:** Significant problems (public variables, no fault checking)
* **D1-D3:** Serious flaws, inappropriate data structures
* **E1-E3:** No encapsulation, unclear public/private usage
* **F-H:** No classes, global variables

**Failsafe Memory Management:**

* **A1-A2:** Completely leak-free
* **A3-A5:** Leak-free but uses new/delete unnecessarily
* **B1-B3:** Excessive new/delete usage
* **C1-C3:** Lack of care in memory cleanup
* **D1-D3:** Serious flaws leading to crashes
* **E1-E3:** Serious flaws causing out-of-memory
* **F-H:** No memory management

### 3. Realtime Coding

| Grade Range     | A1, A2 | A3, A4, A5 | B1, B2, B3 | C1, C2, C3 | D1, D2, D3 | E1, E2, E3 | F, G, H |
| --------------- | ------ | ---------- | ---------- | ---------- | ---------- | ---------- | ------- |
| **Score** | 22, 21 | 20–18     | 17–15     | 14–12     | 11–9      | 8–6       | 5–0    |

**Assessment of Latencies:**

* **A1-A2:** Professional quantitative assessment leading to clear decisions
* **A3-A5:** Good quantitative assessment with small omissions
* **B1-B3:** Correct assessment with smaller shortcomings
* **C1-C3:** Partially wrong or incomplete assessment
* **D1-D3:** Not seriously assessed, no strategy justification
* **E1-E3:** Almost no research effort
* **F-H:** Virtually nothing achieved

**Realtime Coding Implementation:**

* **A1-A2:** Production-level using threads/timers/signals/kernel interrupts
* **A3-A5:** Working prototype with minor shortfalls
* **B1-B3:** Solid with smaller latency issues
* **C1-C3:** Shortcomings in responsiveness/timing
* **D1-D3:** Significant shortcomings, long latencies
* **E1-E3:** Major weaknesses, uses delays/blocking
* **F-H:** Few expected graduate skills shown

**Realtime Event Handling:**

* **A1-A2:** Production-level with defined callbacks and async operations
* **A3-A5:** Working prototype with minor event handling issues
* **B1-B3:** Solid but interface problems hinder reuse
* **C1-C3:** Shortcomings in flexibility/safety, buggy
* **D1-D3:** Significant issues, partial polling usage
* **E1-E3:** Major weaknesses, purely polling-based
* **F-H:** Few expected graduate skills shown

### 4. Revision Control and Project Management

| Grade Range     | A1, A2 | A3, A4, A5 | B1, B2, B3 | C1, C2, C3 | D1, D2, D3 | E1, E2, E3 | F, G, H |
| --------------- | ------ | ---------- | ---------- | ---------- | ---------- | ---------- | ------- |
| **Score** | 22, 21 | 20–18     | 17–15     | 14–12     | 11–9      | 8–6       | 5–0    |

**Revision Control:**

* **A1-A2:** Professional use with regular commits, branching, merging
* **A3-A5:** Good use with detailed commits
* **B1-B3:** Used but shortcomings in commits, development on master
* **C1-C3:** Only master branch, shortcomings in commits
* **D1-D3:** Few commits with generic comments
* **E1-E3:** GitHub used only as upload site
* **F-H:** Virtually nothing achieved

**Project Management:**

* **A1-A2:** Professional management tools, clear division, proven contributions, work throughout duration
* **A3-A5:** Excellent planning, all members contributed, work evenly spread
* **B1-B3:** Good planning with minor deficiencies, small gaps
* **C1-C3:** Satisfactory but better tool usage needed, work towards end
* **D1-D3:** Poor planning, some minimal contribution, work at end
* **E1-E3:** No formal planning, ad-hoc work before deadline
* **F-H:** Very little work, almost all in last week

**Reliability/Testing/Bug Fixing:**

* **A1-A2:** Professional testing with unit tests, issue tracking
* **A3-A5:** Good test scenarios with unit tests
* **B1-B3:** Satisfactory with smaller shortcomings
* **C1-C3:** Testing only in some cases
* **D1-D3:** Poor qualitative testing only
* **E1-E3:** No explicit testing
* **F-H:** Virtually nothing achieved

### 5. Documentation and PR

| Grade Range     | A1, A2 | A3, A4, A5 | B1, B2, B3 | C1, C2, C3 | D1, D2, D3 | E1, E2, E3 | F, G, H |
| --------------- | ------ | ---------- | ---------- | ---------- | ---------- | ---------- | ------- |
| **Score** | 22, 21 | 20–18     | 17–15     | 14–12     | 11–9      | 8–6       | 5–0    |

**Quality of Content:**

* **A1-A2:** Professional documentation, easily reproducible
* **A3-A5:** Comprehensive with minor issues (e.g., missing prerequisite)
* **B1-B3:** Good coverage, requires filling smaller gaps
* **C1-C3:** Significant omissions, reproduction not straightforward
* **D1-D3:** Major omissions, hard to understand/reproduce
* **E1-E3:** Little relevant material, won't compile
* **F-H:** Nothing of substance

**Illustrations and Video Content:**

* **A1-A2:** Publication-worthy, catchy graphics, slick videos
* **A3-A5:** Well-chosen, illuminating illustrations, excellent video
* **B1-B3:** Good illustrations and eye-catching video
* **C1-C3:** Satisfactory but could be better, unclear video message
* **D1-D3:** Poor illustrations, low-quality video
* **E1-E3:** Images only from web or missing, poor/missing video
* **F-H:** No illustrations, no video

**PR/Social Media Strategy:**

* **A1-A2:** Perfect strategy across all channels, right audience
* **A3-A5:** Well-devised covering relevant channels and audience
* **B1-B3:** Good amateur project with shortcomings for professional product
* **C1-C3:** OK for local audience but limited reach
* **D1-D3:** Poor, few last-minute posts
* **E1-E3:** Limited to GitHub only
* **F-H:** No PR

---

## §1 Task Overview

### Aims

Development and promotion of a product requiring realtime operation.

### Objectives

* Propose a product requiring realtime processing that solves a real-world task
* Select hardware connecting to a Raspberry Pi as proof of concept
* Develop realtime software in C++ as main language (web pages in browsers & mobile apps may use scripting)
* Create, maintain, schedule and document project using Git version control, tests, and quality management
* Promote final product via GitHub, social media, and live demos

---

## §2 Task Requirements

### Product Requirements

The task is to present an end-user product requiring realtime processing, built around Linux on a Raspberry Pi. The project must solve a real-world problem (e.g., watering plants while on holiday, sleep-sensing mattress).

**Warning:** Creative shortcuts that remove realtime requirements or make the application trivial will not demonstrate mastery of intended learning outcomes.

### Technical Requirements

The Linux system must:

* Measure physical values
* Plot them on screen
* Allow mouse interaction to change parameters
* Generate meaningful outputs
* Operate in realtime
* Boot up as standalone embedded application performing chosen task

### Hardware

Use data acquisition hardware such as:

* Sound card
* Raspberry Pi sensor boards
* Digital sensors

### Software Requirements

**Language & OS:**

* Main coding language: **C++** (mandatory)
* Operating system: **Linux** (mandatory)
* Object-oriented code with testing framework (unit testing)
* **Exception:** Web clients in browsers and mobile apps may use scripting languages (PHP, JS, Python, Java, Swift, etc.)
* **All code on Raspberry Pi must be C++**

**Code Architecture:**

* Must be event-driven
* Either userspace with callbacks and/or waking up threads
* And/or interrupt-driven in kernel space

### Team Structure

* Form groups of **five members**
* Every person should have a distinct role
* Enter names, matric numbers, and GitHub links on Moodle wiki

---

## Critical Requirements (Zero Marks Risk)

Ignoring these requirements may result in zero marks:

* ❌ Program goes into wait state and becomes unresponsive
* ❌ Using wait statements for timing instead of threads/timers/load balancing
* ❌ Not using callbacks to process events
* ❌ Single-threaded loop with blocking/delaying code
* ❌ Trivial work relying on PR without substance
* ❌ No version control indication or Git "upload" just before deadline
* ❌ Not using C++ as coding language on Raspberry Pi

**Note:** Discuss any original approaches with course coordinator if worried about being off-topic.

---

## §3 Formal Contact Hours and Independent Work

* **Lab hours (supervised):** 33 hours
* **Lectures:** 11 hours
* **Independent work:** 156 hours (lab and study)

This course requires a high degree of independent work. Lab sessions are for advice, guidance, and feedback from academics and teaching assistants.

---

## §4 Hardware Purchases

**Budget:** £75 per team for orders via electronics store and/or technician
