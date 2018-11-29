#pragma once
#include <cfenv>
#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<stdexcept>
#include<Windows.h>
#include"MyStack.h"
#include"BaseUnit.h"
#pragma fenv_access (on)


namespace MyLab
{
constexpr auto INVALIDCHAR = 'a';


	class calcu
	{
	private:
		std::string raw_expression;//原生表达式，无空白字符
		size_t error_index;//首个错误位置
		BaseUnit rt;//结果存储
		bool checked;//标识是否已进行合法性检测
		bool isValid;//合法性标识，仅在checked为真时有效
		bool isCalculated;//标识是否已进行计算
		bool zeroDivision;//零除标识
		bool invalidStr;//非法字符标识
		bool undefine;//未定义行为
		bool inexact;//精度受损标识
		bool outrange;//输入数值溢出标识
		//剔除所有空格
		inline std::string &trim_all(std::string &);
		//规范化表达式，将所有一元运算符转换为二元运算符，并添加最外层括号
		inline std::string &format_tool(std::string &);
		//判断当前字符是否为操作符
		inline bool isOperator(char);
		//判断当前字符是否为数字0-9
		inline bool isDigit(char);
		//表达式合法性检测
		inline bool validCheck();
		//获取栈内优先级
		inline int isp(char);
		//获取栈外优先级
		inline int osp(char);
		//根据读取的运算符进行计算
		BaseUnit call_calculate(char op, BaseUnit &a, BaseUnit &b);

	public:
		calcu();
		calcu(const std::string &);
		calcu(const calcu &);
		calcu(calcu &&);
		~calcu();
		calcu &Calculate();
		calcu &Clear();
		//赋值函数
		calcu &operator=(const calcu &);
		//移动赋值函数
		calcu &operator=(calcu &&);
		//比较函数
		bool operator==(const calcu &);
		friend std::istream &operator>>(std::istream &, calcu &);
		friend std::ostream &operator<<(std::ostream &, calcu &);
	};

	WORD Setcolor(unsigned short);
}