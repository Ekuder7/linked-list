#pragma once

#include <memory>

#include <vector>
#include <stdexcept>

template <class T>
class LinkedList
{
public:
	// Default constructor
	LinkedList() {}

	// Constructor from std::initializer_list
	explicit LinkedList(std::initializer_list<T> vec)
	{
		for (const T& i : vec)
		{
			push_back(i);
		}
	}

	~LinkedList()
	{
		while (_Size > 0)
		{
			pop_back();
		}
	}

	void push_back(const T& data)
	{
		std::shared_ptr<ListNode> newNode{ std::make_shared<ListNode>(data) };

		if (_Root.get() == nullptr)
		{
			_Root = newNode;
		}
		else
		{
			// Finding last node
			std::shared_ptr<ListNode> LastNode{ _Root };
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
			//delete _Root;
			_Root = nullptr;

			--_Size;
			return;
		}

		// Finding pre-last node
		std::shared_ptr<ListNode> PrelastNode{ _Root };
		//ListNode* PrelastNode = _Root;

		while (PrelastNode->NextListNode->NextListNode.get() != nullptr)
		{
			PrelastNode = PrelastNode->NextListNode;
		}

		//delete PrelastNode->NextListNode;
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

		//ListNode* CurrentNode = _Root;
		std::shared_ptr<ListNode> CurrentNode{ _Root };

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

		//ListNode* CurrentNode = _Root;
		std::shared_ptr<ListNode> CurrentNode{ _Root };

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

		std::shared_ptr<ListNode> newNode{ std::make_shared<ListNode>(data) };
		//ListNode* newNode = new ListNode(data);

		if (index == 0)
		{
			std::shared_ptr<ListNode> PrevNextNode{ _Root };
			//ListNode* PrevNextNode = _Root;

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

		std::shared_ptr<ListNode> CurrentNode{ _Root };
		//ListNode* CurrentNode = _Root;

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
		std::shared_ptr<ListNode> PrevNextNode{ CurrentNode->NextListNode };
		//ListNode* PrevNextNode = CurrentNode->NextListNode;

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
			std::shared_ptr<ListNode> NextNode{ _Root->NextListNode };
			//ListNode* NextNode = _Root->NextListNode;

			//delete _Root;

			_Root = NextNode;

			--_Size;
			return;
		}
		else if (index == _Size)
		{
			pop_back();
			return;
		}
		
		std::shared_ptr<ListNode> CurrentNode{ _Root };
		//ListNode* CurrentNode = _Root;

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

		std::shared_ptr<ListNode> NextNode{ CurrentNode->NextListNode->NextListNode };
		//ListNode* NextNode = CurrentNode->NextListNode->NextListNode;

		//delete CurrentNode->NextListNode;

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

		std::shared_ptr<ListNode> NextListNode{ nullptr };

		ListNode(T data) : Data(data) {}
	};

	size_t _Size = 0;
	std::shared_ptr<ListNode> _Root{ nullptr };
};
