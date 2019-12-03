
#include "constants.h"

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

} // namespace IDSBuilder