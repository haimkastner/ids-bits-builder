#include <iostream>

#include "ids_builder.h"

void encode_ids_example()
{
	// Original value to convert
	float value = 646773.5;

	// Create a vector of fields
	auto idsFields = std::vector<IDSBuilder::Field>();

	// Create a field for 646773.5 (the original value) as a float value (4 bytes)
	auto fieldA = IDSBuilder::Field((float)value);

	// Create another field for -646773.5 as double value (8 bytes)
	auto fieldB = IDSBuilder::Field((double)value * -1);

	// Create another field for 646773.5 as int value (4 bytes)
	auto fieldC = IDSBuilder::Field((int)value);

	// Add the fields to the fields vector.
	idsFields.push_back(fieldA);
	idsFields.push_back(fieldB);
	idsFields.push_back(fieldC);

	// Create an IDS with the fields vector.
	auto ids = IDSBuilder::IDS(idsFields);

	// Convert the IDS to an array of bytes.
	auto binaryData = ids.encode_ids();

	// Print the raw binary data as decimal digits.
	ids.print_ids(binaryData, true); // 88, 231, 29, 73, 0, 0, 0, 0, 235, 188, 35, 193, 117, 222, 9, 0
	ids.print_ids(binaryData, false); // 00011010,11100111,10111000,10010010, 00000000,00000000,00000000,00000000,11010111,00111101,11000100,10000011, 10101110,01111011,10010000,00000000
}

void decode_ids_example()
{
	// Create an array of bytes.
	auto raw = std::vector<char>();

	// Binary array represent value of 646773.5 (float)
	raw.push_back(88);
	raw.push_back(231);
	raw.push_back(29);
	raw.push_back(73);

	// Binary array represent value of -646773.5 (double)
	raw.push_back(0);
	raw.push_back(0);
	raw.push_back(0);
	raw.push_back(0);
	raw.push_back(235);
	raw.push_back(188);
	raw.push_back(35);
	raw.push_back(193);

	// Binary array represent value of 646773 (int)
	raw.push_back(117);
	raw.push_back(222);
	raw.push_back(9);
	raw.push_back(0);

	// Create a vector of fields
	auto idsFields = std::vector<IDSBuilder::Field>();
	
	// Add the fields to the fields vector.
	idsFields.push_back(IDSBuilder::Field((float)0));
	idsFields.push_back(IDSBuilder::Field((double)0));
	idsFields.push_back(IDSBuilder::Field((int)0));
	
	// Create an IDS with the fields vector and the raw binary data.
	auto ids = IDSBuilder::IDS(idsFields, raw);

	// Encode the IDS 
	auto decodedIds = ids.decode_ids(); // [ 646773.5, -646773.5, 646773 ] 
}

int main(int argc, const char *argv[])
{
	encode_ids_example();
	decode_ids_example();

	return 0;
}
