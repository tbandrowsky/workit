
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <ctime>

#define IMPLEMENT_COMPARE \
		template <class T> friend bool operator >(const T& _a, const T& _b);\
		template <class T> friend bool operator >=(const T& _a, const T& _b);\
		template <class T> friend bool operator ==(const T& _a, const T& _b);\
		template <class T> friend bool operator <=(const T& _a, const T& _b);\
		template <class T> friend bool operator <(const T& _a, const T& _b);\
		template <class T> friend bool operator !=(const T& _a, const T& _b); 

namespace json
{
	enum jvalue_type
	{
		type_unknown = 0,
		type_int8 = 1,
		type_int16 = 2,
		type_int32 = 3,
		type_int64 = 4,
		type_double = 5,
		type_datetime = 6,
		type_string = 7,
		type_jobject = 8,
		type_jarray = 9
	};

	enum jvalue_unit
	{
		unit_base = 0,

		// string units
		unit_fullname = 1,
		unit_firstname = 2,
		unit_sublastname = 3,
		unit_lastname = 4,
		unit_middlename = 5,
		unit_ssn = 6,
		unit_email = 7,
		unit_title = 8,
		unit_street = 9,
		unit_substreet = 10,
		unit_city = 11,
		unit_state = 12,
		unit_postal = 13,
		unit_countryname = 21,
		unit_countrycode = 22,
		unit_longname = 23,
		unit_shortname = 24,
		unit_unit = 25,
		unit_code_symbol = 26,
		unit_code_operator = 27,

		// date units
		unit_birthday = 28,
		unit_scheduled = 29,

		// float units
		unit_money = 30,

		// int units
		unit_inventory_qty = 31
	};

	class jdatetime;
	class jlong;
	class jdouble;
	class jstring;
	class jarray;
	class jobject;

	class jresult_base
	{
	public:
		bool ok;
		std::string message;
	};

	template <class jclass> class jresult : public jresult_base
	{
	public:
		jclass item;
	};

	class jdatetime_result;
	class jdouble_result;
	class jstring_result;
	class jlong_result;
	class jblob_result;
	class jobject_result;
	class jarray_result;
	class jtable_result;

	class jvalue
	{
		jvalue_type jtype;

	public:

		jvalue(jvalue_type jtype);
		jvalue_type get_type() { return jtype; }

		bool is_comparable()
		{
			return true;
		}

		IMPLEMENT_COMPARE;

		virtual jdatetime_result as_datetime() = 0;
		virtual jdouble_result as_double() = 0;
		virtual jlong_result as_long() = 0;
		virtual jstring_result as_string() = 0;
		virtual jblob_result as_jblob() = 0;

		virtual jobject_result as_jobject() = 0;
		virtual jarray_result as_jarray() = 0;
		virtual jtable_result as_jtable() = 0;
	};

	template <class T> bool operator > (const T& _a, const T& b)
	{
		return _a.compare(b) > 0;
	}

	template <class T> bool operator >= (const T& _a, const T& b)
	{
		return _a.compare(b) >= 0;
	}

	template <class T> bool operator == (const T& _a, const T& b)
	{
		return _a.compare(b) == 0;
	}

	template <class T> bool operator <= (const T& _a, const T& b)
	{
		return _a.compare(b) <= 0;
	}

	template <class T> bool operator < (const T& _a, const T& b)
	{
		return _a.compare(b) < 0;
	}

	template <class T> bool operator != (const T& _a, const T& b)
	{
		return _a.compare(b) != 0;
	}

	class jdatetime : public jvalue
	{
	private:

		struct jdatetime_parts
		{
			unsigned short millisecond : 10;
			unsigned char second : 6;
			unsigned char minute : 6;
			unsigned char hour : 5;
			unsigned char day : 5;
			unsigned char month : 4;
			unsigned short year : 11;
		};

		union
		{
			jdatetime_parts mdy;
			int64_t			packedtime;
		};

	public:

		jdatetime(unsigned short _year = 0,
			unsigned short _month = 0,
			unsigned short _day = 0,
			unsigned short _hour = 0,
			unsigned short _minute = 0,
			unsigned short _second = 0,
			unsigned short _millisecond = 0) : jvalue(jvalue_type::type_datetime)
		{
			jdatetime_parts mdy;
			mdy.year = _year;
			mdy.month = _month;
			mdy.day = _day;
			mdy.hour = _hour;
			mdy.day = _day;
			mdy.hour = _hour;
			mdy.minute = _minute;
			mdy.second = _second;
			mdy.millisecond = _millisecond;
		}

		jdatetime(const jdatetime& _src) : jvalue(jvalue_type::type_datetime)
		{
			packedtime = _src.packedtime;
		}

		int compare(const jdatetime& _src) const
		{
			packedtime - _src.packedtime;
		}

		jdatetime static now()
		{
			auto current = std::time(nullptr);
			auto tmp = localtime(&current);

			auto newdatetime = jdatetime(tmp->tm_year, tmp->tm_mon, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
			return newdatetime;
		}

		int year()
		{
			return mdy.year;
		}

		int month()
		{
			return mdy.month;
		}

		int day()
		{
			return mdy.day;
		}

		int hour()
		{
			return mdy.hour;
		}

		int minute()
		{
			return mdy.minute;
		}

		int second()
		{
			return mdy.second;
		}

		int millisecond()
		{
			return mdy.millisecond;
		}

		jdatetime& operator = (const jdatetime& _src)
		{
			packedtime = _src.packedtime;
			return *this;
		}

		IMPLEMENT_COMPARE;

		virtual jdatetime_result as_datetime();
		virtual jdouble_result as_double();
		virtual jlong_result as_long();
		virtual jstring_result as_string();
		virtual jblob_result as_jblob();

		virtual jobject_result as_jobject();
		virtual jarray_result as_jarray();
		virtual jtable_result as_jtable();

	};

	class jlong : public jvalue
	{
		int64_t value;
	public:

		IMPLEMENT_COMPARE;

		int compare(const jlong& _src) const
		{
			return value - _src.value;
		}
	};

	class jdouble : public jvalue
	{
		double value;
	public:

		IMPLEMENT_COMPARE;

		int compare(const jdouble& _src) const
		{
			return value > _src.value ? 1 : (value < _src.value) ? -1 : 0;
		}

	};

	class jstring : public jvalue
	{
		int length;
		char value[];

	public:

		IMPLEMENT_COMPARE;

		int compare(const jstring& _src) const
		{
			return value > _src.value ? 1 : (value < _src.value) ? -1 : 0;
		}

	};

}

