    
    /**
     * @file NRE_Uncopyable.hpp
     * @brief Declaration of Utility's API's Interface : Uncopyable
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
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            
            /**
             * @class Uncopyable
             * @brief Describe an un-copyable object
             */
            template <class T>
            class Uncopyable {
                friend T;
                public:    // Methods
                    //## Copy-Constructor ##//
                        /**
                         * Copy o into this
                         * @param o the object to copy the content
                         */
                        Uncopyable(Uncopyable const& o) = delete;
                        
                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the object to move the content
                         */
                        Uncopyable(Uncopyable && o) = default;
                        
                    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of o into this
                         * @param o the object to copy into this
                         * @return  the reference of himself
                         */
                        Uncopyable& operator =(Uncopyable const& o) = delete;
                        /**
                         * Move assignment of o into this
                         * @param o the object to move into this
                         * @return  the reference of himself
                         */
                        Uncopyable& operator =(Uncopyable && o) = default;
                
                protected: // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Uncopyable() = default;
                        
                    //## Deconstructor ##//
                        /**
                         * Uncopyable Deconstructor
                         */
                        ~Uncopyable() = default;
            };
        }
    }
