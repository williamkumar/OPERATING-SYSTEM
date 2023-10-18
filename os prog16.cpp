#include <stdio.h>
#include <stdlib.h>

// Define the structure of an employee record
struct Employee {
    int empID;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *file;
    struct Employee emp;
    int choice, empID, found = 0;

    // Open the file in binary mode for random access
    file = fopen("employee_data.dat", "rb+");

    if (file == NULL) {
        printf("File not found. Creating a new one...\n");
        file = fopen("employee_data.dat", "wb+");
        if (file == NULL) {
            perror("File creation failed");
            exit(1);
        }
    }

    while (1) {
        printf("Random Access Employee Database\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add Employee
                printf("Enter Employee ID: ");
                scanf("%d", &emp.empID);
                printf("Enter Employee Name: ");
                scanf("%s", emp.empName);
                printf("Enter Employee Salary: ");
                scanf("%f", &emp.empSalary);

                fseek(file, (emp.empID - 1) * sizeof(emp), SEEK_SET);
                fwrite(&emp, sizeof(emp), 1, file);
                break;

            case 2:
                // Update Employee
                printf("Enter Employee ID to update: ");
                scanf("%d", &empID);

                while (fread(&emp, sizeof(emp), 1, file)) {
                    if (emp.empID == empID) {
                        printf("Enter new Employee Name: ");
                        scanf("%s", emp.empName);
                        printf("Enter new Employee Salary: ");
                        scanf("%f", &emp.empSalary);
                        fseek(file, -sizeof(emp), SEEK_CUR);
                        fwrite(&emp, sizeof(emp), 1, file);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Employee not found.\n");
                }

                break;

            case 3:
                // Delete Employee
                printf("Enter Employee ID to delete: ");
                scanf("%d", &empID);

                while (fread(&emp, sizeof(emp), 1, file)) {
                    if (emp.empID == empID) {
                        emp.empID = -1;  // Mark record as deleted
                        fseek(file, -sizeof(emp), SEEK_CUR);
                        fwrite(&emp, sizeof(emp), 1, file);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Employee not found.\n");
                }

                break;

            case 4:
                // Display Employee
                rewind(file);

                while (fread(&emp, sizeof(emp), 1, file)) {
                    if (emp.empID != -1) {  // Skip deleted records
                        printf("Employee ID: %d\n", emp.empID);
                        printf("Employee Name: %s\n", emp.empName);
                        printf("Employee Salary: %.2f\n", emp.empSalary);
                        printf("\n");
                    }
                }
                break;

            case 5:
                // Exit
                fclose(file);
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

