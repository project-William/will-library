#pragma once 
#include "allocator.h"
#include "utility.h"
#include "vector.h"

namespace will
{
	template<class T>
	struct BSTreeNode
	{
		size_t m_Key;
		T m_Data;
		BSTreeNode* m_LeftChild;
		BSTreeNode* m_RightChild;
		BSTreeNode() :m_LeftChild(nullptr), m_RightChild(nullptr) {}
		~BSTreeNode() {}
	};

	template<class T, typename allocator=Allocator<BSTreeNode<T>>>
	class BSTree
	{
	public:
		BSTree();
		~BSTree();

		void insertNode(size_t key, const T& data);
		void insertNode(const Pair<int, T>& pr);


		bool delNode(size_t key);
		BSTreeNode<T>* searchNode(size_t key);
		size_t depth(BSTreeNode<T>* node);
		void KeyPreTraverseRecursive(BSTreeNode<T>* node);
		void KeyOrderTraverseRecursive(BSTreeNode<T>* node);
		void KeyPostTraverseRecursive(BSTreeNode<T>* node);

		void KeyPreTraverse();
		void KeyOrderTraverse();
		void KeyPostTraverse();


		BSTreeNode<T>* getRootNode()const { return m_Root; }


	private:
		allocator m_Alloc;
		BSTreeNode<T>* m_Root;
		size_t m_Size;
	};

	template<class T, typename allocator>
	BSTree<T, allocator>::BSTree()
		:m_Root(nullptr),m_Size(0)
	{

	}

	template<class T,typename allocator>
	BSTree<T, allocator>::~BSTree()
	{

	}


	template<class T,typename allocator>
	void BSTree<T, allocator>::insertNode(size_t key, const T& data)
	{
		if (!m_Root)
		{
			m_Root = m_Alloc.allocate(1);
			m_Root->m_Data = data;
			m_Root->m_Key = key;
			m_Root->m_LeftChild = m_Root->m_RightChild = nullptr;
			m_Size++;
		}
		else
		{
			BSTreeNode<T>* ptr = m_Root;
			while (ptr)
			{
				if (key >= ptr->m_Key)
				{
					if (ptr->m_RightChild == nullptr)
					{
						ptr->m_RightChild = m_Alloc.allocate(1);
						ptr->m_RightChild->m_Key = key;
						ptr->m_RightChild->m_Data = data;
						ptr->m_RightChild->m_LeftChild = ptr->m_RightChild->m_RightChild = nullptr;
						m_Size++;
						break;
					}
					ptr = ptr->m_RightChild;
				}
				else
				{
					if (ptr->m_LeftChild == nullptr)
					{
						ptr->m_LeftChild = m_Alloc.allocate(1);
						ptr->m_LeftChild->m_Key = key;
						ptr->m_LeftChild->m_Data = data;
						ptr->m_LeftChild->m_LeftChild = ptr->m_LeftChild->m_RightChild = nullptr;
						m_Size++;
						break;
					}
					ptr = ptr->m_LeftChild;
				}
			}
		
		}

	}

	template<class T,typename allocator>
	void BSTree<T, allocator>::insertNode(const Pair<int, T>& pr)
	{
		if (!m_Root)
		{
			m_Root = m_Alloc.allocate(1);
			m_Root->m_Data = pr.second;
			m_Root->m_Key = pr.first;
			m_Root->m_LeftChild = m_Root->m_RightChild = nullptr;
		}
		else
		{
			BSTreeNode<T>* ptr = m_Root;
			while (ptr)
			{
				if (pr.first >= ptr->m_Key)
				{
					if (ptr->m_RightChild == nullptr)
					{
						ptr->m_RightChild = m_Alloc.allocate(1);
						ptr->m_RightChild->m_Key = pr.first;
						ptr->m_RightChild->m_Data = pr.second;
						ptr->m_RightChild->m_LeftChild = ptr->m_RightChild->m_RightChild = nullptr;
						break;
					}
					ptr = ptr->m_RightChild;
				}
				else
				{
					if (ptr->m_LeftChild == nullptr)
					{
						ptr->m_LeftChild = m_Alloc.allocate(1);
						ptr->m_LeftChild->m_Key = pr.first;
						ptr->m_LeftChild->m_Data = pr.second;
						ptr->m_LeftChild->m_LeftChild = ptr->m_LeftChild->m_RightChild = nullptr;
						break;
					}
					ptr = ptr->m_LeftChild;
				}
			}

		}
	}

	template<class T,typename allocator>
	bool BSTree<T, allocator>::delNode(size_t key)
	{
		BSTreeNode<T>* ptr = m_Root;
		BSTreeNode<T>* temp = ptr;
		while (ptr)
		{
			if (key == ptr->m_Key)
			{
				//1st condition,no leftchild no right child
				if (!ptr->m_LeftChild && !ptr->m_RightChild)
				{
					m_Alloc.deallocate(ptr);
				}
				//2nd condition no left child but has right child
				else if (!ptr->m_LeftChild && ptr->m_RightChild)
				{
					temp = ptr;
					ptr = ptr->m_RightChild;
					m_Alloc.deallocate(temp);
				}
				//3nd condition has right child but no left child
				else if (ptr->m_LeftChild && ptr->m_RightChild)
				{
					temp = ptr;
					ptr = ptr->m_LeftChild;
					m_Alloc.deallocate(temp);
				}
				else // has both left and right child
				{
					BSTreeNode<T>* temp_left_tree = ptr->m_LeftChild;
					temp = ptr;
					ptr = ptr->m_RightChild;
					ptr->m_LeftChild = temp_left_tree;
					m_Alloc.deallocate(temp);
					while (temp_left_tree)
					{
						if (ptr->m_LeftChild->m_Key >= temp_left_tree->m_Key)
						{
							if (temp_left_tree->m_RightChild == nullptr)
							{
								temp_left_tree->m_RightChild = ptr->m_LeftChild;
								break;
							}
							temp_left_tree = temp_left_tree->m_RightChild;
						}
						else
						{
							if (temp_left_tree->m_LeftChild == nullptr)
							{
								temp_left_tree->m_LeftChild = ptr->m_LeftChild;
								break;
							}
							temp_left_tree = temp_left_tree->m_LeftChild;
						}

					}
				}
				return true;
			}
			else
			{
				if (key >= ptr->m_Key)
					ptr = ptr->m_RightChild;
				else ptr = ptr->m_LeftChild;
			}
		}
		return false;
	}

