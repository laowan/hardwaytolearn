#include <iostream>
using namespace std;

int main()
{
	const int max_length = 21;
	char input_line[max_length] = "1?2?3?4?5?6?7?8?9?0?";

	int quest_count = 0;
	for (int i = 0; i < max_length; i++)
	{
		if (input_line[i] == '?')
			quest_count++;
	}

	int i = 0;
	while (i < max_length)
	{
		if (input_line[i] == '?')
			quest_count++;
		i++;
	}

	for (char *p = input_line; *p != '\0'; p++)
	{
		if (*p == '?')
			quest_count++;
	}

	cout << quest_count << endl;
}