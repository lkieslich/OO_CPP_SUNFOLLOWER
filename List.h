
#pragma once

#include "Node.h"

class List {

  Node* head;

public:
  List();
  ~List();
  void insertBeforeFirst(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa);
  void insertAfterLast(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa);
  int readFirst(int &retldr1, int &retldr2, int &retldr_dig, int &retstep_mot, int &rethr, int &retmin, int &retsec, int &retampm, int &retdd, int &retmm, int &retaa);
  int removeFirst(int &retldr1, int &retldr2, int &retldr_dig, int &retstep_mot, int &rethr, int &retmin, int &retsec, int &retampm, int &retdd, int &retmm, int &retaa);
  void insertionSort(int value);
  int removeNode(int dat);
  int listAll();

};
