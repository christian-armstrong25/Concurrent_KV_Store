#include "synchronized_queue.hpp"
/**
 * Implementation of a thread-safe, generic queue.
 *
 * This class is a wrapper for a std::queue that handles all synchronization
 * automatically. Any number of threads can be using this queue concurrently,
 * without having to explicitly lock and unlock mutexes.
 *
 * The class is parametrized by <T>, which can be any object or struct. This
 * allows the queue to be used in a very similar way to the bare std::queue.
 *
 * Before termination of a program the queue needs to be stopped, to allow all
 * waiting threads to continue and to allow the std::condition_variable to be
 * cleaned up.
 */
template <typename T>
/**
 * Get current size of queue.
 *
 * NOTE: By the time this call returns, another thread may have changed the
 * size of the queue. For this reason it is not advised to use this call for
 * anything other than logging.
 *
 * @return current size of the queue
 */
size_t synchronized_queue<T>::size() {
    std::unique_lock<std::mutex> guard(this->mtx);
    // TODO (Part A, Step 3): IMPLEMENT
    return this->q.size();
}

/**
 * Pop and set the elt pointer element from the front of the queue. Returns
 * true if the queue has been stopped, or false otherwise.
 *
 * Unless the queue has been stopped, calling pop() will always set elt and
 * return false. If the queue is empty, pop will wait until an element is
 * pushed onto it.
 *
 * However, if the queue has been stopped, even if the queue is not empty, the
 * function will return true with no element set.
 *
 * @param elt pointer to be set to popped element
 * @return true if the queue has been stopped, or false otherwise
 */
template <typename T>
bool synchronized_queue<T>::pop(T* elt) {
    std::unique_lock<std::mutex> guard(this->mtx);

    if (this->is_stopped) {
        return true;
    }

    while (this->q.empty()) {  // don't just do `if (queue.size() == 0)` here
        cv.wait(guard);
        if (this->is_stopped) {
            return true;
        }
    }

    // get here only if the queue has data
    *elt = this->q.front();
    this->q.pop();
    return false;
}

/**
 * Push an element onto the back of the queue.
 *
 * If the queue is empty, this call will signal any one thread that is waiting
 * to pop from the queue.
 *
 * @param elt element to be pushed on the queue
 */
template <typename T>
void synchronized_queue<T>::push(T elt) {
    std::unique_lock<std::mutex> guard(this->mtx);
    // TODO (Part A, Step 3): IMPLEMENT
    if (this->q.empty()) {
        this->q.push(elt);
        cv.notify_all();
    } else {
        this->q.push(elt);
    }
}

/**
 * Flush will return a vector of all elements currently in the queue, even if
 * the queue has been stopped.
 *
 * After this function is called the queue will be empty. This call may
 * return an empty vector without blocking.
 *
 * @return vector of all elements in the queue
 */
template <typename T>
std::vector<T> synchronized_queue<T>::flush() {
    std::unique_lock<std::mutex> guard(this->mtx);
    // TODO (Part A, Step 3): IMPLEMENT
    std::vector<T> v;
    while (!this->q.empty()) {
        v.push_back(this->q.front());
        this->q.pop();
    }
    return v;
}

/**
 * Stop the queue.
 *
 * This function serves as a way to release any threads waiting for the
 * queue to become non-empty. Doing this also allows the condition variable
 * to be cleaned up when the program exists.
 */
template <typename T>
void synchronized_queue<T>::stop() {
    std::unique_lock<std::mutex> guard(this->mtx);
    // TODO (Part A, Step 3): IMPLEMENT
    this->is_stopped = true;
    cv.notify_all();
}

// NOTE: DO NOT TOUCH! Why is this necessary? Because C++ is a beautiful
// language:
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
template class synchronized_queue<int>;
template class synchronized_queue<std::shared_ptr<ClientConn>>;
