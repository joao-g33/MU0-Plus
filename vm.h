#ifndef __ASSETS_H
#define __ASSETS_H

#include <stddef.h>
#include <stdint.h>

// NÃO ULTILIZADOS:

// define o valor de um bit dentro de um bitfield
// #define SET_BIT(BF, N) BF |= ((uint32_t)0x00000001 << N)

// zera o valor de um bit dentro de um bitfield
// #define CLR_BIT(BF, N) BF &= ~((uint32_t)0x00000001 << N)

// verifica se o valor de um bit dentro de um bitfield é igual a 1
// #define IS_BIT_SET(BF, N) ((BF >> N) & 0x1)

// modos de mensagem de LOG
#define WARNINGMSG "[\e[0;31mWARNING\e[0m]: "
#define ERRORMSG "[\e[0;31mERROR\e[0m]: "

// corpo de uma instrução
typedef struct Instruction_t {
    uint16_t address;   // endereço na memória
    uint16_t opcode;    // ultimos 16 bits
    uint16_t operand;   // primeiros 16 bits
} Instruction_t;

// registradores
struct reg {
    int32_t pc, cir, mar, mbr, acc;
} reg;

// instruções da maquina virtual
enum instructions {
    LDA  = 1, 
    STO  = 2, 
    CLA  = 3,
    ADD  = 4, 
    SUB  = 5, 
    MUL  = 6, 
    DIV  = 7,
    AND  = 8, 
    OR   = 9, 
    XOR  = 10,  
    SHL  = 11, 
    SHR  = 12,
    JMP  = 13, 
    JGE  = 14, 
    JNE  = 15,
    JAC  = 16,
    HALT = 17
} instructions;

// esse union tem o propósitod de dividir um uint32_t em dois uint16_t 
union i32 {
    uint32_t v;
    struct {
        int n1:16;
        int n2:16;
    } n;
};

// memória
int32_t mem[INT16_MAX];

// estado de execução da maquina
bool running = true;


/// @brief exibe uma mensagem de aviso no stderr
/// @param message mensagem
void warning(const char *message); 

/// @brief exibe uma mensagem de erro no stderr
/// @param message mensagem
void failure(const char *message);

/// @brief busca a próxima instrução dentro da memória da maquina virtual
/// @return 0 se houve sucesso
int fetch();

/// @brief recebe uma instrução em um dado endereço e retorna os subcomponentes dessa instrução (opcode e operando)
/// @param address endereço da instrução na memória da maquina virtual
/// @param raw_instruction instrução "crua"
/// @return instrução formatada
Instruction_t parse_instruction(uint16_t address, uint32_t raw_instruction);

/// @brief recebe uma instrução formatada e executa ela na maquina virtual
/// @param instruction instrução formatada
/// @return 0 se houve sucesso
int execute(Instruction_t instruction);

#endif //__ASSETS_H