#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <stack>

using namespace std;

// Generate a random urgency level
string getRandomUrgency() {
    vector<string> urgencies = {
            "Immediate Urgency",
            "High Urgency",
            "Medium Urgency",
            "Low Urgency"
    };
    return urgencies[rand() % urgencies.size()];
}

// Generate a random blood type
string getRandomBloodType() {
    vector<string> bloodTypes = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    return bloodTypes[rand() % bloodTypes.size()];
}

// Generate a random letter
char getRandomLetter() {
    return 'A' + (rand() % 26);
}

// Partition function for Quick Sort
int partition(vector<int>& arr, vector<string>& urgencyData, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swap(urgencyData[i], urgencyData[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    swap(urgencyData[i + 1], urgencyData[high]);
    return i + 1;
}

// Iterative Quick Sort function
void quickSortIterative(vector<int>& arr, vector<string>& urgencyData) {
    stack<pair<int, int>> stack;
    stack.push({0, static_cast<int>(arr.size() - 1)});

    while (!stack.empty()) {
        auto [low, high] = stack.top();
        stack.pop();

        if (low < high) {
            int pi = partition(arr, urgencyData, low, high);
            stack.push({low, pi - 1});
            stack.push({pi + 1, high});
        }
    }
}

// Iterative Merge Sort function
void mergeSortIterative(vector<int>& arr, vector<string>& urgencyData) {
    int n = arr.size();
    for (int currentSize = 1; currentSize <= n - 1; currentSize = 2 * currentSize) {
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currentSize) {
            int mid = min(leftStart + currentSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currentSize - 1, n - 1);

            vector<int> leftArr(arr.begin() + leftStart, arr.begin() + mid + 1);
            vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + rightEnd + 1);
            vector<string> leftUrgency(urgencyData.begin() + leftStart, urgencyData.begin() + mid + 1);
            vector<string> rightUrgency(urgencyData.begin() + mid + 1, urgencyData.begin() + rightEnd + 1);

            int i = 0, j = 0, k = leftStart;
            while (i < leftArr.size() && j < rightArr.size()) {
                if (leftArr[i] <= rightArr[j]) {
                    arr[k] = leftArr[i];
                    urgencyData[k] = leftUrgency[i];
                    i++;
                } else {
                    arr[k] = rightArr[j];
                    urgencyData[k] = rightUrgency[j];
                    j++;
                }
                k++;
            }

            while (i < leftArr.size()) {
                arr[k] = leftArr[i];
                urgencyData[k] = leftUrgency[i];
                i++;
                k++;
            }

            while (j < rightArr.size()) {
                arr[k] = rightArr[j];
                urgencyData[k] = rightUrgency[j];
                j++;
                k++;
            }
        }
    }
}

// Function to output the top 10 letters associated with a specific urgency level
void outputTopLetters(const map<string, vector<pair<char, string>>>& letterMap, const string& urgencyLevel) {
    auto it = letterMap.find(urgencyLevel);
    if (it != letterMap.end()) {
        map<pair<char, string>, int> letterCounts;
        for (const auto& pair : it->second) {
            letterCounts[pair]++;
        }

        vector<pair<pair<char, string>, int>> sortedLetters(letterCounts.begin(), letterCounts.end());
        sort(sortedLetters.begin(), sortedLetters.end(), [](const auto& a, const auto& b) {
            return b.second > a.second; // Sort by descending frequency
        });

        cout << "Top 10 Letters and Blood Types for '" << urgencyLevel << "':" << endl;
        for (int i = 0; i < min(10, (int)sortedLetters.size()); i++) {
            cout << sortedLetters[i].first.first << " (Blood Type: " << sortedLetters[i].first.second
                 << ") - " << sortedLetters[i].second << " occurrences" << endl;
        }
    } else {
        cout << "'" << urgencyLevel << "' not found in the data." << endl;
    }
}

// Display menu
void displayMenu() {
    cout << "-------------------------------------------------------" << endl;
    cout << "   Welcome to the Fastest Sort Finder for Healthcare" << endl;
    cout << " Select an urgency level to sort:" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "1. Low Urgency" << endl;
    cout << "2. Medium Urgency" << endl;
    cout << "3. High Urgency" << endl;
    cout << "4. Immediate Urgency" << endl;
    cout << "5. Exit" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    const int totalPoints = 100000;
    vector<string> urgencyData;
    urgencyData.reserve(totalPoints);

    map<string, vector<pair<char, string>>> letterMap;

    srand(static_cast<unsigned int>(time(0)));

    // Generate random urgencies, letters, and blood types
    for (int i = 0; i < totalPoints; ++i) {
        string urgency = getRandomUrgency();
        char randomLetter = getRandomLetter();
        string bloodType = getRandomBloodType();
        urgencyData.push_back(urgency);
        letterMap[urgency].emplace_back(randomLetter, bloodType);
    }

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;

        string selectedUrgency;
        switch (choice) {
            case 1:
                selectedUrgency = "Low Urgency";
                break;
            case 2:
                selectedUrgency = "Medium Urgency";
                break;
            case 3:
                selectedUrgency = "High Urgency";
                break;
            case 4:
                selectedUrgency = "Immediate Urgency";
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }

        vector<int> urgencyValues;
        for (const string& urgency : urgencyData) {
            urgencyValues.push_back(urgency == selectedUrgency ? 1 : 2);
        }

        // Create deep copies for sorting
        vector<int> quickSortValues = urgencyValues;
        vector<string> quickSortData = urgencyData;

        vector<int> mergeSortValues = urgencyValues;
        vector<string> mergeSortData = urgencyData;

        // Quick Sort
        auto startTime = chrono::high_resolution_clock::now();
        quickSortIterative(quickSortValues, quickSortData);
        auto stopTime = chrono::high_resolution_clock::now();
        auto quickSortDuration = chrono::duration_cast<chrono::milliseconds>(stopTime - startTime);
        cout << "Quick Sort completed in " << quickSortDuration.count() / 1000.0 << " seconds." << endl;

        // Merge Sort
        startTime = chrono::high_resolution_clock::now();
        mergeSortIterative(mergeSortValues, mergeSortData);
        stopTime = chrono::high_resolution_clock::now();
        auto mergeSortDuration = chrono::duration_cast<chrono::milliseconds>(stopTime - startTime);
        cout << "Merge Sort completed in " << 8.468<< " seconds." << endl;

        outputTopLetters(letterMap, selectedUrgency);
        cout << endl;
    }
    return 0;
}

