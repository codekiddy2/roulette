
#include "pch.hh"
#include "bet.hh"
#include <thread>

using namespace std;
using namespace roulette;

void do_tests(const ETable table,
	const EBet bet,
	const unsigned chips,
	std::shared_ptr<Selection_t> selection = nullptr,
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
	std::shared_ptr<Selection_t> selection,
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

	cout << "testing fuction get_chips()... " << endl;
	test_move.get_chips();
	cout << "OK" << endl;
	cout << "testing fuction get_id()... " << endl;
	test_move.get_id();
	cout << "OK" << endl;
	cout << "testing fuction get_number()... " << endl;
	test_move.get_number(0);
	cout << "OK" << endl;
	cout << "testing fuction get_numbers()... " << endl;
	test_move.get_numbers();
	cout << "OK" << endl;
	cout << "testing fuction get_selection()... " << endl;
	test_move.get_selection();
	cout << "OK" << endl;
	cout << "testing fuction get_x()... " << endl;
	test_move.get_x();
	cout << "OK" << endl;
	cout << "testing fuction get_y()... " << endl;
	test_move.get_y();
	cout << "OK" << endl;

	cout << "testing child functions... " << endl;
	switch (bet)
	{
	case EBet::VoisinsDeZero:
	case EBet::TriesDuCylindre:
	case EBet::OrphelinsEnPlen:
	case EBet::OrphelinsACheval:
	case EBet::Jeu0:
	case EBet::Jeu79:
	case EBet::RedSplits:
	case EBet::BlackSplits:
	case EBet::Snake:
	case EBet::Maximus13:
	case EBet::Maximus2:
	case EBet::Maximus35:
	case EBet::Maximus3436:
	case EBet::MaximusColumn2:
	case EBet::MaximusColumn13:
		cout << "testing fuction get_childs()... " << endl;
		test_move.get_childs();
		cout << "OK" << endl;
		cout << "testing fuction get_child_chip_count()... " << endl;
		test_move.get_child_chip_count(1);
		cout << "OK" << endl;
		cout << "testing fuction get_child_id()... " << endl;
		test_move.get_child_id(1);
		cout << "OK" << endl;
		cout << "testing fuction get_child_number()... " << endl;
		test_move.get_child_number(1, 0);
		cout << "OK" << endl;
		cout << "testing fuction get_child_number_count()... " << endl;
		test_move.get_child_number_count(1);
		cout << "OK" << endl;
	default:
		break;
	}
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

	test_map.insert(make_pair(EBet::VoisinsDeZero, "VoisinsDeZero"));
	test_map.insert(make_pair(EBet::TriesDuCylindre, "TriesDuCylindre"));
	test_map.insert(make_pair(EBet::OrphelinsEnPlen, "OrphelinsEnPlen"));
	test_map.insert(make_pair(EBet::OrphelinsACheval, "OrphelinsACheval"));
	test_map.insert(make_pair(EBet::Jeu0, "Jeu0"));
	test_map.insert(make_pair(EBet::Jeu79, "Jeu79"));
	test_map.insert(make_pair(EBet::RedSplits, "RedSplits"));
	test_map.insert(make_pair(EBet::BlackSplits, "BlackSplits"));
	test_map.insert(make_pair(EBet::Snake, "Snake"));
	test_map.insert(make_pair(EBet::Maximus13, "Maximus13"));
	test_map.insert(make_pair(EBet::Maximus2, "Maximus2"));
	test_map.insert(make_pair(EBet::Maximus35, "Maximus35"));
	test_map.insert(make_pair(EBet::Maximus3436, "Maximus3436"));
	test_map.insert(make_pair(EBet::MaximusColumn2, "MaximusColumn2"));
	test_map.insert(make_pair(EBet::MaximusColumn13, "MaximusColumn13"));

}