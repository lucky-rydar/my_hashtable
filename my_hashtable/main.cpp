#include <iostream>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

namespace containers
{
	template <class Value> class BinaryTreeNode
	{
		friend class BinaryTreeNode;
	public:
		BinaryTreeNode(size_t key, Value value) : key(key), value(value)
		{
			this->leftChild = nullptr;
			this->rightChild = nullptr;
		}

		~BinaryTreeNode()
		{
			delete this->leftChild;
			delete this->rightChild;
		}

		void addChild(BinaryTreeNode* node)
		{
			if (node->key > this->key)
			{
				if (rightChild == nullptr)
					rightChild = node;
				else
					rightChild->addChild(node);
			}
			else if (node->key < this->key)
			{
				if (leftChild == nullptr)
					leftChild = node;
				else
					leftChild->addChild(node);
			}
			else if (node->key == this->key)
			{
				this->value = node->value;
				delete node;
			}
		}

		Value get(size_t key)
		{
			if (key > this->key)
				return rightChild->get(key);
			else if (key < this->key)
				return leftChild->get(key);
			else if (key = this->key)
				return value;
			else
				return 0;
		}

	private:
		BinaryTreeNode* leftChild;
		BinaryTreeNode* rightChild;

		size_t key;
		Value value;

	};

	template <class Key, class Value> class BinaryTree
	{
	public:
		BinaryTree(Key firstKey, Value firstValue)
		{
			size_t hashedKey = hash<Key>{}(firstKey);
			this->root = new BinaryTreeNode<Value>(hashedKey, firstValue);
		}

		~BinaryTree()
		{
			delete this->root;
		}

		void push(Key key, Value value)
		{
			size_t hashedKey = hash<Key>{}(key);
			root->addChild(new BinaryTreeNode<Value>(hashedKey, value));
		}

		Value get(Key key)
		{
			size_t hashedKey = hash<Key>{}(key);
			return root->get(hashedKey);
		}

	private:
		BinaryTreeNode<Value>* root;
	};

	template <class Key, class Value> class HashTable
	{
	public:
		HashTable() { }
		HashTable(Key firstKey, Value firstValue)
		{
			this->binTree = new BinaryTree<Key, Value>(firstKey, firstValue);
		}
		
		~HashTable()
		{
			if(this->binTree != nullptr)
				delete this->binTree;
		}

		void insert(Key key, Value value)
		{
			if (this->binTree == nullptr)
				binTree = new BinaryTree<Key, Value>(key, value);
			else
				binTree->push(key, value);
		}

		Value get(Key key)
		{
			if (binTree == nullptr)
				return Value();
			else
				return binTree->get(key);
		}

	private:
		BinaryTree<Key, Value>* binTree;
	};
}

using containers::HashTable;

int main()
{
	HashTable<std::string, int> ht;

	for (int i = 1; i < 1000000; i++)
		ht.insert(to_string(i), i);

	cout << ht.get("12") << endl;
}