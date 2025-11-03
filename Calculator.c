#include <stdio.h>
#include <stdlib.h>

// Function to clear the screen and set background color
void setBackgroundPink() {
    printf("\033[48;2;255;182;193m"); // RGB for light pink
    printf("\033[2J"); // clear screen
    printf("\033[H");  // move cursor to home
}

// Function to reset colors
void resetColor() {
    printf("\033[0m");
}

// Function to print a centered calculator border
void printBorder() {
    printf("\033[38;2;255;255;255m"); // White text
    printf("╔══════════════════════════════════╗\n");
    printf("║          🧮 MODERN CALCULATOR    ║\n");
    printf("╠══════════════════════════════════╣\n");
}

// Function to display calculator menu
void showMenu() {
    printf("║ 1. Addition (+)\n");
    printf("║ 2. Subtraction (-)\n");
    printf("║ 3. Multiplication (*)\n");
    printf("║ 4. Division (/)\n");
    printf("║ 5. Exit\n");
    printf("╚══════════════════════════════════╝\n");
}

// Main calculator logic
int main() {
    int choice;
    double num1, num2, result;

    setBackgroundPink();

    // Move calculator roughly to the center of the screen
    for (int i = 0; i < 5; i++) printf("\n");
    printf("                "); // Center horizontally

    printBorder();
    printf("                "); // Center horizontally
    showMenu();

    while (1) {
        printf("\nEnter your choice (1-5): ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("\nThank you for using the Modern Calculator! 💖\n");
            break;
        }

        printf("Enter first number: ");
        scanf("%lf", &num1);
        printf("Enter second number: ");
        scanf("%lf", &num2);

        switch (choice) {
            case 1: result = num1 + num2; break;
            case 2: result = num1 - num2; break;
            case 3: result = num1 * num2; break;
            case 4:
                if (num2 != 0)
                    result = num1 / num2;
                else {
                    printf("Error: Division by zero!\n");
                    continue;
                }
                break;
            default:
                printf("Invalid choice! Try again.\n");
                continue;
        }

        printf("\n✨ Result: %.2lf ✨\n", result);
    }

    resetColor();
    return 0;
}
