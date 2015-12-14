
#include "pch.hh"
#include "bet.hh"
#include <thread>

using namespace std;
using namespace roulette;

void do_tests(const ETable table,
	const EBet bet,
	const unsigned chips,
	Selection_t* selection = nullptr,
	Bet* parent = nullptr,
	const int x = 0,
	const int y = 0);

void init_bets(map<EBet, string>& test_map);

int main()
{
	map<EBet, string> test_map;
	init_bets(test_map);

	for (size_t i = 0; i < 50; i++)
	{
		auto temp = test_map.find(static_cast<EBet>(i));

		if (temp != test_map.end())
		{
			cout << "Testig: " << temp->second << endl;
			do_tests(ETable::European, temp->first, 100);
			this_thread::sleep_for(500ms);
			cout << endl;
		}
	}

	cout << "Test done" << endl;
	cin.get();
	return 0;
}


void do_tests(const ETable table,
	const EBet bet,
	const unsigned chips,
	Selection_t* selection,
	Bet* parent,
	const int x,
	const int y)
{
	cout << "test constructor... ";
	Bet test_bet(table, bet, chips, selection, parent, x, y);
	cout << "OK" << endl;

	cout << "test copy constructor... ";
	Bet test_copy(test_bet);
	cout << "OK" << endl;

	cout << "test copy asignment... ";
	Bet test_asignment = test_bet;
	cout << "OK" << endl;

	cout << "test move constructor... ";
	Bet test_move(std::move(test_bet));
	cout << "OK" << endl;

	cout << "test move asignment... ";
	Bet test_move_asignment = std::move(test_move);
	cout << "OK" << endl;
}

void init_bets(map<EBet, string>& test_map)
{
	test_map.insert(make_pair(EBet::StraightUp, "StraighUp"));
	test_map.insert(make_pair(EBet::Black, "Black"));
	test_map.insert(make_pair(EBet::Red, "Red"));
	test_map.insert(make_pair(EBet::Even, "Even"));
	test_map.insert(make_pair(EBet::Odd, "Odd"));
	test_map.insert(make_pair(EBet::Split, "Split"));
	test_map.insert(make_pair(EBet::Corner, "Corner"));
	test_map.insert(make_pair(EBet::Dozen1, "Dozen1"));
	test_map.insert(make_pair(EBet::Dozen2, "Dozen2"));
	test_map.insert(make_pair(EBet::Dozen3, "Dozen3"));
	test_map.insert(make_pair(EBet::Low, "Low"));
	test_map.insert(make_pair(EBet::High, "High"));
	test_map.insert(make_pair(EBet::Column1, "Column1"));
	test_map.insert(make_pair(EBet::Column2, "Column2"));
	test_map.insert(make_pair(EBet::Column3, "Column3"));
}