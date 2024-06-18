//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 6.1
// Drzewo BST
//
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

//SPACJA O WIELKOSCI 10 (POTRZEBNE DO RYSOWANIA DRZEWA)
#define SPACE 10

using namespace std;

//STRUKTURA DRZEWA BST
struct DrzewoBST
{
	int wartosc;
  	struct DrzewoBST *lewo;
  	struct DrzewoBST *prawo;
};

//FUNCKJA ZEBY SPRAWDZIC CZY DRZEWO JEST PUSTE
int CzyPusteDrzewoBST(struct DrzewoBST *korzen)
{
    if (korzen == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//FUNCKJA SPRAWDA CZY SZUKANA DANA JEST W DRZEWIE, JESLI TAK, ZWROCI TRUE, JESLI NIE, ZWROCI FALSE
bool CzyJestWDrzewie(struct DrzewoBST* korzen, int dana)
{
    if(korzen == NULL)
    {
        return false;
    }
    if(korzen->wartosc == dana)
    {
        return true;
    }
    bool szukaj1 = CzyJestWDrzewie(korzen->lewo, dana);
    if(szukaj1)
    {
        return true;
    }

    bool szukaj2 = CzyJestWDrzewie(korzen->prawo, dana);
    return szukaj2;
}

//FUNKCJA NA STWORZENIE PIERWSZEGO WEZLU
struct DrzewoBST* Wezel(int dana)
{
    struct DrzewoBST* tymczasowa = (struct DrzewoBST*)malloc(sizeof(struct DrzewoBST));

    tymczasowa->wartosc = dana;
    tymczasowa->lewo = NULL;
    tymczasowa->prawo = NULL;

    return tymczasowa;
};

//FUNCKJA NA DODAWANIE DO DRZEWA
struct DrzewoBST* DodajDoDrzewa(struct DrzewoBST* korzen, int dana)
{
    if(korzen == NULL)
    {
        return Wezel(dana);
    }
    if(dana < korzen->wartosc)
    {
        korzen->lewo = DodajDoDrzewa(korzen->lewo, dana);
    }
    else if(dana > korzen->wartosc)
    {
        korzen->prawo = DodajDoDrzewa(korzen->prawo, dana);
    }
    return korzen;
};


//FUNCKJA NA WYSZUKIWANIE DANEGO ELEMENTU Z DRZEWA I WYPISANIE SCIEZKI DO SZUKANEJ DANEJ
struct DrzewoBST* Wyszukaj(struct DrzewoBST *korzen, int dana)
{
    if(korzen == NULL || korzen->wartosc == dana)
    {
        cout << korzen ->wartosc;
        return korzen;
    }
    else if(dana > korzen->wartosc)
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->prawo, dana);
    }
    else
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->lewo, dana);
    }
};

//FUNKCJA NA ZNALEZENIE NAJMNIEJSZEGO WEZLA (POTRZEBNE DO USUWANIA)
struct DrzewoBST* NajmniejszyWezel(struct DrzewoBST* drzewko)
{
    struct DrzewoBST* tymczasowa = drzewko;

    while(tymczasowa && tymczasowa->lewo != NULL)
    {
        tymczasowa = tymczasowa->lewo;
    }
    return tymczasowa;
};

//FUNKCJA NA ZNALEZIENIE MAKSA W DRZEWIE
struct DrzewoBST* NajwiekszyWezel(struct DrzewoBST* drzewko)
{
    struct DrzewoBST* tymczasowa = drzewko;

    while(tymczasowa && tymczasowa->prawo != NULL)
    {
        tymczasowa = tymczasowa->prawo;
    }
    return tymczasowa;
};

//FUNKCJA NA USUNIECIE DANEGO ELEMENTU Z DRZEWA I ZWROCENIE STRUKTURY PO USUNIECIU DRZEWA
struct DrzewoBST* UsunWezel(struct DrzewoBST* korzen, int dana)
{
    if(korzen == NULL)
    {
        return korzen;
    }
    if(dana < korzen->wartosc)
    {
        korzen->lewo = UsunWezel(korzen->lewo, dana);
    }
    else if(dana > korzen->wartosc)
    {
        korzen->prawo = UsunWezel(korzen->prawo, dana);
    }
    else
    {
        if(korzen->lewo == NULL && korzen->prawo == NULL)
        {
            return NULL;
        }
        else if(korzen->lewo == NULL)
        {
            struct DrzewoBST* tymczasowa = korzen->prawo;
            free(korzen);
            return tymczasowa;
        }
        else if(korzen->prawo == NULL)
        {
            struct DrzewoBST* tymczasowa = korzen->lewo;
            free(korzen);
            return tymczasowa;
        }
        
        struct DrzewoBST* tymczasowa = NajmniejszyWezel(korzen->prawo);
        korzen->wartosc = tymczasowa->wartosc;
        korzen->prawo = UsunWezel(korzen->prawo, tymczasowa->wartosc);
    }
    return korzen;
};

//FUNCKJA NA RYSOWANIE DRZEWA WRAZ ODSTEPAMI ABY DRZEWO LADNIE WYGLADALO
void RysowanieDrzewa(struct DrzewoBST* korzen, int spacja)
{
    if (korzen == NULL)
    {
        return;
    }
    spacja = spacja + SPACE;
    RysowanieDrzewa(korzen->prawo, spacja);
    cout<<endl;
    for (int i = SPACE; i < spacja; i++)
    {
        cout<<" ";
    }
    cout<<korzen->wartosc<<endl;
    RysowanieDrzewa(korzen->lewo, spacja);
}

