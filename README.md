# 202510600_DSA
CPP WORK FOR VEHICLE REGISTRATION SYSTEM
**Course:** Object-Oriented Programming
---

## Description

A console based Vehicle Registration and Owner Management System built in C++. It allows a transport authority to register vehicles and their owners, store records persistently, search by plate number, and display all entries in a formatted table.

## Features

- Add vehicle and owner records with full input validation
- Display all records in a formatted table
- Search for a vehicle by plate number
- Data stored persistently in `records.txt` (CSV format)

## Class Structure

```
User (base class)
    VehicleOwner (derived class)

Vehicle (associated with VehicleOwner)
```

## How to Compile & Run

```bash
g++ -o vehicle main.cpp
./vehicle
```

## File Format (records.txt)

```
PlateNumber,VehicleType,Year,OwnerName,Email,Phone
RAA123A,Sedan,2020,John Alexis,john@gmail.com,+250796159615
```

## Validation Rules

| Field | Rule |
|-------|------|
| Plate Number | 3 uppercase letters + 3 digits + 1 uppercase letter (e.g. RAA123A) |
| Email | Must contain `@` and `.` |
| Phone | Must start with `+250`, exactly 13 characters |
| Year | Between 1900 and 2025 |
