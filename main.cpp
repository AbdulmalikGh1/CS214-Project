#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// =============================
// TASK STRUCTURE
// =============================

struct Task {
    int id;
    string title;
    string description;
    int priority;
};

// =============================
// MAIN DATA STRUCTURES
// =============================

// 1) Array for storing all tasks
const int MAX_TASKS = 100;
Task tasks[MAX_TASKS];
int taskCount = 0;

// 2) Manual Stack for deleted tasks
Task deletedTasks[MAX_TASKS];
int top = -1;

// 3) Manual Hash Table for ID -> index
int idIndexMap[MAX_TASKS];

// =============================
// FUNCTION DECLARATIONS
// =============================

void initializeHashTable();
void addTask();
void editTask();
void deleteTask();
void searchTask();
void displayTasks();
void printTasksToFile();
void loadTasksFromFile();
void displayMenu();

// =============================
// MAIN FUNCTION
// =============================

int main() {
    initializeHashTable();
    loadTasksFromFile();

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                editTask();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                searchTask();
                break;
            case 5:
                displayTasks();
                break;
            case 6:
                printTasksToFile();
                break;
            case 7: {
                ofstream saveFile("tasks.txt");
                if (saveFile) {
                    saveFile << taskCount << endl;
                    for (int i = 0; i < taskCount; i++) {
                        saveFile << tasks[i].id << endl;
                        saveFile << tasks[i].title << endl;
                        saveFile << tasks[i].description << endl;
                        saveFile << tasks[i].priority << endl;
                    }
                    saveFile.close();
                }
                cout << "Exiting program..." << endl;
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}

// =============================
// HASH TABLE
// =============================

void initializeHashTable() {
    for (int i = 0; i < MAX_TASKS; i++) {
        idIndexMap[i] = -1;
    }
}

// =============================
// CORE FUNCTIONS
// =============================

void addTask() {
    if (taskCount >= MAX_TASKS) {
        cout << "Task list is full." << endl;
        return;
    }

    Task newTask;

    cout << "Enter task ID: ";
    cin >> newTask.id;

    if (newTask.id < 0 || newTask.id >= MAX_TASKS) {
        cout << "ID must be between 0 and " << MAX_TASKS - 1 << endl;
        return;
    }

    if (idIndexMap[newTask.id] != -1) {
        cout << "Task ID already exists." << endl;
        return;
    }

    cin.ignore();

    cout << "Enter task title: ";
    getline(cin, newTask.title);

    cout << "Enter task description: ";
    getline(cin, newTask.description);

    cout << "Enter task priority (1=High, 2=Medium, 3=Low): ";
    cin >> newTask.priority;

    tasks[taskCount] = newTask;
    idIndexMap[newTask.id] = taskCount;
    taskCount++;

    cout << "Task added successfully." << endl;
}

void editTask() {
    int id;
    cout << "Enter task ID to edit: ";
    cin >> id;

    if (id < 0 || id >= MAX_TASKS || idIndexMap[id] == -1) {
        cout << "Task not found." << endl;
        return;
    }

    int index = idIndexMap[id];

    cin.ignore();

    cout << "Enter new title: ";
    getline(cin, tasks[index].title);

    cout << "Enter new description: ";
    getline(cin, tasks[index].description);

    cout << "Enter new priority (1=High, 2=Medium, 3=Low): ";
    cin >> tasks[index].priority;

    cout << "Task updated successfully." << endl;
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;

    if (id < 0 || id >= MAX_TASKS || idIndexMap[id] == -1) {
        cout << "Task not found." << endl;
        return;
    }

    int index = idIndexMap[id];

    if (top < MAX_TASKS - 1) {
        top++;
        deletedTasks[top] = tasks[index];
    }

    for (int i = index; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;

    initializeHashTable();
    for (int i = 0; i < taskCount; i++) {
        idIndexMap[tasks[i].id] = i;
    }

    cout << "Task deleted successfully." << endl;
}

void searchTask() {
    int id;
    cout << "Enter task ID to search: ";
    cin >> id;

    if (id < 0 || id >= MAX_TASKS || idIndexMap[id] == -1) {
        cout << "Task not found." << endl;
        return;
    }

    int index = idIndexMap[id];

    cout << "\nTask found:" << endl;
    cout << "ID: " << tasks[index].id << endl;
    cout << "Title: " << tasks[index].title << endl;
    cout << "Description: " << tasks[index].description << endl;
    cout << "Priority: " << tasks[index].priority << endl;
}

void displayTasks() {
    if (taskCount == 0) {
        cout << "No tasks available." << endl;
        return;
    }

    cout << "\nAll Tasks:" << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < taskCount; i++) {
        cout << "ID: " << tasks[i].id << endl;
        cout << "Title: " << tasks[i].title << endl;
        cout << "Description: " << tasks[i].description << endl;
        cout << "Priority: " << tasks[i].priority << endl;
        cout << "-----------------------------" << endl;
    }
}

void printTasksToFile() {
    ofstream outFile("output.txt");

    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    outFile << "All Tasks" << endl;
    outFile << "-----------------------------" << endl;

    for (int i = 0; i < taskCount; i++) {
        outFile << "ID: " << tasks[i].id << endl;
        outFile << "Title: " << tasks[i].title << endl;
        outFile << "Description: " << tasks[i].description << endl;
        outFile << "Priority: " << tasks[i].priority << endl;
        outFile << "-----------------------------" << endl;
    }

    outFile.close();
    cout << "Tasks printed to output.txt successfully." << endl;
}

void loadTasksFromFile() {
    ifstream inFile("tasks.txt");

    if (!inFile) {
        return;
    }

    inFile >> taskCount;
    inFile.ignore();

    for (int i = 0; i < taskCount; i++) {
        inFile >> tasks[i].id;
        inFile.ignore();
        getline(inFile, tasks[i].title);
        getline(inFile, tasks[i].description);
        inFile >> tasks[i].priority;
        inFile.ignore();
    }

    inFile.close();

    initializeHashTable();
    for (int i = 0; i < taskCount; i++) {
        idIndexMap[tasks[i].id] = i;
    }
}

void displayMenu() {
    cout << "\n===== Task Management System =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Edit Task" << endl;
    cout << "3. Delete Task" << endl;
    cout << "4. Search Task" << endl;
    cout << "5. Display All Tasks" << endl;
    cout << "6. Print Tasks to File" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}