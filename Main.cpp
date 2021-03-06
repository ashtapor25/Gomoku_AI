#include "Utility.h"
#include "a_b_prune.h"
#include <iostream>

using namespace std;

int main()
{
	State* mystate = new State;
	State* tempstate = nullptr;
	chrono::system_clock::time_point timelimit;
	int turntime; // max duration for the AI to make a move
	int person, row, col;
	string finish;
	pair<int, int> move_input;
	cout << "         <<Made by GRAWP>>         Copyright 2018 GRAWP ALL RIGHTS RESERVED. " << endl;
	cout << endl;
	cout << "Renju Rule을 따르는 게임입니다." << endl;
	cout << "흑(선공): 3X3, 4X4, 6목, 7목, ..., n목을 만드는 수는 둘 수 없습니다." << endl;
	cout << "백(후공): 모든 수를 둘 수 있습니다." << endl;
	cout << endl;
	cout << "선공(1) 이나 후공(2)을 골라주세요: ";
	cin >> person;
	mystate->computer = 3 - person; // assigns the order of first moves for using appropriate value table
	while (person != 1 && person != 2)
	{
		cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
		cout << "선공(1) 이나 후공(2)을 골라주세요: ";
		cin >> person;
	}
	cout << "인공지능이 1턴마다 생각하는 시간을 정해주세요(30초이상 권장): ";
	cin >> turntime;
	chrono::seconds turnlimit(turntime);
	if (person == 1) // person plays first, AI plays second
	{
		while (1)
		{
			print_board(mystate);
			if (Terminal_check(mystate))
			{
				cout << "(ㅜ _ ㅜ) [[ YOU LOSE ]] (ㅜ _ ㅜ)" << endl;
				cout << "종료하려면 아무것이나 입력해주세요: ";
				cin >> finish;
				break;
			}
			
			cout << "행 값을 입력해주세요(왼쪽에 붙어 보이는 숫자들): ";
			cin >> row;
			cout << "열 값을 입력해주세요(위쪽에 붙어 보이는 숫자들): ";
			cin >> col;
			while (!(mystate->board.spot_available(row, col)))
			{
				cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
				cout << "행 값을 입력해주세요(왼쪽에 붙어 보이는 숫자들): ";
				cin >> row;
				cout << "열 값을 입력해주세요(위쪽에 붙어 보이는 숫자들): ";
				cin >> col;
			}
			cout << "다음에 두는 사람: " << mystate->player << endl;
			while (Check_Forbidden(mystate, make_pair(row, col)))
			{
				cout << "선공을 둘 수 없는 수입니다.(3X3, 4X4, 6목, 7목...)" << endl;
				cout << "행 값을 입력해주세요(왼쪽에 붙어 보이는 숫자들): ";
				cin >> row;
				cout << "열 값을 입력해주세요(위쪽에 붙어 보이는 숫자들): ";
				cin >> col;
			}
			
			move_input.first = row;
			move_input.second = col;
			mystate = change_state(mystate, move_input);
			print_board(mystate);
			if (Terminal_check(mystate))
			{
				cout << "/ (^o^) / [[ YOU WIN ]] / (^o^) /" << endl;
				cout << "종료하려면 아무것이나 입력해주세요: ";
				cin >> finish;
				break;
			}
			
			cout << "인공지능이 생각 중입니다..." << endl;
			timelimit = chrono::system_clock::now() + turnlimit;
			move_input = Iter_Pruning(mystate, timelimit);
			cout << "인공지능이 둔 수는..." << move_input.first << ", " << move_input.second << endl;
			tempstate = mystate;
			mystate = change_state(mystate, move_input);
			tempstate->next_states.erase(move_input);
			Recursive_Destoryer(tempstate);
		}
	}
	if (person == 2) // AI plays first, person plays second
	{
		move_input.first = 9;
		move_input.second = 9;
		cout << "인공지능이 둔 수는..." << move_input.first << ", " << move_input.second << endl;
		mystate = change_state(mystate, move_input);
		while (1)
		{
			print_board(mystate);
			if (Terminal_check(mystate))
			{
				cout << "(ㅜ _ ㅜ) [[ YOU LOSE ]] (ㅜ _ ㅜ)" << endl;
				cout << "종료하려면 아무것이나 입력해주세요: ";
				cin >> finish;
				break;
			}
			
			cout << "행 값을 입력해주세요(왼쪽에 붙어 보이는 숫자들): ";
			cin >> row;
			cout << "열 값을 입력해주세요(위쪽에 붙어 보이는 숫자들): ";
			cin >> col;
			while (!(mystate->board.spot_available(row, col)))
			{
				cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
				cout << "행 값을 입력해주세요(왼쪽에 붙어 보이는 숫자들): ";
				cin >> row;
				cout << "열 값을 입력해주세요(위쪽에 붙어 보이는 숫자들): ";
				cin >> col;
			}
			move_input.first = row;
			move_input.second = col;
			mystate = change_state(mystate, move_input);
			print_board(mystate);
			if (Terminal_check(mystate))
			{
				cout << "(ㅜ _ ㅜ) [[ YOU LOSE ]] (ㅜ _ ㅜ)" << endl;
				cout << "종료하려면 아무것이나 입력해주세요: ";
				cin >> finish;
				break;
			}
			
			cout << "인공지능이 생각 중입니다..." << endl;
			timelimit = chrono::system_clock::now() + turnlimit;
			move_input = Iter_Pruning(mystate, timelimit);
			cout << "인공지능이 둔 수는..." << move_input.first << ", " << move_input.second << endl;
			tempstate = mystate;
			mystate = change_state(mystate, move_input);
			tempstate->next_states.erase(move_input);
			Recursive_Destoryer(tempstate);
		}
	}
	return 0;
}

