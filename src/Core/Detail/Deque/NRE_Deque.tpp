    
    /**
     * @file NRE_Deque.tpp
     * @brief Implementation of Core's API's Container : Deque
     * @author Louis ABEL
     * @date 08/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Core {
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
                        return (node - it.node - 1) * static_cast <DifferenceType> (BUFFER_SIZE) + (current - first) + (it.last - it.current);
                    }
                    
                    template <class T, class Category>
                    inline bool DequeIterator<T, Category>::equal(Iterator const& it) const {
                        return current == it.current;
                    }
                    
                    template <class T, class Category>
                    inline void DequeIterator<T, Category>::setNode(MapPointer newNode) {
                        node = newNode;
                        first = *node;
                        last  = first + static_cast <DifferenceType> (BUFFER_SIZE);
                    }
                
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(AllocatorType const& alloc) : AllocatorType(alloc), map(nullptr), mapSize(0) {
                    initializeMap(0);
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(SizeType count, ConstReference value, AllocatorType const& alloc) : AllocatorType(alloc), map(nullptr), mapSize(0) {
                    initializeMap(count);
                    assign(count, value);
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(SizeType count, AllocatorType const& alloc) : Deque(count, ValueType(), alloc) {
                }
                
                template <class T, class Allocator>
                template <class InputIterator>
                inline Deque::Deque(InputIterator begin, InputIterator end, AllocatorType const& alloc) : AllocatorType(alloc), map(nullptr), mapSize(0) {
                    initializeMap(std::distance(begin, end));
                    assign(begin, end);
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(std::initializer_list<T> init, Allocator const& alloc) : Deque(init.begin(), init.end(), alloc) {
                }
    
                template <class T, class Allocator>
                inline Deque::Deque(Deque const& d) : Deque(d, static_cast <AllocatorType const&> (d)) {
                }
    
                template <class T, class Allocator>
                inline Deque::Deque(Deque const& d, AllocatorType const& alloc) : AllocatorType(alloc), map(nullptr), mapSize(0) {
                    initializeMap(d.getSize());
                    copy(d);
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(Deque && d) : Deque(std::move(d), static_cast <AllocatorType const&> (d)) {
                }
                
                template <class T, class Allocator>
                inline Deque::Deque(Deque && d, AllocatorType const& alloc) : AllocatorType(alloc), map(d.map), mapSize(d.mapSize), start(d.start), finish(d.finish) {
                    d.map = nullptr;
                    d.mapSize = 0;
                }
                
                template <class T, class Allocator>
                inline void Deque::initiliazeMap(SizeType nbElements) {
                    const SizeType nbNodes = nbElements / BUFFER_SIZE + 1;
                    mapSize = std::max(INITIAL_MAP_SIZE, nbNode + 2);
                    map = allocateMap(mapSize);
                    
                    Pointer* begin = map + (mapSize - nbNodes) / 2;
                    Pointer* end   = end + nbNodes;
                    
                    try {
                        createsNodes(begin, end);
                    } catch (std::exception& e) {
                        deallocateMap(map, mapSize);
                        map = nullptr;
                        mapSize = 0;
                        throw e;
                    }
                    
                    start.setNode(begin);
                    start.current = start.first;
                    finish.setNode(end - 1);
                    finish.current = finish.first + nbElements % BUFFER_SIZE;
                }
    
                template <class T, class Allocator>
                inline void Deque::createNodes(Pointer* begin, Pointer* end) {
                    Pointer* currentNode = nullptr;
                    try {
                        for (currentNode = begin; currentNode < end; currentNode++) {
                            *currentNode = allocateNode();
                        }
                    } catch (std::exception& e) {
                        destroyNodes(begin, currentNode);
                        throw e;
                    }
                }
                
                template <class T, class Allocator>
                inline void Deque::destroyNodes(Pointer* begin, Pointer* end) {
                    for (auto current = begin; current < end; current++) {
                        deallocateNode(current);
                    }
                }
                
                template <class T, class Allocator>
                inline typename Deque::Pointer Deque::allocateNode() {
                    return this->allocate(BUFFER_SIZE);
                }
                
                template <class T, class Allocator>
                inline void Deque::deallocateNode(Pointer p) {
                    this->deallocate(p, BUFFER_SIZE);
                }
                
                template <class T, class Allocator>
                inline typename Deque::MapPointer Deque::allocateMap(SizeType nbElements) {
                    return static_cast <MapAllocator*> (this)->allocate(nbElements);
                }
                
                template <class T, class Allocator>
                inline void Deque::deallocateMap(MapPointer p, SizeType nbElements) {
                    static_cast <MapAllocator*> (this)->deallocate(p, nbElements);
                }
            }
        }
    }