//FUNKCJA ABY WYPISAC W STYLU VLR (PRE-ORDER, PREFIKSOWE)
void Preorder(struct DrzewoBST *r)
{
    if (r == NULL)
    {
		return;
	}

    cout << r -> wartosc << " ";
    Preorder(r -> lewo);
    Preorder(r -> prawo);
}

//FUNKCJA ABY WYPISAC W STYLU LVR (IN-ORDER, INFIKSOWE)
void Inorder(struct DrzewoBST *r)
{
    if (r == NULL)
    {
    	return;
	}
    Inorder(r -> lewo);
    cout << r -> wartosc << " ";
    Inorder(r -> prawo);
}

//FUNKCJA ABY WYPISAC W STYLU LRV (POST-ORDER, POSTFIKSOWE)
void Postorder(struct DrzewoBST *r)
{
    if (r == NULL)
    {
		return;
	}
    Postorder(r -> lewo);
    Postorder(r -> prawo);
    cout << r -> wartosc << " ";
}

//FUNCKJA USUWA DANE Z DRZEWA
void UsunCaleDrzewoBST(struct DrzewoBST* korzen)
{
    if (korzen == NULL)
    {
       return;
    }

    UsunCaleDrzewoBST(korzen->lewo);
    UsunCaleDrzewoBST(korzen->prawo);
    free(korzen);
}

//FUNKCJA WYWOLUJE INNA FUNKCJE DO USUWANIE DRZEWA I ZAMIENIA USUNIETE ZNAKI NA NULL
void UsunDrzewoBST(struct DrzewoBST** korzen)
{
    UsunCaleDrzewoBST(*korzen);
    *korzen = NULL;
}

//MAIN
int main()
{
	struct DrzewoBST* korzen = NULL;
	int opcja, wartosc;
	int petla = 1;
	
	while(petla)
	{
		system("cls");
		cout << "Drzewo BST" << endl;
		cout << "Wybierz operacje:" << endl;
    	cout << "1. Dodaj wezel z klawiatury." << endl;
    	cout << "2. Usun wezel." << endl;
    	cout << "3. Szukaj wezla." << endl;
    	cout << "4. Usun cale drzewo." << endl;
    	cout << "5. Rysuj drzewo." << endl;
   		cout << "6. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl;
   		cout << "0. Koniec dzialania." << endl;
		cout << endl;
		
    	cin >> opcja;

		system("cls");
    	switch (opcja)
		{
    	case 0: //KONIEC PROGRAMU
            	cout << "Koniec pracy programu." << endl;
            	exit(0);
      			break;
    	case 1: //DODAWANIE DO WEZLA Z KLAWIATURY
      			cout << "1. Dodawanie wezla\n\nPodaj liczbe:" << endl;
	      		cin >> wartosc;
                korzen = DodajDoDrzewa(korzen, wartosc);
	      		cout<<endl;
    			break;
    	case 2: //USUWANIE DANEGO WEZLA Z DRZEWA
    			if(CzyPusteDrzewoBST(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
                    cout << "2. Usun wezel \n\nPodaj wezel do usuniecia" << endl;
                    cin >> wartosc;
                    cout << endl;
                    if(CzyJestWDrzewie(korzen, wartosc))
                    {
                        korzen = UsunWezel(korzen, wartosc);
                        cout << "Usunieto pomyslnie wezel." << endl << endl;
                    }
                    else
                    {
                        cout << "Wprowadzony wezel nie znajduje sie w liscie." << endl << endl;
                    }

      			}
      			break;
    	case 3: //SZUKANIE WEZLA W DRZEWIE
    			if(CzyPusteDrzewoBST(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
                    cout << "3. Szukaj wezla\n\nPodaj szukany wezel i wyswietl sciezke do niego." << endl;
                    cin >> wartosc;
                    cout << endl;
                    if(CzyJestWDrzewie(korzen, wartosc))
                    {
                    	cout << "Sciezka:" << endl;
                        Wyszukaj(korzen, wartosc);
                        cout << endl << endl;
                    }
                    else
                    {
                        cout << "Podany wezel nie znajduje sie w drzewie." << endl << endl;
                    }
                }
      			break;
      	case 4: //USUWANIE CALEGO DRZEWA
                if(CzyPusteDrzewoBST(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
                else
                {
                    cout << "4. USUWANIE CALEGO DRZEWA." << endl << endl;
                    UsunDrzewoBST(&korzen);
                    cout << "Pomyslnie usunieto cale drzewo." << endl << endl;
                }
      			break;
      	case 5: //RYSOWANIE DRZEWA
      			if(CzyPusteDrzewoBST(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
      			cout << "5. RYSOWANIE DRZEWA." << endl << endl;
     			RysowanieDrzewa(korzen, 0);
      			cout << endl;
      			}
      			break;
    	case 6: //WYPISYWANIE WEZLOW DRZEWA W KOLEJNOSCI VLR, LVR, LRV
    			if(CzyPusteDrzewoBST(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
    			cout << "6. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl << endl;
    			cout << "VLR - pre-order, przejscie wzdluzne, prefiksowe" << endl;
      	      	Preorder(korzen);
      	      	cout << endl;
    			cout << endl << "LVR - in-order, przejscie poprzeczne, infiksowe" << endl;
      	      	Inorder(korzen);
      	      	cout << endl;
    			cout << endl << "LRV - post-oder, przejscie wsteczne, postfiksowe" << endl;
      	     	Postorder(korzen);
      	     	cout << endl << endl;
      	     	}
    			break;
    	default:
      			cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
    	}
    system("pause");
};

return 0;
}

