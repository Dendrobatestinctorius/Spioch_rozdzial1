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
	const string name = "Bin";
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
		myfile.open("save1.sfs", std::ofstream::out | std::ofstream::trunc);
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

class graph {
private:
	HANDLE  Console = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND console_wnd = GetConsoleWindow();
public:

	void okno_rozmiar()
	{
		RECT r;
		GetWindowRect(console_wnd, &r);
		MoveWindow(console_wnd, r.left, r.top, 1280, 720, TRUE);
	}

	void printdb(string text, bool delay, short x, short y, int color) {
		SetConsoleTextAttribute(Console, color);
		COORD pos = { x, y };
		SetConsoleCursorPosition(Console, pos);
		if (delay == true) {
			size_t lng = text.length();
			for (int i = 0; i <= lng; i++) {
				cout << text[i];
				Sleep(50);
			}
		}
		else {
			cout << text;
		}
	}

	void pak()
	{
		Sleep(2000);
		printdb("Nacisnij dowolny przycisk żeby kontynnuować", true, 100, 30, 8);
		int ret = _getch();
	}
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

		printdb("Dendrobates Studio ", false, 2, 41, 2);
		printdb(" Adam Machowski", false, 22, 41, 15);
	}
};


//deklaracje funkcji

//Sterowniki
int inpt();
bool zla_opcja();

//Główne okna
void Title();
void menu();
bool info();
bool NowaGra();

//Fabuła
void wstep();
bool Scena_1();
bool Scena_2();
bool Scena_3();


//Obiekty globalne
Postac player;
graph grp;


int main()
{
	grp.okno_rozmiar();
	setlocale(LC_ALL, "pl_PL");
	srand(time(NULL));
	Title();
	menu();
	return 0;
}

//Definicje funkcji



//Wprowadzanie opcji
int inpt()
{
	int opcja;
	grp.printdb("                                                 ", false, 100, 38, 15);
	grp.printdb(": ", false, 100, 38, 15);
	cin >> opcja;
	if (cin.fail()) {
		do {
			grp.printdb("Niezła próba, ale to nie liczba, jeszcz raz      ", false, 100, 37, 15);
			cin.clear();
			cin.ignore(1000, '\n');
			grp.printdb("                                                 ", false, 100, 38, 15);
			grp.printdb(": ", false, 100, 38, 15);
			cin >> opcja;
		} while (cin.fail());
	}

	return opcja;
}

//Opcja poza zakresem
bool zla_opcja()
{
	grp.printdb("nie ma takiego wyboru, spróbuj jeszcze raz       ", false, 100, 37, 15);
	cin.clear();
	cin.ignore(1000, '\n');
	grp.printdb("                                                 ", false, 100, 38, 15);
	return false;
}



//Powitanie
void Title()
{
	grp.printdb("Dendrobates Studio", true, 65, 19, 2);
	Sleep(1000);
	grp.printdb("Przedstawia:", true, 68, 22, 2);
	Sleep(1000);
	Sleep(1500);
	grp.ClearScreen();
	grp.printdb("    _", false, 48, 10, 11);
	grp.printdb("   //", false, 48, 11, 11);
	grp.printdb(" #####", false, 48, 12, 11);
	grp.printdb("#     # #####  #  ####   ####  #    # ", false, 48, 13, 11);
	grp.printdb("#       #    # # #    # #    # #    # ", false, 48, 14, 11);
	grp.printdb(" #####  #    # # #    # #      ###### ", false, 48, 15, 11);
	grp.printdb("      # #####  # #    # #      #    # ", false, 48, 16, 11);
	grp.printdb("#     # #      # #    # #    # #    # ", false, 48, 17, 11);
	grp.printdb(" #####  #      #  ####   ####  #    # ", false, 48, 18, 11);
	grp.printdb("######                                                 ### ", false, 48, 20, 11);
	grp.printdb("#     #  ####  ###### #####  ###### #   ##   #  _       #  ", false, 48, 21, 11);
	grp.printdb("#     # #    #     #  #    #     #  #  #  #  # //       #  ", false, 48, 22, 11);
	grp.printdb("######  #    #    #   #    #    #   # #    # #//        #  ", false, 48, 23, 11);
	grp.printdb("#   #   #    #   #    #    #   #    # ###### #/         #  ", false, 48, 24, 11);
	grp.printdb("#    #  #    #  #     #    #  #     # #    # #          #  ", false, 48, 25, 11);
	grp.printdb("#     #  ####  ###### #####  ###### # #    # ######    ### ", false, 48, 26, 11);
	grp.printdb("Gra Fabularna na podstawie prozy ", true, 55, 28, 15);
	grp.printdb("Dawida Wąsowicza.", true, 89, 28, 9);
	grp.pak();
}


