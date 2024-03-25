#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main()
{

    ifstream f("fisier.txt");
    int n;///numar de cuvinte
    f>>n;
    for(int i=1;i<=n;i++)
    {
        char cuvant[20];

        f>>cuvant;
         char cuvant_aux[20];
        for(int i=0;i<strlen(cuvant);i++)
        {
            cuvant_aux[i]=cuvant[strlen(cuvant)-1-i]; ///formam un cuvant auxiliar cu literele de la coada la cap si apoi vedem daca sunt egale
        }
       cuvant_aux[strlen(cuvant)]='\0';///(merge si fara linia asta)punem NULL la finalul scuvantului sa stim unde se opreste(mai pot ramane litere de la cuvintele an terioare daca cuvantul actual e mai mic

        if(strcmp(cuvant,cuvant_aux)==0)///daca sunt egale, cuvant e palindrom -> strcmp==- daca sunt egale
        {
            cout<<1<<endl;
        }
        else
        {
            cout<<0<<endl;
        }
    }
    return 0;
}
