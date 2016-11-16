#include "MC.h"
#include "AsciiGameSystem.h"
#include "AsciiInitgame.h"

extern bool isDone;

void AsciiInitgame::playgameAscii(){

	system("color e");

	char ch;
	char ch1;

	string s = " \t==Welcome==";

	cout << endl;
	for (int i = 0; i < s.size(); i++){
		Sleep(150);
		printf("%c", s[i]);
	}
	cout << endl;

	s = " \tThis is my ascii roguelike game";
	for (int i = 0; i < s.size(); i++){
		Sleep(150);
		printf("%c", s[i]);
	}
	cout << endl;

	s = " \tJust Play and enjoy..... ";
	for (int i = 0; i < s.size(); i++){
		Sleep(150);
		printf("%c", s[i]);
	}	
	cout << endl;
	cout << endl;

	do{
		system("color e");
		cout << endl;
		system("cls");
		s = " **Menu**";
		for (int i = 0; i < s.size(); i++){
			Sleep(150);
			printf("%c", s[i]);
		}
		cout << endl;
		s = " \t1.Play game.....";
		for (int i = 0; i < s.size(); i++){
			Sleep(150);
			printf("%c", s[i]);
		}
		cout << endl;

		s = " \t2.Instructions....";
		for (int i = 0; i < s.size(); i++){
			Sleep(150);
			printf("%c", s[i]);
		}
		cout << endl;
		cout << endl;
		mc:
		s = " Enter your choice: ";
		for (int i = 0; i < s.size(); i++){
			Sleep(150);
			printf("%c", s[i]);
		}
		cout << flush;
		cin >> ch1;
		cout << endl;

		if (ch1 == '1'){
			do{
				AsciiGameSystem gamesystem("Asciilevel1.txt");
				gamesystem.playGameAscii();
				cout << endl << "You Died!!" << endl;
				system("color c");
				isDone = false;
				cout << " Do you want to play match <y/n>: " << flush;
				cin >> ch;
			} while ((ch == 'y') || (ch == 'Y'));
		}
		else if (ch1 == '2'){
			vector<string> Instrct;
			ifstream file;
			string line;

			file.open("instructAscii.txt");
			if (file.fail()){
				perror("instructAscii.txt");
				system("PAUSE");
				exit(1);
			}

			while (getline(file, line)){
				Instrct.push_back(line);
			}
			file.close();
			for (int i = 0; i < Instrct.size(); i++){
				printf(" %s\n", Instrct[i].c_str());
			}
			system("color a");
		}
		else {
			cout << " InvalidInput!!" << endl << endl;
			goto mc;
		}
		cout << endl;
		isDone = false;
			cout << " Do you Want to go to main menu <y/n>: " << flush;
			cin >> ch;
	} while ((ch == 'y') || (ch == 'Y'));

	system("color d");
	cout << endl;
	cout << " **Thank You for Playing ...**" << endl;
	cout << " **Good Bye.......**" << endl;
	cout << " **Have a nice day....**" << endl;
	cout << endl;
	cout << " ";
	cout << "Press any key to exit..." << flush;
	ch = _getch();
}

