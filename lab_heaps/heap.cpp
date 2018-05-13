/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>
using namespace std;
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // 0 based indexing heap
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return (2 * currentIdx + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return (2 * currentIdx + 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return (2 * currentIdx + 1) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
	return higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]) ? leftChild(currentIdx) : rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // base case
	if (!hasAChild(currentIdx))
		return;
	size_t childIdx = maxPriorityChild(currentIdx);
	if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
		std::swap(_elems[currentIdx], _elems[childIdx]);
		heapifyDown(childIdx);
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
	cout << "heapifyUp called" << endl;
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.
	for (size_t i = 0; i < elems.size(); i++) {
		_elems.push_back(elems[i]);
	}
	for (size_t i = parent(_elems.size() - 1); i > 0; i--)
		heapifyDown(i);
	heapifyDown(root());
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // Remove, and return, the element with highest priority
    T el = _elems[root()];
    _elems[root()] = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(root());
    return el;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems[_elems.size() - 1]);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
	return _elems.empty();
}
