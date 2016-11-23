#include <iostream>

using namespace std;
const int tam = 250;

void leerlabe(int& F, int& C, char mlabe[tam][tam]){

   char carac;
    for(int i=0; i < F; i++)
    {
        for(int j=0; j < C; j++)
        {
            cin.get(carac);
            mlabe[i][j] = carac;
        }
    }
}

bool casillasol(int& fB, int& cB, int* solf, int* solc, int& tama){
   for(int i=0; i < tama; i++){
      if(solf[i] == fB && solc[i] == cB)
         return true;
   }
   return false;
}

void escribelabe(int& F, int& C, char mlabe[tam][tam], int* solf, int* solc, int& psol){

    if (psol > 0){
       for(int i=0; i<F; i++)
       {
           for(int j=0; j<C; j++)
           {
               if (mlabe[i][j]=='p')
                  cout << "#";
               else if (mlabe[i][j]=='e')
                  cout << "e";
               else if (mlabe[i][j]=='s')
                  cout << "s";
               else if (mlabe[i][j]=='l')
               {
                   if (casillasol(i, j, solf, solc, psol))
                     cout << ".";
                   else
                      cout << " ";
               }
           }
           cout << endl;
       }
    }else
       cout << "El laberinto no tiene solucion"<<endl;
}

void buscacarac(int& F, int& C, char mlabe[tam][tam], char carac, int& posf, int& posc){
   bool salida=false;
   for(int i=0; i<F && !salida; i++){
      for(int j=0; j<C && !salida; j++){
         if(mlabe[i][j]==carac)
         {
             posf=i;
             posc=j;
             salida=true;
         }
      }
   }
   if(!salida){
      posf= posc=-1;
   }
}

void resuelvelabe(int& F, int& C, char mlabe[tam][tam], int* solf, int* solc, bool mvisi[tam][tam],int& psol){
    int posf, posc;
    int posfs, poscs;
    int fil=0, col=0;
    

    buscacarac(F, C, mlabe, 'e', posf, posc);
    solf[0]=posf;
    solc[0]=posc;
   
    buscacarac(F, C, mlabe, 's', posfs, poscs);
   
    fil = solf[0];
    col = solc[0];
    psol = 1;
    mvisi[fil][col] = true;
    //Le he cambiado las condiciones al bucle, si son diferentes de la salida entra en el bucle. Tambien compruebo que psol > 0, esto quiere decir que estamos dando vueltas mientras haya camino donde ir, si no hay camino es que no tiene solucion.
    //Tambien he modificiado el contenido del bucle, quitando psol++ de cada condicion y poniendolo al final para no repetir codigo.
    //En la condicion else he cambiado que te dismininuye en 1 porque siempre vamos uno por delante, al ser una posicion sin camino ponemos los valores a -1 (como lo que te puse de buscacarac que te devolvia -1) y vuelve a disminuir para irnos al anterior (Que es una posicion con camino).
    //Al final del bucle te pongo psol++ que lo quite de cada condicion, y pongo en fil y col la ultima posicion valida de solf y solc que es una posicion con camino posible.
    while((posfs != fil || poscs != col) && psol > 0){
      
       if (!mvisi[fil][col+1] && mlabe[fil][col+1] != 'p')
        {
            mvisi[fil][col+1] = true;
            solf[psol] = fil;
            solc[psol] = col+1;

        }else if (!mvisi[fil][col-1] && mlabe[fil][col-1] != 'p')
        {
            mvisi[fil][col-1] = true;
            solf[psol] = fil;
            solc[psol] = col-1;          
 
        }else if  (!mvisi[fil+1][col] && mlabe[fil+1][col] != 'p')
        {
            mvisi[fil+1][col] = true;
            solf[psol] = fil+1;
            solc[psol] = col;            

        }else if  (!mvisi[fil-1][col] && mlabe[fil-1][col] != 'p')
        {
            mvisi[fil-1][col] = true;
            solf[psol] = fil-1;
            solc[psol] = col;          

        }else{
            psol--;
            solf[psol]=-1;
            solc[psol]=-1;
            psol--;
                                
        }
        fil = solf[psol];
        col = solc[psol];
        psol++;
    }
}

int main(int argc, int argv[])
{
    int F, C;

    cin >> F >> C ;
    F++;
    C++;
    char mlabe[tam][tam];

    int solf[tam*tam];
    int solc[tam*tam];

    bool mvisi[tam][tam];
    int psol=1;//Le he cambiado el nombre antes era tamsol.

    leerlabe(F, C, mlabe);
    
    resuelvelabe(F, C, mlabe, solf, solc,  mvisi, psol);
    
    escribelabe(F, C, mlabe, solf, solc, psol);
}
