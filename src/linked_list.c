#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

//funkcija za inicijalizaciju nove prazne liste
//alocira se memorija za nju te joj se pointeri za pocetak i kraj postavljaju na NULL
//counter se takodjer postavlja na 0
struct lista_troskova* newEmptyList()
{
	struct lista_troskova *nova_lista = (struct lista_troskova*)malloc(sizeof(struct lista_troskova));
	if (nova_lista == NULL) {
		printf("Neuspjesna alokacija memorije.\n");
		return NULL;
	} else {
		nova_lista->head = NULL;
		nova_lista->tail = NULL;
		nova_lista->counter = 0;
		return nova_lista;
	}
}

//funkcija za izradu novog cvora, tj. troska
//alocira se memorija te se varijable strukture postave na vrijednosti predane u funkciji
struct trosak* newNode(float iznos, Kategorija kategorija, short dan, short mjesec, char opis[50])
{
	struct trosak* noviTrosak = (struct trosak*)malloc(sizeof(struct trosak));
	if (noviTrosak == NULL) {
		printf("Neuspjesna alokacija memorije.\n");
		return NULL;
	} else {
		noviTrosak->prev = NULL;
		noviTrosak->next = NULL;
		noviTrosak->iznos = iznos;
		noviTrosak->kategorija = kategorija;
		noviTrosak->dan = dan;
		noviTrosak->mjesec = mjesec;
		snprintf(noviTrosak->opis, sizeof(noviTrosak->opis), "%s", opis);
		return noviTrosak;
	}
}

//funkcija koja provjerava je li lista prazna ili ne
int checkIfEmptyList(struct lista_troskova* list) {
	if(list->head == NULL && list->tail == NULL && list->counter == 0) {
		printf("Prazna lista\n");
		return 1;
	} else {
		printf("Nije prazna lista\n");
		return 0;
	}
}

//funkcija za dodavanje cvora/troska na pocetak liste 
void addNodeToListAtHead(struct trosak* trosak, struct lista_troskova* lista) {
	if (trosak == NULL || lista == NULL) return;
	if(checkIfEmptyList(lista)==1) { //prazna lista, cvor je ujedno i kraj i pocetak liste
		lista->head = trosak;
		lista->tail = trosak;
		lista->counter += 1;
	} else {
		trosak->prev = NULL;
		trosak->next = lista->head;
		lista->head->prev = trosak;
		lista->head = trosak;
		lista->counter += 1;
	}
}

//funkcija za dodavanje cvora/troska na kraj liste
void addNodeToListAtTail(struct trosak* trosak, struct lista_troskova* lista) {
	if (trosak == NULL || lista == NULL) return;
	if(checkIfEmptyList(lista)==1) { //isti slucaj kao gore
		lista->head = trosak;
		lista->tail = trosak;
		lista->counter += 1;
	} else {
		trosak->prev = lista->tail;
		lista->tail->next = trosak;
		lista->tail = trosak;
		lista->counter += 1;
	}
}

//printanje svih troskova liste
void printList(struct lista_troskova* lista) {
	if (lista == NULL || lista->head == NULL) {
		printf("Lista je prazna ili nije inicijalizirana.\n");
		return;
	}
	struct trosak* temp = lista->head;
	int counter = 1;
	do {
		printf("Iznos troska %d: %f \n", counter, temp->iznos);
		printf("Kategorija troska %d: %s \n", counter, getCategoryName(temp->kategorija));
		printf("Datum troska %d je %d.%d. \n", counter, temp->dan, temp->mjesec);
		printf("Opis troska %d : %s \n", counter, temp->opis);
		temp = temp->next;
		counter++;
	} while(temp != NULL);
}

//brisanje troska na unesenoj poziciji
void deleteNodeAtPosition(struct lista_troskova* lista, int pozicija) {
	if (lista == NULL || lista->head == NULL) {
		printf("Lista je prazna ili nije inicijalizirana.\n");
		return;
	}

	//provjera ispravnosti unesene pozicije
	if (pozicija < 1 || pozicija > lista->counter) {
		printf("Nevazeca pozicija %d. Lista ima %d elemenata.\n", pozicija, lista->counter);
		return;
	}

	struct trosak* temp = lista->head;
	int counter = 1;

	//pronalazak trazenog troska
	while (temp != NULL && counter < pozicija) {
		temp = temp->next;
		counter++;
	}

	if (temp == NULL) {
		printf("Ne postoji trosak na poziciji %d.\n", pozicija);
		return;
	}

	//slucaj brisanja jedinog troska
	if (lista->head == lista->tail) {
		lista->head = NULL;
		lista->tail = NULL;
	}
	//slucaj brisanja prvog troska
	else if (temp == lista->head) {
		lista->head = temp->next;
		if (lista->head != NULL) {
			lista->head->prev = NULL;
		}
	}
	//slucaj brisanja zadnjeg troska
	else if (temp == lista->tail) {
		lista->tail = temp->prev;
		if (lista->tail != NULL) {
			lista->tail->next = NULL;
		}
	}
	//slucaj brisanja troska negdje u sredini
	else {
		if (temp->prev != NULL) {
			temp->prev->next = temp->next;
		}
		if (temp->next != NULL) {
			temp->next->prev = temp->prev;
		}
	}

	free(temp);
	lista->counter--;
	printf("Trosak na poziciji %d uspjesno uklonjen.\n", pozicija);
}

