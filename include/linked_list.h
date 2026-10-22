/*
 * linked_list.h
 *
 *  Created on: Dec 16, 2024
 *      Author: rtrk
 */
/*enum: 1-Hrana, 2-Rezije, 3-Zabava, 4-Ostalo*/
#ifndef INCLUDE_LINKED_LIST_H_
#define INCLUDE_LINKED_LIST_H_

typedef enum
{
	Hrana = 1,
	Rezije,
	Zabava,
	Ostalo
} Kategorija;


struct trosak
{
	struct trosak* next;
	struct trosak* prev;
	float iznos;
	Kategorija kategorija;
	short dan;
	short mjesec; 
	char opis[50]; 
};

struct lista_troskova
{
	struct trosak* head;
	struct trosak* tail;
	int counter;
};

//konstruktorske funkcije
struct lista_troskova* newEmptyList();
struct trosak* newNode(float iznos, Kategorija kategorija, short dan, short mjesec, char opis[50]);
//operacije dodavanja
void addNodeToListAtHead(struct trosak* trosak, struct lista_troskova* lista);
void addNodeToListAtTail(struct trosak* trosak, struct lista_troskova* lista);
//operacije brisanja
void deleteNodeAtPosition(struct lista_troskova* lista, int pozicija);
//pomocne funkcije
int checkIfEmptyList(struct lista_troskova* lista_troskova);
void printList(struct lista_troskova* lista_troskova);
const char* getCategoryName(Kategorija kategorija);
//dodatne funkcije
float calculateTotal(struct lista_troskova* lista);
void printTotalByCategory(struct lista_troskova* lista);
void printCostsByCategory(struct lista_troskova* lista, int kategorija);


#endif /* INCLUDE_LINKED_LIST_H_ */
