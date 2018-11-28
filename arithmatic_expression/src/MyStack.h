#pragma once
#include <iostream>
namespace MyLab
{
	template<typename T>
	class MyStack
	{
	private:
		//嵌套结构模板声明，用于描述，不会占用内存空间
		template <typename E>
		struct MyStackNode
		{
			E _element;
			MyStackNode<E> *_next_node;
		};
		MyStackNode<T> *header;

	public:
		//默认构造函数
		MyStack();
		//复制构造函数
		MyStack(const MyStack<T> &);
		//移动构造函数
		MyStack(MyStack<T> &&);
		~MyStack();
		bool empty() const;
		size_t size() const;
		const T &top() const;
		void pop();
		void push(const T &x);
		void push(T &&x);
		void swap(MyStack<T> &other);
		void clear();
		MyStack<T> &operator=(const MyStack<T> &);
		MyStack<T> &operator=(MyStack<T> &&);
	};

	template<typename T>
	MyStack<T>::MyStack()
	{
		this->header = nullptr;
	}

	template<typename T>
	MyStack<T>::MyStack(const MyStack<T> &other)
	{
		MyStackNode<T> **current = &(this->header);
		MyStackNode<T> *current_other = other.header;
		while (current_other != nullptr)
		{
			*current = new MyStackNode<T>{ current_other->_element, nullptr };
			current = &((*current)->_next_node);
			current_other = current_other->_next_node;
		}
	}

	template<typename T>
	MyStack<T>::MyStack(MyStack<T> &&other)
	{
		header = other.header;
		other.header = nullptr;
	}

	template<typename T>
	MyStack<T>::~MyStack()
	{
		MyStackNode<T> *current = this->header;
		MyStackNode<T> *tmp;
		while (current != nullptr)
		{
			tmp = current;
			current = current->_next_node;
			delete tmp;
		}
		this->header = nullptr;
	}

	template<typename T>
	bool MyStack<T>::empty() const
	{
		return (this->header) ? false : true;
	}

	template<typename T>
	size_t MyStack<T>::size() const
	{
		size_t len = 0;
		MyStackNode<T> *current = this->header;
		while (current)
		{
			len++;
			current = current->_next_node;
		}
		return len;
	}

	template<typename T>
	const T& MyStack<T>::top() const
	{
		return (this->header->_element);
	}

	template<typename T>
	void MyStack<T>::pop()
	{
		MyStackNode<T> *tmp = this->header;
		this->header = tmp->_next_node;
		delete tmp;
	}

	template <typename T>
	void MyStack<T>::push(const T &x)
	{
		MyStackNode<T> *tmp = new MyStackNode<T>{ x, this->header };
		this->header = tmp;
	}

	template <typename T>
	void MyStack<T>::push(T &&x)
	{
		MyStackNode<T> *tmp = new MyStackNode<T>;
		tmp->_next_node = nullptr;
		tmp->_element = std::move(x);
		this->header = tmp;
	}

	template<typename T>
	void MyStack<T>::swap(MyStack<T> &other)
	{
		MyStackNode<T> *tmp;
		tmp = this->header;
		this->header = other->header;
		other->header = tmp;
	}

	template<typename T>
	void MyStack<T>::clear()
	{
		MyStackNode<T> *current = this->header;
		MyStackNode<T> *tmp;
		while (current != nullptr)
		{
			tmp = current;
			current = current->_next_node;
			delete tmp;
		}
		this->header = nullptr;
	}


	template<typename T>
	MyStack<T> & MyStack<T>::operator=(const MyStack<T> &other)
	{
		MyStackNode<T> **current = &(this->header);
		MyStackNode<T> *current_other = other.header;

		while (*current != nullptr && current_other != nullptr)
		{
			(*current)->_element = current_other->_element;
			current = &((*current)->_next_node);
			current_other = current_other->_next_node;
		}

		if (current_other == nullptr && *current != nullptr)
		{
			MyStackNode<T> *tmp = *current;
			while (tmp != nullptr)
			{
				*current = nullptr;
				current = &(tmp->_next_node);
				delete tmp;
				tmp = *current;
			}
		}
		while (current_other != nullptr)
		{
			*current = new MyStackNode<T>{ current_other->_element, nullptr };
			current = &((*current)->_next_node);
			current_other = current_other->_next_node;
		}
		return *this;
	}

	template<typename T>
	MyStack<T> & MyStack<T>::operator=(MyStack<T> &&other)
	{
		header = other.header;
		other.header = nullptr;
		return *this;
	}
}