//Menu, główna pętla programu
void menu()
{
	int menuchoice = 1;
	bool ctrl = true;
	do {
		grp.ClearScreen();
		grp.printdb("#     #                      ", false, 65, 6, 8);
		grp.printdb("##   ## ###### #    # #    # ", false, 65, 7, 8);
		grp.printdb("# # # # #      ##   # #    # ", false, 65, 8, 8);
		grp.printdb("#  #  # #####  # #  # #    # ", false, 65, 9, 8);
		grp.printdb("#     # #      #  # # #    # ", false, 65, 10, 8);
		grp.printdb("#     # #      #   ## #    # ", false, 65, 11, 8);
		grp.printdb("#     # ###### #    #  ####  ", false, 65, 12, 8);
		grp.printdb("#==================#", false, 68, 14, 15);
		grp.printdb("|   Nowa Gra [1]   |", false, 68, 15, 15);
		grp.printdb("|==================|", false, 68, 16, 15);
		grp.printdb("|  Informacje [9]  |", false, 68, 17, 15);
		grp.printdb("|==================|", false, 68, 18, 15);
		grp.printdb("| Zakończ Grę [0]  |", false, 68, 19, 15);
		grp.printdb("#==================#", false, 68, 20, 15);
		do {
			menuchoice = inpt();
			switch (menuchoice) {
			case 1:
				ctrl = NowaGra();
				break;
			case 9:
				info();
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

void info()
{
	grp.ClearScreen();
	grp.printdb("Śpioch Rozdział I. Gra fabularna v0.0.1", false, 53, 15, 15);
	grp.printdb("Dendrobates Studio ", false, 53, 17, 2);
	grp.printdb("Adam Machowski.", false, 73, 17, 15);
	grp.printdb("Na podstawie prozy Dawida Wąsowicza.", false, 53, 19, 15);
	grp.printdb("Sterowanie jest proste, poprzez podanie cyfry odpowiadającej wyborowi", false, 53, 21, 15);
	grp.pak();
	grp.ClearScreen();
}

bool NowaGra()
{
	grp.ClearScreen();
	int NowaGra = 0;
	bool ctrl = true;
	grp.printdb("#========================#", false, 68, 14, 15);
	grp.printdb("|Rozpocznij przygodę! [1]|", false, 68, 15, 15);
	grp.printdb("|========================|", false, 68, 16, 15);
	grp.printdb("|    Wczytaj zapis[2]    |", false, 68, 17, 15);
	grp.printdb("|========================|", false, 68, 18, 15);
	grp.printdb("|    Wróć do Menu [0]    |", false, 68, 19, 15);
	grp.printdb("#========================#", false, 68, 20, 15);
	do {
		NowaGra = inpt();
		switch (NowaGra) {
		case 1:
			player.charcr();
			player.save();
			wstep();
			ctrl = Scena_1();
			if (player.Hidden_Path == 1)
				ctrl = Scena_3();
			break;
		case 2:
			player.load();
			if (player.last_scn != 0) {
				grp.printdb("Dostępny zapis z: ", false, 65, 25, 15);
				cout << player.data << " " << player.czas;
				grp.printdb("kontynuować? tak[1]/nie[2]", false, 65, 26, 15);
				bool ctrl1 = true;
				do {
					int dalej = inpt();
					switch (dalej) {
					case 1:
						if (player.Hidden_Path == 1) {
							ctrl1 = Scena_3();
							ctrl = ctrl1;
						}
						break;
					case 2:
						grp.printdb("                                                                               ", false, 65, 25, 15);
						grp.printdb("                                                                               ", false, 65, 26, 15);
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
				grp.printdb("Brak zapisu gry",false, 65, 25, 15);
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


void wstep()
{
	grp.ClearScreen();
	grp.printdb("Wielki precel z pary wodnej wyglądał niezwykle majestatycznie gdy w świetle księżyca", false, 20, 5, 15);
	grp.printdb("obserwowało się jak otacza całą Oktawie.  Zarazem bronił przed światem zewnętrznym jak i nie", false, 20, 6, 15);
	grp.printdb("pozwalał się wydostać. Wiedziałem już, że i tak nie było po co się wydostawać. Chyba, że ktoś", false, 20, 7, 15);
	grp.printdb("lubił patrzeć na niekończącą się powierzchnię stwardniałego waniliowego budyniu ze szczyptą", false, 20, 8, 15);
	grp.printdb("cynamonu. Słońce właśnie wyłaniało się z zza wiecznej chmury oświetlając kolejno każdy z", false, 20, 9, 15);
	grp.printdb("ośmiu pierścieni", false, 20, 10, 15);
	grp.printdb("Mój świat jest daleko. Czy może raczej dawno? Wyruszam dzisiaj po to by nie przepadły", false, 20, 12, 15);
	grp.printdb("resztki tego co mnie z nim wiążą. Tak naprawdę nie wierzyłem w to, że cokolwiek zostało z tego", false, 20, 13, 15);
	grp.printdb("co ukryłem w skryte wbudowanej w podstawę mojej trumny. Jednakże musiałem spróbować.", false, 20, 14, 15);
	grp.printdb("Dla siebie, by nie oszaleć od obcości Oktawii.", false, 20, 15, 15);
	Sleep(2000);
	grp.printdb("Te ponure rozmyślania przerwał mi Gyce.", true, 20, 17, 15);
	grp.pak();
}

bool Scena_1()
{
	int scena1 = 0, scena1_1 = 0, scena1_1_1 = 0, scena1_1_1_1;
	bool ctrl = true, scena2 = false;
	grp.ClearScreen();
	grp.printdb("Gyce", false, 20, 5, 8);
	if (player.gyce_talk == false )
		grp.printdb(" – Jeżeli dobrze zrozumiałem zostawiłeś coś w kapliczce i teraz chcesz to odzyskać?", false, 24, 5, 15);
	else
		grp.printdb(" – Jednak wróciłeś", false, 24, 5, 15);
	grp.printdb("[1] - daj mi spokój                                                                 ", false, 60, 30, 15);
	grp.printdb("[2] Odejdź bez słowa. Wciąż jesteś wściekły na to, że naraził twoje życie.          ", false, 60, 31, 15);
	grp.printdb("[3] - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.", false, 60, 32, 15);
	grp.printdb("Dobrą flaszkę piętnostoletniej whisky.                                              ", false, 64, 33, 15);
	grp.printdb("Zakończ przygodę [0]", false, 100, 36, 15);
	do {
		scena1 = inpt();
		switch (scena1) {
		case 1:
			grp.printdb(player.name, false, 20, 6, 2);
			grp. printdb(" - daj mi spokój", false, 23, 6, 15);
			grp.printdb("Gyce zapatrzył się na chmurę, nie reagując na moją niegrzeczność. Nie odszedł jednak", false, 20, 7, 15);
			grp.printdb("                                                                                    ", false, 60, 30, 15);
			grp.printdb("[2] Odejdź bez słowa. Wciąż jesteś wściekły na to, że naraził twoje życie.          ", false, 60, 31, 15);
			grp.printdb("[3] - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.", false, 60, 32, 15);
			grp.printdb("Dobrą flaszkę piętnostoletniej whisky.                                              ", false, 64, 33, 15);
			do{
				scena1_1 = inpt();
				switch (scena1_1) {
				case 2:
					grp.ClearScreen();
					grp.printdb("Odchodzisz w stronę mostu na siódmy pierścień", false, 53, 19, 15);
					grp.pak();
					scena2 = Scena_2();
					if (scena2 == true) {
						Scena_1();
					}
					ctrl = true;
					break;
				case 3:
					grp.printdb(player.name, false, 20, 8, 2);
					grp.printdb(" - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.", false, 23, 8, 15);
					grp.printdb("Dobrą flaszkę piętnostoletniej whisky.", false, 20, 9, 15);
					grp.printdb("Gyce", false, 20, 10, 8);
					grp.printdb(" - Właśnie o tym chciałem z Tobą porozmawiać – spuścił nieco wzrok – w ramach przeprosin za", false, 24, 10, 15);
					grp.printdb("to moje oszustwo. Za to, ze nie powiedziałem ci o tym obozie –  spojrzał prosto w moją twarz - ", false, 20, 11, 15);
					grp.printdb("pomogę ci odzyskać tą butelkę.", false, 20, 12, 15); 
					grp.printdb("Miejscowi porobili sobie ukryte drogi. Jak myślisz? Skąd mają mięso czy owoce? Z tego", false, 20, 13, 15);
					grp.printdb("spłachetka ziemi tutaj, nie byliby się w stanie wyżywić. Pokaże Ci drogę, która doprowadzi Cię", false, 20, 14, 15);
					grp.printdb("na ósmy pierścień niedaleko twojej kapliczki.", false, 20, 15, 15);
					grp.printdb("[1] Posłuchaj Gycego.                                                               ", false, 60, 30, 15);
					grp.printdb("[2] Nie słuchaj oszusta i wyrusz na wyprawę bez jego wskazówek                      ", false, 60, 31, 15);
					grp.printdb("                                                                                    ", false, 60, 32, 15);
					grp.printdb("                                                                                    ", false, 60, 33, 15);
					do {
						scena1_1_1 = inpt();
						switch (scena1_1_1) {
						case 1:
							player.Hidden_Path = 1;
							grp.printdb("Gyce rozrysowuje patykiem w piachu pierścienie Oktawii i pokazuje Ci, gdzie znajdują się ukryte przejścia", false, 20, 16, 15);
							grp.printdb("Z uwagą słuchasz tego co Gyce ma Ci do powiedzenia. Teraz posiadasz wiedzę o miejscach ukrytych przejść", false, 20, 17, 15);
							grp.printdb("Twoje szanse na powodzenie, wzrosły.", false, 20, 19, 15);
							grp.printdb("[1] Wyrusz na wyprawę                                                               ", false, 60, 30, 15);
							grp.printdb("[2] Zapomnij o tym i wróć do osady                                                  ", false, 60, 31, 15);
							grp.printdb("[3] Daj rzeźbiarzowi w twarz. Dalej masz do niego pretensje                         ", false, 60, 32, 15);
							grp.printdb("                                                                                    ", false, 60, 33, 15);
							do {
								scena1_1_1_1 = inpt();
								switch (scena1_1_1_1) {
								case 1:
									grp.ClearScreen();
									grp.printdb("Tutaj rozpoczyna sie twoja przygoda. cdn.", false, 53, 19, 15);
									grp.pak();
									break;
								case 2:
									grp.ClearScreen();
									grp.printdb("Zaprzestajesz prób dotarcia do swojej trumny. ", false, 50, 19, 15);
									grp.printdb("Z czasem żal za utraconym powoduje, że nie widząc sensu dalszej egzystencji, ", false, 50, 20, 15);
									grp.printdb("odchodzisz poza Oktawię i giniesz na pustkowiach.", false, 50, 21, 15);
									player.Hidden_Path = 0;
									grp.pak();
									break;
								case 3:
									grp.ClearScreen();
									grp.printdb("Uderzyłeś rzeźbiarza. ", false, 50, 19, 15);
									grp.printdb("Ten zatoczył się, potknął i nieszczęśliwie zsunął się w głąb kanału.", false, 50, 20, 15);
									grp.printdb("Ostatnim wymachem ręki, łapię za nogawkę twoich spodni i spadacie obaj w objęcia śmierci.", false, 50, 21, 15);
									player.Hidden_Path = 0;
									grp.pak();
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
							grp.ClearScreen();
							grp.printdb("Odchodzisz w stronę mostu na siódmy pierścień", false, 53, 19, 15);
							grp.pak();
							scena2 = Scena_2();
							if (scena2 == true) {
								Scena_1();
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
			grp.ClearScreen();
			grp.printdb("Odchodzisz w stronę mostu na siódmy pierścień", false, 53, 19, 15);
			grp.pak();
			scena2 = Scena_2();
			if (scena2 == true) {
				Scena_1();
			}
			ctrl = true;
			break;
		case 3:
			grp.printdb(player.name, false, 20, 6, 2);
			grp.printdb(" - Tak, zostawiłem tam moją dodatkową nagrodę za wzięcie udziału w eksperymencie.", false, 23, 6, 15);
			grp.printdb("Dobrą flaszkę piętnostoletniej whisky.", false, 20, 7, 15);
			grp.printdb("Gyce", false, 20, 8, 8);
			grp.printdb(" - Właśnie o tym chciałem z Tobą porozmawiać – spuścił nieco wzrok – w ramach przeprosin za", false, 24, 8, 15);
			grp.printdb("to moje oszustwo. Za to, ze nie powiedziałem ci o tym obozie –  spojrzał prosto w moją twarz - ", false, 20, 9, 15);
			grp.printdb("pomogę ci odzyskać tą butelkę.", false, 20, 10, 15);
			grp.printdb("Miejscowi porobili sobie ukryte drogi. Jak myślisz? Skąd mają mięso czy owoce? Z tego", false, 20, 11, 15);
			grp.printdb("spłachetka ziemi tutaj, nie byliby się w stanie wyżywić. Pokaże Ci drogę, która doprowadzi Cię", false, 20, 12, 15);
			grp.printdb("na ósmy pierścień niedaleko twojej kapliczki.", false, 20, 13, 15);
			grp.printdb("[1] Posłuchaj Gycego.                                                               ", false, 60, 30, 15);
			grp.printdb("[2] Nie słuchaj oszusta i wyrusz na wyprawę bez jego wskazówek                      ", false, 60, 31, 15);
			grp.printdb("                                                                                    ", false, 60, 32, 15);
			grp.printdb("                                                                                    ", false, 60, 33, 15);
			do {
				scena1_1_1 = inpt();
				switch (scena1_1_1) {
				case 1:
					player.Hidden_Path = 1;
					grp.printdb("Gyce rozrysowuje patykiem w piachu pierścienie Oktawii i pokazuje Ci, gdzie znajdują się ukryte przejścia", false, 20, 14, 15);
					grp.printdb("Z uwagą słuchasz tego co Gyce ma Ci do powiedzenia. Teraz posiadasz wiedzę o miejscach ukrytych przejść", false, 20, 15, 15);
					grp.printdb("Twoje szanse na powodzenie, wzrosły.", false, 20, 17, 15);
					grp.printdb("[1] Wyrusz na wyprawę                                                               ", false, 60, 30, 15);
					grp.printdb("[2] Zapomnij o tym i wróć do osady                                                  ", false, 60, 31, 15);
					grp.printdb("[3] Daj rzeźbiarzowi w twarz. Dalej masz do niego pretensje                         ", false, 60, 32, 15);
					grp.printdb("                                                                                    ", false, 60, 33, 15);
					do {
						scena1_1_1_1 = inpt();
						switch (scena1_1_1_1) {
						case 1:
							grp.ClearScreen();
							grp.printdb("Tutaj rozpoczyna sie twoja przygoda.", false, 53, 19, 15);
							grp.pak();
							break;
						case 2:
							grp.ClearScreen();
							grp.printdb("Zaprzestajesz prób dotarcia do swojej trumny. ", false, 50, 19,15);
							grp.printdb("Z czasem żal za utraconym powoduje, że nie widząc sensu dalszej egzystencji, ", false, 50, 20, 15);
							grp.printdb("odchodzisz poza Oktawię i giniesz na pustkowiach.", false, 50, 21, 15);
							player.Hidden_Path = 0;
							grp.pak();
							break;
						case 3:
							grp.ClearScreen();
							grp.printdb("Uderzyłeś rzeźbiarza. ", false, 50, 19, 15);
							grp.printdb("Ten zatoczył się, potknął i nieszczęśliwie zsunął się w głąb kanału.", false, 50, 20, 15);
							grp.printdb("Ostatnim wymachem ręki, łapię za nogawkę twoich spodni i spadacie obaj w objęcia śmierci.", false, 50, 21, 15);
							player.Hidden_Path = 0;
							grp.pak();
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
					grp.ClearScreen();
					grp.printdb("Odchodzisz w stronę mostu na siódmy pierścień", false, 53, 19, 15);
					grp.pak();
					scena2 = Scena_2();				
						if (scena2 == true) {
							Scena_1();
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



bool Scena_2()
{
	grp.ClearScreen();
	bool ctrl = true;
	int scena2 = 0;
	grp.printdb("Most na śiódmy pierścień", false, 20, 5, 15);
	grp.printdb("[1] Wróć i porozmawiaj z Gycem", false, 60, 30, 15);
	grp.printdb("[2] Wyrusz na wyprawę", false, 60, 31, 15);
	grp.printdb("Zakończ przygodę [0]", false, 100, 36, 15);
	do {
		scena2 = inpt();
		switch (scena2) {
		case 1:
			player.gyce_talk = true;
			return true;
		case 2:
			grp.ClearScreen();
			grp.printdb("pełen negatywnych emocji związanych z rzeźbiarzem wkraczasz na wąską deską stanowiącą przejście na drugą stronę", true, 20, 19, 15);
			grp.printdb("Jesteś poddenerwowany i zdekoncentrowany. Spadasz i giniesz w wodach między siódmym, a ósmym pierścieniem", true, 20, 20, 15);
			grp.pak();
			break;
		}
	} while (ctrl == false);
	return false;
}

bool Scena_3()
{
	grp.ClearScreen();
	grp.printdb(" Mając wiedzę o tajemnych przejściach stajesz przed mostem na krąg siódmy.", true, 20, 19, 15);
	player.last_scn = 3;
	player.save();
	grp.pak();
	return true;
}