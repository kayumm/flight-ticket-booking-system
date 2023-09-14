// first semister basic c project
// contain lots of bugs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void book_ticket();
void cancel_ticket();
void find_tickets();
void seating_chart();
void seating_data_collect_store();
void no_4_func_mechanism();
void no_3_func_mechanism();
void update_seat_number();
void clearScreen() {
    printf("\e[1;1H\e[2J");
}


int seat_array[40] = {0};

struct user_info {
    char name[30];
    char email[50];
    char phone_number[15];
} data;

void main() {
    int menu_user_input;
    do {
        printf("\n\n");
        printf("\t_______________________________________________________\n");
        printf("\t|                                                     |\n");
        printf("\t|       Flight Tickt Booking System                   |\n");
        printf("\t|                                                     |\n");
        printf("\t|_____________________________________________________|\n\n");
        printf("\t        [1] Book Ticket\n");
        printf("\t        [2] Cancel Ticket\n");
        printf("\t        [3] Find Your Tickets\n");
        printf("\t        [4] Show Available/Reserved Seats\n");
        printf("\t        [5] Update Seat Number\n");
        printf("\t        [0] Exit\n");
        printf("\n\t      Enter your choice: ");
        scanf("%d", &menu_user_input);
        switch (menu_user_input) {
            case 1:
                book_ticket();
                break;
            case 2:
                cancel_ticket();
                break;
            case 3:
                no_3_func_mechanism();
                break;
            case 4:
                no_4_func_mechanism();
                break;
            case 5:
                update_seat_number();
                break;
            case 0:
                exit(0);
                break;

            default:
                printf("       Invalid Choice!");
                break;
        }
    } while (menu_user_input != 0);
}

void seating_chart() {
    clearScreen();

    char *empty = "empty ";
    char *booked = "BOOKED";

    int num, i = 0, counter1, counter2;
    FILE *read_seat_data;

    read_seat_data = fopen("seat_data.txt", "r");

    if (read_seat_data == NULL) {
        read_seat_data = fopen("seat_data.txt", "w");
    } else {
        while (fscanf(read_seat_data, "%d", &num) == 1) {
            seat_array[i] = num;
            i++;
        }
    }
    fclose(read_seat_data);

    int total_seats = 40, reserved = 0;
    printf("         -----------------------------------------------------\n");

    for (int j = 1; j <= 40; j++) {
        if (j % 2 == 0) {
            counter1 = 0;
            for (int k = 0; k < 40; k++) {
                if (seat_array[k] == j) {
                    counter1++;
                    total_seats--;
                    reserved++;
                    break;
                }
            }
            if (counter1 != 0)
                printf("%3d.%s", j, booked);
            else
                printf("%3d.%s", j, empty);
        } else {
            counter2 = 0;
            for (int k = 0; k < 40; k++) {
                if (seat_array[k] == j) {
                    counter2++;
                    total_seats--;
                    reserved++;
                    break;
                }
            }
            if (counter2 != 0)
                printf("%12d.%s |", j, booked);
            else
                printf("%12d.%s |", j, empty);
        }

        if (j % 4 == 0) {
            printf("\n");
        }
    }

    printf("         -----------------------------------------------------\n");
    printf("           Total Seats Remaining: %d\n", total_seats);
    printf("           Reserved Seats: %d\n", reserved);
    printf("         -----------------------------------------------------\n");
}

void no_4_func_mechanism() {
    seating_chart();
    int exit_func;
    do {
        printf("         enter 0 to return to the main menu....  ");
        scanf("%d", &exit_func);
    } while (exit_func != 0);
    clearScreen();
}

