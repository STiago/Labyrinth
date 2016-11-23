/*##################################################################
#
#  Práctica final
#  
#  Maria Victoria Santiago Alcalá
#
#
###################################################################*/

#include <iostream>

using namespace std;

class laberinto {
    private:
       static const int tam = 250;
       int fil;
       int col;
       char mlabe[tam][tam];
       int solf[tam*tam];//Te he modificado el tamaño a mas grande porque si no fallaba.
       int solc[tam*tam];//Te he modificado el tamaño a mas grande porque si no fallaba.
       int soluti;
       bool mvisi[tam][tam];

       bool casillasol(int& fB, int& cB){
          for(int i=0; i<soluti; i++){
              if(solf[i]==fB && solc[i]==cB)
                  return true;
           }
           return false;
       }

       void buscacarac(char carac, int& posf, int& posc){
           bool salida=false;
           for(int i=0; i < fil && !salida; i++){
              for(int j=0; j < col && !salida; j++){
                 if (mlabe[i][j] == carac)
                 {
                     posf=i;
                     posc=j;
                     salida=true;
                  }
               }
            }
            if(!salida){
            posf = posc = -1;
           }
       }
       //Te he añadido este metodo que lo que nos hace es eliminar la ultima posicion de sol, que corresponde a un camino no valido.
       void eliminaSolUlti(){soluti--;solf[soluti]=-1;solc[soluti]=-1;}
    public:
       laberinto():fil(0),col(0),soluti(0){}
       laberinto(int f, int c):fil(f),col(c),soluti(0){}
       int getFila(){return fil;}
       int getCol(){return col;}
       int getSolUti(){return soluti;}
       char getCarac(int f, int c){return mlabe[f][c];}
       bool getVisi(int f, int c){return mvisi[f][c];}
       int getSolf(int pos){return solf[pos];}
       int getSolc(int pos){return solc[pos];}
       int getSolfUlti(){return solf[soluti-1];}
       int getSolcUlti(){return solc[soluti-1];}
       void insertaLabe(int f, int c, char carac){ mlabe[f][c] = carac;}
       void visita(int f, int c){mvisi[f][c] = true;}
       void insertaSol(int f, int c){solf[soluti]=f; solc[soluti]=c; soluti++;}
       char getCaracImpre(int f, int c){
          char carac = NULL;

          if (mlabe[f][c]=='p')
               carac = '#';
          else if (mlabe[f][c]=='e')
               carac = 'e';
          else if (mlabe[f][c]=='s')
               carac = 's';
          else if (mlabe[f][c]=='l')
          {
             if (casillasol(f, c))
                 carac = '.';
             else
                 carac = ' ';
           }
           return carac;
       }
   //Este metodo es le mismo que el de laberinto.cpp pero adaptado a la clase y usando sus metodos.
   void resuelvelabe(){
      int posf, posc;
      int posfs, poscs;
      int filCam=0, colCam=0;
      int psol=1;

      buscacarac('e', posf, posc);
      insertaSol(posf, posc);
    
      buscacarac('s', posfs, poscs);
    
      filCam=getSolf(0);
      colCam=getSolc(0);
      visita(filCam, colCam);

      while((posfs != filCam || poscs != colCam) && soluti > 0){
         if (!getVisi(filCam, colCam+1) && getCarac(filCam, colCam+1) != 'p')
         {
            visita(filCam, colCam+1);
            insertaSol(filCam, colCam+1);
         }else if (!getVisi(filCam, colCam-1) && getCarac(filCam, colCam-1) != 'p')
         {
            visita(filCam, colCam-1);
            insertaSol(filCam, colCam-1);
         }else if (!getVisi(filCam+1, colCam) && getCarac(filCam+1, colCam) != 'p')
         {
            visita(filCam+1, colCam);
            insertaSol(filCam+1, colCam);
         }else if (!getVisi(filCam-1, colCam) && getCarac(filCam-1, colCam) != 'p')
         {
            visita(filCam-1, colCam);
            insertaSol(filCam-1, colCam);
         }else{
            eliminaSolUlti();           
         }
         filCam = getSolfUlti();
         colCam = getSolcUlti();
      }
   }
   //Este metodo te lo he añadido por si no quieres leer del main como te dije, llamas a este metodo y te lo lee.
   void impriemLabe(){      
      if (getSolUti() > 0){
         for(int i = 0; i < fil; i++)
         {  
            for(int j = 0; j < col; j++)
            {      
              cout << getCaracImpre(i, j);
            }      
            cout << endl;
         }
      }
      else
         cout << "El laberinto no tiene solucion"<<endl;
   }
    //Este metodo te lo he añadido por si no quieres escribir en el main como te dije, llamas a este metodo y te lo escribe.
   void leeLabe(){
      char carac;

      for(int i=0; i < fil; i++)
      {
         for(int j=0; j < col; j++)
         {
            cin.get(carac);
            insertaLabe(i, j, carac);
         }
      }
   }
};

int main(int argc, int argv[])
{
    int F, C;

    cin >> F >> C ;
    F++;
    C++;

   laberinto labe(F,C);
//Un ejemplo de leer en el main seria de esta forma, pero te he hecho una funcion en la clase que nos lo lee solo.
/*
   char carac;

      for(int i=0; i < F; i++)
      {
         for(int j=0; j < C; j++)
         {
            cin.get(carac);
            labe.insertaLabe(i, j, carac);
         }
      }
*/
   labe.leeLabe();

   labe.resuelvelabe();
      
   labe.impriemLabe(); 

//Un ejemplo de imprimir en el main seria de esta forma, pero te he hecho una funcion en la clase que nos lo imprime solo.
/*
   if (labe.getSolUti() > 0){
      for(int i = 0; i < fil; i++)
      {  
         for(int j = 0; j < col; j++)
         {      
           cout << labe.getCaracImpre(i, j);
         }      
         cout << endl;
      }
   }
   else
      cout << "El laberinto no tiene solucion"<<endl;
*/
}

