#ifndef BST_HPP
#define BST_HPP

namespace ft
{
	template <typename K, class Compare>
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
		Node *to_delete = bst_search(root, key);
		if (!to_delete)
		{
			deleted = false;
			return root;
		}
		Node *parent = to_delete->parent;
		// if to delete has no right replace with its left
		if (!to_delete->right)
		{
			if (parent)
			{
				if (to_delete == parent->right)
					parent->right = to_delete->left;
				else if (parent && to_delete == parent->left)
					parent->left = to_delete->left;
			}
			else
				root = to_delete->left;
			if (to_delete->left)
				to_delete->left->parent = parent;
			delete to_delete;
		}
		// if to_delete has no left replace with its right
		else if (!to_delete->left)
		{
			if (parent)
			{
				if (to_delete == parent->left)
					parent->left = to_delete->right;
				else if (parent && to_delete == parent->right)
					parent->right = to_delete->right;
			}
			else
				root = to_delete->right;
			if (to_delete->right)
				to_delete->right->parent = parent;
			delete to_delete;
		}
		// if to_delte has both righ and left find next successor and replace it value with it and delete the successor instead
		else
		{
			Node *succ = to_delete->right;
			while (succ->left != NULL)
			{
				parent = succ;
				succ = succ->left;
			}
			if (parent != to_delete)
			{
				if (succ->right)
					succ->right->parent = parent;
				parent->left = succ->right;
			}
			else
			{
				if (succ->right)
					succ->right->parent = parent;
				parent->right = succ->right;
			}
			root->key = succ->key;
			delete succ;
		}
		return root;
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
	template <typename Node, typename K>
	Node *bst_nearest(Node *root, K const &key)
	{
		if (!root || root->key.first == key)
			return root;
		while (true)
		{
			if (root->left && root->cmp(key, root->key.first))
				root = root->left;
			else if (root->right && root->cmp(root->key.first, key))
				root = root->right;
			else
				return root;
		}
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
}
#endif