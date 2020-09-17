    
    /**
     * @file NRE_Allocator.hpp
     * @brief Declaration of Memory's API's Object : Allocator
     * @author Louis ABEL
     * @date 21/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "NRE_AllocatorTraits.hpp"
    #include "Default/NRE_DefaultAllocator.hpp"
    #include "Direct/NRE_DirectAllocator.hpp"

    #ifdef NRE_USE_MEMORY_MANAGER
        #include "Manager/NRE_ManagerAllocator.hpp"
    #endif