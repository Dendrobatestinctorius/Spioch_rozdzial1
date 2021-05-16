// Śpioch Rozdział I. Gra fabularna
// © Adam Machowski
// GitHub Dendrobatestinctorius
//


#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;


//Postac i jej wartości
class Postac {
public:
	bool aktywnaP = false;
	bool gyce_talk = false;
	int Hidden_Path = 0, last_scn = 0;
	string name;
	string data, czas;
	fstream myfile;
	int randattr()
	{
		int attr = (rand() % 12) + 8;
		return attr;
	}
	void charcr()
	{
		aktywnaP = true;
	}
	void save()
	{
		SYSTEMTIME lt = { 0 };
		GetLocalTime(&lt);
		fstream myfile;
		myfile.open("save1.sfs");
		myfile << lt.wHour << ":" << lt.wMinute << " " << lt.wDay << "." << lt.wMonth << "." << lt.wYear << " " << Hidden_Path << " " << last_scn;
		myfile.close();
	}
	void load()
	{
		myfile.open("save1.sfs");
		if (!myfile.is_open())
			cout << "Unable to open file";

		else
		{
			myfile >> data >> czas >> Hidden_Path >> last_scn;

			myfile.close();
		}
	}

};


//deklaracje funkcji

//Sterowniki
void okno_rozmiar();
void kolor_txt(int color);
void ClearScreen();
void gotoxy(short x, short y);
//bool Dane_postaci(Postac& player);
int inpt();
bool zla_opcja();
//Główne okna
void Title();
void menu();
bool info();
bool NowaGra();
void pak();
//Fabuła
void wstep();
bool Scena_1(Postac& player);
bool Scena_2(Postac& player);
bool Scena_3(Postac& player);
void delay_txt(string text);

//Zmienne globalne
HANDLE  Console = GetStdHandle(STD_OUTPUT_HANDLE);
HWND console_wnd = GetConsoleWindow();


int main()
{
	okno_rozmiar();
	setlocale(LC_ALL, "pl_PL");
	srand(time(NULL));
	Title();
	menu();
	return 0;
}

//Definicje funkcji

//wielkość okna konsolo  !!Windows!!
void okno_rozmiar()
{
	RECT r;
	GetWindowRect(console_wnd, &r);
	MoveWindow(console_wnd, r.left, r.top, 1280, 720, TRUE);
}

//ustawienie koloru tekstu !!Windows!!
void kolor_txt(int color)
{
	SetConsoleTextAttribute(Console, color);
}

