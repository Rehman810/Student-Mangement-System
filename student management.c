#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Constants
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Structure definition
struct Student {
  int rollNumber;
  char name[MAX_NAME_LENGTH];
};

// Function prototypes
void addStudent(struct Student students[], int *numStudents);
void displayStudents(const struct Student students[], int numStudents);
void searchStudent(const struct Student students[], int numStudents,int rollNumber);
void updateStudent(struct Student students[], int numStudents, int rollNumber);
void deleteStudent(struct Student students[], int *numStudents, int rollNumber);

// File I/O functions
void saveDataToFile(const struct Student students[], int numStudents, const char *filename);
void loadDataFromFile(struct Student students[], int *numStudents, const char *filename);

int main() {
  struct Student students[MAX_STUDENTS];
  int numStudents = 0;
  char filename[] = "student_data.txt";

  // Load existing data from file, if any
  loadDataFromFile(students, &numStudents, filename);

  int choice;
  do {
    // Display menu
    printf("\n\033[1m===== Student Record Management System =====\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student Information\n");
    printf("5. Delete Student\n");
    printf("6. Save Data to File\n");
    printf("0. Exit\033[0m\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addStudent(students, &numStudents);
      break;
    case 2:
      displayStudents(students, numStudents);
      break;
    case 3: {
      int rollNumber;
      printf("Enter the Roll Number of the Student to search: ");
      scanf("%d", &rollNumber);
      searchStudent(students, numStudents, rollNumber);
      break;
    }
    case 4: {
      int rollNumber;
      printf("Enter the Roll Number of the Student to update: ");
      scanf("%d", &rollNumber);
      updateStudent(students, numStudents, rollNumber);
      break;
    }
    case 5: {
      int rollNumber;
      printf("Enter the Roll Number of the Student to delete: ");
      scanf("%d", &rollNumber);
      deleteStudent(students, &numStudents, rollNumber);
      break;
    }
    case 6:
      saveDataToFile(students, numStudents, filename);
      break;
    case 0:
      printf("Exiting program. Goodbye!\n");
      break;
    default:
      printf("Invalid choice. Please enter a valid option.\n");
    }
  } while (choice != 0);

  return 0;
}

// Function to add a new student
void addStudent(struct Student students[], int *numStudents) {
  if (*numStudents < MAX_STUDENTS) {
    int newRollNumber;
    int isDuplicate = 0;

    do {
      isDuplicate = 0; 
      printf("Enter Roll Number for the new student: ");
      scanf("%d", &newRollNumber);

      // Check for identical roll numbers
      for (int i = 0; i < *numStudents; i++) {
        if (students[i].rollNumber == newRollNumber) {
          printf("Error: Roll Number already exists. Please choose a different Roll Number.\n");
          isDuplicate = 1; 
          break;
        }
      }
    } while (isDuplicate);

    students[*numStudents].rollNumber = newRollNumber;

    printf("Enter name for the new student: ");
    scanf("%s", students[*numStudents].name);

    (*numStudents)++;
    printf("Student added successfully!\n");
  } else {
    printf("Cannot add more students. Maximum limit reached.\n");
  }
}


// Function to display all students
void displayStudents(const struct Student students[], int numStudents) {
  if (numStudents > 0) {
    printf("\n===== List of Students =====\n");
    for (int i = 0; i < numStudents; i++) {
      printf("Roll Number: %d\n", students[i].rollNumber);

      // Display the name in uppercase
      printf("Name: ");
      for (int j = 0; j < strlen(students[i].name); j++) {
        printf("%c", toupper(students[i].name[j]));
      }
      
      printf("\n\n");
    }
  } else {
    printf("No students to display.\n");
  }
}

// Function to search for a student by roll number
void searchStudent(const struct Student students[], int numStudents, int rollNumber) {
  int found = 0;
  for (int i = 0; i < numStudents; i++) {
    if (students[i].rollNumber == rollNumber) {
      found = 1;
      printf("Student found:\n");
      printf("Roll Number: %d\n", students[i].rollNumber);
      printf("Name: %s\n", students[i].name);
      printf("\n\n");
      break;
    }
  }
  if (!found) {
    printf("Student with Roll Number %d is not exist.\n", rollNumber);
  }
}

// Function to update student information
void updateStudent(struct Student students[], int numStudents, int rollNumber) {
  int found = 0;
  for (int i = 0; i < numStudents; i++) {
    if (students[i].rollNumber == rollNumber) {
      found = 1;
      printf("Enter new details for the student:\n");
      printf("Name: ");
      scanf("%s", students[i].name);
      printf("Student information updated successfully!\n");
      break;
    }
  }
  if (!found) {
    printf("Student with Roll Number %d not found. Cannot update.\n", rollNumber);
  }
}

// Function to delete a student
void deleteStudent(struct Student students[], int *numStudents, int rollNumber) {
  int found = 0;
  for (int i = 0; i < *numStudents; i++) {
    if (students[i].rollNumber == rollNumber) {
      found = 1;
      // Move all subsequent elements one position back to delete the student
      for (int j = i; j < *numStudents - 1; j++) {
        students[j] = students[j + 1];
      }
      (*numStudents)--;
      printf("Student with Roll Number %d deleted successfully!\n", rollNumber);
      break;
    }
  }
  if (!found) {
    printf("Student with Roll Number %d not found. Cannot delete.\n", rollNumber);
  }
}

// Function to save data to a file
void saveDataToFile(const struct Student students[], int numStudents, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    for (int i = 0; i < numStudents; i++) {
      fprintf(file, "Roll Number: %d Student Name: %s", students[i].rollNumber, students[i].name);
      fprintf(file, "\n");
    }
    fclose(file);
    printf("Data saved to file successfully!\n");
  } else {
    printf("Error opening file for writing.\n");
  }
}

// Function to load data from a file
void loadDataFromFile(struct Student students[], int *numStudents, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    while (fscanf(file, "%d %s", &students[*numStudents].rollNumber, students[*numStudents].name) == 2) {
      (*numStudents)++;
      if (*numStudents >= MAX_STUDENTS) {
        break; 
      }
    }
    fclose(file);
    printf("Data loaded from file successfully!\n");
  } else {
    printf("No previous data found.\n");
  }
}
