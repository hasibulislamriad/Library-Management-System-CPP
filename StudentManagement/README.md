# Student Management System - C++

A console-based Student Management System built with C++ using Object-Oriented Programming and file handling.

## Features

- Add Student
- Show All Students
- Search Student by ID
- Update Student
- Delete Student
- Automatic Grade Calculation
- Student Statistics
- Persistent data storage using `students.txt`
- Basic input validation

## Student Information

- Student ID
- Name
- Department
- Phone
- Average Marks
- Grade

## Grade Scale

| Marks | Grade |
|---:|:---|
| 80-100 | A+ |
| 70-79 | A |
| 60-69 | A- |
| 50-59 | B |
| 40-49 | C |
| 33-39 | D |
| 0-32 | F |

## How to Run

From the `StudentManagement` directory:

```bash
g++ main.cpp -o student_management
```

Windows:

```bash
student_management.exe
```

Linux/macOS:

```bash
./student_management
```

## Project Structure

```text
StudentManagement/
├── main.cpp
├── README.md
└── students.txt   # created automatically
```

## Concepts Used

- C++ Classes and Objects
- Encapsulation
- Constructors
- STL `vector`
- Functions
- File I/O with `fstream`
- CRUD operations
- Input validation
- Basic statistics

## Author

**Hasibul Islam Riad**
