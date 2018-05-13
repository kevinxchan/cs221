/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 */

#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "quadtree.h"
#include "png.h"

// Quadtree
//   - parameters: none
//   - constructor for the Quadtree class; makes an empty tree
Quadtree::Quadtree() 
{
	// set root to NULL
	root = NULL;
	// empty image
	res = 0;
}

// Quadtree
//   - parameters: PNG const & source - reference to a const PNG
//                    object, from which the Quadtree will be built
//                 int resolution - resolution of the portion of source
//                    from which this tree will be built
//   - constructor for the Quadtree class; creates a Quadtree representing
//        the resolution by resolution block in the upper-left corner of
//        source
Quadtree::Quadtree(PNG const& source, int setresolution)
{
	res = setresolution;
	build(source, root, res, 0, 0);
}

/**
 * Private helper function to construct a Quadtree, and for buildTree. 
 * Returns a Quadtree with nodes built recursively
 * @param source The source image file in PNG format
 * @param subRoot The current node in the recursion
 * @param res The resolution of the current Quadtree in the recursion
 * @param x The x axis value corresponding to a QuadtreeNode
 * @Param y The y axis value corresponding to a QuadtreeNode
 */
void Quadtree::build(PNG const& source, QuadtreeNode* & subRoot, int res, int x, int y) {
	// base case, condition: single pixel resolution
	if (res == 1) {
		// make a new node with NULL children and pixel as element
		subRoot = new QuadtreeNode(*source(x, y));
		return;
	}
	else {
		// general case
		subRoot = new QuadtreeNode();

		// recursive calls for subRoot's children
		// take res / 2 since res * res image
		// calculate x,y based on 4 quadrants of tree
		build(source, subRoot->nwChild, res / 2, x, y);
		build(source, subRoot->neChild, res / 2, x + res / 2, y);
		build(source, subRoot->swChild, res / 2, x, y + res / 2);
		build(source, subRoot->seChild, res / 2, x + res / 2, y + res / 2);

		// component wise averages for RGBA
		int red = (subRoot->nwChild->element.red + subRoot->neChild->element.red +
			subRoot->swChild->element.red + subRoot->seChild->element.red) / 4;
		int green = (subRoot->nwChild->element.green + subRoot->neChild->element.green +
			subRoot->swChild->element.green + subRoot->seChild->element.green) / 4;
		int blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue +
			subRoot->swChild->element.blue + subRoot->seChild->element.blue) / 4;
		int alpha = (subRoot->nwChild->element.alpha + subRoot->neChild->element.alpha +
			subRoot->swChild->element.alpha + subRoot->seChild->element.alpha) / 4;

		// store averages of all children in current node's element
		subRoot->element = RGBAPixel(red, green, blue, alpha);
	}
}


// Quadtree
//   - parameters: Quadtree const & other - reference to a const Quadtree
//                    object, which the current Quadtree will be a copy of
//   - copy constructor for the Quadtree class
Quadtree::Quadtree(Quadtree const& other) 
{ 
	res = other.res;
	root = copy(other.root);
}

// ~Quadtree
//   - parameters: none
//   - destructor for the Quadtree class
Quadtree::~Quadtree()
{
	clear(root);
}

/**
 * Private helper function for Quadtree destructor that clears beneath the parameter node
 * @param subRoot The current node in the recursion
 */
void Quadtree::clear(QuadtreeNode* & subRoot) {
	if (subRoot == NULL)
		return;
	else {
		// clear node and it's quad children recursively
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);

		delete subRoot;
		subRoot = NULL;
	}
}

// operator=
//   - parameters: Quadtree const & other - reference to a const Quadtree
//                    object, which the current Quadtree will be a copy of
//   - return value: a const reference to the current Quadtree
//   - assignment operator for the Quadtree class
Quadtree const& Quadtree::operator=(Quadtree const& other)
{
	// guard for self assignment
	if (this != &other) {
		// clear previous root contents
		clear(root);
		// set res
		res = other.res;
		// deep copy of root contents
		root = copy(other.root);
	}
	return *this;
}

