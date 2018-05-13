/**
 * @file quadtree.h
 * Quadtree class definition.
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"
#include <cmath>

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    /**
     * The no parameters constructor takes no arguments, and produces
     * an empty Quadtree object, i.e. one which has no associated
     * QuadtreeNode objects, and in which root is NULL.
     */
    Quadtree();

    /**
     * This constructor's purpose is to build a Quadtree representing
     * the upper-left resolution by resolution block of the source image. This
     * effectively crops the source image into a resolution by resolution 
     * square.
     *
     * You may assume that resolution is a power of two, and that the width and
     * height of source are each at least resolution.
     *
     * Perhaps, to implement this, you could leverage the functionality
     * of another function you have written.
     *
     * @param source The source image to base this Quadtree on
     * @param resolution The width and height of the sides of the image to
     *  be represented
     */
    Quadtree(PNG const& source, int resolution);

    /**
     * Copy constructor. Simply sets this Quadtree to be a copy of the
     * parameter.
     * @param other The Quadtree to make a copy of
     */
    Quadtree(Quadtree const& other);

    /**
     * Destructor; frees all memory associated with this Quadtree.
     */
    ~Quadtree();

    /**
     * Assignment operator; frees memory associated with this Quadtree
     * and sets its contents to be equal to the parameter's.
     *
     * @param other The Quadtree to make a copy of
     * @return A constant reference to the Quadtree value that was copied
     */
    Quadtree const& operator=(Quadtree const& other);

    /**
     * Deletes the current contents of this Quadtree object, then turns
     * it into a Quadtree object representing the upper-left resolution 
     * by resolution block of source. You may assume that resolution 
     * is a power of two, and that the width and height of source 
     * are each at least resolution.
     *
     * @param source The source image to base this Quadtree on
     * @param resolution The width and height of the sides of the image to
     *  be represented
     */
    void buildTree(PNG const& source, int resolution);

    /**
     * Gets the RGBAPixel corresponding to the pixel at coordinates (x,
     * y) in the bitmap image which the Quadtree represents.
     *
     * Note that the Quadtree may not contain a node specifically
     * corresponding to this pixel (due, for instance, to pruning - see
     * below). In this case, getPixel will retrieve the pixel (i.e. the
     * color) of the square region within which the smaller query grid
     * cell would lie. (That is, it will return the element of the
     * nonexistent leaf's deepest surviving ancestor.) If the supplied
     * coordinates fall outside of the bounds of the underlying bitmap,
     * or if the current Quadtree is "empty" (i.e., it was created by
     * the default constructor) then the returned RGBAPixel should be
     * the one which is created by the default RGBAPixel constructor.
     *
     * @param x The x coordinate of the pixel to be retrieved
     * @param y The y coordinate of the pixel to be retrieved
     * @return The pixel at the given (x, y) location
     */
    RGBAPixel getPixel(int x, int y) const;

    /**
     * Returns the underlying PNG object represented by the Quadtree.
     *
     * If the current Quadtree is "empty" (i.e., it was created by the
     * default constructor) then the returned PNG should be the one
     * which is created by the default PNG constructor.  This function
     * effectively "decompresses" the Quadtree. A Quadtree object, in
     * memory, may take up less space than the underlying bitmap image,
     * but we cannot simply look at the Quadtree and tell what image it
     * represents. By converting the Quadtree back into a bitmap image,
     * we lose the compression, but gain the ability to view the image
     * directly.
     *
     * @return The decompressed PNG image this Quadtree represents
     */
    PNG decompress() const;

    /**
     * Rotates the Quadtree object's underlying image clockwise by 90
     * degrees. (Note that this should be done using pointer
     * manipulation, not by attempting to swap the element fields of
     * QuadtreeNodes.  Trust us; it's easier this way.)
     */
    void clockwiseRotate();

