//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 6.2
// Kopiec
//
//============================================================================

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

//STRUKTURA DEFINIUJACA STOG
struct Stog
{
    int liczba;
    struct Stog *ojciec;
    struct Stog *lewo;
    struct Stog *prawo;
};

//STRUKTURA NA KOPIEC
struct Kopiec
{
	int poziom;
    int IloscElementow;
    struct Stog ***wysokosc;
};

//DODAWANIE PIERWSZEGO WEZLA
struct Stog *heap(int liczba)
{
    struct Stog *element = (struct Stog*)malloc(sizeof(struct Stog));
    
    element->liczba = liczba;
    element->ojciec = NULL;
    element->lewo = NULL;
    element->prawo = NULL;
    
    return element;
};


struct Kopiec *DrzewoKopiec(int maksimum)
{
    struct Kopiec *dana = (struct Kopiec *)malloc(sizeof(struct Kopiec));
    
    int i;
    dana->poziom = -1;
    dana->IloscElementow = 0;
    
    dana->wysokosc = (struct Stog ***)malloc(sizeof(struct Stog **) * maksimum);
    
    for (i = 0; i < maksimum; i++)
    {
        dana->wysokosc[i] = NULL;
    }
    return dana;
};

//FUNCKJA NA ZWRACANIE POTEG LICZBY 2
int PotegaLiczby2(int n)
{
    int i;
    int wynik;
    wynik = 1;
    
    for (i = 0; i < n; i++)
    {
        wynik = 2 * wynik;
    }
    return wynik;
}

//WYPISANIE DO KONSOLI KOPCA
void Wyswietl(struct Kopiec *korzen)
{
    int poziom, i;
    
    for (poziom = 0; poziom <= korzen->poziom; poziom++)
    {
        for (i = 0; i < PotegaLiczby2(poziom); i++)
        {
            if (korzen->wysokosc[poziom][i] != NULL)
			{
                printf("%d ", korzen->wysokosc[poziom][i]->liczba);
            }
        }
        cout << endl;
    }
    cout << endl;
}

//FUNKCJA NA DODANIE NOWEJ GALEZI
void DodajGalaz(struct Kopiec *korzen, int poziom)
{   int i;
    if (korzen->wysokosc[poziom] == NULL)
    {
        korzen->wysokosc[poziom] = (struct Stog **)malloc(sizeof(struct Stog *) * PotegaLiczby2(poziom));
        for(i=0;i<PotegaLiczby2(poziom);i++)
		{
            korzen->wysokosc[poziom][i] == NULL;
        }
        korzen->poziom = poziom;
        korzen->IloscElementow = 0;
    }
}

//FUNKCJA ABY WYPISAC W STYLU VLR (PRE-ORDER, PREFIKSOWE)
void Preorder(struct Stog *wezel)
{
    if (wezel)
    {
        printf("%d ", wezel->liczba);
        Preorder(wezel->lewo);
        Preorder(wezel->prawo);
    }
}

//FUNKCJA ABY WYPISAC W STYLU LVR (IN-ORDER, INFIKSOWE)
void Inorder(struct Stog *wezel)
{
    if (wezel)
    {
        Inorder(wezel->lewo);
        printf("%d ", wezel->liczba);
        Inorder(wezel->prawo);
    }
}

//FUNKCJA ABY WYPISAC W STYLU LRV (POST-ORDER, POSTFIKSOWE)
void Postorder(struct Stog *wezel)
{
    if (wezel)
    {
        Postorder(wezel->lewo);
        Postorder(wezel->prawo);
        printf("%d ", wezel->liczba);
    }
}

//FUNKCJA NA WYBRANIE SPOSOBU WYSWIETLANIA
void RodzajWyswietlania(struct Kopiec *korzen, int RodzajWyswietlania)
{
    struct Stog *temp;
    temp=korzen->wysokosc[0][0];
    if (RodzajWyswietlania==1)
    {
        Preorder(temp);
    }
    
    else if (RodzajWyswietlania==2)
    {
        Inorder(temp);
    }
    
    else if (RodzajWyswietlania==3)
    {
        Postorder(temp);
    }
}


//FUNKCJA NA USUNIECIE DANEJ GALEZI
void Usungalaz(struct Kopiec *korzen, int poziom)
{
    korzen->poziom = poziom - 1;
    if (korzen->poziom >= 0)
    {
        korzen->IloscElementow = PotegaLiczby2(korzen->poziom);
    }
}

//FUNCKJA NA DODAWANIE DO KOPCA
void DodajDoKopca(struct Kopiec *korzen, struct Stog *element)
{
    struct Stog *element2;
    struct Stog *ojciec;
    int liczba;
    if ((korzen->poziom == -1) || (korzen->IloscElementow >= PotegaLiczby2(korzen->poziom)))
    {
        DodajGalaz(korzen, korzen->poziom + 1);
    }
    korzen->wysokosc[korzen->poziom][korzen->IloscElementow] = element;
    korzen->IloscElementow++;
    if (korzen->poziom > 0)
    {
        ojciec = korzen->wysokosc[korzen->poziom - 1][(korzen->IloscElementow - 1) / 2];
        element->ojciec = ojciec;
        if (ojciec->lewo == NULL)
        {
            ojciec->lewo = element;
        }
        else
        {
            ojciec->prawo = element;
        }
        element2 = element;
        while (element2->ojciec != NULL)
        {
            if (element2->ojciec->liczba < element2->liczba)
            {
                liczba = element2->ojciec->liczba;
                element2->ojciec->liczba = element2->liczba;
                element2->liczba = liczba;
            }
            else
            {
                break;
            }
            element2 = element2->ojciec;
        }
    }
}