/**
 * Private helper function for operator= and copy constructor
 * @param subRoot The current node in the recursion
 */
Quadtree::QuadtreeNode* Quadtree::copy(const QuadtreeNode* subRoot) {
	if (subRoot == NULL)
		return NULL;

	// copy node and it's quad children
	QuadtreeNode* newQuad = new QuadtreeNode(subRoot->element);
	newQuad->nwChild = copy(subRoot->nwChild);
	newQuad->neChild = copy(subRoot->neChild);
	newQuad->swChild = copy(subRoot->swChild);
	newQuad->seChild = copy(subRoot->seChild);

	return newQuad;
}

// buildTree (public interface)
//   - parameters: PNG const & source - reference to a const PNG
//                    object, from which the Quadtree will be built
//                 int resolution - resolution of the portion of source
//                    from which this tree will be built
//   - transforms the current Quadtree into a Quadtree representing
//        the resolution by resolution block in the upper-left corner of
//        source
void Quadtree::buildTree(PNG const& source, int setresolution)
{
	// delete contents of current Quadtree object
	clear(root);
	res = setresolution;
	build(source, root, res, 0, 0);
}

// getPixel (public interface)
//   - parameters: int x, int y - coordinates of the pixel to be retrieved
//   - return value: an RGBAPixel representing the desired pixel of the
//        underlying bitmap
//   - retrieves and returns the pixel at coordinates (x, y) in the
//        underlying bitmap
RGBAPixel Quadtree::getPixel(int x, int y) const
{
	// if x,y out of bounds or empty Quadtree
	if (x < 0 || y < 0 || x > res || y > res || root == NULL || res == 0)
		return RGBAPixel();
	return retrieve(root, res, x, y);
}

/**
 * Private helper function for retrieving a pixel at coordinates (x,y). 
 * Returns deepest surviving ancestor if leaf node of interest is non-existent
 * @param subRoot The current node in the recursion
 * @param res The resolution of the current image in the recursion
 * @param x The x coordinate to retrieve
 * @param y The y coordinate to retrieve
 * @return the pixel at (x,y)
 */
RGBAPixel Quadtree::retrieve(QuadtreeNode* subRoot, int res, int x, int y) const {
	// base case, condition: leaf node is non-existent
	// since all internal nodes have non-null children, checking one will suffice
	// thus check one child for simplification
	if (subRoot->nwChild == NULL)
		return subRoot->element;
	// general case, check bounds to determine which quadrant
	else {
		int half = res / 2;
		// bounds for nw quadrant
		if (x >= 0 && x < res / 2 && y >= 0 && y < res / 2) {
			return retrieve(subRoot->nwChild, half, x, y);
		}
		// bounds for ne quadrant
		else if (x >= res / 2 && x < res && y >= 0 && y < res / 2) {
			return retrieve(subRoot->neChild, half, x - half, y);
		}
		else if (x >= 0 && x < res / 2 && y >= res / 2 && y < res) {
			return retrieve(subRoot->swChild, half, x, y - half);
		}
		else {
			return retrieve(subRoot->seChild, half, x - half, y - half);
		}

	}
}


// decompress (public interface)
//   - parameters: none
//   - return value: a PNG object representing this quadtree's underlying
//        bitmap
//   - constructs and returns this quadtree's underlying bitmap
PNG Quadtree::decompress() const
{
	PNG ret;
	// if Quadtree is empty
	if (root == NULL)
		return ret;
	// restore PNG with appropriate pixels
	else {
		ret = PNG((size_t) res, (size_t) res);
		for (int i = 0; i < res; i++) {
			for (int j = 0; j < res; j++) {
				*ret(i, j) = getPixel(i, j);
			}
		}
	}
	return ret;
}

