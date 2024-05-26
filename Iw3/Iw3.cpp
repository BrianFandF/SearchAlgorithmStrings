#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<array>
#include<termcolor/termcolor.hpp>
using namespace std;

vector<int> find_substring_simple(string south, string sample)
{
	vector<int> positions;
	int position = 0;
	int iter_compare = 0;
	for (int i = 0; i < south.size(); i++)
	{
		position = 0;
		iter_compare++;
		while (position < sample.size() && i + position < south.size() && sample[position] == south[i + position])
		{
			position++;
		}

		iter_compare++;
		if (position == sample.size())
		{
			positions.push_back(i);
		}
	}

	cout << "Number of comparisons simple: " << iter_compare << endl;
	return positions;
}

vector<int> prefix(string sample)
{
	vector<int> values(sample.size());
	for (int i = 1; i < sample.size(); i++)
	{
		int j = values[i - 1];
		while (j > 0 && sample[i] != sample[j])
		{
			j = values[j - 1];
		}

		if (sample[i] == sample[j])
		{
			j++;
		}

		values[i] = j;
	}

	return values;
}

vector<int> KMP_search(string text, string sample)
{
	vector<int> founded_positions;
	vector<int> prefix_res = prefix(sample);

	int position_text = 0;
	int position_sample = 0;
	int iter_compare = 0;

	while (position_text < text.size())
	{
		iter_compare++;
		if (sample[position_sample] == text[position_text])
		{
			position_text++;
			position_sample++;
		}

		iter_compare++;
		if (position_sample == sample.size())
		{
			founded_positions.push_back(position_text - position_sample);
			position_sample = prefix_res[position_sample - 1];
		}

		else if (position_text < text.size() && sample[position_sample] != text[position_text])
		{
			iter_compare++;
			if (position_sample != 0)
			{
				position_sample = prefix_res[position_sample - 1];
			}

			else
			{
				position_text += 1;
			}
		}
	}

	cout << "Number of comparisons KMP: " << iter_compare << endl;
	return founded_positions;
}

int main()
{
	string text = "I am vengeance! I am the night! I am Batman!";
	string text_test = "I am Batman";
	string substring = "Bat";
	cout << termcolor::bright_white << "Text: " << termcolor::bright_yellow << text << endl;
	cout << termcolor::bright_white << "Substring: " << termcolor::bright_yellow << substring << termcolor::reset << endl;
	vector<int> all_positions_KMP = KMP_search(text, substring);
	vector<int> all_positions_simple = find_substring_simple(text, substring);
	cout << termcolor::bright_green << "Positions for KMP: " << endl;
	for (int i = 0; i < all_positions_KMP.size(); i++)
	{
		cout << termcolor::bright_blue << all_positions_KMP[i] << " ";
	}
	cout << termcolor::reset << endl;

	cout << termcolor::bright_green << "Positions for simple method: " << endl;
	for (int i = 0; i < all_positions_simple.size(); i++)
	{
		cout << termcolor::bright_blue << all_positions_simple[i] << " ";
	}
	cout << termcolor::reset << endl;

}