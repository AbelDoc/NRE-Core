
    /**
     * @file NRE_Id.hpp
     * @brief Declaration of Utility's API's Object : Id
     * @author Louis ABEL
     * @date 16/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <cstdint>

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**< Id are currently unsigned 32 bits values, could change to longer values but will never be signed */
        using Id =  uint32_t;
    }