// clockwiseRotate (public interface)
//   - parameters: none
//   - transforms this quadtree into a quadtree representing the same
//        bitmap, rotated 90 degrees clockwise
void Quadtree::clockwiseRotate()
{
	if (root != NULL)
		rotate(root);
}

/**
 * Private helper function to rotate the Quadtree by 90 degrees clockwise.
 * @param subRoot The current root in the recursion
 */
void Quadtree::rotate(QuadtreeNode* & subRoot) {
	if (subRoot->nwChild == NULL)
		return;
	else {
		// store nwChild in a tmp node
		QuadtreeNode* tmp = subRoot->nwChild;

		// rotation. draw it out to see...
		subRoot->nwChild = subRoot->swChild;
		subRoot->swChild = subRoot->seChild;
		subRoot->seChild = subRoot->neChild;
		subRoot->neChild = tmp;

		rotate(subRoot->nwChild);
		rotate(subRoot->neChild);
		rotate(subRoot->swChild);
		rotate(subRoot->seChild);
	}
}

// prune (public interface)
//   - parameters: int tolerance - an integer representing the maximum
//                    "distance" which we will permit between a node's color
//                    (i.e. the average of its descendant leaves' colors)
//                    and the color of each of that node's descendant leaves
//   - for each node in the quadtree, if the "distance" between the average
//        of that node's descendant leaves' colors and the color of each of
//        that node's descendant leaves is at most tolerance, this function
//        deletes the subtrees beneath that node; we will let the node's
//        color "stand in for" the colors of all (deleted) leaves beneath it
void Quadtree::prune(int tolerance)
{
	if (root != NULL)
		pruneTree(root, tolerance);
}

/**
 * Private helper function to prune the given tree.
 * @param subRoot The current node in the recursion
 * @param tolerance The tolerance range to determine if prune
 */
void Quadtree::pruneTree(QuadtreeNode* & subRoot, int tolerance) {
	if (subRoot == NULL)
		return;
	else {
		// general case: non-leaf node
		// if differences are within tolerance, prune the node
		if (shouldPrune(subRoot->nwChild, subRoot, tolerance) &&
			shouldPrune(subRoot->neChild, subRoot, tolerance) &&
			shouldPrune(subRoot->swChild, subRoot, tolerance) &&
			shouldPrune(subRoot->seChild, subRoot, tolerance)) {

			clear(subRoot->nwChild);
			clear(subRoot->neChild);
			clear(subRoot->swChild);
			clear(subRoot->seChild);
		}
		else {
			// recurse down one level and determine if node
			// should be pruned
			pruneTree(subRoot->nwChild, tolerance);
			pruneTree(subRoot->neChild, tolerance);
			pruneTree(subRoot->swChild, tolerance);
			pruneTree(subRoot->seChild, tolerance);
		}
	}
	
}

/**
 * Private helper function to determine whether or not a node
 * should be pruned.
 * @param child The leaf node to be considered
 * @param parent The parent node (current node) in the recursion
 * @param tolerance The tolerance range to determine if prune
 * @return true if the node should be pruned, false otherwise
 */
bool Quadtree::shouldPrune(QuadtreeNode* child, QuadtreeNode* parent, int tolerance) const {
	// case if leaf node passed in
	if (child == NULL)
		return false;
	// base case: the child is a leaf node
	else if (child->nwChild == NULL) {
		int bound = diff(child, parent);
		return bound <= tolerance;
	}
	// general case
	// recurse until a leaf node is reached
	else {
		return shouldPrune(child->nwChild, parent, tolerance) &&
			shouldPrune(child->neChild, parent, tolerance) &&
			shouldPrune(child->swChild, parent, tolerance) &&
			shouldPrune(child->seChild, parent, tolerance);
	}
}

/**
 * Private helper function to calculate the difference between two colors
 * between two nodes.
 * @param node1 The first node of comparison
 * @param node2 The second node of comparison
 * @return the difference between two colors between two nodes
 */