//ukupna suma troskova
float calculateTotal(struct lista_troskova* lista) {
	if (lista == NULL || lista->head == NULL) {
		printf("Lista je prazna ili nije inicijalizirana.\n");
		return 0.0;
	}

	float suma = 0.0;
	struct trosak* temp = lista->head;

	while (temp != NULL) {
		suma += temp->iznos;
		temp = temp->next;
	}

	return suma;
}

//ispis suma troskova po kategorijama
void printTotalByCategory(struct lista_troskova* lista) {
	if (lista == NULL || lista->head == NULL) {
		printf("Lista je prazna ili nije inicijalizirana.\n");
		return;
	}

	float sumaHrana = 0.0, sumaRezije = 0.0, sumaZabava = 0.0, sumaOstalo = 0.0;
	struct trosak* temp = lista->head;

	while (temp != NULL) {
		switch (temp->kategorija) {
		case 1:
			sumaHrana += temp->iznos;
			break;
		case 2:
			sumaRezije += temp->iznos;
			break;
		case 3:
			sumaZabava += temp->iznos;
			break;
		case 4:
			sumaOstalo += temp->iznos;
			break;
		}
		temp = temp->next;
	}
	printf("Ukupni troskovi po kategorijama:\n");
	printf("Hrana: %.2f\n", sumaHrana);
	printf("Rezije: %.2f\n", sumaRezije);
	printf("Zabava: %.2f\n", sumaZabava);
	printf("Ostalo: %.2f\n", sumaOstalo);
}

//ispis troskova po odabranoj kategoriji
void printCostsByCategory(struct lista_troskova* lista, int kategorija) {
	if (lista == NULL || lista->head == NULL) {
		printf("Lista je prazna ili nije inicijalizirana.\n");
		return;
	}

	struct trosak* temp = lista->head;
	int found = 0;

	printf("Troskovi za kategoriju %s:\n", getCategoryName(kategorija));

	while (temp != NULL) {
		if ((int)temp->kategorija == kategorija) {
			printf("Iznos: %.2f\n", temp->iznos);
			printf("Datum: %d.%d.\n", temp->dan, temp->mjesec);
			printf("Opis: %s\n", temp->opis);
			printf("----------------------\n");
			found = 1;
		}
		temp = temp->next;
	}

	if (!found) {
		printf("Nema troskova za ovu kategoriju.\n");
	}
}

//funkcija za printanje enuma kao string
const char* getCategoryName(Kategorija kategorija)
{
	switch (kategorija)
	{
	case 1:
		return "Hrana";
	case 2:
		return "Rezije";
	case 3:
		return "Zabava";
	case 4:
		return "Ostalo";
	default:
		return "Nepoznato";
	}
}

