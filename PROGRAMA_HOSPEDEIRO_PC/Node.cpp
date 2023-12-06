#include "Node.h"

// Constructor - initializes the node
//
Node::Node(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa, Node* nxt){
     LDR1 = ldr1;
     LDR2 = ldr2; 
     LDR_DIG = ldr_dig;
     STEP_MOT = step_mot;
     HR = hr;
     MIN = min;
     SEC = sec;
     AMPM = ampm;
     DD = dd;
     MM = mm;
     AA = aa;
     next = nxt;
}

// getVal returns the integer value stored in the node
//
int Node::getldr1(){
     return LDR1;
}
int Node::getldr2(){
     return LDR2;
}
int Node::getldr_dig(){
     return LDR_DIG;
}
int Node::getstep_mot(){
     return STEP_MOT;
}
int Node::gethr(){
     return HR;
}
int Node::getmin(){
     return MIN;
}
int Node::getsec(){
     return SEC;
}
int Node::getampm(){
     return AMPM;
}
int Node::getdd(){
     return DD;
}
int Node::getmm(){
     return MM;
}
int Node::getaa(){
     return AA;
}
// getNext returns a pointer for the next node in the linked list
//
Node* Node::getNext(){
     return next;
}

// setVal stores the integer value in the node
//
void Node::setVal(int ldr1, int ldr2, int ldr_dig, int step_mot, int hr, int min, int sec, int ampm, int dd, int mm, int aa){
     LDR1 = ldr1;
     LDR2 = ldr2; 
     LDR_DIG = ldr_dig;
     STEP_MOT = step_mot;
     HR = hr;
     MIN = min;
     SEC = sec;
     AMPM = ampm;
     DD = dd;
     MM = mm;
     AA = aa;

}


// setNext stores the pointer to the next node in the list in the "next" field
//
void Node::setNext(Node* nxt){
       next = nxt;
}
