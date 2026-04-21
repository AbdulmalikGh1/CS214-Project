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
    // your code here
    return 0;
}

// =============================
// HASH TABLE
// =============================

void initializeHashTable() {
    // your code here
}

// =============================
// CORE FUNCTIONS
// =============================

void addTask() {
    // your code here
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