//FUNKCJA NA USUNIECIE PIERWSZEGO(MAKSYMALNEGO WEZLA)
struct Stog *UsunPierwszyWezel(struct Kopiec *korzen)
{
    struct Stog *element = NULL;
    struct Stog *element2;
    int liczba;
    if (korzen->poziom >= 0)
    {
        element = korzen->wysokosc[korzen->poziom][korzen->IloscElementow -1];
        korzen->wysokosc[korzen->poziom][korzen->IloscElementow -1] = NULL;
        korzen->IloscElementow--;
        if (element->ojciec)
        {
            if (element->ojciec->prawo != NULL)
            {
                element->ojciec->prawo = NULL;
            }
            else
            {
                element->ojciec->lewo = NULL;
            }
        }
        
        if (korzen->IloscElementow == 0)
        {
            Usungalaz(korzen, korzen->poziom);
        }
        
        if (korzen->poziom >= 0)
        {
            liczba = korzen->wysokosc[0][0]->liczba;
            korzen->wysokosc[0][0]->liczba = element->liczba;
            element->liczba = liczba;

            element2 = korzen->wysokosc[0][0];
            while (element2)
            {
                if ((element2->prawo != NULL && element2->prawo->liczba > element2->liczba) || (element2->lewo != NULL && element2->lewo->liczba > element2->liczba))
                {
                    if (element2->prawo && element2->prawo->liczba > element2->lewo->liczba)
                    {
                        liczba = element2->liczba;
                        element2->liczba = element2->prawo->liczba;
                        element2->prawo->liczba = liczba;
                        element2 = element2->prawo;
                    }
                    else
                    {
                        liczba = element2->liczba;
                        element2->liczba = element2->lewo->liczba;
                        element2->lewo->liczba = liczba;
                        element2 = element2->lewo;
                    }
                }
                else
                {
                    element2 = NULL;
                }
            }
        }
    }
    return element;
};

//MAIN
int main()
{    
    struct Kopiec *dana;
    struct Stog *element;
    
    //DEKLARACJA KOPCA O WIELKOSCI 10 ELEMENTOW
    dana = DrzewoKopiec(10);
    
    int opcja, wartosc;
    int petla = 1;
    
    //MENU 
    while (petla)
	{
        cout << "KOPIEC" << endl;
		cout << "Wybierz operacje:" << endl;
    	cout << "1. Dodaj wezel z klawiatury." << endl;
    	cout << "2. Usun maksymalny wezel." << endl;
    	cout << "3. Wyswietl kopiec." << endl;
   		cout << "4. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl;
   		cout << "5. Wyczysc konsole" << endl;
   		cout << "0. Koniec dzialania." << endl;
		
		cin >> opcja;
		
        switch (opcja)
        {
            case 0: //KONIEC PROGRAMU
            		cout << "Koniec pracy programu." << endl;
            		exit(0);
                	break;
                	
            case 1: //DODAWANIE DO WEZLA Z KLAWIATURY
               	 	cout << "1. Dodawanie wezla\n\nPodaj liczbe:" << endl;
                	scanf("%d", &wartosc);
                	DodajDoKopca(dana, heap(wartosc));
                	break;
                	
            case 2: //USUWANIE MAKSYMALNEGO WEZLA
                	printf("Usun wezel max kopca: ");
                	element = UsunPierwszyWezel(dana);
                	if(element != NULL)
                	{
                    	printf("%d ", element->liczba);
                	}
                	break;
            		
            case 3: //WYSWIETLANIE KOPCA
            		cout << "3. Wyswietl kopiec" << endl << endl;
            		Wyswietl(dana);
            		break;
            		
            case 4: //WYPISYWANIE WEZLOW KOPCA W KOLEJNOSCI VLR, LVR, LRV
            		cout << "4. Wypisanie wezlow kopca w kolejnosci VLR, LVR, LRV." << endl << endl;
                	cout << "VLR - pre-order, przejscie wzdluzne, prefiksowe" << endl;
                	RodzajWyswietlania(dana,1);
                	cout << endl;
    				cout << endl << "LVR - in-order, przejscie poprzeczne, infiksowe" << endl;
                	RodzajWyswietlania(dana,2);
                	cout << endl;
    				cout << endl << "LRV - post-oder, przejscie wsteczne, postfiksowe" << endl;
                	RodzajWyswietlania(dana,3);
                	cout << endl << endl;
                	break;
            case 5: //WYCZYSZCZENIE KONSOLI
					system("cls");
					break;
            default:
            		cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
                	break;
        }
    };
    
    return 0;
}