int Quadtree::diff(QuadtreeNode* node1, QuadtreeNode* node2) const {
	// (n2 - n1)
	int red = (node2->element.red - node1->element.red);
	int green = (node2->element.green - node1->element.green);
	int blue = (node2->element.blue - node1->element.blue);

	// (n2 - n1) ^ 2
	red = pow(red, 2);
	green = pow(green, 2);
	blue = pow(blue, 2);

	// return sum
	return red + green + blue;
}

// pruneSize (public interface)
//   - parameters: int tolerance - an integer representing the maximum
//                    "distance" which we will permit between a node's color
//                    (i.e. the average of its descendant leaves' colors)
//                    and the color of each of that node's descendant leaves
//   - returns the number of leaves which this quadtree would contain if it
//        was pruned using the given tolerance; does not actually modify the
//        tree
int Quadtree::pruneSize(int tolerance) const
{
	if (root == NULL)
		return 0;
	return numPrunes(root, tolerance);
}

/**
 * Private helper function that returns a 
 * count of the total number of leaves the Quadtree would 
 * have if it were pruned as in the prune function.
 * @param subRoot The current node in the recursion
 * @param tolerance The given tolerance range
 * @return a count of the total number of leaves the Quadtree 
 *         after hypothetical pruning
 */
int Quadtree::numPrunes(QuadtreeNode* subRoot, int tolerance) const {
	// leaf node is a single node
	if (subRoot->nwChild == NULL)
		return 1;
	// if the node should be pruned then this node should "become" a leaf node
	else if (shouldPrune(subRoot->nwChild, subRoot, tolerance) &&
				shouldPrune(subRoot->neChild, subRoot, tolerance) &&
				shouldPrune(subRoot->swChild, subRoot, tolerance) &&
				shouldPrune(subRoot->seChild, subRoot, tolerance)) {
		return 1;
	}
	else {
		return  numPrunes(subRoot->nwChild, tolerance) +
				numPrunes(subRoot->neChild, tolerance) + 
				numPrunes(subRoot->swChild, tolerance) + 
				numPrunes(subRoot->seChild, tolerance);
	}
}

// idealPrune (public interface)
//   - parameters: int numLeaves - an integer representing the number of
//                    leaves we wish the quadtree to have, after pruning
//   - returns the minimum tolerance such that pruning with that tolerance
//        would yield a tree with at most numLeaves leaves
int Quadtree::idealPrune(int numLeaves) const
{
	if (root == NULL)
		return 0;
	// distance between white and black = 3(255^2)
	return minTolerance(numLeaves, 0, 255*255*3);
}


/**
 * Private helper function that does a binary search
 * over all possible tolerances to return a tolerance
 * that prunes the tree with at most numLeaves.
 * @param numLeaves The number of leaves you want to remain in the tree
 *  after prune is called.
 * @param min The minimum tolerance range
 * @param max The maximum tolerance range
 * @return The minimum tolerance needed to guarantee that there are no
 *  more than numLeaves remaining in the tree.
 */
int Quadtree::minTolerance(int numLeaves, int min, int max) const {
	if (min < max) {
		int mid = (min + max) / 2;
		if (pruneSize(mid) == numLeaves) {
			return mid;
		}
		else if (pruneSize(mid) > numLeaves) {
			return minTolerance(numLeaves, mid + 1, max);
		}
		else {
			return minTolerance(numLeaves, min, mid);
		}
	}
	else {
		return min;
	}
}

// QuadtreeNode
//   - parameters: none
//   - constructor for the QuadtreeNode class; creates an empty
//        QuadtreeNode, with all child pointers NULL
Quadtree::QuadtreeNode::QuadtreeNode()
{
    neChild = seChild = nwChild = swChild = NULL;
}

// QuadtreeNode
//   - parameters: RGBAPixel const & elem - reference to a const
//        RGBAPixel which we want to store in this node
//   - constructor for the QuadtreeNode class; creates a QuadtreeNode
//        with element elem and all child pointers NULL
Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel const& elem)
{
    element = elem;
    neChild = seChild = nwChild = swChild = NULL;
}
