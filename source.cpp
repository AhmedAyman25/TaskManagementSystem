#include <iostream>
#include <string>
#include <fstream> 

using namespace std;


struct Task {
    string name;
    string description;
    string deadline;
    int priority;
    bool isCompleted;
};


void saveTasksToFile(Task* tasks[], int taskCount) {
    ofstream file("tasks.txt", ios::app | ios::out);

    if (!file) {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        file <<"Task Name :"<< tasks[i]->name << endl;
        file <<"Description : "<< tasks[i]->description << endl;
        file <<"Deadline : "<< tasks[i]->deadline << endl;
        file <<"priority : "<< tasks[i]->priority << endl;
        file << "IsCompleted : "<< tasks[i]->isCompleted << endl;
        file << "\t--------------------------" << endl;
    }

    file.close();
}

void loadTasksFromFile(Task* tasks[], int& taskCount, int maxTasks) {
    ifstream file("tasks.txt");

    if (!file) {
        cout << "No previous tasks found. Starting fresh.\n";
        return;
    }

    while (taskCount < maxTasks) {
        Task* task = new Task;
        if (!getline(file, task->name)) break;           
        getline(file, task->description);                
        getline(file, task->deadline);                  
        file >> task->priority;                          
        file >> task->isCompleted;                       
        file.ignore();                                   

        tasks[taskCount] = task;
        taskCount++;
    }

    file.close();
}


void addTask(Task* tasks[], int& taskCount, int maxTasks) {
    if (taskCount >= maxTasks) {
        cout << "Task list is full. Cannot add more tasks.\n";
        return;
    }

    Task* task = new Task; 
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, task->name);
    cout << "Enter task description: ";
    getline(cin, task->description);
    cout << "Enter task deadline: ";
    getline(cin, task->deadline);
    cout << "Enter task priority (1-5): ";
    cin >> task->priority;
    task->isCompleted = false; 

    tasks[taskCount] = task; 
    taskCount++;

    saveTasksToFile(tasks, taskCount); 
}


void displayTasks(Task* tasks[], int taskCount) {
    if (taskCount == 0) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "********** Display Tasks **********\n";
    for (int i = 0; i < taskCount; i++) {
    
        cout << "\tTask " << i + 1 << ": " << tasks[i]->name << endl;
        cout << "\tDescription: " << tasks[i]->description << endl;
        cout << "\tDeadline: " << tasks[i]->deadline << endl;
        cout << "\tPriority: " << tasks[i]->priority << endl;
        cout << "\tStatus: " << (tasks[i]->isCompleted ? "Completed" : "Incomplete") << endl;
        cout << "***********************************\n";
    }
}

void updateTaskStatus(Task* tasks[], int taskCount) {
    string taskName;
    cout << "Enter task name to update status: ";
    cin.ignore();
    getline(cin, taskName);

    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i]->name == taskName) {
            cout << "Is the task completed? (1 for Yes, 0 for No): ";
            cin >> tasks[i]->isCompleted;
            found = true;
            cout << "Task status updated.\n";
            break;
        }
    }

    if (!found) {
        cout << "Task not found.\n";
    }

    saveTasksToFile(tasks, taskCount); 
}


void deleteTask(Task* tasks[], int& taskCount) {
    string taskName;
    cout << "Enter task name to delete: ";
    cin.ignore();
    getline(cin, taskName);

    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i]->name == taskName) {
            delete tasks[i]; 
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1]; 
            }
            taskCount--;
            found = true;
            cout << "Task deleted.\n";
            break;
        }
    }

    if (!found) {
        cout << "Task not found.\n";
    }

    saveTasksToFile(tasks, taskCount); 
}


void freeAllTasks(Task* tasks[], int& taskCount) {
    for (int i = 0; i < taskCount; i++) {
        delete tasks[i]; 
    }
    taskCount = 0;
}

int main() {
    const int MAX_TASKS = 100; 
    Task* tasks[MAX_TASKS];    
    int taskCount = 0;         

    loadTasksFromFile(tasks, taskCount, MAX_TASKS);

    int choice;

    do {
        cout << "\nTask Manager Menu\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Update Task Status\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTask(tasks, taskCount, MAX_TASKS);
            break;
        case 2:
            displayTasks(tasks, taskCount);
            break;
        case 3:
            updateTaskStatus(tasks, taskCount);
            break;
        case 4:
            deleteTask(tasks, taskCount);
            break;
        case 5:
            freeAllTasks(tasks, taskCount); 
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
