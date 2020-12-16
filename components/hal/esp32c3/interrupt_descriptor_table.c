// Copyright 2020 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "sdkconfig.h"
#include "hal/interrupt_controller_hal.h"
#include "soc/soc_caps.h"
#include "soc/soc.h"

//This is basically a software-readable version of the interrupt usage table in include/soc/soc.h
const int_desc_t interrupt_descriptor_table[32] = {
    { 1, INTTP_NA, {INTDESC_RESVD } }, //0
    { 1, INTTP_NA, {INTDESC_SPECIAL } }, //1
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //2
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //3
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //4
    { 1, INTTP_NA, {INTDESC_SPECIAL } }, //5
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //6
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //7
    { 1, INTTP_NA, {INTDESC_SPECIAL } }, //8
    { 1, INTTP_NA, {INTDESC_SPECIAL } }, //9
    { 1, INTTP_NA, {INTDESC_NORMAL } },  //10
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //11
    { 1, INTTP_NA, {INTDESC_SPECIAL } }, //12
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //13
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //14
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //15
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //16
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //17
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //18
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //19
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //20
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //21
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //22
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //23
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //24
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //25
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //26
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //27
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //28
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //29
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //30
    { 1, INTTP_NA, {INTDESC_NORMAL } }, //31
};

const int_desc_t *interrupt_controller_hal_desc_table(void)
{
    return interrupt_descriptor_table;
}
