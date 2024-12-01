#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"


/* 
* @brief Cria um Nó.
*
* @param digit Dígito do Nó.
* @return O Nó criado.
*
* @details A função inicializa o Nó apenas com o dígito, sem nenhuma ligação com algum Nó
*          posterior ou anterior.
*/

Node* create_node(int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->next_digit = NULL;
    new_node->prev_digit = NULL;

    return new_node;
}


/* 
* @brief Cria um Big Number.
*
* @param str_number String do número.
* @return O Big Number criado.
*
* @details A função adiciona cada Nó a medida que lê cada dígito da string, ou seja, a cada
*          iteração, um novo Nó é adicionado ao final do Big Number. Cada dígito lido da
*          string é convertido em inteiro, antes de ser usado para a criação de um Nó.
*/

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
            big_number->last_digit->next_digit = new_node;
            new_node->prev_digit = big_number->last_digit;
            big_number->last_digit = new_node;
        }

        i++;
    }

    return big_number;
}


/* 
* @brief Realiza o print de um Big Number.
*
* @param big_number Big Number a ser printado.
*/

void print_big_number(BigNumber *big_number) {
    if ((big_number->is_positive = 0)) printf("-");

    Node* current_node = big_number->first_digit;

    while (current_node != NULL) {
        printf("%d", current_node->digit);
        current_node = current_node->next_digit;
    }
}


/* 
* @brief Libera a memória alocada pelo Big Number.
*
* @param big_number Big Number a ser liberado da memória.
*/

void free_big_number(BigNumber *big_number) {
    Node* current_node = big_number->first_digit;   

    while (current_node != NULL) {
        Node* next_node = current_node->next_digit;
        free(current_node);
        current_node = next_node;
    }

    free(big_number);
}


/* 
* @brief Adiciona um novo nó em um Big Number.
*
* @param big_number Registro do tipo Big Number.
* @param digit Número que representa o nó a ser criado.
*
* @details A função atualiza os campos do Nó criado (dígito posterior e anterior),
*          além alocar o novo Nó na primeira posição do Big Number.
*/

void add_node_to_big_number(BigNumber *big_number, int digit) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->digit = digit;
    new_node->next_digit = big_number->first_digit;
    new_node->prev_digit = NULL;

    if (big_number->first_digit == NULL) big_number->last_digit = new_node;
    if (big_number->first_digit != NULL) big_number->first_digit->prev_digit = new_node;
        
    big_number->first_digit = new_node;
}


/* 
* @brief Realiza a soma entre dois Big Numbers.
*
* @param x Big Number a ser somado.
* @param y Big Number a ser somado.
*
* @details A função inicializa a soma a partir do último Nó dos Big Numbers, e só finaliza
*          quando não há mais nenhum Nó, tanto do Big Number x, ou do Big Number y, além de
*          não precisar somar o dígito de transporte (quando a soma feita entre dois
*          dígitos ultrapassa 10).
*/

BigNumber* sum_big_numbers(BigNumber *x, BigNumber *y) {
    BigNumber* result = create_big_number("");

    Node* node_x = x->last_digit;
    Node* node_y = y->last_digit;

    int carry_digit = 0;

    while (node_x != NULL || node_y != NULL || carry_digit > 0) {
        int digit_x, digit_y, sum, new_result_digit;

        digit_x = (node_x != NULL) ? node_x->digit : 0;
        digit_y = (node_y != NULL) ? node_y->digit : 0;

        sum = digit_x + digit_y + carry_digit;
        carry_digit = sum / 10;
        new_result_digit = sum % 10;

        add_node_to_big_number(result, new_result_digit);
        
        if (node_x != NULL) node_x = node_x->prev_digit;
        if (node_y != NULL) node_y = node_y->prev_digit;
    }

    return result;
}