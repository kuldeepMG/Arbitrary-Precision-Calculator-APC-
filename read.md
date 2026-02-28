
#  Arbitrary Precision Calculator (APC)

An Arbitrary Precision Calculator implemented in C, capable of performing arithmetic on numbers beyond the limits of standard integer data types like int and long long.

---

##  Features

✔ Handles large integers using Doubly Linked Lists  
✔ Supports operations:
- Addition (+)
- Subtraction (-)
- Multiplication (x)
- Division (/)

✔ Digit-wise arithmetic implementation  
✔ Handles carry, borrow, negative numbers, and input validation  
✔ No use of long long or external BigInt libraries  

---

##  Data Structure Used

Numbers are stored as a Doubly Linked List where each node contains one digit.

Example:
12345 → 1 <-> 2 <-> 3 <-> 4 <-> 5

---

##  Project Structure

APC_Project/
│── apc.h
│── apc.c
│── main.c
│── README.md

---

##  Example Usage

Command:
./a.out 12345678901234567890 + 98765432109876543210

Output:
111111111011111111100

---

##  Learning Outcomes

- Big integer implementation
- Linked list based arithmetic
- Dynamic memory management in C
- Modular programming and error handling

