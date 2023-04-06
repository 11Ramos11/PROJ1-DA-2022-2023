/** @file Graph.h
 *  @brief Contains the Graph class declaration.
 *  @author João Ramos e Matilde Simões
 *  @bug No known bugs.
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

template <class T>
/** @brief MutablePriorityQueue class represents the Mutable Priority Queue data structure.
 *
 * @tparam T
 */
class MutablePriorityQueue {

    //! @brief Holds the pointers to elements of type T.
	std::vector<T *> H;

    /** @brief Used when inserting a new element
     * or modifying the priority of an existing element.
     *
     * @param i of unsigned type.
     * @return Void.
     */
	void heapifyUp(unsigned i);

    /** @brief Used when deleting the element with the highest priority
     * or modifying the priority of an existing element
     *
     * @param i of unsigned type.
     * @return Void.
     */
	void heapifyDown(unsigned i);

    /** @brief Updates the position of an element
     *
     * @param i of unsigned type.
     * @param x of T* type.
     */
	inline void set(unsigned i, T * x);

public:

    /** @brief Creates a new MutablePriorityQueue.
     *
     */
	MutablePriorityQueue();

    /** @brief Inserts a new element.
     *
     * @param x of T* type.
     * @return Void.
     */
	void insert(T * x);

    /** @brief Extracts an element with the minimum value.
     *
     * @return Element of type T.
     */
	T * extractMin();

    /** @brief decrease the priority of an element.
     *
     * @param x of T* type.
     * @return Void.
     */
	void decreaseKey(T * x);

    /** @brief Checks if the size of the heap is equal to 1.
     *
     * @return True if the heap is empty or false if otherwise.
     */
	bool empty();
};

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
	H.push_back(nullptr);
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
	return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
	auto x = H[1];
	H[1] = H.back();
	H.pop_back();
	if(H.size() > 1) heapifyDown(1);
	x->queueIndex = 0;
	return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
	H.push_back(x);
	heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
	heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
	auto x = H[i];
	while (i > 1 && *x < *H[parent(i)]) {
		set(i, H[parent(i)]);
		i = parent(i);
	}
	set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
	auto x = H[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= H.size())
			break;
		if (k+1 < H.size() && *H[k+1] < *H[k])
			++k; // right child of i
		if ( ! (*H[k] < *x) )
			break;
		set(i, H[k]);
		i = k;
	}
	set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
	H[i] = x;
	x->queueIndex = i;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */
