#include <fstream>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <map>
#include <deque>

#define waza() std::cout << "WAZAAAAAAAA,\t\tline: " << __LINE__ << ",\tfunc: " << __FUNCTION__ << std::endl

struct vec
{
	int x, y, z;
	vec(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z)
	{
		std::cout << "constructor called" << std::endl;
	}
	vec(vec const &obj) : x(obj.x), y(obj.y), z(obj.z)
	{
		std::cout << "copy constructor called" << std::endl;
	}
	vec &operator=(vec &obj)
	{
		std::cout << "oparetor = is called" << std::endl;
		x = obj.x;
		y = obj.y;
		z = obj.z;
		return *this;
	}
	~vec()
	{
		std::cout << "vec deconstructor called" << std::endl;
	}
};
std::ostream &operator<<(std::ostream &out, vec &v)
{
	out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return out;
}

template <
	typename K,
	class Compare = std::less<K> >
struct bst
{
	K key;
	bst *left;
	bst *right;
	bst *parent;
	Compare cmp;
	bst(K const &k = K());
	bst(const bst<K, Compare> &obj);
	~bst();
};

template <typename K, class Compare>
bst<K, Compare>::bst(K const &k)
	: key(k), left(NULL), right(NULL), parent(NULL) {}

template <typename K, class Compare>
bst<K, Compare>::bst(const bst<K, Compare> &obj)
	: key(obj.key), left(obj.left), right(obj.right), parent(obj.parent) {}

template <typename K, class Compare>
bst<K, Compare>::~bst() {}

template <typename Node, typename K>
Node *bst_insert(Node *node, K const &key, bool &inserted)
{
	if (node == NULL)
		return new Node(key);

	Node *child;
	if (node->cmp(key.first, node->key.first))
	{
		child = bst_insert(node->left, key, inserted);
		if (!node->left)
			child->parent = node;
		node->left = child;
	}
	else if (node->cmp(node->key.first, key.first))
	{
		child = bst_insert(node->right, key, inserted);
		if (!node->right)
			child->parent = node;
		node->right = child;
	}
	else
		inserted = false;
	return node;
}

template <typename Node, typename K>
Node *bst_erease(Node *root, K key, bool &deleted)
{
	if (root == NULL)
	{
		deleted = false;
		return NULL;
	}
	if (root->cmp(key, root->key.first))
	{
		Node *new_child = bst_erease(root->left, key, deleted);
		if(new_child)
		{
			waza();
			new_child->parent = root->left;
		}
		root->left = new_child;
		return root;
	}
	else if (root->cmp(root->key.first, key))
	{
		Node *new_child = bst_erease(root->right, key, deleted);
		if(new_child)
		{
			new_child->parent = root->right;
			waza();
		}
		root->right = new_child;
		return root;
	}
	if (root->left == NULL)
	{
		Node *rihgt = root->right;
		delete root;
		return rihgt;
	}
	else if (root->right == NULL)
	{
		Node *left = root->left;
		delete root;
		return left;
	}
	else
	{
		Node *succParent = root;
		Node *succ = root->right;
		while (succ->left != NULL)
		{
			succParent = succ;
			succ = succ->left;
		}
		if (succParent != root)
			succParent->left = succ->right;
		else
			succParent->right = succ->right;
		root->key = succ->key;
		delete succ;
		return root;
	}
}

template <typename Node, typename K>
Node *bst_search(Node *root, K const &key)
{
	if (!root || root->key.first == key)
		return root;
	if (root->cmp(key, root->key.first))
		return (bst_search(root->left, key));
	else
		return (bst_search(root->right, key));
}

template <typename Node>
void bst_destroy(Node *root)
{
	if (!root)
		return;
	bst_destroy(root->left);
	Node *right = root->right;
	delete root;
	bst_destroy(right);
}
template <typename Node>
void inorder(Node *root)
{
	if (!root)
		return;
	inorder(root->left);
	std::cout << root->key.first << ", " << root->key.second << std::endl;
	inorder(root->right);
}

