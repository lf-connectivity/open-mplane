/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fcntl.h>
#include <string>

extern "C" {
#include "MplaneHardware.h"
}

namespace{
const bool kModelNamePres = true;
const bool kSerialNoPres = true;

const char* kOranName = "ZCU111";
const char* kProductCode = "EK-U1-ZCU111-G";
}//namespace

/**
 * Get energy saving state associated with this hardware component
 * hw_comp->energysaving_state is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_energysaving_state(hw_component_t *hw_comp){
    //no energysaving state known on ZCU111
    *(hw_comp->energy_saving_state) = ENERGY_SAVING_STATE_UNKNOWN;
    return NONE;
}

/**
 * Get the availability type associated with this hardware component
 * hw_comp->availability_type is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_availability_type(hw_component_t *hw_comp){
    //TODO when alarms list is available
    return UNIMPLEMENTED;
}

/**
 * Get label content details (model name and serial no. present?) associated with
 * this hardware component
 * hw_comp->label_content is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_label_content(hw_component_t *hw_comp){
    *(hw_comp->label_content->model_name) = kModelNamePres;
    *(hw_comp->label_content->serial_number) = kSerialNoPres;

    return NONE;
}

/**
 * Get the product code associated with this hardware component
 * hw_comp->product_code is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_product_code(hw_component_t *hw_comp){
    hw_comp->product_code = kProductCode;
    return NONE;
}

/**
 * Checks if energy saving is enabled on this hardware component
 * hw_comp->energy_saving_enabled is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_is_energy_saving_enabled(hw_component_t *hw_comp){
    //need to implement low power mode in order for energy_saving to be possible
    //default is false in O-RAN spec
    *(hw_comp->energy_saving_enabled) = false;
    return NONE;
}

/**
 * Checks if dying gasp support is enabled on this hardware component
 * hw_comp->dying_gasp_support is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_dying_gasp_support(hw_component_t *hw_comp){
    //dying gasp support needs to be implemented before this can be supported
    //default is false in O-RAN spec
    *(hw_comp->dying_gasp_support) = false;
    return NONE;
}

/**
 * Get the last service date of this hardware component
 * hw_comp->last_service_date is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_last_service_date(hw_component_t *hw_comp){
    //how this gets populated is vendor specific
    return UNIMPLEMENTED;
}

/**
 * Get the O-RAN compliant name of this hardware component
 * hw_comp->o_ran_name is filled by this function
 * Returns an error if encountered, NONE otherwise
 */
halmplane_error_t halmplane_get_o_ran_name(hw_component_t *hw_comp){
    hw_comp->o_ran_name = kOranName;
    return NONE;
}
