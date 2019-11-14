#include <iostream>

#include "ids_builder.hpp"

void encode_ids_example()
{
	float value = -646773.5;
	auto idsFields = std::vector<IDSBuilder::Field>();
	idsFields.push_back(IDSBuilder::Field((float)value));
	auto ids = IDSBuilder::IDS(idsFields);
	ids.print_ids(true);
}

void decode_ids_example()
{
	auto raw = std::vector<char>();
	// Binary array of float 646773.5
	raw.push_back(88);
	raw.push_back(231);
	raw.push_back(29);
	raw.push_back(73);

	// Binary array of float -646773.5
	raw.push_back(88);
	raw.push_back(231);
	raw.push_back(29);
	raw.push_back(201);

	auto idsFields = std::vector<IDSBuilder::Field>();
	idsFields.push_back(IDSBuilder::Field((float)0));
	idsFields.push_back(IDSBuilder::Field((float)0));
	auto ids = IDSBuilder::IDS(idsFields, raw);
	auto decodedIds = ids.decode_ids();
}

int main(int argc, const char *argv[])
{
	encode_ids_example();
	decode_ids_example();

	return 0;
}
