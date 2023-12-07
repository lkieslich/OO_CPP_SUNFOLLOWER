/*
Classe para criação de uma lista, construida com base na classe Node estudada em aula.
Utilizada para envio do log.
*/
#include "List.h"

List::List() {
   head = 0;
}

List::~List() {
  Node* cursor = head;
  while(head) {
    cursor = cursor->getNext();
    delete head;
    head = cursor;
  }
  head = 0; // Officially empty
}

void List::insertBeforeFirst(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa) {
  head = new Node(ldr1, ldr2, ldr_dig, step_mot, hr, min, sec, ampm, dd, mm, aa, head);
}

void List::insertAfterLast(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm,int dd, int mm, int aa) {
  Node* p = head;
  Node* q = head;

  if (head == 0)
     head = new Node(ldr1, ldr2, ldr_dig, step_mot, hr, min, sec, ampm, dd, mm, aa, head);
  else {
     while (q != 0) {
        p = q;
        q = p->getNext();
     }
     p->setNext(new Node(ldr1, ldr2, ldr_dig, step_mot, hr, min, sec, ampm, dd, mm, aa, 0));
  }
}

int List::readFirst(int &retldr1, int &retldr2, int &retldr_dig, int &retstep_mot, int &rethr, int &retmin, int &retsec, int &retampm, int &retdd, int &retmm, int &retaa) {
   if (head != 0){
  //   cout << "Removendo: " << head << endl;
  //   cout << "e fica:" << head->getVal() << endl;
     retldr1 = head->getldr1();
 
     retldr2 = head->getldr2();
   
     retldr_dig = head->getldr_dig();

     retstep_mot = head->getstep_mot();

     rethr = head->gethr();

     retmin = head->getmin();

    retsec = head->getsec();

    retampm = head->getampm();

    retdd = head->getdd();

    retmm = head->getmm();
    
    retaa = head->getaa();


 
   }
}

int List::removeFirst(int &retldr1, int &retldr2, int &retldr_dig, int &retstep_mot, int &rethr, int &retmin, int &retsec, int &retampm, int &retdd, int &retmm, int &retaa) {

  if (head != 0){
  //   cout << "Removendo: " << head << endl;
  //   cout << "e fica:" << head->getVal() << endl;
     retldr1 = head->getldr1();
     retldr2 = head->getldr2();
     retldr_dig = head->getldr_dig();
     retstep_mot = head->getstep_mot();
     rethr = head->gethr();
     retmin = head->getmin();
     retsec = head->getsec();
     retampm = head->getampm();
     retdd = head->getdd();
     retmm = head->getmm();
     retaa = head->getaa();
     Node* oldHead = head;
     head = head->getNext();
     delete oldHead;
  }
 
}

int List::listAll() {
  Node* aux = head;
  int Node_number = 0;
  while (aux != 0){
  Node_number++;
    cout << aux->getldr1() << endl;
    cout << aux->getldr2() << endl;
    cout << aux->getldr_dig() << endl;
    cout << aux->getstep_mot() << endl;
    cout << aux->gethr() << endl;
    cout << aux->getmin() << endl;
    cout << aux->getsec() << endl;
    cout << aux->getampm() << endl;
    cout << aux->getdd() << endl;
    cout << aux->getmm() << endl;
    cout << aux->getaa() << endl;
    aux = aux->getNext();
  }
  return Node_number;
}
