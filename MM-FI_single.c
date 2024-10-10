#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/multicore.h"
#include "hardware/structs/sio.h"
#include "hardware/watchdog.h"

#define MATRIX_SIZE 3
#define SIZE 40

uint32_t A[MATRIX_SIZE][MATRIX_SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

uint32_t B[MATRIX_SIZE][MATRIX_SIZE] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}};

uint32_t C[MATRIX_SIZE][MATRIX_SIZE] = {0};
uint32_t D[MATRIX_SIZE][MATRIX_SIZE] = {0};
int iteration = 0;

void matrix_multiply(uint32_t A[MATRIX_SIZE][MATRIX_SIZE], uint32_t B[MATRIX_SIZE][MATRIX_SIZE], uint32_t C[MATRIX_SIZE][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Result matrix on interation %d:\n", iteration);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            D[i][j] = C[i][j];
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

// Functions to introduce a SDC bit-flip in a matrix element
void flip_random_bit_r1(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r1, #1\n"                     // Load 1 into r1
        "lsl r1, %1\n"                     // Shift left r1 by the bit_position
        "eor %0, %0, r1\n"                 // XOR
        : "=r"(*element)                   // Output operand
        : "r"(bit_position), "0"(*element) // Input operands
        : "r1"                             // register
    );
}
void flip_random_bit_r2(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r2, #1\n"                     // Load 1 into r2
        "lsl r2, %1\n"                     // Shift left r2 by the bit_position
        "eor %0, %0, r2\n"                 // Exclusive OR element with r2 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r2"                             // Clobbered register: r2
    );
}
void flip_random_bit_r3(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r3, #1\n"                     // Load 1 into r3
        "lsl r3, %1\n"                     // Shift left r3 by the bit_position
        "eor %0, %0, r3\n"                 // Exclusive OR element with r3 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r3"                             // Clobbered register: r3
    );
}
void flip_random_bit_r4(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r4, #1\n"                     // Load 1 into r4
        "lsl r4, %1\n"                     // Shift left r4 by the bit_position
        "eor %0, %0, r4\n"                 // Exclusive OR element with r4 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r4"                             // Clobbered register: r4
    );
}
void flip_random_bit_r5(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r5, #1\n"                     // Load 1 into r5
        "lsl r5, %1\n"                     // Shift left r5 by the bit_position
        "eor %0, %0, r5\n"                 // Exclusive OR element with r5 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r5"                             // Clobbered register: r5
    );
}
void flip_random_bit_r6(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r6, #1\n"                     // Load 1 into r6
        "lsl r6, %1\n"                     // Shift left r6 by the bit_position
        "eor %0, %0, r6\n"                 // Exclusive OR element with r6 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r6"                             // Clobbered register: r6
    );
}
void flip_random_bit_r7(uint32_t *element)
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the element
    asm volatile(
        "mov r7, #1\n"                     // Load 1 into r7
        "lsl r7, %1\n"                     // Shift left r7 by the bit_position
        "eor %0, %0, r7\n"                 // Exclusive OR element with r7 to flip the chosen bit
        : "=r"(*element)                   // Output operand: store the result back in *element
        : "r"(bit_position), "0"(*element) // Input operands: bit_position and current element value
        : "r7"                             // Clobbered register: r7
    );
}

// attempt to modify stack pointer
void flip_random_bit_in_sp()
{
    // Generate a random bit position to flip (0 to 31)
    uint32_t bit_position = rand() % 32;

    // Inline assembly to flip the chosen bit in the stack pointer (sp)
    asm volatile(
        "mov r0, sp\n"      // Move the current stack pointer into r0
        "mov r1, #1\n"      // Load 1 into r1
        "lsl r1, %0\n"      // Shift left r1 by the bit_position
        "eor r0, r0, r1\n"  // XOR r0 with the bit mask in r1 (flipping the bit)
        "mov sp, r0\n"      // Move the modified value back into sp
        :                   // No output operands
        : "r"(bit_position) // Input: the bit position
        : "r0", "r1"        // Clobbered registers: r0 and r1
    );
}

void inject_SDC_fault()
{
    // Seed the random number generator
    srand(time(NULL));
    // Introduce a bit-flip in a random element of matrix A
    int random_row = (rand() % MATRIX_SIZE) + 1;
    int random_col = (rand() % MATRIX_SIZE) + 1;
    int register_select = (rand() % 7) + 1; // select random register between 0 and 8

    printf("Selected: %d\n", register_select);
    printf("Flipping bit in A[%d][%d]!\n", random_row, random_col);
    
    //flip_random_bit_in_sp();

    switch (register_select)
    {
    case 1:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r1(&A[random_row][random_col]);
        break;

    case 2:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r2(&A[random_row][random_col]);
        break;

    case 3:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r3(&A[random_row][random_col]);
        break;

    case 4:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r4(&A[random_row][random_col]);
        break;

    case 5:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r5(&A[random_row][random_col]);
        break;

    case 6:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r6(&A[random_row][random_col]);
        break;

    case 7:
        printf("Changed register %d! \n", register_select);
        flip_random_bit_r7(&A[random_row][random_col]);
        break;
    }
    sleep_ms(1000);
}


//unused
volatile void inject_crash()
{
    // Inline assembly to modify the stack pointer by flipping its most significant bit
    // asm volatile(
    //     "ldr r0, =0xFFFFFFFF\n" // Load 0xFFFFFFFF into r0
    //     "mov sp, r0\n"          // Move r0 into sp (stack pointer)
    //     :                       // No output operands
    //     :                       // No input operands
    //     : "r0"                  // Clobbers: Register r0 is used
    // );

    // address misalignment
    uint32_t *unaligned_address = (uint32_t *)0x20000001; // Deliberately misaligned address (not multiple of 4)
    printf("Test!\n");

    asm volatile(
        "ldr r0, [%0]\n" // Attempt to load a 32-bit word from the misaligned address
        :
        : "r"(unaligned_address) // Input: the misaligned address
        : "r0"                   // Clobbers: r0 is used
    );

    printf("Test2!\n");

    // volatile int flip_sp = 1000;
}


void core0_check_and_jump()
{
    // Check if FIFO contains data from Core 1
    if (multicore_fifo_rvalid())  // Check if FIFO contains a valid message
    {
        uint32_t command = multicore_fifo_pop_blocking(); // Read the command sent by Core 1

        if (command == 0xDEADBEEF)  // Specific command to modify the stack pointer
        {
            printf("Core 0: Received command to modify SP from Core 1.\n");
            flip_random_bit_in_sp();  // Call the function to flip a random bit in the stack pointer
        }
    }
}

void core1()
{

    // Inject faults from this core
    while (true)
    {
        sleep_ms(10000);
        // srand((unsigned)time(NULL));

        inject_SDC_fault();
    }
}

int main()
{
    stdio_init_all();
    watchdog_enable(5000, 1);
    //multicore_launch_core1(core1);
    sleep_ms(2000);

    // Correct Matrix Values:
    // 30 24 18
    // 84 69 54
    // 138 114 90

    while (true)
    {
        core0_check_and_jump();
        matrix_multiply(A, B, C);

        printf("Complete\n\n\n\n\n\n\n\n\n\n");
        iteration++;

        if (iteration == 10) {
            inject_SkDC_fault();
        }        

        watchdog_update();
        sleep_ms(1000);
    }
}