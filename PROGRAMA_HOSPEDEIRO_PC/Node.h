#pragma once
#include <iostream>

using namespace std;
class Node {

    int LDR1;
    int LDR2;
    int LDR_DIG;
    int STEP_MOT;
    int HR;
    int MIN;
    int SEC;
    int AMPM;
    int DD;
    int MM;
    int AA;
    Node* next;

  public:
         
    Node(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa, Node* nxt);
    int getldr1();
    int getldr2();
    int getldr_dig();
    int getstep_mot();
    int gethr();
    int getmin();
    int getsec();
    int getampm();
    int getdd();
    int getmm();
    int getaa();
    Node* getNext();
    void setVal(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa);

    void setNext(Node* nxt);
};
