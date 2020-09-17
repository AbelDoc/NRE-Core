    
    /**
     * @file NRE_StaticInterface.hpp
     * @brief Declaration of Core's API's Object : StaticInterface
     * @author Louis ABEL
     * @date 20/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
            
            /**
             * @class StaticInterface
             * @brief Describe an object using CRTP to create static interface (static polymorphism)
             */
            template <class T>
            class StaticInterface {
            };
            /**
             * @class StaticInterface
             * @brief Describe an object using CRTP to create static interface (static polymorphism)
             */
            template <template<class, class...> class M, class T, class ... Args>
            class StaticInterface<M<T, Args...>> {
                public:    // Methods
                    /**
                     * @return the derived object
                     */
                    T& impl() {
                        return static_cast <T&> (*this);
                    }
                    /**
                     * @return the derived object
                     */
                    T const& impl() const {
                        return static_cast <T const&> (*this);
                    }
            };
        }
    }
