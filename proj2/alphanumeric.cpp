#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <pthread.h>
#include <atomic>

using std::cin, std::cout, std::endl, std::string;

string sentence;
std::vector<string> words;
std::atomic<int> current_word(0);

void* alpha(void*) {
    while (current_word < words.size()) {
        if (isalpha(words[current_word][0])) {
            cout << "ALPHABETIC: " << words[current_word] << endl;
            current_word++;
        }
    }
    pthread_exit(0);
}

void* numeric(void*) {
    while (current_word < words.size()) {
        if (isdigit(words[current_word][0])) {
            cout << "NUMERIC: " << words[current_word] << endl;
            current_word++;
        }
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please enter 2 arguments" << endl;
        return 1;
    }

    if (argc > 2) {
        cout << "Please enter only 2 arguments" << endl;
        return 1;
    }

    sentence = argv[1];
    
    std::istringstream iss(sentence);
    string word;

    while (iss >> word) {
        words.push_back(word);
    }

    pthread_t alpha_thread, numeric_thread;
    pthread_create(&alpha_thread, NULL, alpha, NULL);
    pthread_create(&numeric_thread, NULL, numeric, NULL);

    pthread_join(alpha_thread, NULL);
    pthread_join(numeric_thread, NULL);

    return 0;
}