void seating_data_collect_store() {
start_of_current_function:
    printf("\n           Enter the seat you want to book: ");
    FILE *seating_data;
    int seat_number;
    scanf("%d", &seat_number);

    for (int i = 0; i < 40; i++) {
        if (seat_array[i] == seat_number) {
            printf("            Seat is already booked!! Select other seats!");
            goto start_of_current_function;
        }
    }

    if (seat_number < 1 || seat_number > 40) {
        printf("\n           Invalid Seat! Please choose between 1 - 40");
        goto start_of_current_function;
    }

    seating_data = fopen("seat_data.txt", "a");
    if (seating_data == NULL) {
        printf("    Error! Could not find file.");
    } else {
        fprintf(seating_data, "%d\n", seat_number);
    }
    fclose(seating_data);
}
void book_ticket() {
    clearScreen();
    seating_chart();
    seating_data_collect_store();

    // Allocate memory for user information
    struct user_info *data = (struct user_info *)malloc(sizeof(struct user_info));

    if (data == NULL) {
        printf("    Error! Memory allocation failed.");
        return;
    }

    printf("\n           Enter your last name: ");
    scanf("%s", data->name);

    printf("\n           Enter your email address: ");
    scanf("%s", data->email);

    printf("\n           Enter your phone number: ");
    scanf("%s", data->phone_number);

    FILE *info_file = fopen("user_data.txt", "a");

    if (info_file == NULL) {
        printf("    Error! Could not find file.");
        free(data);
        return;
    } else {
        fprintf(info_file, "%s %s %s\n", data->name, data->email, data->phone_number);
    }
    printf("\n");

    int exit_func;

    printf("              ---TICKET BOOKING SUCCESSFUL---\n                   ---THANK YOU---\n");
    do {
        printf("         enter 0 to return to the main menu....  ");
        scanf("%d", &exit_func);
    } while (exit_func != 0);
    fclose(info_file);

    // Free the allocated memory
    free(data);
}

void cancel_ticket() {
    clearScreen();
    seating_chart();
    int seat_number;
    printf("\n           Enter the seat number to cancel: ");
    scanf("%d", &seat_number);

    // Check if the seat is already booked
    int seat_found = 0;
    for (int i = 0; i < 40; i++) {
        if (seat_array[i] == seat_number) {
            seat_array[i] = 0; // Mark the seat as empty
            seat_found = 1;
            printf("\n           Ticket for seat %d has been canceled.", seat_number);
            break;
        }
    }

    if (!seat_found) {
        printf("\n           Seat %d is not booked or does not exist.", seat_number);
    }

    // Update the seat data file

    FILE *seating_data = fopen("seat_data.txt", "w");
    if (seating_data == NULL) {
        printf("    Error! Could not find file.");
    } else {
        for (int i = 0; i < 40; i++) {
        fprintf(seating_data, "%d\n", seat_array[i]);
        }
    }
    fclose(seating_data);

}

void find_tickets() {
    clearScreen();
    char search_name[30];
    int found = 0;
    printf("\n           Enter your last name to find your tickets: ");
    scanf("%s", search_name);

    FILE *info_file = fopen("user_data.txt", "r");
    if (info_file == NULL) {
        printf("    Error! Could not find file.");
    } else {
        char line[100];
        while (fgets(line, sizeof(line), info_file)) {
            char *name = strtok(line, " ");
            char *email = strtok(NULL, " ");
            char *phone = strtok(NULL, " \n");

            if (strcmp(name, search_name) == 0) {
                printf("\n           Ticket Holder's Information:\n");
                printf("           Name: %s\n", name);
                printf("           Email: %s\n", email);
                printf("           Phone: %s\n", phone);
                found = 1;
            }
        }
        fclose(info_file);
    }

    if (!found) {
        printf("\n           No tickets found for %s.", search_name);
    }
}

void no_3_func_mechanism()
{
    find_tickets();
    int exit_func;
    do {
        printf("         enter 0 to return to the main menu....  ");
        scanf("%d", &exit_func);
    } while (exit_func != 0);

}
void update_seat_number() {
    clearScreen();
    seating_chart();
    int old_seat, new_seat;
    printf("\n           Enter the current seat number you want to update: ");
    scanf("%d", &old_seat);

    // Check if the old seat is already booked
    int seat_found = 0;
    for (int i = 0; i < 40; i++) {
        if (seat_array[i] == old_seat) {
            seat_found = 1;
            printf("\n           Enter the new seat number: ");
            scanf("%d", &new_seat);

            if (new_seat < 1 || new_seat > 40) {
                printf("\n           Invalid Seat! Please choose between 1 - 40");
            } else {
                seat_array[i] = new_seat;
                printf("\n           Seat number updated successfully!");

                // Update the seat data file
                FILE *seating_data = fopen("seat_data.txt", "w");
                if (seating_data == NULL) {
                    printf("    Error! Could not find file.");
                    return;
                }
                for (int j = 0; j < 40; j++) {
                    fprintf(seating_data, "%d\n", seat_array[j]);
                }
                fclose(seating_data);

                // Refresh the seating chart
                seating_chart();

                break;
            }
        }
    }

    if (!seat_found) {
        printf("\n           Seat %d is not booked or does not exist.", old_seat);
    }
}
