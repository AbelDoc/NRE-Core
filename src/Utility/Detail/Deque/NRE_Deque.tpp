    
    /**
     * @file NRE_Deque.tpp
     * @brief Implementation of Utility's API's Container : Deque
     * @author Louis ABEL
     * @date 08/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Utility {
            namespace Detail {
                namespace DequeInner {
    
                    template <class T, class Category>
                    inline typename DequeIterator<T, Category>::Reference DequeIterator<T, Category>::dereference() const {
                        return *current;
                    }
                    
                    template <class T, class Category>
                    inline void DequeIterator<T, Category>::increment() {
                        current++;
                        if (current == last) {
                            setNode(node + 1);
                            current = first;
                        }
                    }
                    
                    template <class T, class Category>
                    inline void DequeIterator<T, Category>::decrement() {
                        if (current == first) {
                            setNode(node - 1);
                            current = last;
                        }
                        current--;
                    }
                    
                    template <class T, class Category>
                    inline void DequeIterator<T, Category>::advance(DifferenceType n) {
                        DifferenceType offset = n + (current - first);
                        if (offset >= 0 && offset < BUFFER_SIZE) {
                            current += n;
                        } else {
                            DifferenceType nodeOffset = offset > 0 ? offset / static_cast <DifferenceType> (BUFFER_SIZE)
                                                                   : - static_cast <DifferenceType> ((-offset - 1) / BUFFER_SIZE) - 1;
                            setNode(node + nodeOffset);
                            current = first + (offset - nodeOffset * static_cast <DifferenceType> (BUFFER_SIZE));
                        }
                    }
                    
                    template <class T, class Category>
                    inline typename DequeIterator<T, Category>::DifferenceType DequeIterator<T, Category>::distanceTo(Iterator const& it) const {
                        return (node - it.node) * static_cast <DifferenceType> (BUFFER_SIZE) + ((current - first) - (it.current - it.first));
                    }
                    
                    template <class T, class Category>
                    inline bool DequeIterator<T, Category>::equal(Iterator const& it) const {
                        return current == it.current;
                    }
                    
                    template <class T, class Category>
                    inline void DequeIterator<T, Category>::setNode(MapPointer newNode) {
                        node = newNode;
                        first = *node;
                        last  = first + static_cast <DifferenceType> ()
                    }
                
                }
            }
        }
    }