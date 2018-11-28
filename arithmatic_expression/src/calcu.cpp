#include"calcu.h"

namespace MyLab
{
	std::string &calcu::format_tool(std::string &orign)
	{
		size_t index = orign.find('=', 0);
		orign.replace(index, 1, ")=");
		orign = "(" + orign;
		index = orign.find("(+", 0);
		while (index != orign.npos)
		{
			orign.replace(index, 2, "(0+");
			index = orign.find("(+", index);
		}
		index = orign.find("(-", 0);
		while (index != orign.npos)
		{
			orign.replace(index, 2, "(0-");
			index = orign.find("(-", index);
		}		
		return orign;
	}

	std::string & calcu::trim_all(std::string & orign)
	{
		size_t index = orign.find(' ', 0);
		while (index != orign.npos)
		{
			orign.erase(index, 1);
			index = orign.find(' ', index);
		}
		return orign;
	}

	bool calcu::isDigit(char ch)
	{
		if (ch >= '0' && ch <= '9')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool calcu::isOperator(char ch)
	{
		switch (ch)
		{
		case '+':
			return true;
		case '-':
			return true;
		case '*':
			return true;
		case '/':
			return true;
		case '^':
			return true;
		case '%':
			return true;
		case '&':
			return true;
		case '(':
			return true;
		case ')':
			return true;
		case '=':
			return true;
		default:
			return false;
		}
	}

	bool calcu::validCheck()
	{
		MyStack<char> left;
		size_t len = raw_expression.length();
		char current;
		char pre = ' ';
		char pre_dot = ' ';
		for (size_t i = 0; i < len; i++)
		{
			current = raw_expression[i];
			if (calcu::isDigit(current))
			{
				if (pre == ')' || pre == '=')
				{
					return false;
				}
			}
			else if (current == '(')
			{
				if (calcu::isDigit(pre) || pre == ')' || pre == '.' || pre == '=')
				{
					return false;
				}
				else
				{
					left.push(current);
				}
			}
			else if (current == ')')
			{
				if (left.empty())
				{
					return false;
				}
				else
				{
					if (!calcu::isDigit(pre) && pre != ')')
					{
						return false;
					}
					else
					{
						left.pop();
					}					
				}
			}
			else if (calcu::isOperator(current))
			{				
				pre_dot = ' ';				
				if (pre == ' ' || pre == '(')
				{
					if (current != '+' && current != '-')
					{
						return false;
					}					
				}
				else if (calcu::isOperator(pre))
				{
					if (pre != '(' && pre != ')')
					{
						return false;
					}	
					else if (current == '=' && i != len - 1)
					{
						return false;
					}
				}
			}
			else if (current == '.')
			{
				if (!calcu::isDigit(pre) || pre_dot == '.')
				{
					return false;
				}
				else
				{
					pre_dot = '.';
				}
			}
			else
			{
				return false;
			}
			pre = current;
		}
		if (raw_expression[len - 1] != '=')
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	int calcu::isp(char ch)
	{
		int level = 0;
		switch (ch)
		{
		case '=':
			level = 0;
			break;
		case '+':
		case '-':
			level = 3;
			break;
		case '*':
		case '/':
		case '%':
			level = 5;
			break;
		case '(':
			level = 1;
			break;
		case ')':
			level = 8;
			break;
		case '^':
		case '&':
			level = 7;
			break;
		}
		return level;
	}

	int calcu::osp(char ch)
	{
		int level = 0;
		switch (ch)
		{
		case '=':
			level = 0;
			break;
		case '+':
		case '-':
			level = 2;
			break;
		case '*':
		case '/':
		case '%':
			level = 4;
			break;
		case '(':
			level = 8;
			break;
		case ')':
			level = 1;
			break;
		case '^':
		case '&':
			level = 6;
			break;
		}
		return level;
	}

	BaseUnit calcu::call_calculate(char op, BaseUnit &a, BaseUnit &b)
	{
		BaseUnit local_rt;

		switch (op)
		{
		case '+':
			local_rt = a + b;
			break;
		case '-':
			local_rt = a - b;
			break;
		case '*':
			local_rt = a * b;
			break;
		case '/':
			local_rt = a / b;
			break;
		case '%':
			local_rt = a % b;
			break;
		case '^':
			local_rt = a ^ b;
			break;
		case '&':
			local_rt = a & b;
			break;
		default:
			throw INVALIDCHAR;
			break;
		}
		return local_rt;
	}

	calcu::calcu() : raw_expression(""), checked(true), isValid(false), isCalculated(false), zeroDivision(false), undefine(false), invalidStr(true), inexact(false), outrange(false)
	{
	}

	calcu::calcu(const std::string & expr_str) : isCalculated(false), zeroDivision(false), undefine(false), inexact(false), outrange(false)
	{
		raw_expression = expr_str;
		raw_expression = trim_all(raw_expression);//剔除空格
		isValid = (validCheck()) ? true : false;
		invalidStr = !isValid;
		checked = true;
	}

	calcu::calcu(const calcu & other)
	{
		raw_expression = other.raw_expression;
		rt = other.rt;
		checked = other.checked;
		isValid = other.isValid;
		isCalculated = other.isCalculated;
		zeroDivision = other.zeroDivision;
		undefine = other.undefine;
		invalidStr = other.invalidStr;
		inexact = other.inexact;
		outrange = other.outrange;
	}

	calcu::calcu(calcu &&other)
	{
		raw_expression = std::move(other.raw_expression);
		rt = other.rt;
		checked = other.checked;
		isValid = other.isValid;
		isCalculated = other.isCalculated;
		zeroDivision = other.zeroDivision;
		undefine = other.undefine;
		invalidStr = other.invalidStr;
		inexact = other.inexact;
		outrange = other.outrange;
	}

	calcu::~calcu()
	{
		//没有需要手动清理的对象
	}

	calcu &calcu::Calculate()
	{
		MyStack<char> opter;
		MyStack<BaseUnit> opnd;
		BaseUnit tmp, a, b;
		char tmp_opter, called_opter;
		if (!checked || !isValid)
		{
			/*若表达式非法，则认为已计算*/
			isCalculated = true;
			return *this;
		}
		else if (!isCalculated)
		{
			std::fenv_t current_fe_env;
			std::fegetenv(&current_fe_env);//保存当前浮点环境
			std::feclearexcept(FE_ALL_EXCEPT);//清除浮点异常
			std::string local_formt_expression = raw_expression;
			local_formt_expression = format_tool(local_formt_expression);
			std::istringstream expression_stream(local_formt_expression);
			try
			{
				expression_stream >> tmp_opter;
				while (tmp_opter != '=')
				{
					/*读取表达式*/
					if (calcu::isDigit(tmp_opter))
					{
						expression_stream.putback(tmp_opter);
						expression_stream >> tmp;
						opnd.push(tmp);
					}
					else
					{
						while (!opter.empty() && (calcu::isp(opter.top()) > calcu::osp(tmp_opter)))
						{
							b = opnd.top();
							opnd.pop();
							a = opnd.top();
							opnd.pop();
							called_opter = opter.top();
							opter.pop();
							tmp = call_calculate(called_opter, a, b);
							opnd.push(tmp);
						}
						if (!opter.empty() && calcu::isp(opter.top()) == calcu::osp(tmp_opter))
						{
							opter.pop(); //处理括号对
						}
						else
						{
							opter.push(tmp_opter);
						}
					}
					expression_stream >> tmp_opter;
				}
				rt = opnd.top();//读取结果
				opnd.clear();//清空操作数
				opter.clear();//弹出左括号
				/*处理浮点异常*/
				int feerror = std::fetestexcept(FE_ALL_EXCEPT);				
				if (feerror & FE_INVALID)
				{
					undefine = true;
					isValid = false;
					isCalculated = true;
					std::fesetenv(&current_fe_env);//恢复浮点环境
					return *this;
				}
				if (feerror & FE_DIVBYZERO)
				{
					zeroDivision = true;
					isValid = false;
					isCalculated = true;
					std::fesetenv(&current_fe_env);//恢复浮点环境
					return *this;
				}
				if (feerror & FE_INEXACT)
				{
					inexact = true;
					isValid = true;
					isCalculated = true;
					std::fesetenv(&current_fe_env);//恢复浮点环境
					return *this;
				}
				std::fesetenv(&current_fe_env);//恢复浮点环境
			}
			catch (const char &a)
			{
				isCalculated = true;
				/*处理整型异常*/
				switch (a)
				{
				case INVALIDCHAR:
					isValid = false;
					invalidStr = true;
					break;
				case DIVBYZERO:
					isValid = false;
					zeroDivision = true;
					break;
				case UNDEFINE:
					isValid = false;
					undefine = true;
					break;
				default:
					break;
				}
				opnd.clear();
				opter.clear();
				isCalculated = true;
				return *this;
			}
			catch (const std::out_of_range& )
			{
				outrange = true;
				isValid = false;
				return *this;
			}
			isCalculated = true;
			return *this;
		}
		else
		{
			return *this;//返回已存在的计算结果
		}
	}

	calcu & calcu::Clear()
	{
		raw_expression.clear();
		raw_expression = "";
		rt = 0ll;
		checked = true;
		isValid = false;
		isCalculated = false;
		zeroDivision = false;
		undefine = false;
		invalidStr = true;
		inexact = false;
		return *this;
	}

	calcu &calcu::operator=(const calcu & other)
	{
		raw_expression.clear();
		raw_expression = other.raw_expression;
		rt = other.rt;
		checked = other.checked;
		isValid = other.isValid;
		isCalculated = other.isCalculated;
		zeroDivision = other.zeroDivision;
		undefine = other.undefine;
		invalidStr = other.invalidStr;
		inexact = other.inexact;
		return *this;
	}

	calcu &calcu::operator=(calcu &&other)
	{
		raw_expression.clear();
		raw_expression = std::move(other.raw_expression);
		rt = other.rt;
		checked = other.checked;
		isValid = other.isValid;
		isCalculated = other.isCalculated;
		zeroDivision = other.zeroDivision;
		undefine = other.undefine;
		invalidStr = other.invalidStr;
		inexact = other.inexact;
		return *this;
	}

	bool calcu::operator==(const calcu &other)
	{
		return (raw_expression == other.raw_expression) ? true : false;
	}

	std::istream &operator>>(std::istream &is, calcu &obj)
	{
		std::string tmp;
		std::getline(is, tmp);//支持行内空格
		tmp = obj.trim_all(tmp);
		obj = calcu(tmp);
		return is;
	}

	std::ostream &operator<<(std::ostream &os, calcu &obj)
	{
		if (!obj.checked)
		{
			os << "error, initialization failed...";
			return os;
		}
		if (obj.isValid && !obj.isCalculated)
		{
			obj.Calculate();
		}
		if (obj.isValid)
		{
			char current, pre = '(';			
			size_t len = obj.raw_expression.length() - 1;
			for (size_t i = 0; i < len; i++)
			{
				current = obj.raw_expression[i];
				if (!obj.isOperator(current))
				{
					os << current;
				}
				else if (current == '+' || current == '-')
				{
					if (pre == '(')
					{
						os <<current;
					}
					else
					{
						os << ' ' << current << ' ';
					}
				}
				else if (current == '^' || current == '&'|| current == '(' || current == ')')
				{
					os << current;
				}
				else
				{
					os << ' ' << current << ' ';
				}
				pre = current;
			}
			std::streamsize curr_en = os.precision(16);
			os << ' ' << '=' << ' ' << obj.rt;
			os.precision(curr_en);
			if (obj.inexact)
			{
				os << " <MAY BE INEXACT>";
			}
		}
		else if (obj.invalidStr)
		{
			os << "error, invalid expression...";
		}
		else if (obj.zeroDivision)
		{
			os << "error, zerodivision...";
		}
		else if (obj.undefine)
		{
			os << "error, undefined behavier...";
		}
		else
		{
			os << "error, at least one operand is out of range..";
		}
		return os;
	}
}