
#include "constants.hpp"

namespace IDSBuilder
{
#ifndef IDS_FIELD_H
#define IDS_FIELD_H

class Field
{
public:
	/* Bites amount for current field */
	size_t _bytesAmount;
	/* Is the field value support fraction */
	bool _isFloat;
	/* int number value */
	long long _value;
	/* float number value */
	double _floatValue;

	/**
	 * @param bytesAmount The amount of field side in bytes.
	 * @param value The int value to set to this field.
	 */
	Field(size_t bytesAmount, long long value);
	/**
	 * @param bytesAmount The amount of field side in bytes.
	 * @param value The float value to set to this field.
	 */
	Field(size_t bytesAmount, double value);
	/**
	 * @param value The value of field, the size is the c++ short size.
	 */
	Field(short value);
	/**
	 * @param value The value of field, the size is the c++ int size.
	 */
	Field(int value);
	/**
	 * @param value The value of field, the size is the c++ long long size.
	 */
	Field(long long value);
	/**
	 * @param value The value of field, the size is the c++ float size.
	 */
	Field(float value);
	/**
	 * @param value The value of field, the size is the c++ double size.
	 */
	Field(double value);
};

#endif

#ifndef IDS_FIELD_CPP
#define IDS_FIELD_CPP

Field::Field(size_t bytesAmount, long long value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(bytesAmount)
{
}

Field::Field(size_t bytesAmount, double value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(bytesAmount) {}

Field::Field(short value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(SHORT_BYTES_AMOUNT) {}

Field::Field(int value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(INT_BYTES_AMOUNT) {}

Field::Field(long long value) : _isFloat(false), _value(value), _floatValue(0), _bytesAmount(LONG_LONG_BYTES_AMOUNT) {}

Field::Field(float value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(FLOAT_BYTES_AMOUNT) {}

Field::Field(double value) : _isFloat(true), _value(0), _floatValue(value), _bytesAmount(DOUBLE_BYTES_AMOUNT) {}

#endif

} // namespace IDSBuilder