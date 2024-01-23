#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Constants
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_SUBJECTS 5
#define MAX_MARK 100
#define MIN_MARK 0

const char DEFAULT_SUBJECTS[MAX_SUBJECTS][MAX_NAME_LENGTH] = {"Functional English", "IICT", "Programming Fundamentals", "Applied Physics", "Calculus"};

// Structure definition
struct Student
{
  int rollNumber;
  char name[MAX_NAME_LENGTH];
  int marks[MAX_SUBJECTS];
};

// Function prototypes
void addStudent(struct Student students[], int *numStudents);
void displayStudents(const struct Student students[], int numStudents);
void searchStudent(const struct Student students[], int numStudents, int rollNumber);
void updateStudent(struct Student students[], int numStudents, int rollNumber);
void deleteStudent(struct Student students[], int *numStudents, int rollNumber);
void enterMarks(struct Student students[], int numStudents);
void displayMarks(const struct Student students[], int numStudents);
int isValidMarks(int mark);

// File I/O functions
void saveDataToFile(const struct Student students[], int numStudents, const char *filename);
void loadDataFromFile(struct Student students[], int *numStudents, const char *filename);

int main()
{
  struct Student students[MAX_STUDENTS];
  int numStudents = 0;
  char filename[] = "student_data.txt";

  // Load existing data from file, if any
  loadDataFromFile(students, &numStudents, filename);

  int choice;
  do
  {
    // Display menu
    printf("\n\033[1m===== Student Record Management System =====\n");
    printf("1. Add Student\n");
    printf("2. Display Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student Information\n");
    printf("5. Delete Student\n");
    printf("6. Enter Marks\n");
    printf("7. Display Marks\n");
    printf("0. Exit\033[0m\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      addStudent(students, &numStudents);
      saveDataToFile(students, numStudents, filename);
      break;
    case 2:
      displayStudents(students, numStudents);
      break;
    case 3:
    {
      int rollNumber;
      printf("Enter the Roll Number of the Student to search: ");
      scanf("%d", &rollNumber);
      searchStudent(students, numStudents, rollNumber);
      break;
    }
    case 4:
    {
      int rollNumber;
      printf("Enter the Roll Number of the Student to update: ");
      scanf("%d", &rollNumber);
      updateStudent(students, numStudents, rollNumber);
      break;
    }
    case 5:
    {
      int rollNumber;
      printf("Enter the Roll Number of the Student to delete: ");
      scanf("%d", &rollNumber);
      deleteStudent(students, &numStudents, rollNumber);
      break;
    }
    case 6:
      enterMarks(students, numStudents);
      saveDataToFile(students, numStudents, filename);
      break;
    case 7:
      displayMarks(students, numStudents);
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
void addStudent(struct Student students[], int *numStudents)
{
  if (*numStudents < MAX_STUDENTS)
  {
    students[*numStudents].rollNumber = (*numStudents) + 1;

    printf("Enter name for the new student: ");
    scanf("%s", students[*numStudents].name);

    for (int i = 0; i < strlen(students[*numStudents].name); i++)
    {
      students[*numStudents].name[i] = toupper(students[*numStudents].name[i]);
    }

    // Check if the name contains only letters
    int isValidName = 1;
    for (int i = 0; i < strlen(students[*numStudents].name); i++)
    {
      if (!isalpha(students[*numStudents].name[i]))
      {
        isValidName = 0;
        break;
      }
    }

    if (!isValidName)
    {
      printf("Error: Name should contain only letters.\n");
      return;
    }

    (*numStudents)++;
    printf("Student added successfully!\n");
  }
  else
  {
    printf("Cannot add more students. Maximum limit reached.\n");
  }
}

// Function to display all students
void displayStudents(const struct Student students[], int numStudents)
{
  if (numStudents > 0)
  {
    printf("\n===== List of Students =====\n");
    for (int i = 0; i < numStudents; i++)
    {
      printf("Roll Number: %d\n", students[i].rollNumber);

      // Display the name in uppercase
      printf("Name: ");
      for (int j = 0; j < strlen(students[i].name); j++)
      {
        printf("%c", toupper(students[i].name[j]));
      }

      printf("\n\n");
    }
  }
  else
  {
    printf("No students to display.\n");
  }
}

// Function to search for a student by roll number
void searchStudent(const struct Student students[], int numStudents, int rollNumber)
{
  int found = 0;
  for (int i = 0; i < numStudents; i++)
  {
    if (students[i].rollNumber == rollNumber)
    {
      found = 1;
      printf("Student found:\n");
      printf("Roll Number: %d\n", students[i].rollNumber);
      printf("Name: %s\n", students[i].name);
      printf("\n\n");
      break;
    }
  }
  if (!found)
  {
    printf("Student with Roll Number %d is not exist.\n", rollNumber);
  }
}

void enterMarks(struct Student students[], int numStudents)
{
  int rollNumber;
  printf("Enter the Roll Number of the student to enter marks: ");
  scanf("%d", &rollNumber);

  int studentIndex = -1;
  for (int i = 0; i < numStudents; i++)
  {
    if (students[i].rollNumber == rollNumber)
    {
      studentIndex = i;
      break;
    }
  }

  if (studentIndex != -1)
  {
    printf("Enter marks for each subject:\n");

    for (int i = 0; i < MAX_SUBJECTS; i++)
    {
      do
      {
        printf("Enter marks for %s: ", DEFAULT_SUBJECTS[i]);
        scanf("%d", &students[studentIndex].marks[i]);

        // Validate marks
        if (!isValidMarks(students[studentIndex].marks[i]))
        {
          printf("Error: Marks should be in the range of %d to %d.\n", MIN_MARK, MAX_MARK);
        }

      } while (!isValidMarks(students[studentIndex].marks[i]));
    }

    printf("Marks entered successfully!\n");
  }
  else
  {
    printf("Student with Roll Number %d not found.\n", rollNumber);
  }
}

// Function to validate marks
int isValidMarks(int mark)
{
  return (mark >= MIN_MARK && mark <= MAX_MARK);
}

void displayMarks(const struct Student students[], int numStudents)
{
  int rollNumber;
  printf("Enter the Roll Number of the student to display marks: ");
  scanf("%d", &rollNumber);

  int studentIndex = -1;
  for (int i = 0; i < numStudents; i++)
  {
    if (students[i].rollNumber == rollNumber)
    {
      studentIndex = i;
      break;
    }
  }

  if (studentIndex != -1)
  {
    printf("Displaying marks for the student:\n");
    printf("Student Roll Number: %d\n", students[studentIndex].rollNumber);
    printf("Student Name: %s\n", students[studentIndex].name);

    for (int j = 0; j < MAX_SUBJECTS; j++)
    {
      printf("%s: Marks: %d\n", DEFAULT_SUBJECTS[j], students[studentIndex].marks[j]);
    }

    printf("\n");
  }
  else
  {
    printf("Student with Roll Number %d is not exist.\n", rollNumber);
  }
}

// Function to update student information
void updateStudent(struct Student students[], int numStudents, int rollNumber)
{
  int found = 0;
  for (int i = 0; i < numStudents; i++)
  {
    if (students[i].rollNumber == rollNumber)
    {
      found = 1;
      printf("Enter new details for the student:\n");
      printf("Name: ");
      scanf("%s", students[i].name);
      printf("Student information updated successfully!\n");
      break;
    }
  }
  if (!found)
  {
    printf("Student with Roll Number %d not found. Cannot update.\n", rollNumber);
  }
}

// Function to delete a student
void deleteStudent(struct Student students[], int *numStudents, int rollNumber)
{
  int found = 0;
  for (int i = 0; i < *numStudents; i++)
  {
    if (students[i].rollNumber == rollNumber)
    {
      found = 1;
      // Move all subsequent elements one position back to delete the student
      for (int j = i; j < *numStudents - 1; j++)
      {
        students[j] = students[j + 1];
      }
      (*numStudents)--;
      printf("Student with Roll Number %d deleted successfully!\n", rollNumber);
      break;
    }
  }
  if (!found)
  {
    printf("Student with Roll Number %d not found. Cannot delete.\n", rollNumber);
  }
}

// Function to save data to a file
void saveDataToFile(const struct Student students[], int numStudents, const char *filename)
{
  FILE *file = fopen(filename, "w");
  if (file != NULL)
  {
    fprintf(file, "%d\n", numStudents); // Save the number of students

    for (int i = 0; i < numStudents; i++)
    {
      fprintf(file, "%d %s", students[i].rollNumber, students[i].name);

      for (int j = 0; j < MAX_SUBJECTS; j++)
      {
        fprintf(file, " %d", students[i].marks[j]);
      }

      fprintf(file, "\n");
    }

    fclose(file);
    printf("Data saved to file successfully!\n");
  }
  else
  {
    printf("Error opening file for writing.\n");
  }
}

// Function to load data from a file
void loadDataFromFile(struct Student students[], int *numStudents, const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file != NULL)
  {
    int readStudents;
    fscanf(file, "%d", &readStudents); // Read the number of students

    for (int i = 0; i < readStudents; i++)
    {
      fscanf(file, "%d %s", &students[*numStudents].rollNumber, students[*numStudents].name);

      for (int j = 0; j < MAX_SUBJECTS; j++)
      {
        fscanf(file, "%d", &students[*numStudents].marks[j]);
      }

      (*numStudents)++;
    }

    fclose(file);
    printf("Data loaded from file successfully!\n");
  }
  else
  {
    printf("No previous data found.\n");
  }
}
