
    /**
     * @file NRE_IException.hpp
     * @brief Declaration of Core's API's Object : IException
     * @author Louis ABEL
     * @date 19/08/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <stdexcept>
    #include "../Core/String/NRE_String.hpp"
    #include "../Core/Interfaces/Stringable/NRE_Stringable.hpp"

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Exception
         * @brief Core's API
         */
        namespace Exception {

            /**
             * @pure IException
             * @brief An interface for exception
             */
            class IException : public std::runtime_error, public Core::Stringable<IException> {
                public:
                    //## Constructor ##//
                        /**
                         * No Default Constructor
                         */
                        IException() = delete;
                        /**
                         * Construct an IException with a custom log
                         * @param log the IException's log
                         */
                        IException(Core::String const& log) throw() : runtime_error(log.getCData()) {
                        }
    
                    //## Copy Constructor ##//
                        /**
                         * Copy e into this
                         * @param e the IException to copy the content
                         */
                        IException(IException const& e) throw() = default;
    
                    //## Move Constructor ##//
                        /**
                         * Move e into this, leaving e empty
                         * @param e the IException to move
                         */
                        IException(IException && e) throw() = default;
    
                    //## Deconstructor ##//
                        /**
                         * IException Deconstructor
                         */
                        virtual ~IException() throw() = default;
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of e into this
                         * @param e the IException to copy into this
                         * @return the reference of himself
                         */
                        IException& operator=(IException const& e) = default;
                        /**
                         * Move assignment of e into this, leaving e empty
                         * @param e the IException to move into this
                         * @return the reference of himself
                         */
                        IException& operator=(IException && e) = default;
    
                    //## Stream Operator ##//
                        /**
                         * Convert an IException into a string
                         * @return   the converted IException
                         */
                        Core::String toString() const {
                           return Core::String(what());
                        }
            };
        }
    }
