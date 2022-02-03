#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

#define MAX_STRING_SIZE 256

struct InfoStudent {
	char nume[MAX_STRING_SIZE];
	char facultate[MAX_STRING_SIZE];
	int an;
	double medie;
};

static void
print_student(struct InfoStudent *p_info)
{
	if (p_info == NULL) {
		return;
	}
	printf("Studentul %s este inscris la facultatea %s si are media %lf.\n", p_info->nume,
		p_info->facultate, p_info->medie);
}

int main(void)
{
	hashtable_t *ht_studenti;
	struct InfoStudent informatii_student[5];
	struct InfoStudent *p_infoStudent;

	strcpy(informatii_student[0].nume, "David");
	strcpy(informatii_student[0].facultate, "ACS");
	informatii_student[0].an = 1;
	informatii_student[0].medie = 9.5;

	strcpy(informatii_student[1].nume, "Alex");
	strcpy(informatii_student[1].facultate, "ACS");
	informatii_student[1].an = 2;
	informatii_student[1].medie = 6.5;

	strcpy(informatii_student[2].nume, "Filip");
	strcpy(informatii_student[2].facultate, "ACS");
	informatii_student[2].an = 1;
	informatii_student[2].medie = 9.9;

	strcpy(informatii_student[3].nume, "Carlos");
	strcpy(informatii_student[3].facultate, "ACS");
	informatii_student[3].an = 1;
	informatii_student[3].medie = 10;

	strcpy(informatii_student[4].nume, "Cineva");
	strcpy(informatii_student[4].facultate, "ACS");
	informatii_student[4].an = 4;
	informatii_student[4].medie = 7.5;
	
	ht_studenti = ht_create(10, hash_function_string,
				compare_function_strings);

	/* Se adauga studentii in dictionar */
	ht_put(ht_studenti, "David", strlen("David") + 1, &informatii_student[0],
		sizeof(informatii_student[0]));
	ht_put(ht_studenti, "Alex", strlen("Alex") + 1, &informatii_student[1],
		sizeof(informatii_student[1]));
	ht_put(ht_studenti, "Filip", strlen("Filip") + 1, &informatii_student[2],
		sizeof(informatii_student[2]));
	ht_put(ht_studenti, "Carlos", strlen("Carlos") + 1, &informatii_student[3],
		sizeof(informatii_student[3]));
	ht_put(ht_studenti, "Cineva", strlen("Cineva") + 1, &informatii_student[4],
		sizeof(informatii_student[4]));

/* Se citeste de la tastatura numele unui student (subpunctul b) */
	char key[MAX_STRING_SIZE];
	scanf("%s", key);

	p_infoStudent = ht_get(ht_studenti, key);
	if (p_infoStudent == NULL) {
		printf("Studentul %s nu a fost gasit!\n", key);
	} else {
		print_student(p_infoStudent);
	}

	ht_free(ht_studenti);

	return 0;
}