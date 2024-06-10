#pragma once

#include <vector> // only for constructor
#include <stdexcept>

template <class T>
class list
{
public:
	// Default constructor
	list() : _Root(nullptr), _Size(0) {}

	// Constructor from std::vector
	explicit list(std::vector<T> vec) : _Root(nullptr), _Size(0)
	{
		for (const T& i : vec)
		{
			push_back(i);
		}
	}

	~list()
	{
		while (_Size > 0)
		{
			pop_back();
		}
	}

	void push_back(const T& data)
	{
		ListNode* newNode = new ListNode(data);

		if (_Root == nullptr)
		{
			_Root = newNode;
		}
		else
		{
			// Finding last node
			ListNode* LastNode = _Root;
			while (LastNode->NextListNode != nullptr)
			{
				LastNode = LastNode->NextListNode;
			}

			LastNode->NextListNode = newNode;
		}

		++_Size;
	}

	void pop_back()
	{
		if (_Size == 1)
		{
			delete _Root;

			_Root = nullptr;
			return;
		}

		// Finding pre-last node
		ListNode* PrelastNode = _Root;

		while (PrelastNode->NextListNode->NextListNode != nullptr)
		{
			PrelastNode = PrelastNode->NextListNode;
		}

		delete PrelastNode->NextListNode;
		PrelastNode->NextListNode = nullptr;

		--_Size;
	}

	// read-write
	T& operator[](const size_t index)
	{
		if (index > _Size - 1 || index < 0)
		{
			throw std::invalid_argument("Invalid index");
		}

		if (index == 0)
		{
			return _Root->Data;
		}

		ListNode* CurrentNode = _Root;

		for (size_t i = 0; i < index; ++i)
		{
			if (CurrentNode->NextListNode != nullptr)
			{
				CurrentNode = CurrentNode->NextListNode;
			}
			else
			{
				throw std::invalid_argument("Invalid index");
			}
		}

		return CurrentNode->Data;
	}

	// Only read
	[[nodiscard]] T operator[](const size_t index) const
	{
		if (index > _Size - 1 || index < 0)
		{
			throw std::invalid_argument("Invalid index");
		}

		if (index == 0)
		{
			return _Root->Data;
		}

		ListNode* CurrentNode = _Root;

		for (size_t i = 0; i < index; ++i)
		{
			if (CurrentNode->NextListNode != nullptr)
			{
				CurrentNode = CurrentNode->NextListNode;
			}
			else
			{
				throw std::invalid_argument("Invalid index");
			}
		}

		return CurrentNode->Data;
	}

	void insert(size_t index, const T& data)
	{
		if (index > _Size || index < 0)
		{
			throw std::invalid_argument("Invalid index");
			return;
		}

		ListNode* newNode = new ListNode(data);

		if (index == 0)
		{
			ListNode* PrevNextNode = _Root;

			_Root = newNode;

			_Root->NextListNode = PrevNextNode;

			++_Size;
			return;
		}
		else if (index == _Size)
		{
			push_back(data);
			return;
		}

		ListNode* CurrentNode = _Root;

		for (size_t i = 0; i < index - 1; ++i)
		{
			if (CurrentNode->NextListNode != nullptr)
			{
				CurrentNode = CurrentNode->NextListNode;
			}
			else
			{
				throw std::invalid_argument("Invalid index");
			}
		}

		ListNode* PrevNextNode = CurrentNode->NextListNode;

		CurrentNode->NextListNode = newNode;

		CurrentNode->NextListNode->NextListNode = PrevNextNode;

		++_Size;
	}

	void erase(size_t index)
	{
		if (index > _Size - 1 || index < 0)
		{
			throw std::invalid_argument("Invalid index");
			return;
		}

		if (index == 0)
		{
			ListNode* NextNode = _Root->NextListNode;

			delete _Root;

			_Root = NextNode;

			--_Size;
			return;
		}
		else if (index == _Size)
		{
			pop_back();
			return;
		}

		ListNode* CurrentNode = _Root;

		for (size_t i = 0; i < index - 1; ++i)
		{
			if (CurrentNode->NextListNode != nullptr)
			{
				CurrentNode = CurrentNode->NextListNode;
			}
			else
			{
				throw std::invalid_argument("Invalid index");
			}
		}

		ListNode* NextNode = CurrentNode->NextListNode->NextListNode;

		delete CurrentNode->NextListNode;

		CurrentNode->NextListNode = NextNode;

		--_Size;
	}

	constexpr size_t size() const
	{
		return _Size;
	}

	constexpr size_t sizeofNode() const
	{
		return sizeof(ListNode);
	}

private:
	struct ListNode
	{
		T Data;
		ListNode* NextListNode;

		ListNode(T data) : Data(data), NextListNode(nullptr) {}
	};

	size_t _Size;
	ListNode* _Root;
};