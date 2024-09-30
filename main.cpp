#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Task{
    public:
        string description;
        bool completed;

    Task(string description, bool completed = false){
        this->description = description;
        this->completed = completed;
    }

    void displayTask(int index) const {
        cout << index + 1 << ". [" << (completed ? "X]" : " ]") << description << endl;
    }
};

void loadTasks(vector<Task>& tasks){
    ifstream file("TODO/tasks.txt");
    string line;
    bool completed;
    while (file >> completed && getline(file >> ws, line)) {
        if (!line.empty()) {
            tasks.emplace_back(line, completed);
        }
    }
    file.close();
}

void saveTasks(const vector<Task>& tasks){
    ofstream file("TODO/tasks.txt");
    for (const auto& task : tasks) {
        file << task.completed << " " << task.description << endl;
    }
    file.close();
}

void addTask(vector<Task>& tasks){
    cout << "Enter a new task" << endl;
    string description;
    cin.ignore();
    getline(cin, description);
    tasks.emplace_back(description);
    saveTasks(tasks);
    cout << "Task added!" << endl;
}

void viewTask(const vector<Task>& tasks){
    if (tasks.empty()) {
        cout << "No tasks are available!" << endl;
    } else {
        cout << "Your tasks:" << endl;
        for(size_t i = 0; i < tasks.size(); i++){
            tasks[i].displayTask(i);
        }
    }
}



void markTaskComplete(vector<Task>& tasks) {
    viewTask(tasks);
    if (tasks.empty()) return;

    cout << "Enter task number to mark as complete (0 to cancel): ";
    int taskNum;
    cin >> taskNum;

    if (taskNum == 0) return;

    if (taskNum > 0 && taskNum <= static_cast<int>(tasks.size())) {
        tasks[taskNum - 1].completed = true;
        saveTasks(tasks);
        cout << "Task marked as complete!" << endl;
        system("/home/frynor/workspace/TODOApp/transfer.sh");
    } else {
        cout << "Invalid task number!" << endl;
    }
}


void deleteTask(vector<Task>& tasks){
    viewTask(tasks);
    if (tasks.empty()) return;

    cout << "Enter task number to delete: " << endl;
    int taskNum;
    cin >> taskNum;

    if(taskNum > 0 && taskNum <= tasks.size()){
        tasks.erase(tasks.begin() + (taskNum - 1));
        saveTasks(tasks);
        cout << "Task has been deleted!" << endl;
    } else {
        cout << "Invalid task number!" << endl;
    }
}

int main(){
    vector<Task> tasks;
    loadTasks(tasks);

    while(true){
        cout << "\n--- TODO App ---" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Complete" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch(choice){
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTask(tasks);
                break;
            case 3:
                markTaskComplete(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    }
}
