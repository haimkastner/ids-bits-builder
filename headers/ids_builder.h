#include <vector>

#include "ids_field.h"
#include "bits_structures.h"
#include "constants.h"

namespace IDSBuilder
{
#ifndef IDS_BUILDER_H
#define IDS_BUILDER_H

class IDS
{
private:
    /** IDS Fields, note! the order of fileds in the vector is importent */
    std::vector<Field> _idsFields;

    /** IDS raw data for decoding IDS only */
    std::vector<char> _binaryArray;

    /**
     Convert float number to array of chars (represeting array of bytes). 
     @param bytesAmount The amount of bytes array to convert to.
     @param value The float value to convert from.
	 */
    static std::vector<char> convert_float(size_t bytesAmount, double value);
    
    /**
     Convert a float type number to array of chars (represeting array of bytes).
	 @param value The float value to convert from.
	 */
    static std::vector<char> convert_float(float value);

    /**
     Convert a double type number to array of chars (represeting array of bytes). 
	 @param value The float value to convert from.
	 */
    static std::vector<char> convert_float(double value);

    /**
     Convert an array of chars to a float value.
	 @param bytesAmount The amount of bytes array that field expexted.
	 @param value The array of chars to convert from.
	 */
    static double convert_float(size_t bytesAmount, std::vector<char> binaryArray);

    /**
     Convert a number to array of chars (represeting array of bytes).
	 @param bytesAmount The amount of bytes array to convert to.
	 @param value The value to convert from.
	 */
    static std::vector<char> convert_int(size_t bytesAmount, long long value);
     
    /**
     Convert a long long int type number to array of chars (represeting array of bytes).
	 @param value The value to convert from.
	 */
    static std::vector<char> convert_int(long long value);

    /**
     Convert an int type number to array of chars (represeting array of bytes).
	 @param value The value to convert from.
	 */
    static std::vector<char> convert_int(int value);

    /**
     Convert a short int type number to array of chars (represeting array of bytes).
	 @param value The value to convert from.
	 */
    static std::vector<char> convert_int(short value);

    /**
     Convert a number to array of chars (represeting array of bytes), manually by math (worse performance then direct convertions).
	 @param bytesAmount The amount of bytes array to convert to.
	 @param value The value to convert from.
	 */
    static std::vector<char> convert_int_manually(size_t bytesAmount, long long value);

    /**
     Convert an array of chars to an int value.
	 @param bytesAmount The amount of bytes array that field expexted.
	 @param value The array of chars to convert from.
	 */
    static long long convert_int(size_t bytesAmount, std::vector<char> binaryArray);

public:

    /**
     Create an instance of IDS from a vector of fields. 
     @param idsFields The array of ids fields.  note: position in the arrays is important.
     */
    IDS(std::vector<IDSBuilder::Field> idsFields);

	/**
     Create an instance of IDS from a vector of fields and an array of the raw data as chars array.
     @param idsFields The array of ids fields. note: position in the array is important.
     @param binaryArray The array of ids raw binary data. note: position in the array is important.
	 */
    IDS(std::vector<IDSBuilder::Field> idsFields, std::vector<char> binaryArray);

	/**
     Set other fields array as the IDS fields.
     @param idsFields The array of ids fields. note: position in the array is important.
	 */
    void set_ids(std::vector<IDSBuilder::Field> idsFields);

	/**
     Set other fields and chars array and as the IDS fields and raw array data.
     @param idsFields The array of ids fields. note: position in the array is important.
     @param binaryArray The array of ids raw binary data. note: position in the array is important.
	 */
    void set_ids(std::vector<IDSBuilder::Field> idsFields, std::vector<char> binaryArray);

    /**
     Get the total bits amount of the current IDS.
     */
    unsigned int get_total_bits();
    
    /**
     Get the total bytes amount of the current IDS.
     */
    unsigned int get_total_bytes();

    /**
     Convert field to an array of chars (represeting array of bytes).
     @param field A field to convert his value to binary.
     @return The binary data as array of chars (represeting array of bytes).  
     */
    static std::vector<char> encode_field(Field field);

    /**
     Convert an IDS to an array of chars (represeting array of bytes).
     @param idsFields The IDS to encode.
     @return The binary data as array of chars (represeting array of bytes).
     */
    static std::vector<char> encode_ids(IDS idsFields);
    
    /**
     Convert the IDS to an array of bytes).
     @return The binary data as array of chars (represeting array of bytes).
     */
    std::vector<char> encode_ids();

    /**
     Convert a binary data represnting by array of chars to a value.
     @param field The field structure to know how to convert the bytes.
     @param binaryArray The raw binary data as chars array to convert from.
     @return A field loaded with the converted value.
     */
    static Field decode_field(Field field, std::vector<char> binaryArray);

    /**
     Load an IDS fileds with data from a raw binary data.
     @param idsFields The ids stracture.
     @param binaryArray The raw binary data as chars array to convert from.
     @return An IDS loaded with the converted value.
     */
    static IDS decode_ids(IDS idsFields, std::vector<char> binaryArray);

    /**
     Load the IDS fileds with data from a raw binary data.
     @return An IDS loaded with the converted value.
     */
    IDS decode_ids();

    /**
     Print an array of binary data.
     @param rawBinaryArray The binary data as array of chars (represeting array of bytes).
     @param asDecimalNumbersArray print the binary value as binary digits (=false) or decimal numbers (=true) the default is true.
     */
    static void print_ids(std::vector<char> rawBinaryArray, bool asDecimalNumbersArray = true);

    /**
     Print an IDS as binary data.
     @param ids an IDS to print.
     @param asDecimalNumbersArray print the binary value as binary digits (=false) or decimal numbers (=true) the default is true.
     */
    static void print_ids(IDS ids, bool asDecimalNumbersArray = true);

    /**
     Print the IDS as binary data.
     @param asDecimalNumbersArray print the binary value as binary digits (=false) or decimal numbers (=true) the default is true.
     */
    void print_ids(bool asDecimalNumbersArray = true);
};

#endif

}
