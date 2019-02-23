#include <time.h>
#include <stdlib.h>
#include "lili.h"
#include "hwprint.h"

extern element_t* head;

int main() {
    srand(time(NULL));
    bs_hw_next();

    // implement
    int punkte = 0;
    punkte += 1;

    bs_hw_manual("Testen auf Benutzung von perror per Hand", "(perror Check im Quelltext)");
    bs_hw_next();
    
    // insert_element()
    printf("Führe insert_element aus: ");
    unsigned int e1 = rand();
    insert_element(e1);
    printf(BS_SUCCESS);
    punkte += 1;
    bs_hw_next();

    printf("Einfügen des ersten Elements: ");
    if (head->data == e1) {
	punkte += 1;
	printf(BS_SUCCESS);
    } else {
	printf(BS_FAILURE);
    }
    bs_hw_next();

    unsigned int e2 = rand();
    insert_element(e2);
    printf("Einfügen bei Liste der Länge 1: ");
    if (head->data == e1 && head->next != NULL && head->next->data == e2) {
	punkte += 1;
	printf(BS_SUCCESS);
    } else {
	printf(BS_FAILURE);
    }
    bs_hw_next();

    unsigned int e3, e4 = rand();
    insert_element(e3);
    insert_element(e4);
    unsigned int werte[] = {e1, e2, e3, e4};
    printf("Einfügen weiterer Werte: ");
    int insert_t_fail = 0;
    element_t* insert_tester = head;
    for (int i = 0; i < 4; i++) {
	if (insert_tester->data != werte[i]) {
	    printf(BS_FAILURE);
	    printf("Unerwarteter Listeninhalt.\n");
	    insert_t_fail = 1;
	    break;
	}
	if (i < 3 && insert_tester->next == NULL) {
	    printf(BS_FAILURE);
	    printf("Liste zu kurz.\n");
	    insert_t_fail = 1;
	    break;
	}
	insert_tester = insert_tester->next;
    }
    if (!insert_t_fail) {
	punkte += 2;
	printf(BS_SUCCESS);
    }
    bs_hw_next();

    // print_lili
    head = NULL;

    printf("Führe print_lili aus:\n");
    print_lili();
    printf(BS_SUCCESS);
    punkte += 1;
    bs_hw_next();

    insert_element(1);
    insert_element(2);
    insert_element(3);
    insert_element(4);
    insert_element(5);
    insert_element(6);
    bs_hw_manual("Richtige Ausgabe kontrolliert per Hand", "1, 2, 3, 4, 5, 6");
    print_lili();
    bs_hw_next();

    // remove_element()
    printf("Führe remove_element aus: ");
    remove_element();
    printf(BS_SUCCESS);
    punkte += 1;
    bs_hw_next();

    bs_hw_manual("Keine Memoryleaks entstehen, getestet per Hand", "(Überprüfen im Quelltext)");
    bs_hw_next();

    head = NULL;
    printf("Führe remove_element auf leerer Liste aus:\n");
    remove_element();
    if (head == NULL) {
	printf(BS_SUCCESS);
	punkte += 1;
    } else {
	printf(BS_FAILURE);
    }
    bs_hw_next();

    head = NULL;
    printf("Teste Funktionsweise und Rückgabe von remove_element: ");
    unsigned int remove_werte[] = {rand(), rand(), rand(), rand(), rand()};
    int failed = 0;
    for (int i = 0; i < 5; i++) {
	insert_element(remove_werte[i]);
    }
    for (int i = 0; i < 5; i++) {
	unsigned int ret = remove_element();
	if (ret != remove_werte[i]) {
	    printf(BS_FAILURE);
	    printf("falscher Rückgabewert.\n");
	    failed = 1;
	    break;
	}
	element_t* rem_iter = head;
	for (int j = i+1; j < 5; j++) {
	    if (rem_iter == NULL || rem_iter->data != remove_werte[j]) {
		printf(BS_FAILURE);
		printf("Werte falsch entfernt.\n");
		failed = 1;
		break;
	    }
	    rem_iter = rem_iter->next;
	}
    }
    if (head != NULL) {
	printf(BS_FAILURE);
	printf("Liste wurde nicht geleert.\n");
	failed = 1;
    }
    if (!failed) {
	printf(BS_SUCCESS);
	punkte += 2;
    }
    bs_hw_next();

    bs_hw_print(punkte, 11, 4, "02R_Zeiger");

}
