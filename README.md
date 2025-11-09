# 🖥️ System Monitor Tool (C++ & ncurses)

A **Linux-based System Monitor Tool** built in **C++** that displays real-time information about running processes, CPU usage, and memory utilization — similar to the `top` command.

---

## 🎯 Project Objective

To create a terminal-based application that:
- Displays live system data (CPU, Memory, Processes)
- Allows sorting by CPU or Memory usage
- Supports killing unwanted processes
- Updates automatically every few seconds

---

## 📅 Day-wise Tasks

| **Day** | **Task** |
|----------|-----------|
| **Day 1** | Design UI layout and gather system data using system calls |
| **Day 2** | Display process list with CPU and memory usage |
| **Day 3** | Implement process sorting by CPU and memory usage |
| **Day 4** | Add functionality to kill processes |
| **Day 5** | Implement real-time auto-refresh every few seconds |

---

## ⚙️ How to Run

### 🧩 Step 1: Install dependencies
```bash
sudo apt update
sudo apt install g++ libncurses5-dev libncursesw5-dev
````

### 📂 Step 2: Clone the repository

```bash
git clone https://github.com/Ayushitiwari01/System-Monitor-Tool.git
cd System-Monitor-Tool
```

### ⚙️ Step 3: Compile the program

```bash
g++ SystemMonitor.cpp -o monitor -lncurses
```

### ▶️ Step 4: Run the tool

```bash
./monitor
```

### 🕹️ Controls

| **Key** | **Action**           |
| ------- | -------------------- |
| **q**   | Quit program         |
| **c**   | Sort by CPU usage    |
| **m**   | Sort by Memory usage |
| **r**   | Refresh display      |

### 📊 Features

* Displays CPU and Memory usage
* Lists all running processes with PID, Memory, and CPU%
* Sort processes dynamically
* Kill processes directly from the interface
* Auto-refresh every few seconds
* Terminal-based UI with borders and colors

### 🧠 Tech Used

* **Language:** C++
* **Libraries:** ncurses
* **OS:** Linux (Ubuntu or WSL)

---

## 🖼️ Sample Output

```
┌──────────────────────────────────────────────────────────────┐
│    System Monitor - Refresh every 2s (Press 'q' to quit)     │
├──────────────────────────────────────────────────────────────┤
│ CPU Usage: 15.7%             Memory: 1024MB / 4096MB (25.0%) │
├──────┬────────┬────────┬────────┬────────────────────────────┤
│ PID  │ CPU%   │ MEM%   │ RSS(MB)│ COMMAND                    │
├──────┼────────┼────────┼────────┼────────────────────────────┤
│ 102  │ 12.3   │  5.1   │  210   │ gnome-terminal-server      │
│ 224  │  3.0   │  1.2   │   88   │ bash                       │
│ 350  │  0.0   │  0.8   │   64   │ systemd                    │
└──────┴────────┴────────┴────────┴────────────────────────────┘
```

---