// PA 4 FUNCTIONS

    /**
     * Compresses the image this Quadtree represents.
     *
     * If the color values of the leaves of a subquadtree don't vary by
     * much, we might as well represent the entire subtree by, say, the
     * average color value of those leaves. We may use this information
     * to effectively "compress" the image, by strategically trimming
     * the Quadtree.
     *
     * Consider a node \f$n\f$ and the subtree, \f$T_n\f$ rooted at
     * \f$n\f$, and let \f$avg\f$ denote the component-wise average
     * color value of all the leaves of \f$T_n\f$.  Component-wise
     * average means that every internal node in the tree calculates
     * its value by averaging its immediate children. This implies that
     * the average must be calculated in a "bottom-up" manner.
     *
     * Due to rounding errors, using the component-wise average is not
     * equivalent to using the true average of all leaves in a subtree.
     * If a node \f$n\f$ is pruned, the children of \f$n\f$ and the
     * subtrees for which they are the roots are removed from the
     * Quadtree. Node \f$n\f$ is pruned if the color value of no leaf
     * in \f$T_n\f$, differs from \f$avg\f$ by more than tolerance.
     * (Note: for all average calculations, just truncate the value to
     * integer.)
     *
     * We define the "difference" between two colors, \f$(r_1, g_1,
       b_1)\f$ and \f$(r_2, g_2, b_2)\f$, to be \f$(r_2 - r_1)^2 + (g_2
       - g_1)^2 + (b_2 - b_1)^2\f$.
     *
     * To be more complete, if the tolerance condition is met at a node
     * \f$n\f$, then the block of the underlying image which \f$n\f$
     * represents contains only pixels which are "nearly" the same
     * color. For each such node \f$n\f$, we remove from the Quadtree
     * all four children of \f$n\f$, and their respective subtrees (an
     * operation we call a pruning).  This means that all of the leaves
     * that were deleted, corresponding to pixels whose colors were
     * similar, are now replaced by a single leaf with color equal to
     * the average color over that square region.
     *
     * The prune function, given a tolerance value, prunes the Quadtree
     * as extensively as possible. (Note, however, that we do not want
     * the prune function to do an "iterative" prune. It is conceivable
     * that by pruning some mid-level node \f$n\f$, an ancestor \f$p\f$
     * of \f$n\f$ then becomes prunable, due to the fact that the prune
     * changed the leaves descended from \f$p\f$. Your prune function
     * should evaluate the prunability of each node based on the
     * presence of all nodes, and then delete the subtrees based at
     * nodes deemed prunable.)
     *
     * @note You should start pruning from the root of the Quadtree.
     *
     * @param tolerance The integer tolerance between two nodes that
     *  determines whether the subtree can be pruned.
     */
    void prune(int tolerance);

    /**
     * This function is similar to prune; however, it does not actually
     * prune the Quadtree. Rather, it returns a count of the total
     * number of leaves the Quadtree would have if it were pruned as in
     * the prune function.
     *
     * @param tolerance The integer tolerance between two nodes that
     *  determines whether the subtree can be pruned.
     * @return How many leaves this Quadtree would have if it were pruned
     *  with the given tolerance.
     */
    int pruneSize(int tolerance) const;

    /**
     * Calculates and returns the minimum tolerance necessary to
     * guarantee that upon pruning the tree, no more than numLeaves
     * leaves remain in the Quadtree.
     *
     * Essentially, this function is an inverse of pruneSize; for any
     * Quadtree object theTree, and for any positive integer tolerance
     * it should be true that
     *
     *      theTree.pruneSize(theTree.idealPrune(numLeaves)) <= numLeaves
     *
     * Once you understand what this function is supposed to do, you
     * will probably notice that there is an "obvious" implementation.
     * This is probably not the implementation you want to use! There
     * is a fast way to implement this function, and a slow way; you
     * will need to find the fast way. (If you doubt that it makes a
     * significant difference, the tests in the given main.cpp should
     * convince you.)
     *
     * @param numLeaves The number of leaves you want to remain in the tree
     *  after prune is called.
     * @return The minimum tolerance needed to guarantee that there are no
     *  more than numLeaves remaining in the tree.
     * @note The "obvious" implementation involves a sort of linear search over
     *  all possible tolerances. What if you tried a binary search instead?
     */
    int idealPrune(int numLeaves) const;

// END PA 4 FUNCTIONS

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two.
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */

      	// default constructor
      	QuadtreeNode();
        // default param constructor
        QuadtreeNode(RGBAPixel const& elem);
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int res; // resolution of the underlying bitmap (number of pixels in an image)

    ///////////////////////////////////////////
    // HELPER FUNCTIONS ADDED BELOW (by me!) //
    ///////////////////////////////////////////

    /**
     * Private helper function to construct a Quadtree, and for buildTree. 
     * Returns a Quadtree with nodes built recursively
     * @param source The source image file in PNG format
     * @param subRoot The current node in the recursion
     * @param res The resolution of the current Quadtree in the recursion
     * @param x The x axis value corresponding to a QuadtreeNode
     * @param y The y axis value corresponding to a QuadtreeNode
     */
    void build(PNG const& source, QuadtreeNode* & subRoot, int res, int x, int y);

	/**
	 * Private helper function for operator= and copy constructor
	 * @param subRoot The current node in the recursion
     * @return a deep copy of the given subRoot
	 */
    QuadtreeNode* copy(const QuadtreeNode* subRoot);

    /**
     * Private helper function for Quadtree destructor that clears beneath the parameter node.
     * @param subRoot The current node in the recursion
     */
    void clear(QuadtreeNode* & subRoot);

    /**
     * Private helper function for retrieving a pixel at coordinates (x,y). 
     * Returns deepest surviving ancestor if leaf node of interest is non-existent
     * @param subRoot The current node in the recursion
     * @param res The resolution of the current image in the recursion
     * @param x The x coordinate to retrieve
     * @param y The y coordinate to retrieve
     * @return the pixel at (x,y)
     */
    RGBAPixel retrieve(QuadtreeNode* subRoot, int res, int x, int y) const;

    /**
     * Private helper function to rotate the Quadtree by 90 degrees clockwise.
     * @param subRoot The current root in the recursion
     */
    void rotate(QuadtreeNode* & subRoot);

    /**
     * Private helper function to prune the given tree.
     * @param subRoot The current node in the recursion
     * @param tolerance The tolerance range to determine if prune
     */
    void pruneTree(QuadtreeNode* & subRoot, int tolerance);

    /**
     * Private helper function to determien whether or not a node
     * should be pruned.
     * @param child The leaf node to be considered
     * @param parent The parent node (current node) in the recursion
     * @param tolerance The tolerance range to determine if prune
     * @return true if the node should be pruned, false otherwise
     */
    bool shouldPrune(QuadtreeNode* child, QuadtreeNode* parent, int tolerance) const;

    /**
     * Private helper function to calculate the difference between two colors
     * between two nodes.
     * @param node1 The first node of comparison
     * @param node2 The second node of comparison
     * @return the difference between two colors between two nodes
     */
    int diff(QuadtreeNode* node1, QuadtreeNode* node2) const;

    /**
     * Private helper function that returns a 
     * count of the total number of leaves the Quadtree would 
     * have if it were pruned as in the prune function.
     * @param subRoot The current node in the recursion
     * @param tolerance The given tolerance range
     * @return a count of the total number of leaves the Quadtree 
     *         after hypothetical pruning
     */
    int numPrunes(QuadtreeNode* subRoot, int tolerance) const;

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
    int minTolerance(int minLeaves, int min, int max) const;
	
/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
