# SwiftEx Courier System 🚚

An intelligent, enterprise-grade **Courier Logistics Management System** built with advanced data structures and algorithms. This system efficiently handles parcel management, intelligent routing, real-time tracking, and comprehensive courier operations.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Technologies & Data Structures](#technologies--data-structures)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Compilation](#compilation)
- [Running the Application](#running-the-application)
- [System Architecture](#system-architecture)
- [Key Modules](#key-modules)
- [Usage Examples](#usage-examples)
- [Data Files](#data-files)
- [Contributing](#contributing)
- [License](#license)

---

## 📌 Overview

**SwiftEx** is a sophisticated courier management system designed as a Final Year Project for Data Structures & Algorithms. It implements an intelligent logistics engine that processes, routes, and tracks parcels across multiple cities with optimal efficiency.

The system is built entirely in **C++** with custom implementations of fundamental data structures, ensuring maximum control and optimization for the specific domain requirements.

---

## ✨ Features

### 1. **Intelligent Parcel Sorting Module**

- Multi-criteria sorting based on:
  - Priority levels (Overnight, TwoDay, Normal)
  - Weight categories (Light, Medium, Heavy)
  - Destination cities
- Real-time insertion and withdrawal of parcels
- Min-Heap implementation for optimal priority queue operations

### 2. **Advanced Parcel Routing Module**

- **Dijkstra's Algorithm** for shortest path calculation
- **K-Shortest Paths** algorithm for multiple alternative routes
- Dynamic handling of:
  - Blocked routes
  - Overloaded paths with capacity tracking
  - Real-time route recalculation
- Efficient graph-based city network representation

### 3. **Comprehensive Parcel Tracking System**

- Complete lifecycle tracking from pickup to delivery
- Timestamped historical logs for every parcel movement
- Delivery attempt tracking with retry mechanisms
- Return to sender functionality
- Missing parcel detection and reporting

### 4. **Robust Courier Operations Engine**

- Separate operational queues:
  - **Pickup Queue**: Parcels awaiting pickup
  - **Warehouse Queue**: Priority-sorted parcels in storage
  - **Transit Queue**: Parcels in active delivery
- Rider management with capacity tracking
- Missing parcel detection and alerts
- Comprehensive operation logging with undo/replay capabilities

### 5. **Authentication & Authorization**

- Secure admin login with password masking
- Role-based access control
- Operation audit trails

### 6. **Enhanced User Interface**

- Colored console output for better readability
- UTF-8 support for international characters
- Interactive menu-driven interface
- Formatted data display and reports

---

## 🛠️ Technologies & Data Structures

### Programming Language

- **C++** (ISO C++11 and above)

### Custom Data Structures Implemented

| Data Structure | Use Case                              | Complexity                  |
| -------------- | ------------------------------------- | --------------------------- |
| **HashTable**  | O(1) parcel lookup by ID              | O(1) avg, O(n) worst        |
| **MinHeap**    | Priority queue for warehouse sorting  | O(log n) insertion/deletion |
| **Queue**      | FIFO for pickup and transit stages    | O(1) enqueue/dequeue        |
| **Graph**      | City network and route representation | O(V + E) traversal          |
| **Stack**      | Undo operation history                | O(1) push/pop               |
| **LinkedList** | Parcel history and audit trails       | O(n) traversal              |
| **Vector**     | Dynamic array for parcel management   | O(1) access, O(n) insertion |

### Algorithms

- **Dijkstra's Algorithm**: Shortest path routing
- **K-Shortest Paths**: Alternative route generation
- **Priority Queue Operations**: O(log n) parcel sorting
- **Graph Traversal**: BFS/DFS for network analysis

### Libraries Used

- `<iostream>` - Input/Output operations
- `<string>` - String handling
- `<fstream>` - File I/O for CSV data
- `<sstream>` - String streams for parsing
- `<windows.h>` - Windows console API for colors and utilities
- `<algorithm>` - Standard algorithms
- `<ctime>` - Timestamp operations

---

## 📁 Project Structure

```
Courier Service - Final_2/
├── README.md                 # Project documentation
├── main.cpp                  # Entry point & main menu system
├── CourierSystem.h           # Core system header (228 lines)
├── CourierSystem.cpp         # Core system implementation
├── Models.h                  # Data models (Parcel, City, Rider, Admin)
├── DataStructures.h          # Custom data structure implementations
├── Utils.h                   # Utility functions & console formatting
│
├── Data Files (CSV)
│   ├── cities.csv            # City network data
│   ├── parcels.csv           # Parcel records
│   ├── riders.csv            # Rider information
│   ├── routes.csv            # Pre-defined routes
│   └── admins.csv            # Admin credentials
│
├── Build & Compilation
│   └── compile.bat           # Windows batch compilation script
│
├── Documentation (SVG Diagrams)
│   ├── System Flow.svg        # Overall system workflow
│   ├── Class Diagram.svg      # OOP structure
│   ├── Data Structures.svg    # Data structure relationships
│   ├── Parcel Lifecycle.svg   # Parcel status transitions
│   ├── Routing.svg            # Route optimization flow
│   ├── Operation Workflow.svg # Operation sequences
│   ├── Authentication.svg     # Login & auth flow
│   └── Statistics.svg         # Analytics & reports
│
└── source files/             # Additional source files and diagrams
```

---

## 🚀 Getting Started

### Prerequisites

- **Operating System**: Windows (uses Windows-specific console APIs)
- **Compiler**: MinGW-w64, MSVC, or any C++11 compatible compiler
- **RAM**: Minimum 256 MB
- **Disk Space**: ~10 MB (including data files)

### System Requirements

- C++ Standard: C++11 or higher
- Windows Console with ANSI color support
- UTF-8 encoding support

---

## 🔨 Compilation

### Method 1: Using Batch Script (Recommended for Windows)

```bash
compile.bat
```

This script automatically compiles all `.cpp` files and generates the executable.

### Method 2: Manual Compilation with MinGW

```bash
g++ -std=c++11 -o CourierSystem main.cpp CourierSystem.cpp Utils.cpp -lws2_32
```

### Method 3: Using MSVC Compiler

```bash
cl /std:c++latest main.cpp CourierSystem.cpp Utils.cpp /link ws2_32.lib
```

### Compilation Flags

- `-std=c++11` - Use C++11 standard (minimum required)
- `-Wall` - Enable all warnings (optional but recommended)
- `-O2` - Enable optimizations (optional)
- `-lws2_32` - Link Windows socket library

---

## ▶️ Running the Application

### Start the Application

```bash
./CourierSystem.exe
```

Or directly execute the compiled binary.

### First Run

1. The system will display the **SwiftEx Courier System** login screen
2. Enter admin credentials (from `admins.csv`)
3. After successful authentication, you'll access the main menu
4. System automatically loads data from CSV files

---

## 🏗️ System Architecture

### Multi-Layer Architecture

```
┌─────────────────────────────────────┐
│      User Interface Layer           │
│    (main.cpp - Menu System)         │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│    Business Logic Layer             │
│   (CourierSystem - Core Engine)     │
├─────────────────────────────────────┤
│ • Parcel Management                 │
│ • Route Optimization                │
│ • Tracking & History                │
│ • Rider Management                  │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│   Data Structure Layer              │
│   (Custom Implementations)          │
├─────────────────────────────────────┤
│ • HashTable     • MinHeap           │
│ • Queue         • Graph             │
│ • Stack         • LinkedList        │
│ • Vector                            │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│     Data Persistence Layer          │
│      (CSV Files & Storage)          │
├─────────────────────────────────────┤
│ • cities.csv    • admins.csv        │
│ • parcels.csv   • riders.csv        │
│ • routes.csv                        │
└─────────────────────────────────────┘
```

---

## 🔧 Key Modules

### 1. **CourierSystem (Core Engine)**

- **File**: [CourierSystem.h](CourierSystem.h), [CourierSystem.cpp](CourierSystem.cpp)
- **Responsibilities**:
  - Manages all parcels, riders, and routes
  - Implements intelligent sorting and routing
  - Maintains parcel lifecycle
  - Handles operation logging and undo/replay

### 2. **Models**

- **File**: [Models.h](Models.h)
- **Classes**:
  - `Parcel` - Individual package data
  - `City` - Network nodes
  - `Rider` - Delivery personnel
  - `Admin` - System administrators
  - `Enums`: Priority, Status, WeightCategory

### 3. **Data Structures**

- **File**: [DataStructures.h](DataStructures.h)
- **Implementations**:
  - Template-based generic classes
  - Optimized for courier domain
  - O(1) to O(log n) operations

### 4. **Utilities**

- **File**: [Utils.h](Utils.h)
- **Features**:
  - Console formatting and colors
  - UTF-8 support
  - CSV file I/O
  - Input validation
  - Password masking

---

## 💡 Usage Examples

### Admin Login

```
Enter Username: admin_user
Enter Password: ****
Authentication successful!
```

### Main Menu Operations

1. **Add Parcel** - Register new parcel for delivery
2. **Track Parcel** - View parcel status and history
3. **Assign Route** - Calculate optimal delivery route
4. **Manage Riders** - Add/update delivery personnel
5. **View Statistics** - Analytics and reports
6. **Block/Unblock Routes** - Manage network disruptions
7. **Undo/Replay Operations** - Revert or replay actions

### Parcel Status Flow

```
Pending → PickedUp → InWarehouse → InTransit → Delivered
                                          ↓
                                     (Failed Delivery)
                                          ↓
                                    Returned/Missing
```

---

## 📊 Data Files

### CSV Format Specifications

#### cities.csv

```
CityID,CityName
1,New York
2,Los Angeles
3,Chicago
```

#### parcels.csv

```
TrackingID,SenderName,ReceiverName,Priority,Weight,SourceCity,DestinationCity,Status
1001,John Doe,Jane Smith,2,5.5,1,3,Pending
```

#### riders.csv

```
RiderID,RiderName,AssignedCity,VehicleCapacity,CurrentLoad
1,Ahmed Khan,1,50,25
```

#### admins.csv

```
AdminID,Username,Password,Email
1,admin_user,password123,admin@swiftex.com
```

#### routes.csv

```
RouteID,SourceCity,DestinationCity,Distance,EstimatedTime
1,1,2,100,240
```

---

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/YourFeature`)
3. **Commit** your changes (`git commit -m 'Add YourFeature'`)
4. **Push** to the branch (`git push origin feature/YourFeature`)
5. **Open** a Pull Request

### Areas for Contribution

- Database integration (instead of CSV)
- REST API wrapper
- Mobile application client
- Additional routing algorithms
- Performance optimizations
- Unit test suite

---

## 📝 License

This project is created as a **Final Year Project (FYP)** for Data Structures & Algorithms course.

**Usage**: For educational and academic purposes only.

---

## 👨‍💻 Technical Highlights

### Performance Optimizations

- **O(1) Parcel Lookup**: HashTable for instant parcel retrieval
- **O(log n) Sorting**: MinHeap for efficient warehouse management
- **O(V + E) Routing**: Graph-based path finding
- **Efficient Memory Usage**: Custom data structures with minimal overhead

### Code Quality

- Modular architecture with clear separation of concerns
- Comprehensive documentation and comments
- Custom data structure implementations for learning purposes
- Efficient algorithms with proper complexity analysis

### Robustness

- Input validation and error handling
- Audit trails for all operations
- Undo/Replay functionality for reversible operations
- Missing parcel detection

---

## 📞 Support & Documentation

For detailed information:

- View the **SVG diagrams** in the `source files/` directory
- Read inline documentation in header files
- Check the operation logs for system behavior
- Review the parcel lifecycle documentation

---

## 🎓 Project Metadata

- **Type**: Final Year Project (FYP)
- **Course**: Data Structures & Algorithms
- **Semester**: 3rd
- **Language**: C++
- **Platform**: Windows
- **Status**: Complete and Functional

---

**Last Updated**: January 2026

**This Project is for educational and informational purpose you can simply check the source code understand the logic, polish it and add value to it.Moreover,You can also give credits if you want 🚀**

**Developed & Created By Afaaq Anwar**
