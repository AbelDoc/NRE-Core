    
    /**
     * @file NRE_DirectAllocator.tpp
     * @brief Implementation of Memory's API's Object : DirectAllocator
     * @author Louis ABEL
     * @date 24/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Memory {
            
            template <class T>
            template <class K>
            inline DirectAllocator<T>::DirectAllocator(DirectAllocator<K> const&) noexcept {
            }
            
            template <class T>
            inline typename DirectAllocator<T>::Pointer DirectAllocator<T>::allocate(SizeType n) {
                if (auto p = static_cast <Pointer> (std::malloc(n * sizeof(ValueType)))) {
                    return p;
                }
                throw std::bad_alloc();
            }
            
            template <class T>
            inline void DirectAllocator<T>::deallocate(Pointer p) {
                free(p);
            }
            
            template <class T>
            inline void DirectAllocator<T>::deallocate(Pointer p, SizeType) {
                free(p);
            }
            
            template <class T>
            template <class K, class ... Args>
            inline K* DirectAllocator<T>::construct(K* p, Args && ... args) {
                assert(p != nullptr);
                return static_cast <K*> (::new(static_cast <void*> (p)) K(std::forward<Args>(args)...));
            }
            
            template <class T>
            template <class K>
            inline K* DirectAllocator<T>::destroy(K* p) {
                p->~K();
                return p;
            }
            
        }
    }