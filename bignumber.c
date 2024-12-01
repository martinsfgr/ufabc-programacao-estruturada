#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

Node* create_node(int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->next_digit = NULL;
    new_node->prev_digit = NULL;

    return new_node;
};

BigNumber* create_big_number(char *str_number) {
    BigNumber* big_number = (BigNumber*)malloc(sizeof(BigNumber));

    big_number->first_digit = NULL;
    big_number->last_digit = NULL;
    big_number->is_positive = 1;

    int i = 0;

    if (str_number[i] == '-') {
        big_number->is_positive = 0;
        i++;
    }

    while (str_number[i] != '\0') {
        int digit = str_number[i] - '0';
        Node* new_node = create_node(digit);

        if (big_number->first_digit == NULL) {
            big_number->first_digit = new_node;
            big_number->last_digit = new_node;
        } else {
            big_number->last_digit->next_digit = new_node; // Adicionando o caminho do próximo dígito ao, até então, último dígito do número.
            new_node->prev_digit = big_number->last_digit; // Adicionando o caminho do dígito anterior ao novo último dígito.
            big_number->last_digit = new_node; // Atualizando, de fato, o novo último dígito.
        }

        i++;
    }

    return big_number;
}

void print_big_number(BigNumber *big_number) {
    if ((big_number->is_positive = 0)) printf("-");

    Node* current_node = big_number->first_digit;
    while (current_node != NULL) {
        printf("%d", current_node->digit);
        current_node = current_node->next_digit;
    }
}

BigNumber* sum_big_numbers(BigNumber *x, BigNumber *y) {
    BigNumber* result = create_big_number("");

    Node* node_x = x->last_digit;
    Node* node_y = y->last_digit;

    int carry_digit = 0;

    while (node_x != NULL || node_y != NULL || carry_digit > 0) {
        int digit_x, digit_y, sum, result_digit;

        // Atualizando os dígitos a partir do nó atual
        digit_x = (node_x != NULL) ? node_x->digit : 0;
        digit_y = (node_y != NULL) ? node_y->digit : 0;

        // Realizando a soma entre os dois dígitos, verificando o total do dígito atual e o dígito de transporte
        sum = digit_x + digit_y + carry_digit;
        carry_digit = sum / 10;
        result_digit = sum % 10;

        // Criando o nó para o dígito do resultado da soma atual
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->digit = result_digit;
        new_node->next_digit = result->first_digit; // Para o novo nó, marcar o, até então, primeiro dígito do resultado, como o próximo nó dele
        new_node->prev_digit = NULL; // Inicializando o dígito anterior do nó como nulo, caso esse nó realmente tenha um dígito anterior, vai ser preenchido na próxima repetição

        // Atualizando o resultado final
        if (result->first_digit == NULL) result->last_digit = new_node; // Se é o primeiro dígito, também é o último
        if (result->first_digit != NULL) result->first_digit->prev_digit = new_node; // Atualizando o novo nó como o nó anterior do último nó adicionado
        
        result->first_digit = new_node; // Atualizando o primeiro dígito do resultado
        
        // Atualizando os nós dos dígitos para a próxima iteração
        if (node_x != NULL) node_x = node_x->prev_digit;
        if (node_y != NULL) node_y = node_y->prev_digit;
    }

    return result;
}