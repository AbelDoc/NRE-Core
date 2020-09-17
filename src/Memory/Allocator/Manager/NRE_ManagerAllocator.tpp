    
    /**
     * @file NRE_ManagerAllocator.tpp
     * @brief Implementation of Memory's API's Object : ManagerAllocator
     * @author Louis ABEL
     * @date 24/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Memory {
            
            template <class T>
            template <class K>
            inline ManagerAllocator<T>::ManagerAllocator(ManagerAllocator<K> const&) noexcept {
            }
            
            template <class T>
            inline typename ManagerAllocator<T>::Pointer ManagerAllocator<T>::allocate(SizeType n) {
                if (auto p = static_cast <Pointer> (std::malloc(n * sizeof(ValueType)))) {
                    MemoryManager::store(p);
                    return p;
                }
                throw std::bad_alloc();
            }
            
            template <class T>
            inline void ManagerAllocator<T>::deallocate(Pointer p) {
                MemoryManager::remove(p);
                free(p);
            }
            
            template <class T>
            inline void ManagerAllocator<T>::deallocate(Pointer p, SizeType) {
                MemoryManager::remove(p);
                free(p);
            }
            
            template <class T>
            template <class K, class ... Args>
            inline K* ManagerAllocator<T>::construct(K* p, Args && ... args) {
                assert(p != nullptr);
                return static_cast <K*> (::new(static_cast <void*> (p)) K(std::forward<Args>(args)...));
            }
            
            template <class T>
            template <class K>
            inline K* ManagerAllocator<T>::destroy(K* p) {
                p->~K();
                return p;
            }
            
        }
    }