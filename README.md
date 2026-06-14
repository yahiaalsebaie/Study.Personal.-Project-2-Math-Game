# Math Game (CLI)

A structured, clean, and optimized Command Line Interface (CLI) Math Quiz game written in C++. The project is built following solid software engineering principles, such as the Single Responsibility Principle (SRP) and memory-efficient parameter passing.

---

## 🚀 Features

* **Dynamic Question Generation:** Supports 3 difficulty levels (Easy, Med, Hard) and a Mix level.
* **Diverse Operations:** Supports Addition, Subtraction, Multiplication, Division, and a Mix operations mode.
* **Memory Efficient:** Uses pass-by-reference (`const &`) to eliminate unnecessary structural copying in memory.
* **Clean Code Architecture:** Completely decouples game logic, UI rendering, and score tracking.
* **Interactive UI:** Dynamic console coloring to give immediate visual feedback (Green for correct, Red with audio alert for incorrect).

---

## 🛠️ Architecture & Code Design

The application transitions from a monolithic structure to a highly modular architecture:

### 1. Data Structures
* `stQuestion`: Encapsulates all data for a single question (operands, operation type, level, correct answer, player answer, and status).
* `stQuiz`: Manages the overall session, including an array of questions, configuration, counters, and final status.

### 2. Core Modules
* **Generation Logic:** `GenerateQuestion()` utilizes a unified switch-case system to handle bounds before evaluating the math expression via `SimpleCalculator()`.
* **Input/Output Separation:** `AskQuestion()` handles user IO exclusively, while `IsRightAnswer()` acts as a pure function to check results without side effects.
* **State Management:** `UpdateScore()` updates session metrics cleanly using concise ternary expressions.

---

## 💻 Game Preview

```text
Question [1/3].
45 * 12 = 540

Right Answer :) 
---------------

Question [2/3].
88 - 19 = 60

Wrong Answer :( 
The Right Answer Is [69].
----------------------------
