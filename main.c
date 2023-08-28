#include <stdio.h>

int main() {
  printf("hello world");
  return 0;
}


void seating_data_collect_store() {
	FILE *seating_data;
	int seat_number;
	printf("Enter the seat you want to book: ");
	scanf("%d", &seat_number);
	seating_data = fopen("seat_data.txt", "a");
	if (seating_data == NULL) {
		printf("Error! Could not find file.");
	} else {
		fprintf(seating_data, "%d ", seat_number);
	}
	fclose(seating_data);
} 

