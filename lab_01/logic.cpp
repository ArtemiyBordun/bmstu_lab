#include "logic.h"

void mystrcpy(AppContext* context, const char* cstr) {
    strncpy(context->number, cstr, strlen(cstr) + 1);
    checkNegative(context);
    checkNum(context);
}

void init(AppContext* context) {
    context->isNegative = -1;
    context->error = NOERROR;
    context->sourceBase = DECIMAL;
    context->newBase = BINARY;
}

void checkNum(AppContext* context) {
    ERRORTYPE error = NOERROR;
    int enter = convertToDecimal(context->number, context->sourceBase);
    if (strlen(context->number) >= SIZE)
        error = NUMBERLONG;
    else if (checkBase(context))
        error = checkBase(context);
    else if (strlen(context->number) == 0)
        error = EMPTY;
    else if (strpbrk(context->number, "."))
        error = NOTINT;
    else if (checkValid(context->number, context->sourceBase))
        error = NOTBASE;
    else if ((context->isNegative == 1 && enter + 1 <= MAXNEGVAL) || (context->isNegative == -1 && enter - 1 >= MAXVAL))
        error = RESULTLONG;
    context->error = error;
}

int checkValid(char* num, int base) {
    int i = 0;
    for (; num[i]; i++) {
        int valid = 0;
        if (base <= DECIMAL) {
            if (num[i] >= '0' && num[i] <= '0' + base - 1)
                valid = 1;
        }
        else {
            for (int j = 0; j < MAXBASE - DECIMAL; j++)
                if (num[i] == 'a' + j)
                    num[i] = 'A' + j;
            if (num[i] >= '0' && num[i] <= '9')
                valid = 1;
            else if (num[i] >= 'A' && num[i] <= 'A' + base - DECIMAL - 1)
                valid = 1;
            else if (num[i] >= 'a' && num[i] <= 'a' + base - DECIMAL - 1)
                valid = 1;
        }
        if (!valid)
            return 1;
    }
    return 0;
}

ERRORTYPE checkBase(AppContext* context) {
    if (context->sourceBase == 0 || context->newBase == 0)
        return NOTINT;
    else if (context->sourceBase > MAXBASE || context->newBase > MAXBASE)
        return BASEBIG;
    else if (context->sourceBase < BINARY || context->newBase < BINARY)
        return BASESMALL;
    return NOERROR;
}

void checkNegative(AppContext* context) {
    if (context->sourceBase == DECIMAL) {
        if (context->number[0] == '-') {
            context->isNegative = 1;
            context->number[0] = '0';
        }
        else
            context->isNegative = -1;
    }
}

void convertTo(AppContext* context) {
    char* numinbase;
    unsigned int num = 0;
    if (context->sourceBase != DECIMAL)
        num = convertToDecimal(context->number, context->sourceBase);
    else
        num = atoi(context->number);

    if (context->isNegative == 1)
        num = convertTotwos(num);  //если число отрицательное, но переводим его в двоичный дополнительный код

    if (context->newBase == DECIMAL)
        sprintf(context->number, "%d", num);  //если нужно перевести в 10сс, то можно не вызывать функцию
    else {
        numinbase = convertToBase(num, context->newBase);
        strncpy(context->number, numinbase, SIZE);
        free(numinbase);
    }
}

int convertToDecimal(char* num, int base) {
    int result = 0;
    int power = 0;

    for (int i = strlen(num) - 1; i >= 0; i--) {
        int digit;
        if (num[i] >= '0' && num[i] <= '9') {
            digit = num[i] - '0';
        }
        else {
            digit = num[i] - 'A' + DECIMAL;
        }
        result += digit * pow(base, power);
        power++;
    }
    return result;
}

char* convertToBase(unsigned int num, int base) {
    char* result = (char*)malloc(SIZE * sizeof(char));
    int index = 0;

    while (num > 0) {
        int remainder = num % base;
        if (remainder < DECIMAL)
            result[index++] = remainder + '0';
        else
            result[index++] = remainder - DECIMAL + 'A';
        num /= base;
    }
    int len = (SIZE - 1) / log2(base);
    if (base == DECIMAL - BINARY)
        len++;
    for (int j = len - 1; j >= index; j--)
        result[j] = '0';
    result = reverse(result, len);
    result[len] = 0;

    return result;
}

int convertTotwos(int num) {
    char* binary = (char*)malloc(SIZE * sizeof(char));
    itoa(num, binary, BINARY);
    int len = strlen(binary);

    for (int i = 0; binary[i]; i++) {
        if (binary[i] == '0')
            binary[i] = '1';
        else binary[i] = '0';
    }
    for (int j = SIZE - 1; j >= len; j--)
        binary[j] = '1';
    binary = reverse(binary, SIZE - 1);
    binary[SIZE - 1] = '\0';

    binary = addbit(binary);

    unsigned int result = 0;
    int pos = 0;
    for (int i = strlen(binary) - 1; i >= 0; i--) {
        if (binary[i] == '1')
            result += pow(2, pos);
        pos++;
    }

    free(binary);
    return result;
}

char* addbit(char* num) {
    int carry = 1;
    int len = strlen(num);
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '0' && carry) {
            num[i] = '1';
            carry = 0;
        }
        else if (num[i] == '1' && carry)
            num[i] = '0';
    }
    return num;
}

char* reverse(char* s, int index) {
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
    return s;
}
