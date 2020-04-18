#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Adress {
	char* name;
	char* street;
	char* city;
	int number;
	int postalcode;
};

void adress(struct Adress* that, char* name, char* city, char* street, int number, int postalcode) {
	that->name = (char*) malloc(strlen(name) + 1);
	that->street = (char*) malloc(strlen(street) + 1);
	that->city = (char*) malloc(strlen(city) + 1);
	strcpy(that->name, name);
	strcpy(that->street, street);
	strcpy(that->city, city);
	that->number = number;
	that->postalcode = postalcode;
}

void freeSpace(struct Adress* that) {
	free(that->name);
	free(that->street);
	free(that->city);
}
void print(struct Adress* that) {
	printf("%s\n", that->name);
	printf("%s ", that->street), printf("%d\n", that->number);
	printf("%d ", that->postalcode), printf("%s\n", that->city), printf("\n");
}

int main(int argc, char**argv) {
	struct Adress adr1, adr2;
	adress(&adr1, "Ernie", "Mannheim", "Sesamstreet", 55, 68260);
	adress(&adr2, "Bert", "Mannheim", "Sesamstreet", 56, 68260);

	print(&adr1), print(&adr2);

	freeSpace(&adr1), freeSpace(&adr2);

	return 0;
}
