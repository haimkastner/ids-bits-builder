#include <iostream>
#include <vector>

#include "ids_builder.h"

namespace IDSBuilder
{

IDS::IDS(std::vector<IDSBuilder::Field> idsFields)
{
    this->set_ids(idsFields);
}

IDS::IDS(std::vector<IDSBuilder::Field> idsFields, std::vector<char> binaryArray)
{
    this->set_ids(idsFields, binaryArray);
}

void IDS::set_ids(std::vector<IDSBuilder::Field> idsFields)
{
    _idsFields = idsFields;
}

void IDS::set_ids(std::vector<IDSBuilder::Field> idsFields, std::vector<char> binaryArray)
{
    _idsFields = idsFields;
    _binaryArray = binaryArray;
}

unsigned int IDS::get_total_bits()
{
    return this->get_total_bytes() * BITS_IN_BYTE;
}

unsigned int IDS::get_total_bytes()
{
    unsigned int bytes = 0;
    for (auto const &it : this->_idsFields)
    {
        bytes += it._bytesAmount;
    }
    return bytes;
}

std::vector<char> IDS::convert_float(double value)
{
    QwordBytes qword;
    qword.floatValue = value;

    auto res = std::vector<char>();

    res.push_back(qword.bytes.byte0);
    res.push_back(qword.bytes.byte1);
    res.push_back(qword.bytes.byte2);
    res.push_back(qword.bytes.byte3);
    res.push_back(qword.bytes.byte4);
    res.push_back(qword.bytes.byte5);
    res.push_back(qword.bytes.byte6);
    res.push_back(qword.bytes.byte7);

    return res;
}

std::vector<char> IDS::convert_float(float value)
{
    DwordBytes dword;
    dword.floatValue = value;

    auto res = std::vector<char>();

    res.push_back(dword.bytes.byte0);
    res.push_back(dword.bytes.byte1);
    res.push_back(dword.bytes.byte2);
    res.push_back(dword.bytes.byte3);

    return res;
}

std::vector<char> IDS::convert_float(size_t bytesAmount, double value)
{
    switch (bytesAmount)
    {
    case FLOAT_BYTES_AMOUNT:
        return IDS::convert_float((float)value);
        break;
    case DOUBLE_BYTES_AMOUNT:
        return IDS::convert_float(value);
        break;

    default:
        throw std::invalid_argument("Float value conveter supports only 4 (= float) or 8 (= double)");
        break;
    }
}

std::vector<char> IDS::convert_int(short value)
{
    WordBytes word;
    word.value = value;

    auto res = std::vector<char>();

    res.push_back(word.bytes.byte0);
    res.push_back(word.bytes.byte1);

    return res;
}

std::vector<char> IDS::convert_int(int value)
{
    DwordBytes dword;
    dword.value = value;

    auto res = std::vector<char>();

    res.push_back(dword.bytes.byte0);
    res.push_back(dword.bytes.byte1);
    res.push_back(dword.bytes.byte2);
    res.push_back(dword.bytes.byte3);

    return res;
}

std::vector<char> IDS::convert_int(long long value)
{
    QwordBytes qword;
    qword.value = value;

    auto res = std::vector<char>();

    res.push_back(qword.bytes.byte0);
    res.push_back(qword.bytes.byte1);
    res.push_back(qword.bytes.byte2);
    res.push_back(qword.bytes.byte3);
    res.push_back(qword.bytes.byte4);
    res.push_back(qword.bytes.byte5);
    res.push_back(qword.bytes.byte6);
    res.push_back(qword.bytes.byte7);

    return res;
}

std::vector<char> IDS::convert_int(size_t bytesAmount, long long value)
{
    switch (bytesAmount)
    {
    case SHORT_BYTES_AMOUNT:
        return IDS::convert_int((short)value);
        break;
    case INT_BYTES_AMOUNT:
        return IDS::convert_int((int)value);
        break;
    case LONG_LONG_BYTES_AMOUNT:
        return IDS::convert_int(value);
        break;

    default:
        throw std::invalid_argument("Int value conveter supports only 2 (= short) 4 (= int) or 8 (= long long)");
        break;
    }
}

std::vector<char> IDS::convert_int_manually(size_t bytesAmount, long long value)
{
    // Convert any value to unsigned value befor converting it to binary array
    unsigned long long copyValue;
    if (value < 0)
        copyValue = 1 + (~(unsigned long long)(-value));
    else
        copyValue = value;

    // Get the amount of bits that need to alloc
    auto binaryBits = BITS_IN_BYTE * bytesAmount;

    // TODO:: use vector;
    // Alloc memory to hold the binary values in a decimal variables
    short *binary = new short[binaryBits];

    // Convert the value to bits value one by one
    for (size_t i = 0; i < binaryBits; i++)
    {
        if (copyValue <= 0)
            binary[i] = 0;
        else
        {
            binary[i] = copyValue % 2;
            copyValue = copyValue / 2;
        }
    }

    std::vector<char> finalData;

    // Convert the deciaml repesentation of binary value to a real binary value in the memory
    for (size_t i = 0; i < bytesAmount; i++)
    {
        // Get the position of the byte in the binary array
        int offset = i * BITS_IN_BYTE;

        // A real byte
        Byte byte;

        // Fill the bits with a binary value (0/1) in the correct position in a byte.
        byte.bits.bit0 = binary[offset + 0];
        byte.bits.bit1 = binary[offset + 1];
        byte.bits.bit2 = binary[offset + 2];
        byte.bits.bit3 = binary[offset + 3];
        byte.bits.bit4 = binary[offset + 4];
        byte.bits.bit5 = binary[offset + 5];
        byte.bits.bit6 = binary[offset + 6];
        byte.bits.bit7 = binary[offset + 7];

        // Add the byte to the char collection
        finalData.push_back(byte.value);
    }

    delete[] binary;
    return finalData;
}

std::vector<char> IDS::encode_field(Field field)
{
    if (field._bytesAmount > LONG_LONG_BYTES_AMOUNT || field._bytesAmount > DOUBLE_BYTES_AMOUNT)
        throw std::invalid_argument("The bytes amount is limited to 8 bytes (long long / double size)");

    if (field._isFloat)
        return IDS::convert_float(field._bytesAmount, field._floatValue);
    else if (field._bytesAmount == SHORT_BYTES_AMOUNT ||
             field._bytesAmount == INT_BYTES_AMOUNT ||
             field._bytesAmount == LONG_LONG_BYTES_AMOUNT)
        return IDS::convert_int(field._bytesAmount, field._value);

    return IDS::convert_int_manually(field._bytesAmount, field._value);
}

std::vector<char> IDS::encode_ids(IDS IDSData)
{
    std::vector<char> finalData;
    for (auto const &IDSDataIt : IDSData._idsFields)
    {
        auto fieldBytes = IDS::encode_field(IDSDataIt);
        for (auto const &fieldBytesIt : fieldBytes)
        {
            finalData.push_back(fieldBytesIt);
        }
    }

    return finalData;
}

std::vector<char> IDS::encode_ids()
{
    return IDS::encode_ids(this->_idsFields);
}

double IDS::convert_float(size_t bytesAmount, std::vector<char> binaryArray)
{
    if (binaryArray.size() != bytesAmount)
        throw std::invalid_argument("Array size not match the bytes amount");

    switch (bytesAmount)
    {
    case FLOAT_BYTES_AMOUNT:
        DwordBytes dword;

        dword.bytes.byte0 = binaryArray[0];
        dword.bytes.byte1 = binaryArray[1];
        dword.bytes.byte2 = binaryArray[2];
        dword.bytes.byte3 = binaryArray[3];

        return dword.floatValue;
    case DOUBLE_BYTES_AMOUNT:
        QwordBytes qword;

        qword.bytes.byte0 = binaryArray[0];
        qword.bytes.byte1 = binaryArray[1];
        qword.bytes.byte2 = binaryArray[2];
        qword.bytes.byte3 = binaryArray[3];
        qword.bytes.byte4 = binaryArray[4];
        qword.bytes.byte5 = binaryArray[5];
        qword.bytes.byte6 = binaryArray[6];
        qword.bytes.byte7 = binaryArray[7];

        return qword.floatValue;
    default:
        throw std::invalid_argument("Float value conveter supports only 4 (= float) or 8 (= double)");
    }
}

long long IDS::convert_int(size_t bytesAmount, std::vector<char> binaryArray)
{
    if (binaryArray.size() != bytesAmount)
        throw std::invalid_argument("Array size not match the bytes amount");

    switch (bytesAmount)
    {
    case SHORT_BYTES_AMOUNT:
        WordBytes word;

        word.bytes.byte0 = binaryArray[0];
        word.bytes.byte1 = binaryArray[1];

        return word.value;
    case INT_BYTES_AMOUNT:
        DwordBytes dword;

        dword.bytes.byte0 = binaryArray[0];
        dword.bytes.byte1 = binaryArray[1];
        dword.bytes.byte2 = binaryArray[2];
        dword.bytes.byte3 = binaryArray[3];

        return dword.value;
    case LONG_LONG_BYTES_AMOUNT:
        QwordBytes qword;

        qword.bytes.byte0 = binaryArray[0];
        qword.bytes.byte1 = binaryArray[1];
        qword.bytes.byte2 = binaryArray[2];
        qword.bytes.byte3 = binaryArray[3];
        qword.bytes.byte4 = binaryArray[4];
        qword.bytes.byte5 = binaryArray[5];
        qword.bytes.byte6 = binaryArray[6];
        qword.bytes.byte7 = binaryArray[7];

        return qword.value;
    default:
        throw std::invalid_argument("Int value conveter supports only 2 (= short) 4 (= int) or 8 (= long long)");
    }
}

Field IDS::decode_field(Field field, std::vector<char> binaryArray)
{
    if (field._bytesAmount > LONG_LONG_BYTES_AMOUNT || field._bytesAmount > DOUBLE_BYTES_AMOUNT)
        throw std::invalid_argument("The bytes amount is limited to 8 bytes (long long / double size)");

    if (field._isFloat)
        field._floatValue = IDS::convert_float(field._bytesAmount, binaryArray);
    else if (field._bytesAmount == SHORT_BYTES_AMOUNT ||
             field._bytesAmount == INT_BYTES_AMOUNT ||
             field._bytesAmount == LONG_LONG_BYTES_AMOUNT)
        field._value = IDS::convert_int(field._bytesAmount, binaryArray);

    return field;
    // TODO: convart back manually
    // return IDS::convert_int_manually(field._bytesAmount, field._value);
}

IDS IDS::decode_ids(IDS idsFields, std::vector<char> binaryArray)
{
    if (idsFields.get_total_bytes() != binaryArray.size())
        throw std::invalid_argument("Array size not match the IDS fields");

    std::vector<char> finalData;
    for (int i = 0; i < idsFields._idsFields.size(); i++)
    {
        std::vector<char> fieldBinaryArray;
        for (int j = 0; j < idsFields._idsFields[i]._bytesAmount; j++)
        {
            auto b = binaryArray.front();
            binaryArray.erase(binaryArray.begin());
            fieldBinaryArray.push_back(b);
        }

        idsFields._idsFields[i] = IDS::decode_field(idsFields._idsFields[i], fieldBinaryArray);
    }
    return idsFields;
}

IDS IDS::decode_ids()
{
    auto decodedIds = IDS::decode_ids(this->_idsFields, this->_binaryArray);
    this->set_ids(decodedIds._idsFields);
    return decodedIds;
}

void IDS::print_ids(std::vector<char> rawBinaryArray, bool asDecimalNumbersArray)
{
    //std::reverse(rawBinaryArray.begin(), rawBinaryArray.end());
    std::cout << "Array of binary data" << (asDecimalNumbersArray ? ", as it repesented by a decimal numbers array" : "") << std::endl;
    for (auto const &it : rawBinaryArray)
    {
        Byte byte;
        byte.value = it;
        if (asDecimalNumbersArray)
            std::cout << (unsigned int)(unsigned char)byte.value << ", ";
        else
            std::cout << byte.bits.bit0
                      << byte.bits.bit1
                      << byte.bits.bit2
                      << byte.bits.bit3
                      << byte.bits.bit4
                      << byte.bits.bit5
                      << byte.bits.bit6
                      << byte.bits.bit7 << ", ";
    }
    std::cout << std::endl
              << "============= THE END =============" << std::endl;
}

void IDS::print_ids(IDS ids, bool asDecimalNumbersArray)
{
    IDS::print_ids(ids.encode_ids(ids), asDecimalNumbersArray);
}

void IDS::print_ids(bool asDecimalNumbersArray)
{
    IDS::print_ids(this->_idsFields, asDecimalNumbersArray);
}

} // namespace IDSBuilder