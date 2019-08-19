
    /**
     * @file NRE_IException.hpp
     * @brief Declaration of Utility's API's Object : IException
     * @author Louis ABEL
     * @date 19/08/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <stdexcept>
    #include "../Utility/String/NRE_String.hpp"

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Exception
         * @brief Utility's API
         */
        namespace Exception {

            /**
             * @pure IException
             * @brief An interface for exception
             */
            class IException : public std::runtime_error {
                public:
                    /**
                     * No Default Constructor
                     */
                    IException() = delete;
                    /**
                     * Construct an IException with a custom log
                     * @param log the IException's log
                     */
                    IException(Utility::String const& log) throw() : runtime_error(log.getCData()) {
                    }
                    /**
                     * Copy e into this
                     * @param e the IException to copy the content
                     */
                    IException(IException const& e) throw() = default;
                    /**
                     * Move e into this, leaving e empty
                     * @param e the IException to move
                     */
                    IException(IException && e) throw() = default;
                    /**
                     * IException Deconstructor
                     */
                    virtual ~IException() throw() = default;
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
                    /**
                     * Convert an IException into a string
                     * @return   the converted IException
                     */
                    Utility::String toString() const {
                       return Utility::String(what());
                    }

                    /**
                     * Output stream operator for the object
                     * @param  stream the stream to add the object's string representation
                     * @param  o      the object to add in the stream
                     * @return        the modified stream
                     */
                    friend std::ostream& operator <<(std::ostream& stream, IException const& o) {
                        return stream << o.toString();
                    }
            };
        }
    }
