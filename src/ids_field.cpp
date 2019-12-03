
#include "ids_field.h"

namespace IDSBuilder
{

Field::Field(size_t bytesAmount, long long value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(bytesAmount)
{
}

Field::Field(size_t bytesAmount, double value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(bytesAmount) {}

Field::Field(short value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(SHORT_BYTES_AMOUNT) {}

Field::Field(int value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(INT_BYTES_AMOUNT) {}

Field::Field(long long value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(LONG_LONG_BYTES_AMOUNT) {}

Field::Field(float value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(FLOAT_BYTES_AMOUNT) {}

Field::Field(double value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(DOUBLE_BYTES_AMOUNT) {}

} // namespace IDSBuilder