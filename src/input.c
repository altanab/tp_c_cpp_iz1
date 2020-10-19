#include "input.h"

char input_char() {
    char c = '\0';
    int result = 0;
    do {
        result = scanf("%c", &c);
    } while (result != 1);
    return c;
}

char *input_string() {
    struct buffer {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = input_char()) {
        if(c == EOF || c == '\n'){
            break;
        }
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }
            buf.string = tmp;
            buf.capacity = new_capacity;
        }
        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }
    return buf.string;
}


bool is_space(char c) {
    return c == ' ' || c == '\t';
}

char *get_trimmed_string(char const * const str) {
    if (!str) {
        return NULL;
    }
    char *tmp = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!tmp) {
        return NULL;
    }
    tmp[0] = '\0';
    size_t i = 0;
    size_t j = 0;
    while (is_space(str[j])) {
        ++j;
    }
    while (str[j] != '\0') {
        while (str[j] != '\0' && !is_space(str[j])) {
            tmp[i++] = str[j++];
        }
        size_t first_space_index = j;
        while (is_space(str[j])) {
            ++j;
        }
        if (str[j] != '\0') {
            tmp[i] = '\0';
            tmp = strncat(tmp, str + first_space_index, j - first_space_index + 1);
            i += j - first_space_index + 1;
            ++j;
        }
    }
    tmp[i] = '\0';
    char *result = (char *)malloc((strlen(tmp) + 1) * sizeof(char));
    if (!result) {
        free(tmp);
        return NULL;
    }
    result = strcpy(result, tmp);
    free(tmp);
    return result;
}

int input_int(){
    bool fine_input = false;
    int result = 0;
    while(!fine_input){
        char *tr = get_trimmed_string(input_string());
        if(!tr){
            continue;
        }
        int i = 0;
        bool negative = false;
        if(tr[0] == '-'){
            negative = true;
            i = 1;
        }
        for(i; tr[i] != '\0'; ++i){
            if (!(tr[i] >= '0' && tr[i] <= '9')){
                printf("Wrong input\n");
                result = 0;
                fine_input = false;
                break;
            }
            fine_input = true;
            result = result * 10 + tr[i] - '0';
        }
        if(negative){
            result *= (-1);
        }
    }
    return result;
}
