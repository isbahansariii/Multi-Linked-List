// List
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct course
{
    int courseNo;
    char courseName[40];
    struct course *next;
    struct std *stdList;
};
struct course *headCourse;

struct std
{
    int stdID;
    char stdName[40];
    struct std *next;
};
struct std *headStd;

void addCourse(int courseNo, char course_name[])
{
    struct course *newnode = (struct course *)malloc(sizeof(struct course));
    struct course *current = headCourse;

    newnode->courseNo = courseNo;
    strcpy(newnode->courseName, course_name);
    newnode->stdList = NULL;
    newnode->next = NULL;

    if (headCourse == NULL)
    {
        headCourse = current = newnode;
        return;
    }

    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newnode;
    current = newnode;
}
void deleteCourse(int course_no)
{
    struct course *current = headCourse;
    struct course *prev = NULL;
    while (current != NULL && current->courseNo != course_no)
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Course not found.");
        return;
    }
    if (prev == NULL)
    {
        headCourse = headCourse->next;
    }
    else
    {
        prev->next = current->next;
    }
    free(current);
}

void addStd(int courseNo, int stdID, char std_name[])
{
    struct course *currentCourse = headCourse;
    while (currentCourse->courseNo != courseNo && currentCourse != NULL)
    {
        currentCourse = currentCourse->next;
    }

    if (currentCourse == NULL)
    {
        // headCourse==NULL or List is ended
        printf("Course not found.");
        return;
    }

    struct std *newStd = (struct std *)malloc(sizeof(struct std));
    struct std *currentStd = headStd;

    newStd->stdID = stdID;
    strcpy(newStd->stdName, std_name);

    if (currentCourse->stdList == NULL)
    {
        currentCourse->stdList = headStd = currentStd = newStd;
        return;
    }
    while (currentStd->next != NULL)
    {
        currentStd = currentStd->next;
    }
    currentStd->next = newStd;
    currentStd = newStd;
}

void deleteStd(int course_no, int std_ID)
{
    struct course *currentCourse = headCourse;
    struct course *prevCourse = NULL;
    while (currentCourse != NULL && currentCourse->courseNo != course_no)
    {
        prevCourse = currentCourse;
        currentCourse = currentCourse->next;
    }
    if (currentCourse == NULL)
    {
        printf("Course not found for deletion.");
        return;
    }
    struct std *currentStd = headStd;
    struct std *prevStd = NULL;
    while (currentStd != NULL && currentStd->stdID != std_ID)
    {
        prevStd = currentStd;
        currentStd = currentStd->next;
    }
    if (currentStd == NULL)
    {
        printf("Student not found for deletion.");
        return;
    }
    if (prevStd == NULL)
    {
        headStd = headStd->next;
        currentCourse->stdList = headStd;
    }
    else
    {
        prevStd->next = currentStd->next;
    }
    free(currentStd);
}

// From all courses
void removeStd(int std_ID)
{
    struct course *currentCourse = headCourse;
    struct course *prevCourse = NULL;

    while (currentCourse != NULL)
    {
        struct std *currentStd = headStd;
        struct std *prevStd = NULL;
        while (currentStd != NULL && currentStd->stdID != std_ID)
        {
            prevStd = currentStd;
            currentStd = currentStd->next;
        }
        if (currentStd == NULL)
        {
            printf("Student not found for deletion.");
            return;
        }
        if (prevStd == NULL)
        {
            headStd = headStd->next;
            currentCourse->stdList = headStd;
        }
        else
        {
            prevStd->next = currentStd->next;
        }
        free(currentStd);
        prevCourse = currentCourse;
        currentCourse = currentCourse->next;
    }
}

void display(void)
{
    struct course *currentCourse = headCourse;
    if (headCourse == NULL)
    {
        printf("\nNo Course is currently present.");
        return;
    }
    while (currentCourse != NULL)
    {
        printf("\nCourse# %d", currentCourse->courseNo);
        printf("\nCourse Name: %s", currentCourse->courseName);
        printf("\nStudents Enroll: ");

        struct std *currentStd = headStd;
        if (currentCourse->stdList == NULL)
        {
            printf("\n\tNo Student is enrolled.");
        }
        else
        {
            while (currentStd != NULL)
            {
                printf("\n\tStudent ID: %d", currentStd->stdID);
                printf("\t\tStudent Name: %s", currentStd->stdName);
                currentStd = currentStd->next;
            }
        }
        printf("\n");
        currentCourse = currentCourse->next;
    }
}

int main()
{
    int choice, courseNo, stdID;
    char courseName[40], stdName[40];

    while (1)
    {
        printf("\n\nMenu:");
        printf("\n=====\n");
        printf("1. Add/Insert a course\n");
        printf("2. Drop/Delete a course\n");
        printf("3. Add a student to a course\n");
        printf("4. Delete a student from a course\n");
        printf("5. Remove a student\n");
        printf("6. Display all courses\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Course Number: ");
            scanf("%d", &courseNo);
            printf("Enter Course Name: ");
            scanf("%s", courseName);
            addCourse(courseNo, courseName);
            break;
        case 2:
            printf("Enter Course number to delete: ");
            scanf("%d", &courseNo);
            deleteCourse(courseNo);
            break;
        case 3:
            printf("Enter Course Number: ");
            scanf("%d", &courseNo);
            printf("Enter Student ID: ");
            scanf("%d", &stdID);
            printf("Enter Student Name: ");
            scanf("%s", stdName);
            addStd(courseNo, stdID, stdName);
            break;
        case 4:
            printf("Enter Course Number: ");
            scanf("%d", &courseNo);
            printf("Enter Student ID to delete: ");
            scanf("%d", &stdID);
            deleteStd(courseNo, stdID);
            break;
        case 5:
            printf("Enter Student ID to remove: ");
            scanf("%d", &stdID);
            removeStd(stdID);
            break;
        case 6:
            display();
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