//Czyszczenie ekranu !!Windows!!
void ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	if (Console == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(Console, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(Console, (TCHAR)' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(Console, csbi.wAttributes, cellCount, homeCoords, &count))
		return;

	SetConsoleCursorPosition(Console, homeCoords);
	gotoxy(2, 41);
	kolor_txt(2);
	cout << "Dendrobates Studio ";
	kolor_txt(15);
	cout << " Adam Machowski";
}

//Ustawieni początku wiersza
void gotoxy(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(Console, pos);
}

// wywołanie danych postaci
/*bool Dane_postaci(Postac& player)
{
	kolor_txt(9);
	player.Postac_stat();
	kolor_txt(15);
	return false;
}*/

//Wprowadzanie opcji
int inpt()
{
	int opcja;
	kolor_txt(15);
	gotoxy(100, 38);
	cout << "                                                 ";
	gotoxy(100, 38);
	cout << ": ";
	cin >> opcja;
	if (cin.fail()) {
		do {
			gotoxy(100, 37);
			cout << "Niezła próba, ale to nie liczba, jeszcz raz      ";
			cin.clear();
			cin.ignore(1000, '\n');
			gotoxy(100, 38);
			cout << "                                                 ";
			gotoxy(100, 38);
			cout << ": ";
			cin >> opcja;
		} while (cin.fail());
	}

	return opcja;
}

//Opcja poza zakresem
bool zla_opcja()
{
	gotoxy(100, 37);
	cout << "nie ma takiego wyboru, spróbuj jeszcze raz       ";
	cin.clear();
	cin.ignore(1000, '\n');
	gotoxy(100, 38);
	cout << "                                                 ";
	return false;
}




//Powitanie
void Title()
{
	const string studio = "Dendrobates Studio";
	const string pres = "Przedstawia:";
	gotoxy(65, 19);
	kolor_txt(2);
	delay_txt(studio);
	gotoxy(68, 22);
	Sleep(1000);
	delay_txt(pres);
	Sleep(1500);
	ClearScreen();
	gotoxy(48, 10);
	kolor_txt(11);
	cout << "    _" << endl;
	gotoxy(48, 11);
	cout << "   //" << endl;
	gotoxy(48, 12);
	cout << " #####";
	gotoxy(48, 13);
	cout << "#     # #####  #  ####   ####  #    # " << endl;
	gotoxy(48, 14);
	cout << "#       #    # # #    # #    # #    # " << endl;
	gotoxy(48, 15);
	cout << " #####  #    # # #    # #      ###### " << endl;
	gotoxy(48, 16);
	cout << "      # #####  # #    # #      #    # " << endl;
	gotoxy(48, 17);
	cout << "#     # #      # #    # #    # #    # " << endl;
	gotoxy(48, 18);
	cout << " #####  #      #  ####   ####  #    # " << endl;
	gotoxy(48, 20);
	cout << "######                                                 ### " << endl;
	gotoxy(48, 21);
	cout << "#     #  ####  ###### #####  ###### #   ##   #  _       #  " << endl;
	gotoxy(48, 22);
	cout << "#     # #    #     #  #    #     #  #  #  #  # //       #  " << endl;
	gotoxy(48, 23);
	cout << "######  #    #    #   #    #    #   # #    # #//        #  " << endl;
	gotoxy(48, 24);
	cout << "#   #   #    #   #    #    #   #    # ###### #/         #  " << endl;
	gotoxy(48, 25);
	cout << "#    #  #    #  #     #    #  #     # #    # #          #  " << endl;
	gotoxy(48, 26);
	cout << "#     #  ####  ###### #####  ###### # #    # ######    ### " << endl;
	gotoxy(55, 28);
	kolor_txt(15);
	cout << "Gra Fabularna na podstawie prozy ";
	kolor_txt(9);
	cout << "Dawida Wąsowicza.";
	pak();
}


//Menu, główna pętla programu
void menu()
{
	int menuchoice = 1;
	bool ctrl = true;
	do {
		ClearScreen();
		kolor_txt(8);
		gotoxy(65, 6);
		cout << "#     #                      ";
		gotoxy(65, 7);
		cout << "##   ## ###### #    # #    # ";
		gotoxy(65, 8);
		cout << "# # # # #      ##   # #    # ";
		gotoxy(65, 9);
		cout << "#  #  # #####  # #  # #    # ";
		gotoxy(65, 10);
		cout << "#     # #      #  # # #    # ";
		gotoxy(65, 11);
		cout << "#     # #      #   ## #    # ";
		gotoxy(65, 12);
		cout << "#     # ###### #    #  ####  ";
		kolor_txt(15);
		gotoxy(68, 14);
		cout << "#==================#";
		gotoxy(68, 15);
		cout << "|   Nowa Gra [1]   |";
		gotoxy(68, 16);
		cout << "|==================|";
		gotoxy(68, 17);
		cout << "|  Informacje [9]  |";
		gotoxy(68, 18);
		cout << "|==================|";
		gotoxy(68, 19);
		cout << "| Zakończ Grę [0]  |";
		gotoxy(68, 20);
		cout << "#==================#";
		do {
			menuchoice = inpt();
			switch (menuchoice) {
			case 1:
				ctrl = NowaGra();
				break;
			case 9:
				ctrl = info();
				break;
			case 0:
				ctrl = true;
				break;
			default:
				ctrl = zla_opcja();
			}
		} while (ctrl == false);
	} while (menuchoice != 0);
}

bool info()
{
	ClearScreen();
	gotoxy(53, 15);
	cout << "Śpioch Rozdział I. Gra fabularna v0.0.1";
	gotoxy(53, 17);
	kolor_txt(2);
	cout << "Dendrobates Studio ";
	kolor_txt(15);
	cout << "Adam Machowski.";
	gotoxy(53, 19);
	cout << "Na podstawie prozy Dawid Wąsowicz.";
	gotoxy(53, 21);
	cout << "Sterowanie jest proste, poprzez podanie cyfry odpowiadającej wyborowi";
	pak();
	ClearScreen();
	return true;
}

bool NowaGra()
{
	ClearScreen();
	int NowaGra = 0;
	bool ctrl = true;
	Postac player;
	gotoxy(65, 14);
	cout << "#========================#";
	gotoxy(65, 15);
	cout << "|Rozpocznij przygodę! [1]|";
	gotoxy(65, 16);
	cout << "|========================|";
	gotoxy(65, 17);
	cout << "|    Wczytaj zapis[2]    |";
	gotoxy(65, 18);
	cout << "|========================|";
	gotoxy(65, 19);
	cout << "|    Wróć do Menu [0]    |";
	gotoxy(65, 20);
	cout << "#========================#";
	do {
		NowaGra = inpt();
		switch (NowaGra) {
		case 1:
			player.save();
			wstep();
			ctrl = Scena_1(player);
			if (player.Hidden_Path == 1)
				ctrl = Scena_3(player);
			break;
		case 2:
			player.load();
			if (player.last_scn != 0) {
				gotoxy(65, 25);
				cout << "Dostępny zapis z: " << player.data << " " << player.czas;
				gotoxy(65, 26);
				cout << "kontynuować? tak[1]/nie[2]";
				bool ctrl1 = true;
				do {
					int dalej = inpt();
					switch (dalej) {
					case 1:
						if (player.Hidden_Path == 1) {
							ctrl1 = Scena_3(player);
							ctrl = ctrl1;
						}
						break;
					case 2:
						gotoxy(65, 25);
						cout << "                                                                               ";
						gotoxy(65, 26);
						cout << "                                                                               ";
						player.data = " ";
						player.czas = " ";
						ctrl = false;
						break;
					default:
						ctrl1 = zla_opcja();
					}
					break;
				} while (ctrl1 == false);
			}
			else {
				gotoxy(65, 25);
				cout << "Brak zapisu gry";
				ctrl = false;
			}
			break;
		case 0:
			ctrl = true;
			break;
		default:
			ctrl = zla_opcja();
		}
	} while (ctrl == false);
	return ctrl;
}

void pak()
{
	gotoxy(100, 38);
	Sleep(250);
	kolor_txt(8);
	string text = "Nacisnij dowolny przycisk żeby kontynnuować";
	delay_txt(text);
	int ret = _getch();
}

void delay_txt(string text)
{
	size_t lng = text.length();
	for (int i = 0; i < lng; i++) {
		cout << text[i];
		Sleep(50);
	}
}


void wstep()
{
	ClearScreen();
	kolor_txt(15);
	gotoxy(26, 5);
	cout << "Wielki precel z pary wodnej wyglądał niezwykle majestatycznie gdy w świetle księżyca";
	gotoxy(20, 6);
	cout << "obserwowało się jak otacza całą Oktawie.  Zarazem bronił przed światem zewnętrznym jak i nie";
	gotoxy(20, 7);
	cout << "pozwalał się wydostać. Wiedziałem już, że i tak nie było po co się wydostawać. Chyba, że ktoś";
	gotoxy(20, 8);
	cout << "lubił patrzeć na niekończącą się powierzchnię stwardniałego waniliowego budyniu ze szczyptą";
	gotoxy(20, 9);
	cout << "cynamonu. Słońce właśnie wyłaniało się z zza wiecznej chmury oświetlając kolejno każdy z";
	gotoxy(20, 10);
	cout << "ośmiu pierścieni";
	gotoxy(20, 12);
	cout << "Mój świat jest daleko. Czy może raczej dawno? Wyruszam dzisiaj po to by nie przepadły";
	gotoxy(20, 13);
	cout << "resztki tego co mnie z nim wiążą. Tak naprawdę nie wierzyłem w to, że cokolwiek zostało z tego";
	gotoxy(20, 14);
	cout << "co ukryłem w skryte wbudowanej w podstawę mojej trumny. Jednakże musiałem spróbować.";
	gotoxy(20, 15);
	cout << "Dla siebie, by nie oszaleć od obcości Oktawii.";
	gotoxy(20, 17);
	Sleep(2000);
	string txt = "Te ponure rozmyślania przerwał mi Gyce.";
	delay_txt(txt);
	pak();
}

bool Scena_1(Postac &player)
{
	int scena1 = 0, scena1_1 = 0, scena1_1_1 = 0, scena1_1_1_1;
	bool ctrl = true, scena2 = false;
	ClearScreen();
	kolor_txt(8);
	gotoxy(20, 5);
	cout << "Gyce";
	kolor_txt(15);
	if (player.gyce_talk == false )
		cout << "– Jeżeli dobrze zrozumiałem zostawiłeś coś w kapliczce i teraz chcesz to odzyskać?";
	else
		cout << "– Jednak wróciłeś";
	gotoxy(60, 30);
	cout << "[1] - daj mi spokój                                                                 ";
	gotoxy(60, 31);
	cout << "[2] Odejdź bez słowa. Wciąż jesteś wściekły na to, że naraził twoje życie.          ";
	gotoxy(60, 32);
	cout << "[3] - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.";
	gotoxy(64, 33);
	cout << "Dobrą flaszkę piętnostoletniej whisky.                                              ";
	gotoxy(100, 36);
	cout << "Zakończ przygodę [0]";
	do {
		scena1 = inpt();
		switch (scena1) {
		case 1:
			gotoxy(20, 6);
			kolor_txt(2);
			cout << player.name;
			kolor_txt(15);
			cout << " - daj mi spokój";
			gotoxy(20, 7);
			cout << "Gyce zapatrzył się na chmurę, nie reagując na moją niegrzeczność. Nie odszedł jednak";
			gotoxy(60, 30);
			cout << "                                                                                    ";
			gotoxy(60, 31);
			cout << "[2] Odejdź bez słowa. Wciąż jesteś wściekły na to, że naraził twoje życie.          ";
			gotoxy(60, 32);
			cout << "[3] - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.";
			gotoxy(64, 33);
			cout << "Dobrą flaszkę piętnostoletniej whisky.                                              ";
			do{
				scena1_1 = inpt();
				switch (scena1_1) {
				case 2:
					ClearScreen();
					gotoxy(53, 19);
					cout << "Odchodzisz w stronę mostu na siódmy pierścień";
					pak();
					scena2 = Scena_2(player);
					if (scena2 == true) {
						Scena_1(player);
					}
					ctrl = true;
					break;
				case 3:
					gotoxy(20, 8);
					kolor_txt(2);
					cout << player.name;
					kolor_txt(15);
					cout << " - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.";
					gotoxy(20, 9);
					cout << "Dobrą flaszkę piętnostoletniej whisky.";
					gotoxy(20, 10);
					kolor_txt(8);
					cout << "Gyce";
					kolor_txt(15);
					cout << " - Właśnie o tym chciałem z Tobą porozmawiać – spuścił nieco wzrok – w ramach przeprosin za";
					gotoxy(20, 11);
					cout << "to moje oszustwo. Za to, ze nie powiedziałem ci o tym obozie –  spojrzał prosto w moją twarz - ";
					gotoxy(20, 12);
					cout << "pomogę ci odzyskać tą butelkę.";
					gotoxy(20, 13);
					cout << "Miejscowi porobili sobie ukryte drogi. Jak myślisz? Skąd mają mięso czy owoce? Z tego";
					gotoxy(20, 14);
					cout << "spłachetka ziemi tutaj, nie byliby się w stanie wyżywić. Pokaże Ci drogę, która doprowadzi Cię";
					gotoxy(20, 15);
					cout << "na ósmy pierścień niedaleko twojej kapliczki.";
					gotoxy(60, 30);
					cout << "[1] Posłuchaj Gycego.                                                               ";
					gotoxy(60, 31);
					cout << "[2] Nie słuchaj oszusta i wyrusz na wyprawę bez jego wskazówek                      ";
					gotoxy(60, 32);
					cout << "                                                                                    ";
					gotoxy(60, 33);
					cout << "                                                                                    ";
					do {
						scena1_1_1 = inpt();
						switch (scena1_1_1) {
						case 1:
							player.Hidden_Path = 1;
							gotoxy(20, 16);
							cout << "Gyce rozrysowuje patykiem w piachu pierścienie Oktawii i pokazuje Ci, gdzie znajdują się ukryte przejścia";
							gotoxy(20, 17);
							cout << "Z uwagą słuchasz tego co Gyce ma Ci do powiedzenia. Teraz posiadasz wiedzę o miejscach ukrytych przejść";
							gotoxy(20, 19);
							cout << "Twoje szanse na powodzenie, wzrosły.";
							gotoxy(60, 30);
							cout << "[1] Wyrusz na wyprawę                                                               ";
							gotoxy(60, 31);
							cout << "[2] Zapomnij o tym i wróć do osady                                                  ";
							gotoxy(60, 32);
							cout << "[3] Daj rzeźbiarzowi w twarz. Dalej masz do niego pretensje                         ";
							gotoxy(60, 33);
							cout << "                                                                                    ";
							do {
								scena1_1_1_1 = inpt();
								switch (scena1_1_1_1) {
								case 1:
									ClearScreen();
									gotoxy(53, 19);
									cout << "Tutaj rozpoczyna sie twoja przygoda. cdn.";
									pak();
									break;
								case 2:
									ClearScreen();
									gotoxy(50, 19);
									cout << "Zaprzestajesz prób dotarcia do swojej trumny. ";
									gotoxy(50, 20);
									cout << "Z czasem żal za utraconym powoduje, że nie widząc sensu dalszej egzystencji, ";
									gotoxy(50, 21);
									cout << "odchodzisz poza Oktawię i giniesz na pustkowiach.";
									pak();
									break;
								case 3:
									ClearScreen();
									gotoxy(50, 19);
									cout << "Uderzyłeś rzeźbiarza. ";
									gotoxy(50, 20);
									cout << "Ten zatoczył się, potknął i nieszczęśliwie zsunął się w głąb kanału.";
									gotoxy(50, 21);
									cout << "Ostatnim wymachem ręki, łapię za nogawkę twoich spodni i spadacie obaj w objęcia śmierci.";
									pak();
									break;
								case 0:
									player.save();
									ctrl = true;
									break;
								default:
									ctrl = zla_opcja();
								}
							} while (ctrl == false);
							break;
						case 2:
							ClearScreen();
							gotoxy(53, 19);
							cout << "Odchodzisz w stronę mostu na siódmy pierścień";
							pak();
							scena2 = Scena_2(player);
							if (scena2 == true) {
								Scena_1(player);
							}
							ctrl = true;
							break;
						case 0:
							player.save();
							ctrl = true;
							break;
						default:
							ctrl = zla_opcja();
						}
					}while (ctrl == false);
				case 0:
					player.save();
					ctrl = true;
					break;
				default:
					ctrl = zla_opcja();
				}
			}while (ctrl == false);
			break;
		case 2:
			ClearScreen();
			gotoxy(53, 19);
			cout << "Odchodzisz w stronę mostu na siódmy pierścień";
			pak();
			scena2 = Scena_2(player);
			if (scena2 == true) {
				Scena_1(player);
			}
			ctrl = true;
			break;
		case 3:
			gotoxy(20, 6);
			kolor_txt(2);
			cout << player.name;
			kolor_txt(15);
			cout << " - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.";
			gotoxy(20, 7);
			cout << "Dobrą flaszkę piętnostoletniej whisky.";
			gotoxy(20, 8);
			kolor_txt(8);
			cout << "Gyce";
			kolor_txt(15);
			cout << " - Właśnie o tym chciałem z Tobą porozmawiać – spuścił nieco wzrok – w ramach przeprosin za";
			gotoxy(20, 9);
			cout << "to moje oszustwo. Za to, ze nie powiedziałem ci o tym obozie –  spojrzał prosto w moją twarz - ";
			gotoxy(20, 10);
			cout << "pomogę ci odzyskać tą butelkę.";
			gotoxy(20, 11);
			cout << "Miejscowi porobili sobie ukryte drogi. Jak myślisz? Skąd mają mięso czy owoce? Z tego";
			gotoxy(20, 12);
			cout << "spłachetka ziemi tutaj, nie byliby się w stanie wyżywić. Pokaże Ci drogę, która doprowadzi Cię";
			gotoxy(20, 13);
			cout << "na ósmy pierścień niedaleko twojej kapliczki.";
			gotoxy(60, 30);
			cout << "[1] Posłuchaj Gycego.                                                               ";
			gotoxy(60, 31);
			cout << "[2] Nie słuchaj oszusta i wyrusz na wyprawę bez jego wskazówek                      ";
			gotoxy(60, 32);
			cout << "                                                                                    ";
			gotoxy(60, 33);
			cout << "                                                                                    ";
			do {
				scena1_1_1 = inpt();
				switch (scena1_1_1) {
				case 1:
					player.Hidden_Path = 1;
					gotoxy(20, 14);
					cout << "Gyce rozrysowuje patykiem w piachu pierścienie Oktawii i pokazuje Ci, gdzie znajdują się ukryte przejścia";
					gotoxy(20, 15);
					cout << "Z uwagą słuchasz tego co Gyce ma Ci do powiedzenia. Teraz posiadasz wiedzę o miejscach ukrytych przejść";
					gotoxy(20, 17);
					cout << "Twoje szanse na powodzenie, wzrosły.";
					gotoxy(60, 30);
					cout << "[1] Wyrusz na wyprawę                                                               ";
					gotoxy(60, 31);
					cout << "[2] Zapomnij o tym i wróć do osady                                                  ";
					gotoxy(60, 32);
					cout << "[3] Daj rzeźbiarzowi w twarz. Dalej masz do niego pretensje                         ";
					gotoxy(60, 33);
					cout << "                                                                                    ";
					do {
						scena1_1_1_1 = inpt();
						switch (scena1_1_1_1) {
						case 1:
							ClearScreen();
							gotoxy(53, 19);
							cout << "Tutaj rozpoczyna sie twoja przygoda. cdn.";
							pak();
							break;
						case 2:
							ClearScreen();
							gotoxy(50, 19);
							cout << "Zaprzestajesz prób dotarcia do swojej trumny. ";
							gotoxy(50, 20);
							cout << "Z czasem żal za utraconym powoduje, że nie widząc sensu dalszej egzystencji, ";
							gotoxy(50, 21);
							cout << "odchodzisz poza Oktawię i giniesz na pustkowiach.";
							pak();
							break;
						case 3:
							ClearScreen();
							gotoxy(50, 19);
							cout << "Uderzyłeś rzeźbiarza. ";
							gotoxy(50, 20);
							cout << "Ten zatoczył się, potknął i nieszczęśliwie zsunął się w głąb kanału.";
							gotoxy(50, 21);
							cout << "Ostatnim wymachem ręki, łapię za nogawkę twoich spodni i spadacie obaj w objęcia śmierci.";
							pak();
							break;
						case 0:
							player.save();
							ctrl = true;
							break;
						default:
							ctrl = zla_opcja();
						}
					} while (ctrl == false);
					break;
				case 2:
					ClearScreen();
					gotoxy(53, 19);
					cout << "Odchodzisz w stronę mostu na siódmy pierścień";
					pak();
					scena2 = Scena_2(player);				
						if (scena2 == true) {
							Scena_1(player);
						}
					ctrl = true;
					break;
				case 0:
					player.save();
					ctrl = true;
					break;
				default:
					ctrl = zla_opcja();
				}
			} while (ctrl == false);
			break;
		case 0:
			player.save();
			ctrl = true;
			break;
		default:
			ctrl = zla_opcja();
		}
	} while (ctrl == false);
	return ctrl;
}



bool Scena_2(Postac &player)
{
	ClearScreen();
	kolor_txt(15);
	bool ctrl = true;
	int scena2 = 0;
	gotoxy(20, 5);
	cout << "Most na śiódmy pierścień";
	gotoxy(60, 30);
	cout << "[1] Wróć i porozmawiaj z Gycem";
	gotoxy(60, 31);
	cout << "[2] Wyrusz na wyprawę";
	gotoxy(100, 36);
	cout << "Zakończ przygodę [0]";
	do {
		scena2 = inpt();
		switch (scena2) {
		case 1:
			player.gyce_talk = true;
			return true;
		case 2:
			ClearScreen();
			gotoxy(20, 19);
			cout << "pełen negatywnych emocji związanych z rzeźbiarzem wkraczasz na wąską deską stanowiącą przejście na drugą stronę";
			gotoxy(20, 20);
			cout << "Jesteś poddenerwowany i zdekoncentrowany. Spadasz i giniesz w wodach między siódmym, a ósmym pierścieniem";
			pak();
			break;
		}
	} while (ctrl == false);
	return false;
}

bool Scena_3(Postac& player)
{
	ClearScreen();
	kolor_txt(15);
	gotoxy(20, 19);
	cout << " Mając wiedzę o tajemnych przejściach stajesz przed mostem na krąg siódmy.";
	player.last_scn = 3;
	player.save();
	pak();
	return true;
}