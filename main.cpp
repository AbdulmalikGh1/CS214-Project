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

// Add a new task with validation and store in array
void addTask() {
    // Check if array is full
    if (taskCount >= MAX_TASKS) {
        cout << "Error: Task list is full (maximum 100 tasks)." << endl;
        return;
    }

    Task newTask;

    // Get user input
    cout << "Enter task ID: ";
    cin >> newTask.id;
    cin.ignore();

    cout << "Enter task title: ";
    getline(cin, newTask.title);

    cout << "Enter task description: ";
    getline(cin, newTask.description);

    cout << "Enter priority (1=Low, 2=Medium, 3=High): ";
    cin >> newTask.priority;

    // Validate duplicate ID
    if (idIndexMap[newTask.id] != -1) {
        cout << "Error: Task ID already exists." << endl;
        return;
    }

    // Validate priority range
    if (newTask.priority < 1 || newTask.priority > 3) {
        cout << "Error: Priority must be 1, 2, or 3." << endl;
        return;
    }

    // Store task and update hash table
    tasks[taskCount] = newTask;
    idIndexMap[newTask.id] = taskCount;
    taskCount++;

    cout << "Task added successfully!" << endl;
}

void editTask() {
    // your code here
}

void deleteTask() {
    // your code here
}

void searchTask() {
    // your code here
}

void displayTasks() {
    // your code here
}

void printTasksToFile() {
    // your code here
}

void loadTasksFromFile() {
    // your code here
}

void displayMenu() {
    // your code here
}