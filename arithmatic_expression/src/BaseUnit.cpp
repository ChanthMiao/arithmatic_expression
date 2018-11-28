#include"BaseUnit.h"
namespace MyLab
{
	BaseUnit::BaseUnit() :isInt(true), x(0ll), y(0.0l)
	{
	}

	BaseUnit::BaseUnit(const long long int num)
	{
		isInt = true;
		x = num;
	}

	BaseUnit::BaseUnit(const long double num)
	{
		isInt = false;
		y = num;
	}

	BaseUnit::BaseUnit(const BaseUnit & other)
	{
		isInt = other.isInt;
		if (isInt)
		{
			x = other.x;
		}
		else
		{
			y = other.y;
		}
	}

	BaseUnit::~BaseUnit()
	{
	}

	BaseUnit BaseUnit::operator+(const BaseUnit & other) const
	{
		BaseUnit rt;
		//优先处理整数加法
		if (this->isInt && other.isInt)
		{
			rt.isInt = true;
			rt.x = this->x + other.x;
			//溢出检测，如果存在整型溢出，则转为浮点运算
			if (rt.x - other.x != this->x)
			{
				rt.isInt = false;
				rt.y = BU_fe(this->x) + BU_fe(other.x);
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		else
		{
			fenv_t curr_fe_env;
			std::fegetenv(&curr_fe_env);
			rt.isInt = false;
			rt.y = ((this->isInt) ? BU_fe(this->x) : this->y) + ((other.isInt) ? BU_fe(other.x) : other.y);
			if (std::fabsl(rt.y - ((other.isInt) ? BU_fe(other.x) : other.y) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
			{
				std::fesetenv(&curr_fe_env);
			}
			else
			{
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		return rt;
	}

	BaseUnit BaseUnit::operator-(const BaseUnit & other) const
	{
		BaseUnit rt;
		//优先处理整数减法
		if (this->isInt && other.isInt)
		{
			rt.isInt = true;
			rt.x = this->x - other.x;
			//溢出检测，如果存在整型溢出，则转为浮点运算
			if (rt.x + other.x != this->x)
			{
				rt.isInt = false;
				rt.y = BU_fe(this->x) - BU_fe(other.x);
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		else
		{
			fenv_t curr_fe_env;
			std::fegetenv(&curr_fe_env);
			rt.isInt = false;
			rt.y = ((this->isInt) ? BU_fe(this->x) : this->y) - ((other.isInt) ? BU_fe(other.x) : other.y);
			if (std::fabsl(rt.y + ((other.isInt) ? BU_fe(other.x) : other.y) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
			{
				std::fesetenv(&curr_fe_env);
			}
			else
			{
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		return rt;
	}
	BaseUnit BaseUnit::operator*(const BaseUnit & other) const
	{
		BaseUnit rt;
		//优先处理整数乘法
		if (this->isInt && other.isInt)
		{
			rt.isInt = true;
			rt.x = this->x * other.x;
			//溢出检测，如果存在整型溢出，则转为浮点运算
			if (rt.x / other.x != this->x)
			{
				rt.isInt = false;
				rt.y = BU_fe(this->x) * BU_fe(other.x);
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		else
		{
			fenv_t curr_fe_env;
			std::fegetenv(&curr_fe_env);
			rt.isInt = false;
			rt.y = ((this->isInt) ? BU_fe(this->x) : this->y) * ((other.isInt) ? BU_fe(other.x) : other.y);
			if (std::fabsl(rt.y / ((other.isInt) ? BU_fe(other.x) : other.y) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
			{
				std::fesetenv(&curr_fe_env);
			}
			else
			{
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		return rt;
	}
	BaseUnit BaseUnit::operator/(const BaseUnit & other) const
	{
		BaseUnit rt;
		if (this->isInt && other.isInt)
		{
			if (other.x != 0)
			{
				rt.isInt = true;
				rt.x = this->x / other.x;
				//无法整除，则转为浮点运算
				if (rt.x * other.x != this->x)
				{
					fenv_t curr_fe_env;
					std::fegetenv(&curr_fe_env);
					rt.isInt = false;
					rt.y = BU_fe(this->x) / BU_fe(other.x);
					if (std::fabsl(rt.y * BU_fe(other.x) - BU_fe(this->x)) < ACCEPTABLE_MISS)
					{
						std::fesetenv(&curr_fe_env);
					}
					else
					{
						std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
					}
				}
			}
			else
			{
				throw DIVBYZERO;
			}
		}
		else
		{
			fenv_t curr_fe_env;
			std::fegetenv(&curr_fe_env);
			rt.isInt = false;
			rt.y = ((this->isInt) ? BU_fe(this->x) : this->y) / ((other.isInt) ? BU_fe(other.x) : other.y);
			if (std::fabsl(rt.y * ((other.isInt) ? BU_fe(other.x) : other.y) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
			{
				std::fesetenv(&curr_fe_env);
			}
			else
			{
				std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);//仅保留精度异常标志位
			}
		}
		return rt;
	}
	BaseUnit BaseUnit::operator%(const BaseUnit & other) const
	{
		BaseUnit rt;
		//优先考虑整数求模
		if (this->isInt && other.isInt)
		{
			if (other.x != 0)
			{
				rt.isInt = true;
				rt.x = this->x%other.x;
			}
			else
			{
				throw DIVBYZERO;
			}
		}
		else
		{
			rt.isInt = false;
			rt.y = std::fmodl((this->isInt) ? BU_fe(x) : y, (other.isInt) ? BU_fe(other.x) : other.y);
			std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT);
		}
		return rt;
	}
	BaseUnit BaseUnit::operator^(const BaseUnit & other) const
	{
		BaseUnit rt;
		if (this->isInt && other.isInt)
		{
			if (other.x >= 0 && this->x != 0)
			{
				rt.isInt = true;
				rt.x = 1;
				BU_int tmp = rt.x;
				for (BU_int i = 0; i < other.x; i++)
				{
					rt.x = tmp * this->x;
					//溢出检测
					if (rt.x /this->x != tmp)
					{
						rt.isInt = false;
						break;
					}
					tmp = rt.x;
				}
				if (!rt.isInt)
				{
					rt.y = std::powl((this->isInt) ? BU_fe(x) : y, (other.isInt) ? BU_fe(other.x) : other.y);
					std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
				}
			}
			else if (this->x == 0 && other.x > 0)
			{
				rt.isInt = true;
				rt.x = 0;
			}
			else if (this->x == 0)
			{
				throw UNDEFINE;
			}
			else
			{
				//this->x !=0 && other.x < 0
				fenv_t curr_fe_env;
				std::fegetenv(&curr_fe_env);/*保存当前浮点环境*/
				rt.isInt = false;
				rt.y = std::powl(BU_fe(this->x), BU_fe(other.x));
				/*浮点精度有损，但仍在可接受范围内*/
				BU_fe back = BU_fe(BaseUnit(1.0l) / other);
				if (std::fabsl(std::powl(rt.y, back) - BU_fe(this->x)) < ACCEPTABLE_MISS)
				{
					std::fesetenv(&curr_fe_env);
				}
				else
				{
					std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
				}
			}
		}
		else if (std::fabsl(((other.isInt) ? BU_fe(other.x) : other.y) - 0.0l) < ACCEPTABLE_MISS)//other.y==0.0
		{
			if (std::fabsl(((this->isInt) ? BU_fe(this->x) : this->y) - 0.0l) < ACCEPTABLE_MISS)//this.x==0.0
			{
				throw UNDEFINE;
			}
			else
			{
				rt.isInt = true;
				rt.x = 1;
			}
		}
		else if (std::fabsl(((this->isInt) ? BU_fe(this->x) : this->y) - 0.0l) < ACCEPTABLE_MISS)
		{
			if (((other.isInt) ? BU_fe(other.x) : other.y) < -ACCEPTABLE_MISS)
			{
				throw UNDEFINE;
			}
			else
			{
				rt.isInt = true;
				rt.x = 0;
			}
		}
		else//other != 0 && *this != 0
		{
			//other != 0 && *this > 0
			if (((this->isInt) ? BU_fe(this->x) : this->y) > ACCEPTABLE_MISS)
			{
				fenv_t curr_fe_env;
				std::fegetenv(&curr_fe_env);/*保存当前浮点环境*/
				rt.isInt = false;
				rt.y = std::powl((this->isInt) ? BU_fe(this->x) : this->y, (other.isInt) ? BU_fe(other.x) : other.y);
				/*浮点精度有损，但仍在可接受范围内*/
				BU_fe back = BU_fe(BaseUnit(1.0l) / other);
				if (std::fabsl(BU_fe(std::llround(rt.y)) - rt.y) < ACCEPTABLE_MISS)
				{
					rt.isInt = true;
					rt.x = std::llround(rt.y);
				}
				else
				{
					rt.isInt = false;
				}
				if (std::fabsl(std::powl((rt.isInt) ? BU_fe(rt.x) : rt.y, back) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
				{
					std::fesetenv(&curr_fe_env);
				}
				else
				{
					std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
				}
			}
			else
			{
				fenv_t curr_fe_env;
				std::fegetenv(&curr_fe_env);/*保存当前浮点环境*/
				rt.y = std::powl(std::powl((this->isInt) ? BU_fe(this->x) : this->y, 2.0l), ((other.isInt) ? BU_fe(other.x) : other.y) /2.0l);
				rt.isInt = false;
				BU_fe back = BU_fe(BaseUnit(1.0l) / other);
				if ((std::powl(rt.y, back) * ((this->isInt) ? BU_fe(this->x) : this->y)) < -ACCEPTABLE_MISS)
				{
					rt.y = -rt.y;
				}
				if (std::fabsl(BU_fe(std::llround(rt.y)) - rt.y) < ACCEPTABLE_MISS)
				{
					rt.isInt = true;
					rt.x = std::llround(rt.y);
				}
				else
				{
					rt.isInt = false;
				}
				if (std::fabsl(std::powl((rt.isInt) ? BU_fe(rt.x) : rt.y, back) - ((this->isInt) ? BU_fe(this->x) : this->y)) < ACCEPTABLE_MISS)
				{					
					std::fesetenv(&curr_fe_env);
				}
				else
				{
					std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
				}
			}		
		}
		return rt;
	}
	BaseUnit BaseUnit::operator&(const BaseUnit & other) const
	{
		BaseUnit rt;
		if (other.isInt && other.x == 0)
		{
			throw UNDEFINE;
		}
		if (!other.isInt && other.y -0.0l < ACCEPTABLE_MISS)
		{
			throw UNDEFINE;
		}
		else
		{
			BaseUnit tmp = BaseUnit(1ll) / other;
			rt = (*this) ^ tmp;
		}
		return rt;
	}
	BaseUnit & BaseUnit::operator=(const BaseUnit & other)
	{
		isInt = other.isInt;
		if (isInt)
		{
			x = other.x;
		}
		else
		{
			y = other.y;
		}
		return *this;
	}
	bool BaseUnit::operator==(const BaseUnit & other)
	{
		if (isInt == other.isInt)
		{
			if (isInt)
			{
				return(x == other.x) ? true : false;
			}
			else
			{
				return(std::fabsl(y - other.y) < ACCEPTABLE_MISS) ? true : false;
			}
		}
		else if (isInt)
		{
			if (x != BU_int(BU_fe(x)))
			{
				return false;
			}
			else if (std::fabsl(BU_fe(x) - other.y) < ACCEPTABLE_MISS)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (y != BU_int(BU_fe(y)))
			{
				return false;
			}
			else if (std::fabsl(BU_fe(y) - other.x) < ACCEPTABLE_MISS)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	BaseUnit::operator long long int() const
	{
		if (isInt)
		{
			return x;
		}
		else
		{
			return BU_int(y);
		}
	}
	BaseUnit::operator long double() const
	{
		if (isInt)
		{
			return BU_fe(x);
		}
		else
		{
			return y;
		}
	}
	void BaseUnit::transform_fe(BU_fe src, BU_fe & m, BU_int & b) const
	{
		int tmp_x;
		BU_fe tmp_y;
		tmp_y = std::frexpl(src, &tmp_x);
		m = tmp_y * std::powl(2, 52);//win平台long double精度极限
		b = 52 - tmp_x;
	}
	std::istream & operator>>(std::istream & data_in, BaseUnit & obj)
	{
		obj.isInt = true;
		char next_c = data_in.peek();
		std::string tmp = "";
		while ((next_c >= '0' && next_c <= '9') || next_c == '.')
		{
			if (next_c == '.')
			{
				obj.isInt = false;
			}
			data_in >> next_c;
			tmp.append(1, next_c);
			next_c = data_in.peek();
		}
		if (obj.isInt)
		{
			obj.x = std::stoll(tmp);
		}
		else
		{
			obj.y = std::stold(tmp);
			if (std::fabsl(obj.y - 0.0l) < ACCEPTABLE_MISS)
			{
				obj.isInt = true;
				obj.x = 0ll;
				return data_in;
			}
			while (tmp.back() == '0')
			{
				tmp.pop_back();
			}
			tmp.pop_back();
			BU_fe comp_fe = std::stold(tmp);
			if (std::fabsl(obj.y - comp_fe) < ACCEPTABLE_MISS)
			{
				throw std::out_of_range("");
			}
		}
		return data_in;
	}
	std::ostream & operator<<(std::ostream & os, BaseUnit & obj)
	{
		if (obj.isInt)
		{
			os << obj.x;
		}
		else
		{
			os << obj.y;
		}
		return os;
	}
}