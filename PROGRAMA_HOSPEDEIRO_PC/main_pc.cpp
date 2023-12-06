  #include <iostream>
  
  #include "List.h"
  #include "my_serial.h"
  
  using namespace std;
  
  int main(){
  
  List receiveList;

  unsigned char menu = '0';

  while(menu != '4')
  {

    cout << "1 - SOLICITAR DADOS PELA UART." << endl;
    cout << "2 - LISTAR LOG (FILA)." << endl;
    cout << "3 - STATUS DO SISTEMA" << endl;
    cout << "4 - SISTEMA DESATIVADO" << endl;
    cin >> menu;

    switch(menu)
    {
      case '1': 
      {
        char commdaux = 'l';
        int dadosR[11] = {0};// buffer temporário para recebimento dos dados enviados pela uart.
        

        if (commdaux == 'l')                                              
        { /*Tratamento da construção da fila com os dados recebidos*/
        mySerial serial[11]={"/dev/ttyUSB0", 9800};
        unsigned char SerialData[11] = {};  

        serial.Receive(SerialData, 11);

        
        //  int SerialData[11] = {255, 0, 0, 2, 11, 55, 23, 1, 6, 12, 23}; // exemplo de dados lidos pela UART
          for (int i = 0; i < 11; i++)
          {
            dadosR[i] = SerialData[i];
          }
          
          cout << " O dado recebido foi: " << dadosR[0] << ", " << dadosR[1] << ", " << dadosR[2] << ", " << dadosR[3] << ", " << dadosR[4] << ":" << dadosR[5] << ":" << dadosR[6] << "";
            if (dadosR[7] == 1){
              cout << "am ";
            }
            else{
              cout << "pm " << endl;  
            }
          cout << dadosR[8] << "/" << dadosR[9] << "/" << dadosR[10] << endl;
          receiveList.insertAfterLast(dadosR[0], dadosR[1], dadosR[2], dadosR[3], dadosR[4], dadosR[5], dadosR[6], dadosR[7], dadosR[8], dadosR[9], dadosR[10]);
          for (int i = 0; i < 11; i++)
          {
            dadosR[i] = 0;
          }
        }
       
        break;
      }
      case '2':
      receiveList.listAll();

      break;
        //cout << "Os eventos ocorridos nesse periodo foram: " << endl;
        //log1.listAll();

      case '3': // status do sistema
      { 
        int auxldr1, auxldr2, auxldr_dig, auxstep_mot, aux_hr, aux_min, aux_sec, aux_ampm, aux_dd, aux_mm, aux_aa;
        receiveList.readFirst(auxldr1, auxldr2, auxldr_dig, auxstep_mot, aux_hr, aux_min, aux_sec, aux_ampm, aux_dd, aux_mm, aux_aa);
        if (auxldr_dig == 1){
          cout << "Sistema estabilizado! Requisitos mínimos de iluminação atendidos!" << endl;
        }
        else{
          cout << "Nível de iluminação abaixo do ideal. Buscando posição ideal..." << endl;
            if(auxldr1 > auxldr2){
              cout << "Movendo sistema para a direita" << endl;
            }
            else if(auxldr1 < auxldr2){
              cout << "Movendo sistema para a esquerda" << endl;
            }
        }
        break;
      }
      case '4':
      { 
        cout << "Sistema desativado." << endl;
        break;
      }

      default:
      {
        cout << "1 - SOLICITAR DADOS PELA UART." << endl;
        cout << "2 - LISTAR LOG (FILA)." << endl;
        cout << "3 - STATUS DO SISTEMA" << endl;
        cout << "4 - SISTEMA DESATIVADO" << endl;
        cin >> menu;
      }
    }
    
  }

return 0 ;
  
}
