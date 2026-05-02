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
// TASK MANAGER
// =============================

class TaskManager {
private:
    static const int MAX_TASKS = 100;

    // 1) Array for storing all tasks
    Task tasks[MAX_TASKS];
    int taskCount;

    // 2) Manual Stack for deleted tasks
    Task deletedTasks[MAX_TASKS];
    int top;

    // 3) Manual Hash Table / direct ID-to-index map
    int idIndexMap[MAX_TASKS];

    void initializeHashTable();
    void rebuildIdIndexMap();

public:
    TaskManager();
    void addTask();
    void editTask();
    void deleteTask();
    void searchTask();
    void displayTasks();
    void printTasksToFile();
    void loadTasksFromFile();
    void saveTasksToFile();
};

void displayMenu();

// =============================
// MAIN FUNCTION
// =============================

int main() {
    TaskManager taskManager;
    taskManager.loadTasksFromFile();

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                taskManager.addTask();
                break;
            case 2:
                taskManager.editTask();
                break;
            case 3:
                taskManager.deleteTask();
                break;
            case 4:
                taskManager.searchTask();
                break;
            case 5:
                taskManager.displayTasks();
                break;
            case 6:
                taskManager.printTasksToFile();
                break;
            case 7:
                taskManager.saveTasksToFile();
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}

// =============================
// HASH TABLE
// =============================

TaskManager::TaskManager() {
    taskCount = 0;
    top = -1;
    initializeHashTable();
}

void TaskManager::initializeHashTable() {
    for (int i = 0; i < MAX_TASKS; i++) {
        idIndexMap[i] = -1;
    }
}

void TaskManager::rebuildIdIndexMap() {
    initializeHashTable();
    for (int i = 0; i < taskCount; i++) {
        idIndexMap[tasks[i].id] = i;
    }
}

// =============================
// CORE FUNCTIONS
// =============================

// Add a new task with validation and store in array
void TaskManager::addTask() {
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

void TaskManager::editTask() {
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

void TaskManager::deleteTask() {
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

    rebuildIdIndexMap();

    cout << "Task deleted successfully." << endl;
}

void TaskManager::searchTask() {
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

void TaskManager::displayTasks() {
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

void TaskManager::printTasksToFile() {
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

void TaskManager::loadTasksFromFile() {
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

    rebuildIdIndexMap();
}

void TaskManager::saveTasksToFile() {
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
