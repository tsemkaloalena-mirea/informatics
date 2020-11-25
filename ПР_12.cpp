#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

int findPivot(vector <int> arr) {
    // Выбор опорного элемента
    // для этого найдём медиану первого, среднего и последнего элементов
    int size = arr.size();
    int middle = (size - 1) / 2;
    
    if (arr[middle] < arr[0]) {
        swap(arr[0], arr[middle]);
    }
    if (arr[size - 1] < arr[0]) {
        swap(arr[0], arr[size - 1]);
    }
    if (arr[middle] < arr[size - 1]) {
        swap(arr[size - 1], arr[middle]);
    }
    return arr[size - 1];
}

vector <int> quickSort(vector <int> arr) {
    // быстрая рекурсивная сортировка
    // разбиваем массив на 3 массива, содержащие меньшие, большие и равные опорному элементу
    // для массива с меньшими и большими числами вызываем эту же функцию
    int size = arr.size();
    if (size > 1) {
        vector <int> smaller;
        vector <int> bigger;
        vector <int> equivalent;
        int pivot = findPivot(arr);
        for (int i = 0; i < size; i++) {
            if (arr[i] < pivot) {
                smaller.push_back(arr[i]);
            }
            else if (arr[i] > pivot) {
                bigger.push_back(arr[i]);
            }
            else {
                equivalent.push_back(arr[i]);
            }
        }
        vector <int> new_smaller = quickSort(smaller);
        vector <int> new_bigger = quickSort(bigger);
        for (int j = 0; j < size; j++) {
            if (j < smaller.size()) {
                arr[j] = new_smaller[j];
            }
            else if (j < smaller.size() + equivalent.size()) {
                arr[j] = equivalent[j - smaller.size()];
            }
            else {
                arr[j] = new_bigger[j - smaller.size() - equivalent.size()];
            }
        }
        return arr;
    }
    else if (size == 1) {
        return arr;
    }
}


int get_integer_from_16_to_10(string x) {
	string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int x10 = 0, i, ss = 16;
	for (i = x.size() - 1; i >= 0; i--) {
		x10 += symbols.find(x[i]) * pow(ss, x.size() - 1 - i);
	}
	return x10;
}

string get_integer_from_10_to_16(int x) {
    int ss = 16;
	string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	symbols = symbols.substr(0, ss);
	int n = 0, i;
	string x16;
	while (pow(ss, n) <= x) {
		n++;
	}
	int symbol;
	for (i = n - 1; i >= 0; i--) {
		symbol = x / pow(ss, i);
		x16 += symbols[symbol];
		if (x != 0) {
			x -= symbol * pow(ss, i);
		}
	}
	return x16;
}

vector <vector <int>> generateMatrix(int h, int w) {
    cout << "Сгенерированная матрица:" << endl;
    vector <vector <int>> matrix(h, vector <int> (w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            matrix[i][j] = rand() % 256;
            cout << get_integer_from_10_to_16(matrix[i][j]) << " ";
        }
        cout << endl;
    }
    return matrix;
}

bool correctInput(string text) {
    string symbols = "0123456789ABCDEF";
    if (text.size() != 2 or text[0] == *"0") {
        cout << "Число должно быть двузначным" << endl;
        return false;
    }
    for (int i = 0; i < text.size(); i++) {
        if (symbols.find(text[i]) > symbols.size() or symbols.find(text[i]) < 0) {
            cout << "Введенное значение не является числом в шестнадцатиричной системе" << endl;
            return false;
        }
    }
    return true;
}

vector <vector <int>> recordMatrix(int h, int w) {
    cout << "Вводите числа" << endl;
    vector <vector <int>> matrix(h, vector <int>(w));
    string t;
    for (int i = 0; i < h; i++) {
        cout << "Строка " << i + 1 << endl;
        for (int j = 0; j < w; j++) {
            cin >> t;
            while (correctInput(t) != true) {
                cin >> t;
            }
            matrix[i][j] = get_integer_from_16_to_10(t);
        }
    }
    return matrix;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    // спрашиваем у пользователя, каким образом будем заполнять матрицу
    cout << "Вы хотите создать матрицу вручную или сгенерировать случайно?" << endl;
    cout << endl;
    string text1 = "вручную", user_text;
    string text2[2] = { "сгенерировать", "случайно" };
    
    vector <vector <int>> matrix;
    bool ask_way = true;
    while (ask_way) {
        cin >> user_text;
        if (user_text.find(text1) < text1.size()) {
            matrix = recordMatrix(4, 4);
            ask_way = false;
        }
        else {
            for (int i = 0; i < 2; i++) {
                if (user_text.find(text2[i]) < text2[i].size()) {
                    matrix = generateMatrix(4, 4);
                    ask_way = false;
                }
            }
        }
        if (ask_way) {
            cout << "Я Вас не понял, повторите, пожалуйста." << endl;
        }        
    }
    cout << "Отсортированная матрица" << endl;
    for (int i = 0; i < matrix.size(); i++) {
        vector <int> sortedMatrix = quickSort(matrix[i]);
        if (i % 2 == 0) {
            reverse(sortedMatrix.begin(), sortedMatrix.end());
        }
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << get_integer_from_10_to_16(sortedMatrix[j]) << " ";
        }
        cout << endl;
    }

    return 0;
}