#define key_type Key
#define mapped_type T
#define value_type std::pair<Key, T>
#define size_type std::size_t
#define difference_type std::ptrdiff_t
#define key_compare Compare
#define allocator_type Allocator
#define reference value_type &
#define const_reference const value_type &
#define bst_node bst<value_type, Compare>
namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	private:
		key_type _key;
		mapped_type _mapped;
		value_type _value;
		bst_node *root;
		size_type _size;

	public:
		map()
			: _key(key_type()), _mapped(mapped_type()), _value(value_type()), root(NULL), _size(0) {}
		class iterator
		{
		public:
			iterator(bst_node *ptr = NULL) : m_ptr(ptr), end(0) {}
			iterator(iterator const &other) : m_ptr(other.m_ptr), end(other.end) {}
			~iterator() {}
			iterator &operator=(iterator const &other)
			{
				if (*this == other)
					return (*this);
				m_ptr = other.m_ptr;
				return (*this);
			}

			bool operator==(const iterator &other) { return m_ptr + end == other.m_ptr; };
			bool operator!=(const iterator &other) { return m_ptr + end != other.m_ptr; };
			value_type &operator*() const { return (m_ptr + end)->key; }
			value_type *operator->() { return &((m_ptr + end)->key); }
			iterator &operator++()
			{
				bst_node *node = m_ptr;
				// if it == m.begin() - 1
				if (end < 0)
				{
					end = 0;
					return *this;
				}
				// if it == m.end()
				if (end > 0)
					return *this;
				if (node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				else if (node->parent)
				{
					// check if node is the left sibling
					if (node->parent->left == node)
						node = node->parent;
					// get the first parent of right sibling
					else
					{
						while (node->parent && node->parent->right == node)
							node = node->parent;
						node = node->parent;
					}
				}
				if (node)
					m_ptr = node;
				else
					end = 4;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			iterator &operator--()
			{
				if (end > 0)
				{
					end = 0;
					return *this;
				}
				if (end < 0)
					return *this;
				bst_node *node = m_ptr;
				if (node->left)
				{
					node = node->left;
					while (node->right)
						node = node->right;
				}
				else if (node->parent)
				{

					// check if node is the right sibling
					if (node->parent->right == node)
						node = node->parent;
					// get the left parent
					else
					{
						while (node->parent && node->parent->left == node)
							node = node->parent;
						node = node->parent;
					}
				}
				if (node)
					m_ptr = node;
				else
					end = -4;
				return *this;
				// friend value_type &operator=(iterator const &other)
			}
			iterator operator--(int)
			{
				iterator tmp = *this;
				--(*this);
				return tmp;
			}

		private:
			bst_node *m_ptr;
			char end;
		};

		mapped_type &operator[](const key_type &k)
		{
			bst_node *found = bst_search(this->root, k);
			if (found)
				return (found->key.second);
			return _key;
		}
		iterator begin()
		{
			bst_node *left = root->left;
			if (!left)
				return root;
			while (left->left)
				left = left->left;
			return iterator(left);
		}

		void clear()
		{
			bst_destroy(root);
			root = NULL;
			_size = 0;
		}

		size_type count(const key_type &k) const { return (bool(bst_search(root, k))); }

		bool empty() const { return _size == 0; }

		iterator end()
		{
			bst_node *right = root->right;
			if (!right)
				return root;
			while (right->right)
				right = right->right;
			return iterator(right + 4);
		}
		
		void erase (iterator position)
		{
			bool deleted = true;
			root = bst_erease(root, position->first, deleted);
			_size -= deleted;
		}

		size_type erase (const key_type& k)
		{
			bool deleted = true;
			root = bst_erease(root, k, deleted);
			_size -= deleted;
			return deleted;
		}

		void erase (iterator first, iterator last)
		{
			bool deleted;
			(void)last;
			// for(; first != last; first++)
			// {
				deleted = true;
				root = bst_erease(root, first->first, deleted);
				_size -= deleted;
			// }
		}

		std::pair<iterator, bool> insert(const value_type &val)
		{
			std::pair<iterator, bool> p;
			bool inserted = true;
			root = bst_insert(root, val, inserted);
			_size += inserted;
			return p;
		}
		size_type size() const { return _size; }
	};
}

#ifndef NAMESPACE
#define NAMESPACE std
#endif

int main()
{

	NAMESPACE::map<std::string, int> m;

	m.insert(std::pair<std::string, int>("issam0", 28));
	m.insert(std::pair<std::string, int>("issam1", 28));
	m.insert(std::pair<std::string, int>("issam2", 28));
	m.insert(std::pair<std::string, int>("issam3", 28));
	m.insert(std::pair<std::string, int>("yahya", 24));
	m.insert(std::pair<std::string, int>("md", 23));
	m.insert(std::pair<std::string, int>("ichoukri1", 20));
	m.insert(std::pair<std::string, int>("ichoukri2", 40));

	// NAMESPACE::map<std::string, int >::iterator b = m.begin();
	NAMESPACE::map<std::string, int >::iterator it;
	// NAMESPACE::map<std::string, int >::iterator e = m.end();

	int count = 0;
	m.erase("issam1");
	for(it = m.begin() ; it != m.end() && count++ < 30; it++ )
	{
		std::cout << it->first << ", " << it->second << std::endl;
	}



	// std::cout << (*it == *b) << std::endl;

	// std::cout << "----------------------------" << std::endl;
	// std::cout << m[3] << std::endl;

	// std::cout << "----------------------------" << std::endl;
	// bst<std::pair<int, int> , std::greater<int> > *root = NULL;

	// root = bst_insert(root, std::pair<int, int>(4, 5));
	// root = bst_insert(root, std::pair<int, int>(2, 4));
	// root = bst_insert(root, std::pair<int, int>(3, 55));iterator operator++(int)
	// root = bst_insert(root, std::pair<int, int>(44, 7));
	// root = bst_insert(root, std::pair<int, int>(564, 13));
	// root = bst_insert(root, std::pair<int, int>(3434, 89));

	// bst<std::pair<int, int> , std::greater<int> > *tmp = bst_search(root, 2);

	// std::cout << tmp->key.first << ". " << tmp->key.second << std::endl;
	// if (tmp->parent)
	// {
	// 	tmp = tmp->parent;
	// }
	// std::cout << tmp->key.first << ". " << tmp->key.second << std::endl;

	// inorder(root);
}

//////////////////////////////// bugs ////////////////////////////////
// cmp in bst needs to be static
// map::end() return false value
// *it = v (op overload missing)
// bst_insert is broken