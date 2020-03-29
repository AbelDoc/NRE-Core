    
    /**
     * @file NRE_Stack.tpp
     * @brief Implementation of Utility's API's Container : Stack
     * @author Louis ABEL
     * @date 24/02/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Utility {
            
            template <class T, class Container>
            inline Stack<T, Container>::Stack(Container && container) : c(std::move(container)) {
            }
    
            template <class T, class Container>
            inline Stack<T, Container>::Stack(Container const& container) : c(container) {
            }
    
            template <class T, class Container>
            inline typename Stack<T, Container>::Reference Stack<T, Container>::getTop() {
                return c.getLast();
            }
    
            template <class T, class Container>
            inline typename Stack<T, Container>::ConstReference Stack<T, Container>::getTop() const {
                return c.getLast();
            }
            
            template <class T, class Container>
            inline bool Stack<T, Container>::isEmpty() const {
                return c.isEmpty();
            }
            
            template <class T, class Container>
            inline typename Stack<T, Container>::SizeType Stack<T, Container>::getSize() const {
                return c.getSize();
            }
            
            template <class T, class Container>
            inline void Stack<T, Container>::push(ConstReference value) {
                c.pushBack(value);
            }
            
            template <class T, class Container>
            inline void Stack<T, Container>::push(ValueType && value) {
                c.pushBack(std::move(value));
            }
            
            template <class T, class Container>
            template <class ... Args>
            inline void Stack<T, Container>::emplace(Args && ... args) {
                c.emplaceBack(std::forward<Args>(args)...);
            }
            
            template <class T, class Container>
            inline void Stack<T, Container>::pop() {
                c.popBack();
            }
            
            template <class T, class Container>
            inline void Stack<T, Container>::swap(Stack& s) {
                c.swap(s.c);
            }
            
            template <class T, class Container>
            inline bool Stack<T, Container>::operator==(Stack const& s) const {
                return c == s.c;
            }
            
            template <class T, class Container>
            inline bool Stack<T, Container>::operator!=(Stack const& s) const {
                return c != s.c;
            }
            
            template <class T, class Container>
            inline String Stack<T, Container>::toString() const {
                return c.toString();
            }
    
        }
    }