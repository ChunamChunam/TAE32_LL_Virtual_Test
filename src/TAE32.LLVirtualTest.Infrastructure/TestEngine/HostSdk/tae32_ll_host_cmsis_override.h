/* Remap NVIC/SCB CMSIS calls onto tae32_host_scs (include after tae32_ll_host_scs_remap_tail.h). */
#ifndef TAE32_LL_HOST_CMSIS_OVERRIDE_H
#define TAE32_LL_HOST_CMSIS_OVERRIDE_H

static inline void tae32_host_NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    uint32_t reg_value;
    uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);

    reg_value  =  SCB->AIRCR;
    reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk));
    reg_value  =  (reg_value                                   |
                  ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                  (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos));
    SCB->AIRCR = reg_value;
}

static inline uint32_t tae32_host_NVIC_GetPriorityGrouping(void)
{
    return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}

static inline void tae32_host_NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVIC->IP[((uint32_t)IRQn)] =
            (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
    }
    else
    {
        SCB->SHP[(((uint32_t)IRQn) & 0xFUL) - 4UL] =
            (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
    }
}

static inline uint32_t tae32_host_NVIC_GetPriority(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        return (((uint32_t)NVIC->IP[((uint32_t)IRQn)] >> (8U - __NVIC_PRIO_BITS)));
    }
    return (((uint32_t)SCB->SHP[(((uint32_t)IRQn) & 0xFUL) - 4UL] >> (8U - __NVIC_PRIO_BITS)));
}

#undef NVIC_SetPriorityGrouping
#undef NVIC_GetPriorityGrouping
#undef NVIC_SetPriority
#undef NVIC_GetPriority
#define NVIC_SetPriorityGrouping  tae32_host_NVIC_SetPriorityGrouping
#define NVIC_GetPriorityGrouping  tae32_host_NVIC_GetPriorityGrouping
#define NVIC_SetPriority          tae32_host_NVIC_SetPriority
#define NVIC_GetPriority          tae32_host_NVIC_GetPriority

#endif
