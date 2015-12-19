
#include "sets.hh"
#include <iostream>

namespace roulette
{
	bool is_red(const unsigned number);
	bool is_black(const unsigned number);
	bool is_green(const unsigned number);

	unsigned which_column(const unsigned number);
	unsigned which_dozen(const unsigned number);
	unsigned get_neighbor(const ETable table, const unsigned refNum, const unsigned position);

	bool is_red(const unsigned number)
	{
		switch (number)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 12:
		case 14:
		case 16:
		case 18:
		case 19:
		case 21:
		case 23:
		case 25:
		case 27:
		case 30:
		case 32:
		case 34:
		case 36:
			return true;
		default:
			return false;
		}
	}

	bool is_black(const unsigned number)
	{
		if (is_green(number) || is_red(number))
			return false;
		else return(number && (number < 37));
	}

	bool is_green(const unsigned number)
	{
		if (number == 0 || number == 37)
			return true;
		else return false;
	}

	unsigned which_column(const unsigned number)
	{
		if ((number % 3) == 0)
			return 3;
		else return number % 3;
	}

	unsigned which_column(EField field)
	{
		if ((static_cast<unsigned>(field) % 3) == 0)
			return 3;
		else return static_cast<unsigned>(field) % 3;
	}

	unsigned which_dozen(const unsigned number)
	{
		if (number < 13)
			return 1;
		else if (number < 25)
			return 2;
		else return 3;
	}

	unsigned get_neighbor(const ETable table, const unsigned refNum, const unsigned position)
	{
		unsigned i = 0;
		using std::find;
		static type_raw_set::const_iterator iter;

		switch (table)
		{
		case ETable::NoZero:
			iter = find(NoZeroWheel->begin(), NoZeroWheel->end(), refNum);
			while (i != position) // if i == position refNum is returned
			{ // if i != position then iterating.... position times
				if (position > 0) // positive position
				{
					++i;
					++iter;
					if (iter == NoZeroWheel->end())
						iter = NoZeroWheel->begin(); // return to begin and continue
				}
				else // negative position
				{
					if (iter == NoZeroWheel->begin() && i != position) //if begin is not what we want...
						iter = NoZeroWheel->end(); // then go to end
					--iter;
					--i;
				}
			}
			break;

		case ETable::American:
			iter = find(AmericanWheel->begin(), AmericanWheel->end(), refNum);
			while (i != position)
			{
				if (position > 0)
				{
					++i;
					++iter;
					if (iter == AmericanWheel->end())
						iter = AmericanWheel->begin();
				}
				else
				{
					if (iter == AmericanWheel->begin() && i != position)
						iter = AmericanWheel->end();
					--iter;
					--i;
				}
			}
			break;

		case ETable::French:
		case ETable::SingleImprisonment:
		case ETable::InfininiteImprisonment:
		case ETable::DoubleImprisonment:
		case ETable::TripleImprisonment:
		case ETable::European:
			iter = find(EuropeanWheel->begin(), EuropeanWheel->end(), refNum);
			while (i != position)
			{
				if (position > 0)
				{
					++i;
					++iter;
					if (iter == EuropeanWheel->end())
						iter = EuropeanWheel->begin();
				}
				else
				{
					if (iter == EuropeanWheel->begin() && i != position)
						iter = EuropeanWheel->end();
					--iter;
					--i;
				}
			}
			break;
		}
		return *iter;
	}

} // namespace

using namespace std;
using namespace roulette;

int main()
{
	cout << "Number 1 belong to column " << which_column(1) << endl;
	cout << "Number 2 belong to column " << which_column(2) << endl;
	cout << "Number 3 belong to column " << which_column(3) << endl;

	cout << "EField1 belong to column " << which_column(EField::Number1) << endl;
	cout << "EField2 belong to column " << which_column(EField::Number2) << endl;
	cout << "EField3 belong to column " << which_column(EField::Number3) << endl;
	cin.get();
	return 0;
}