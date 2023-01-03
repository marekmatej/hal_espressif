/*
 * SPDX-FileCopyrightText: 2022-2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/portmacro.h"
#include "esp_heap_caps.h"
#include "esp_timer.h"
#include "soc/rtc.h"
#include "esp_private/esp_clk.h"
#include "esp_coexist_adapter.h"
#include "esp32c6/rom/ets_sys.h"

#define TAG "esp_coex_adapter"

#define OSI_FUNCS_TIME_BLOCKING  0xffffffff

bool IRAM_ATTR env_is_chip_wrapper(void)
{
#ifdef CONFIG_IDF_ENV_FPGA
    return false;
#else
    return true;
#endif
}

void IRAM_ATTR task_yield_from_isr_wrapper(void)
{
    portYIELD_FROM_ISR();
}

void *semphr_create_wrapper(uint32_t max, uint32_t init)
{
    return (void *)xSemaphoreCreateCounting(max, init);
}

void semphr_delete_wrapper(void *semphr)
{
    vSemaphoreDelete(semphr);
}

int32_t IRAM_ATTR semphr_take_from_isr_wrapper(void *semphr, void *hptw)
{
    return (int32_t)xSemaphoreTakeFromISR(semphr, hptw);
}

int32_t IRAM_ATTR semphr_give_from_isr_wrapper(void *semphr, void *hptw)
{
    return (int32_t)xSemaphoreGiveFromISR(semphr, hptw);
}

int32_t semphr_take_wrapper(void *semphr, uint32_t block_time_tick)
{
    if (block_time_tick == OSI_FUNCS_TIME_BLOCKING) {
        return (int32_t)xSemaphoreTake(semphr, portMAX_DELAY);
    } else {
        return (int32_t)xSemaphoreTake(semphr, block_time_tick);
    }
}

int32_t semphr_give_wrapper(void *semphr)
{
    return (int32_t)xSemaphoreGive(semphr);
}

void IRAM_ATTR timer_disarm_wrapper(void *timer)
{
    ets_timer_disarm(timer);
}

void timer_done_wrapper(void *ptimer)
{
    ets_timer_done(ptimer);
}

void timer_setfn_wrapper(void *ptimer, void *pfunction, void *parg)
{
    ets_timer_setfn(ptimer, pfunction, parg);
}

void IRAM_ATTR timer_arm_us_wrapper(void *ptimer, uint32_t us, bool repeat)
{
    ets_timer_arm_us(ptimer, us, repeat);
}

uint32_t esp_clk_slowclk_cal_get_wrapper(void)
{
    /* The bit width of WiFi light sleep clock calibration is 12 while the one of
     * system is 19. It should shift 19 - 12 = 7.
    */
    return (esp_clk_slowclk_cal_get() >> (RTC_CLK_CAL_FRACT - SOC_WIFI_LIGHT_SLEEP_CLK_WIDTH));
}

void *IRAM_ATTR malloc_internal_wrapper(size_t size)
{
    return heap_caps_malloc(size, MALLOC_CAP_8BIT | MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
}

coex_adapter_funcs_t g_coex_adapter_funcs = {
    ._version = COEX_ADAPTER_VERSION,
    ._task_yield_from_isr = task_yield_from_isr_wrapper,
    ._semphr_create = semphr_create_wrapper,
    ._semphr_delete = semphr_delete_wrapper,
    ._semphr_take_from_isr = semphr_take_from_isr_wrapper,
    ._semphr_give_from_isr = semphr_give_from_isr_wrapper,
    ._semphr_take = semphr_take_wrapper,
    ._semphr_give = semphr_give_wrapper,
    ._is_in_isr = xPortInIsrContext,
    ._malloc_internal =  malloc_internal_wrapper,
    ._free = free,
    ._esp_timer_get_time = esp_timer_get_time,
    ._env_is_chip = env_is_chip_wrapper,
    ._slowclk_cal_get = esp_clk_slowclk_cal_get_wrapper,
    ._timer_disarm = timer_disarm_wrapper,
    ._timer_done = timer_done_wrapper,
    ._timer_setfn = timer_setfn_wrapper,
    ._timer_arm_us = timer_arm_us_wrapper,
    ._magic = COEX_ADAPTER_MAGIC,
};
