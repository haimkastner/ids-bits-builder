#include <iostream>
#include <bitset>

int main(int argc, const char *argv[])
{
    int n;

	n = 0xA513;

	std::bitset<16> vec;

	for (size_t i = 15; i >= 0; i--)
	{
		vec[i] = n % 2;
		n = n / 2;
		if (n <= 0)
			break;
	}

    return 0;
}
