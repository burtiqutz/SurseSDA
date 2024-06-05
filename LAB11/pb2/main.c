#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///DOES NOT WORK
///NOT EVEN GPT CAN SAVE ME
char* substring(const char* str, int start, int length) {
    char* substr = (char*)malloc((length + 1) * sizeof(char));
    strncpy(substr, str + start, length);
    substr[length] = '\0';
    return substr;
}
char* findCommonPrefix(const char* left, const char* right) {
    int min_len = strlen(left) < strlen(right) ? strlen(left) : strlen(right);
    for (int i = 0; i < min_len; i++) {
        if (left[i] != right[i]) {
            char* prefix = (char*)malloc((i + 1) * sizeof(char));
            strncpy(prefix, left, i);
            prefix[i] = '\0';
            return prefix;
        }
    }
    char* prefix = (char*)malloc((min_len + 1) * sizeof(char));
    strncpy(prefix, left, min_len);
    prefix[min_len] = '\0';
    return prefix;
}

char* commonPrefix(char* word1, char* word2){
    if(strcmp(word1, "") == 0 || strcmp(word2, "") == 0){
        return "";
    }
    if(strcmp(word1, word2) == 0){
        return word1;
    }
    int mid1 = strlen(word1) / 2;
    int mid2 = strlen(word2) / 2;
    char* leftPrefix = commonPrefix(substring(word1,0, mid1),
                                    substring(word2, 0, mid2));
    char* rightPrefix = commonPrefix(substring(word1, mid1 + 1, strlen(word1) - 1),
                                     substring(word2, mid2 + 1, strlen(word2) - 1));
    char* result = findCommonPrefix(leftPrefix, rightPrefix);
    return result;
}
int main() {
    char* sir1 = "gigemescu";
    char* sir2 = "gigelescu";
    char* result = commonPrefix(sir1, sir2);
    printf("%s", result);
    return 0;
}
