#include <iostream>
#include <algorithm>
#include <functional>

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

	public:
		BinaryTreeNode* leftChild;
		BinaryTreeNode* rightChild;

	private:
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
		HashTable(Key firstKey, Value firstValue)
		{
			this->binTree = new BinaryTree<Key, Value>(firstKey, firstValue);
		}

		void insert(Key key, Value value)
		{
			binTree->push(key, value);
		}

		Value get(Key key)
		{
			return binTree->get(key);
		}

	private:
		BinaryTree<Key, Value>* binTree;
	};
}

using containers::HashTable;

int main()
{
	HashTable<std::string, int> ht("one", 1);
	ht.insert("two", 2);
	ht.insert("three", 3);
	cout << ht.get("three") << endl;
}