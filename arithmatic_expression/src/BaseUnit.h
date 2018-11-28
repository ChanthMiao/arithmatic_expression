#pragma once
#include<cmath>
#include<iostream>
#include<cfenv>
#include<sstream>
#include<stdexcept>
#include<string>
#pragma fenv_access (on)
namespace MyLab
{
	constexpr auto DIVBYZERO = 'A';
	constexpr auto UNDEFINE = 'B';
	constexpr auto ACCEPTABLE_MISS = 0.000000000000001l;
	typedef long long int BU_int;
	typedef long double BU_fe;
	class BaseUnit
	{
	public:
		BaseUnit();
		BaseUnit(const long long int num);
		BaseUnit(const long double num);
		BaseUnit(const BaseUnit & other);
		~BaseUnit();
		BaseUnit operator+(const BaseUnit & other) const;
		BaseUnit operator-(const BaseUnit & other) const;
		BaseUnit operator*(const BaseUnit & other) const;
		BaseUnit operator/(const BaseUnit & other) const;
		BaseUnit operator%(const BaseUnit & other) const;
		BaseUnit operator^(const BaseUnit & other) const;
		BaseUnit operator&(const BaseUnit & other) const;
		BaseUnit &operator=(const BaseUnit & other);
		bool operator==(const BaseUnit & other);
		operator long long int() const;
		operator long double() const;
		friend std::istream &operator>>(std::istream &, BaseUnit &);
		friend std::ostream &operator<<(std::ostream &, BaseUnit &);
	private:
		bool isInt;
		BU_int x;
		BU_fe y;
		void transform_fe(BU_fe, BU_fe&, BU_int&) const;
	};
}
