// HW1-2: trying to find illogical parentheses counts
// environment: Clion 2021.3.2
// C++ type: C++ 11
// gcc type: gcc version 8.1.0
#include <iostream>
#include <string>

using namespace std;

// get parentheses user input and new an identical size array
string get_parentheses_str(const string& info, char*& arr) {
    cout << info;
    string input;
    getline(cin, input);
    arr = new char[input.size(), '0'];
    return input;
}

// push function
void push(char push_item, char*& arr, int& top_index) {
    top_index++;
    arr[top_index] = push_item;
}

// pop stack top item and return it
char pop(char*& arr, int& top_index) {
    // empty array(use '!' as representation)
    if (top_index == -1)return '!';
    else {
        char pop_item = arr[top_index];
        top_index--;
        return pop_item;
    }
}

// analyze
int analyze(const string& user_input, char*& arr, int& top_index) {
    int arr_size = int(user_input.size());
    int final_result = 0;
    for (int i = 0; i < arr_size; i++) {
        if (user_input[i] == '(')push(user_input[i], arr, top_index);
        else if (user_input[i] == ')') {
            // call pop
            // when pop_result=='!', it means a ')' impossible to get paired
            char pop_result = pop(arr, top_index);
            if (pop_result == '!')final_result++;
        }
    }
    // top_index means how many '(' still not paired with ')', but since index start with 0, so total counts need +1
    final_result = final_result + top_index + 1;
    return final_result;
}

// show result
void show_result(const int result) {
    cout << "=====Analyze Result=====\n";
    cout << "Illogical count: " << result << endl;
    cout << "========================\n";
}

int main() {

    // create array to simulate stack
    char* arr;
    int top_index = -1;
    string user_input = get_parentheses_str("Enter parentheses: ", arr);

    //analyze
    int result = analyze(user_input, arr, top_index);
    show_result(result);

    // deallocate memory space
    arr = nullptr;
    delete arr;

    system("pause");
    return 0;
}