	template<class T,typename allocator>
	BSTreeNode<T>* BSTree<T, allocator>::searchNode(size_t key)
	{
		BSTreeNode<T>* ptr = m_Root;
		if (!m_Root)
		{
			std::cout << "empty tree" << std::endl;
		}
		else
		{
			while (ptr)
			{
				if (ptr->m_Key == key)
					return ptr;
				if (key >= ptr->m_Key)
					ptr = ptr->m_RightChild;
				else ptr = ptr->m_LeftChild;
			}
			return nullptr;
		}
	}
	
	template<class T,typename allocator>
	size_t BSTree<T, allocator>::depth(BSTreeNode<T>* node)
	{
		if (node)
		{
			int leftDepth = depth(node->m_LeftChild);
			int rightDepth = depth(node->m_RightChild);
			return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
		}
		return 0;
	}

	template<class T,typename allocator>
	void BSTree<T, allocator>::KeyPreTraverseRecursive(BSTreeNode<T>* node)
	{
		if (node)
		{
			std::cout << "Node key:" << node->m_Key << std::endl;
			KeyPreTraverseRecursive(node->m_LeftChild);
			KeyPreTraverseRecursive(node->m_RightChild);
		}
	}

	template<class T,typename allocator>
	void BSTree<T, allocator>::KeyOrderTraverseRecursive(BSTreeNode<T>* node)
	{
		if (node)
		{
			KeyOrderTraverseRecursive(node->m_LeftChild);
			std::cout << "Node key:" << node->m_Key << std::endl;
			KeyOrderTraverseRecursive(node->m_RightChild);
		}
	}

	template<class T,typename allocator>
	void BSTree<T, allocator>::KeyPostTraverseRecursive(BSTreeNode<T>* node)
	{
		if (node)
		{
			KeyPostTraverseRecursive(node->m_LeftChild);
			KeyPostTraverseRecursive(node->m_RightChild);
			std::cout << "Node key:" << node->m_Key << std::endl;
		}
	}

	template<class T, typename allocator>
	void BSTree<T, allocator>::KeyPreTraverse()
	{
		Vector<BSTreeNode<T>*> nodeVec;
		BSTreeNode<T>* ptr = m_Root;

		if (!m_Root)
		{
			std::cout << "Empty tree" << std::endl;
		}
		else
		{
			while (!nodeVec.empty() || ptr)
			{
				while (ptr)
				{
					std::cout << "Node key:" << ptr->m_Key << std::endl;
					nodeVec.push_back(ptr);
					ptr = ptr->m_LeftChild;
				}

				if (!ptr)
				{
					ptr = nodeVec.getLastValue();
					nodeVec.pop_back();
					ptr = ptr->m_RightChild;
				}

			}
		}



	}

	template<class T, typename allocator>
	void BSTree<T, allocator>::KeyOrderTraverse()
	{
		Vector<BSTreeNode<T>*> nodeVec;
		BSTreeNode<T>* ptr = m_Root;

		if (!m_Root)
		{
			std::cout << "Empty tree" << std::endl;
		}
		else
		{
			while (!nodeVec.empty() || ptr)
			{
				while (ptr)
				{
					nodeVec.push_back(ptr);
					ptr = ptr->m_LeftChild;
				}

				if (!ptr)
				{
					ptr = nodeVec.getLastValue();
					std::cout << "Node key:" << ptr->m_Key << std::endl;
					nodeVec.pop_back();
					ptr = ptr->m_RightChild;
				}

			}
		}
	}

	template<class T, typename allocator>
	void BSTree<T, allocator>::KeyPostTraverse()
	{
		Vector<BSTreeNode<T>*> nodeVec;

		BSTreeNode<T>* curPtr = m_Root;
		BSTreeNode<T>* lastVisited = nullptr;
		if (!m_Root)
		{
			std::cout << "Empty tree" << std::endl;
		}
		else
		{
			while (curPtr)
			{
				nodeVec.push_back(curPtr);
				curPtr = curPtr->m_LeftChild;
			}

			while (!nodeVec.empty())
			{
				curPtr = nodeVec.getLastValue();
				nodeVec.pop_back();

				if (curPtr->m_RightChild== nullptr || curPtr->m_RightChild == lastVisited)
				{
					std::cout << "Node key:" << curPtr->m_Key << std::endl;
					lastVisited = curPtr;
				}
				else
				{
					nodeVec.push_back(curPtr);
					curPtr = curPtr->m_RightChild;
					while (curPtr)
					{
						nodeVec.push_back(curPtr);
						curPtr = curPtr->m_LeftChild;
					}
				}
			}
		}
	}
}