#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int ss = 0;
int RK = 0;


/*--------------------------------------------------------------------------------------------*/
void simple_search(int all_text_len, int part_of_the_text_len, char* haystack, char* needle) {
    int n = all_text_len;
    int m = part_of_the_text_len;

    if (m <= 0) return;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && tolower(haystack[i + j]) == tolower(needle[j])) {
            j++;
            ss++;
        }
        ss++;
        if (j == m) {
            cout << (i + 1) << " ";
        }
    }
    cout << "\n";
}

/*--------------------------------------------------------------------------------------------*/
int my_hash(char* S, int start, int len) {
    int h = 0;
    for (int i = 0; i < len; i++) {
        h = (h * 256 + static_cast<int>(tolower(S[start + i]))) % 13;
    }
    return h;
}

/*--------------------------------------------------------------------------------------------*/
void RabinKarp(int all_text_len, int part_of_the_text_len, char* haystack, char* needle) {
    int n = all_text_len;
    int m = part_of_the_text_len;

    if (m <= 0) return;

    int hash_needle = my_hash(needle, 0, m);
    int hash_haystack = my_hash(haystack, 0, m);

    for (int i = 0; i <= n - m; i++) {
        if (hash_haystack == hash_needle) {
            int check = 1;
            for (int j = 0; j < m; j++) {
                RK++;
                if (tolower(haystack[i + j]) != tolower(needle[j])) {
                    check = 0;
                    break;
                }
            }
            if (check == 1) {
                cout << (i + 1) << " ";
            }
        }

        if (i < n - m) {
            hash_haystack = my_hash(haystack, i + 1, m);
        }
    }
    cout << "\n";
}

/*--------------------------------------------------------------------------------------------*/
int main() {
    string text, pattern;

	cout << "Введите весь текст: ";
    getline(cin, text);

	cout << "Введите подстроку текста которую надо найти: ";
    getline(cin, pattern);

    int text_len = static_cast<int>(text.length());
    int pattern_len = static_cast<int>(pattern.length());

    if (pattern_len == 0) {
        cout << "Подстрока пустая!\n";
        return 0;
    }

    if (pattern_len > text_len) {
        cout << "Подстрока длиннее текста!\n";
        return 0;
    }

    char* haystack = new char[text_len + 1];
    char* needle = new char[pattern_len + 1];

    for (int i = 0; i < text_len; i++) {
        haystack[i] = text[i];
    }
    haystack[text_len] = '\0';

    for (int i = 0; i < pattern_len; i++) {
        needle[i] = pattern[i];
    }
    needle[pattern_len] = '\0';

    cout << "Простой поиск: ";
    simple_search(text_len, pattern_len, haystack, needle);

    cout << "Рабин-Карп: ";
    RabinKarp(text_len, pattern_len, haystack, needle);

    delete[] haystack;
    delete[] needle;

    return 0;
}