//funkcija glavnog izbornika
void mainMenu(struct lista_troskova** current_list)
{
	int odabir;

	do {
		printf("\nGlavni izbornik:  \n");
		printf("1: Inicijalizacija liste\n");
		printf("2: Dodavanje novog elementa na pocetak liste\n");
		printf("3: Dodavanje novog elementa na kraj liste\n");
		printf("4: Brisanje elementa\n");
		printf("5: Ispis liste\n");
		printf("6: Provjera liste (Prazna ili ne)\n");
		printf("7: Pregled ukupnog stanja\n");
		printf("8: Pregled po odredjenoj kategoriji\n");
		printf("9: Izlaz iz programa\n");
		printf("\nOdaberite opciju unosom broja (1-9):  \n");

		scanf("%d", &odabir);

		if (odabir < 1 || odabir > 9) {
			printf("Nevazeci unos. Molimo unesite broj izmedju 1 i 9.\n");
			continue;
		}

		switch (odabir) {
		case 1:
			if (*current_list != NULL) {
				printf("Lista je vec inicijalizirana.\n");
			} else {
				*current_list = newEmptyList();
				if (*current_list != NULL) {
					printf("Lista uspjesno inicijalizirana.\n");
				}
			}
			break;
		case 2:
			if (*current_list == NULL) {
				printf("Lista nije inicijalizirana. Prvo inicijalizirajte listu.\n");
			} else {
				float iznos;
				short dan, mjesec;
				char opis[50];
				int kategorija;
				printf("Unesite iznos, kategoriju (1-Hrana, 2-Rezije, 3-Zabava, 4-Ostalo), datum (DD.MM. format), ali odvojeno razmakom: \n");
				if (scanf("%f %d %hd.%hd.", &iznos, &kategorija, &dan, &mjesec) != 4 ||
				    iznos < 0 || kategorija < 1 || kategorija > 4 ||
				    dan < 1 || dan > 31 || mjesec < 1 || mjesec > 12) {
					printf("Nevazeci podaci o trosku.\n");
					int ch;
					while ((ch = getchar()) != '\n' && ch != EOF) {}
					break;
				}
				printf("Unesite opis troska: \n");
				getchar(); //ocisti '\n' iz buffera nakon scanf
				fgets(opis, sizeof(opis), stdin); //omogucuje unos opisa s razmacima
				struct trosak* novi_trosak = newNode(iznos, kategorija, dan, mjesec, opis);
				addNodeToListAtHead(novi_trosak, *current_list);
				printf("Element uspjesno dodan na pocetak liste.\n");
			}
			break;
		case 3:
			if (*current_list == NULL) {
				printf("Lista nije inicijalizirana. Prvo inicijalizirajte listu.\n");
			} else {
				float iznos;
				short dan, mjesec;
				char opis[50];
				int kategorija;
				printf("Unesite iznos, kategoriju (1-Hrana, 2-Rezije, 3-Zabava, 4-Ostalo), datum (DD.MM. format), ali odvojeno razmakom: \n");
				if (scanf("%f %d %hd.%hd.", &iznos, &kategorija, &dan, &mjesec) != 4 ||
				    iznos < 0 || kategorija < 1 || kategorija > 4 ||
				    dan < 1 || dan > 31 || mjesec < 1 || mjesec > 12) {
					printf("Nevazeci podaci o trosku.\n");
					int ch;
					while ((ch = getchar()) != '\n' && ch != EOF) {}
					break;
				}
				printf("Unesite opis troska: \n");
				getchar(); //ocisti '\n' iz buffera nakon scanf
				fgets(opis, sizeof(opis), stdin); //omogucuje unos opisa s razmacima
				struct trosak* novi_trosak = newNode(iznos, kategorija, dan, mjesec, opis);
				addNodeToListAtTail(novi_trosak, *current_list);
				printf("Element uspjesno dodan na kraj liste.\n");
			}
			break;
		case 4:
			if (*current_list == NULL || checkIfEmptyList(*current_list)) {
				printf("Lista je prazna ili nije inicijalizirana.\n");
			} else {
				int position;
				printf("Unesite redni broj troska koji zelite obrisati: ");
				scanf("%d", &position);
				deleteNodeAtPosition(*current_list, position);
			}
			break;
		case 5:
			if (*current_list == NULL || checkIfEmptyList(*current_list)) {
				printf("Lista je prazna ili nije inicijalizirana.\n");
			} else {
				printList(*current_list);
			}
			break;
		case 6:
			if (*current_list == NULL) {
				printf("Lista nije inicijalizirana.\n");
			} else {
				checkIfEmptyList(*current_list);
			}
			break;
		case 7:
			if (*current_list == NULL) {
				printf("Lista nije inicijalizirana.\n");
			} else {
				float ukupno = calculateTotal(*current_list);
				printf("Ukupan iznos troskova: %.2f\n", ukupno);
				printTotalByCategory(*current_list);
			}
			break;
		case 8:
			if (*current_list == NULL) {
				printf("Lista nije inicijalizirana.\n");
			} else {
				int kategorija;
				printf("Unesite kategoriju (1-Hrana, 2-Rezije, 3-Zabava, 4-Ostalo): ");
				scanf("%d", &kategorija);
				if (kategorija < 1 || kategorija > 4) {
					printf("Nevazeca kategorija.\n");
				} else {
					printCostsByCategory(*current_list, kategorija);
				}
			}
			break;
		case 9:
			printf("Izlaz iz programa...\n");
			break;
		default:
			printf("Nevazeci unos. Molimo pokusajte ponovo.\n");
		}
	} while (odabir != 9);
}


int main() {
	struct lista_troskova* current_list = NULL;
	mainMenu(&current_list);
	if (current_list != NULL) {
		struct trosak* node = current_list->head;
		while (node != NULL) {
			struct trosak* next = node->next;
			free(node);
			node = next;
		}
		free(current_list);
	}
	return 0;
}