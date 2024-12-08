#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// stack

typedef struct {
    char items[100];
    int top;
} Stack;

// Inicializar pilha
void initStack(Stack* stack) {
    stack->top = -1;
}

// Empilhar caractere
void push(Stack* stack, char c) {
    stack->items[++stack->top] = c;
}

// Desempilhar caractere
char pop(Stack* stack) {
    return stack->items[stack->top--];
}

// Verificar o topo da pilha
char peek(Stack* stack) {
    return stack->items[stack->top];
}

// Verificar se a pilha está vazia
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// prefix

// Precedência dos operadores
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Verificar se é operador
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Verificar se é letra ou número
bool isLetterOrNumber(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

// Reverter expressão
void reverseExpression(char* expression) {
    int l = 0;
    int r = strlen(expression) - 1;
    char t;

    while (l < r) {
        t = expression[l];
        expression[l] = expression[r];
        expression[r] = t;
        l++;
        r--;
    }
}

// Inverter parênteses
void invertParentesis(char* expression) {
    int size = strlen(expression);

    for (int i = 0; i < size; i++) {
        if (expression[i] == '(')
            expression[i] = ')';
        else if (expression[i] == ')')
            expression[i] = '(';
    }
}

// Converter infix para postfix
void infixToPostfix(char* expression, char* result) {
    Stack operators;
    initStack(&operators);

    int size = strlen(expression), index = 0;

    for (int i = 0; i < size; i++) {
        char c = expression[i];

        if (isLetterOrNumber(c)) {
            // Adicionar operando ao resultado
            result[index++] = c;
        } else if (c == '(') {
            push(&operators, c);
        } else if (c == ')') {
            // Desempilhar até encontrar o parêntese esquerdo
            while(!isEmpty(&operators) && peek(&operators) != '(') {
                result[index++] = pop(&operators);
            }
            pop(&operators); // Remover '('
        } else if(isOperator(c)) {
            // Processar operadores com maior ou igual precedência
            while (!isEmpty(&operators) && precedence(peek(&operators)) >= precedence(c)) {
                result[index++] = pop(&operators);
            }
            push(&operators, c);
        }
    }

    // Desempilhar operadores restantes
    while (!isEmpty(&operators)) {
        result[index++] = pop(&operators);
    }
    result[index] = '\0'; // Finalizar string
}

// Converter infix para prefix
void infixToPrefix(char* expression, char* result) {
    reverseExpression(expression);
    invertParentesis(expression);
    infixToPostfix(expression, result);
    reverseExpression(result);
}

// Função principal
int main() {
    char expression[100], result[100] = "";

    scanf("%s", expression);

    infixToPrefix(expression, result);

    printf("%s\n", result);

    return 0;
}
