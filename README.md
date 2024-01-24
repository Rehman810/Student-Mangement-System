# Student Record Management System

This is a simple console-based Student Record Management System implemented in C. The system allows users to perform various operations related to student information, such as adding a new student, displaying all students, searching for a student by roll number, updating student information, deleting a student, entering marks, and displaying marks.

## Table of Contents

- [Constants](#constants)
- [Structure Definition](#structure-definition)
- [Function Prototypes](#function-prototypes)
- [File I/O Functions](#file-io-functions)
- [Main Function](#main-function)
- [Add Student](#add-student)
- [Display Students](#display-students)
- [Search Student](#search-student)
- [Enter Marks](#enter-marks)
- [Display Marks](#display-marks)
- [Update Student](#update-student)
- [Delete Student](#delete-student)
- [Save Data to File](#save-data-to-file)
- [Load Data from File](#load-data-from-file)

## Constants

- `MAX_STUDENTS`: Maximum number of students the system can handle.
- `MAX_NAME_LENGTH`: Maximum length of a student's name.
- `MAX_SUBJECTS`: Maximum number of subjects.
- `MAX_MARK`: Maximum marks for a subject.
- `MIN_MARK`: Minimum marks for a subject.
- `DEFAULT_SUBJECTS`: Default subjects for which marks can be entered.

## Structure Definition

- `struct Student`: Represents a student with roll number, name, and marks for each subject.

## Function Prototypes

- `addStudent`: Adds a new student to the system.
- `displayStudents`: Displays information for all students.
- `searchStudent`: Searches for a student by roll number.
- `updateStudent`: Updates information for a specific student.
- `deleteStudent`: Deletes a student from the system.
- `enterMarks`: Allows entering marks for a student.
- `displayMarks`: Displays marks for a specific student.
- `isValidMarks`: Validates if entered marks are within the specified range.

## File I/O Functions

- `saveDataToFile`: Saves student data to a file.
- `loadDataFromFile`: Loads student data from a file.

## Main Function

The `main` function initializes the student array, loads existing data from a file (if any), and presents a menu for users to interact with the system. Users can choose various options, and the system performs corresponding operations accordingly. The program continues to run until the user chooses to exit.

## Add Student

The `addStudent` function allows adding a new student to the system. It prompts the user to enter the name and validates that the name contains only letters. The roll number is automatically assigned based on the total number of students.

## Display Students

The `displayStudents` function displays information for all students in the system. It shows the roll number and the uppercase version of the student's name.

## Search Student

The `searchStudent` function allows searching for a student by roll number. It displays the student's information if found.

## Enter Marks

The `enterMarks` function enables entering marks for a specific student. It validates the entered marks to be within the specified range.

## Display Marks

The `displayMarks` function displays the marks for a specific student after the user enters the student's roll number.

## Update Student

The `updateStudent` function allows updating the information (name) for a specific student by entering the roll number.

## Delete Student

The `deleteStudent` function allows deleting a student from the system by entering the roll number.

## Save Data to File

The `saveDataToFile` function saves student data to a file, including the roll number, name, and marks for each subject.

## Load Data from File

The `loadDataFromFile` function loads existing student data from a file, updating the student array and the total number of students.

**Note:** The system automatically saves and loads data to and from a file named "student_data.txt." Ensure that the program has write permissions for the file location.
