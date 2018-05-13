/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL)
        subtree = new Node(key, value);
    else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    
    Node* newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;
    
    t->left->height
        = max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right)) + 1;
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    
    Node* newSubRoot = t->left;
    t->left = newSubRoot->right;
    newSubRoot->right = t;
    t = newSubRoot;

    t->right->height = max(heightOrNeg1(t->right->right), heightOrNeg1(t->right->left)) + 1;
    t->height = max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
	// left subtree is longer than right
    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) == 2) {
        if (heightOrNeg1(subtree->left->left) > heightOrNeg1(subtree->left->right)){
            rotateRight(subtree);
        	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        }
        else{
            rotateLeftRight(subtree);
        	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        }
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == 2) {
        if (heightOrNeg1(subtree->right->right) > heightOrNeg1(subtree->right->left)){
            rotateLeft(subtree);
        	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        	return;
        }
        else{
            rotateRightLeft(subtree);
        	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;        
        }
    } else {
        subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* iop = subtree->left;
            while (iop->right != NULL)
                iop = iop->right;
            swap(subtree, iop);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            Node* curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}
