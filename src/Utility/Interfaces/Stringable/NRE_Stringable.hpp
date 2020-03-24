
    /**
     * @file NRE_Stringable.hpp
     * @brief Declaration of Utility's API's Interface : Stringable
     * @author Louis ABEL
     * @date 21/10/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <cassert>

    #include "../NRE_StaticInterface.hpp"
    #include "../../String/NRE_String.hpp"

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
             * @class Stringable
             * @brief Describe an stringable object
             */
            template <class T>
            class Stringable : public StaticInterface<Stringable<T>> {
                public:    // Methods
                    //## Methods ##//
                        /**
                         * Convert the stringable to string format
                         * @return the object's string representation
                         */
                        [[nodiscard]] String toString() const {
                            return this->impl().toString();
                        }
                        /**
                         * Output stream operator for T object
                         * @param  stream the stream to add T string representation
                         * @param  o      the object to add in the stream
                         * @return the    modified stream
                         */
                        friend std::ostream& operator <<(std::ostream& stream, T const& o) {
                            return stream << o.Stringable<T>::toString();
                        }
            };
        }
    }
