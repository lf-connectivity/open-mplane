#!/usr/bin/env lua

-- Copyright (c) Meta Platforms, Inc. and affiliates.
--
-- This source code is licensed under the MIT license found in the
-- LICENSE file in the root directory of this source tree.

--- M-Plane command-line interface.
-- @script climp

local argparse = require "argparse"
local ffi = require "ffi"
local logger = require "mplane.logger"
local halFunc = require "mplane.hal"

-- Logs the default message for each error type
local function logErrorWithContext(command, error)
    if error == ffi.C.UNIMPLEMENTED then
        logger.error("`%s` is unimplemented on this device.", command)
    elseif error == ffi.C.UNAVAILABLE then
        logger.error("`%s` is unavaliable on this device.", command)
    elseif error == ffi.C.FILE_OPEN_ERROR then
        logger.error("`%s` failed while trying to open a file.", command)
    elseif error == ffi.C.FILE_READ_ERROR then
        logger.error("`%s` failed while trying to read from a file.", command)
    elseif error == ffi.C.FILE_WRITE_ERROR then
        logger.error("`%s` failed while trying to write to a file.", command)
    elseif error == ffi.C.INVALID_ARG then
        logger.error("`%s` received an invalid argument.", command)
    elseif error == ffi.C.DEVICE_ERROR then
        logger.error("`%s` failed due to a device error.", command)
    end
end

--- Climp class
local Climp = {}
Climp.__index = Climp

--- Constructor for Climp
function Climp.new(args)
    local self = setmetatable({}, Climp)
    return self
end

--- Climp handlers static class
local Climp_Handler = {}
Climp_Handler.__index = Climp_Handler
Climp_Handler.halFunc = halFunc

--- `climp externalio get input` command handler
function Climp_Handler.externalioGet(args, name)
    -- create a new io to get port value
    local io = ffi.new("external_io_t[1]")
    local port_value = ffi.new("bool[1]")
    local port
    if args.type == "input" then
        port = ffi.new("input_t[1]")
        io[0].input = port
        io[0].out_setting = nil
        port[0] = {args.port_name, 0, port_value}
    else
        port = ffi.new("output_setting_t[1]")
        io[0].out_setting = port
        io[0].input = nil
        port[0] = {args.port_name, port_value}
    end

    local status = Climp_Handler.halFunc.halmplane_get_io_value(io)

    if status == ffi.C.INVALID_ARG then
        logger.error("External IO: Invalid argument - %s is not a valid gpio name.", args.port_name)
    elseif status ~= ffi.C.NONE then
        logErrorWithContext("externalio get", status)
    else
        -- no error occured
        logger.info("External IO: %s is set to %s.", args.port_name, (port_value[0] and "1" or "0"))
    end
    return status
end

--- `climp externalio set` command handler
function Climp_Handler.externalioSet(args, name)
    local line_out = ffi.new("bool[1]")
    line_out[0] = args.value > 0

    -- create a new output setting and set that value
    local newSetting = ffi.new("output_setting_t[1]")
    newSetting[0] = {args.port_name, line_out}

    local status = Climp_Handler.halFunc.halmplane_set_io_value(newSetting)

    if status == ffi.C.INVALID_ARG then
        logger.error("External IO: Invalid argument - %s is not a valid gpio name.", args.port_name)
    elseif status ~= ffi.C.NONE then
        logErrorWithContext("externalio set", status)
    else
        logger.info("External IO: Successfully set the port value.")
    end

    return status
end

--- `climp fan name` command handler
function Climp_Handler.fanName(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].name = ""
    local status = Climp_Handler.halFunc.halmplane_get_fan_name(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan name", status)
    else
        logger.info("Fan Name: %s", ffi.string(fanState[0].name))
    end

    return status
end

--- `climp fan is_operating` command handler
function Climp_Handler.fanIsOperating(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].present_and_operating = ffi.new("bool[1]")

    local status = Climp_Handler.halFunc.halmplane_get_fan_present_and_operating(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan is_operating", status)
    else
        logger.info("Fan %s operating", (fanState[0].present_and_operating[0] and "is" or "is not"))
    end

    return status
end

--- `climp fan location` command handler
function Climp_Handler.fanLocation(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].fan_location = ffi.new("uint8_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_fan_location(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan location", status)
    else
        logger.info("Fan Location: %d", fanState[0].fan_location[0])
    end

    return status
end

--- `climp fan vendor_code` command handler
function Climp_Handler.fanVendorCode(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].vendor_code = ffi.new("uint8_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_fan_vendor_code(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan vendor_code", status)
    else
        logger.info("Fan Vendor Code: %d", fanState[0].vendor_code[0])
    end

    return status
end

--- `climp fan speed` command handler
function Climp_Handler.fanSpeed(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].fan_speed = ffi.new("uint8_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_fan_speed(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan speed", status)
    else
        logger.info("Fan Speed: %d%%", fanState[0].fan_speed[0])
    end

    return status
end

--- `climp fan target_speed` command handler
function Climp_Handler.fanTargetSpeed(args, name)
    local fanState = ffi.new("fan_state_t[1]")
    fanState[0].target_speed = ffi.new("uint16_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_fan_target_speed(fanState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("fan target_speed", status)
    else
        logger.info("Fan Target Speed: %drpm", fanState[0].target_speed[0])
    end

    return status
end

--- `climp hw energy_saving state` command handler
function Climp_Handler.hwEnergySavingState(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].energy_saving_state = ffi.new("energy_saving_state_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_energysaving_state(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw energy_saving state", status)
    else
        if hwState[0].energy_saving_state[0] == ffi.C.ENERGY_SAVING_STATE_AWAKE then
            logger.info("Energy Saving State: Awake")
        elseif hwState[0].energy_saving_state[0] == ffi.C.ENERGY_SAVING_STATE_SLEEPING then
            logger.info("Energy Saving State: Sleeping")
        else
            logger.info("Energy Saving State: Unknown")
        end
    end

    return status
end

--- `climp hw energy_saving check_enabled` command handler
function Climp_Handler.hwEnergySavingEnabled(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].energy_saving_enabled = ffi.new("bool[1]")

    local status = Climp_Handler.halFunc.halmplane_is_energy_saving_enabled(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw energy_saving check_enabled", status)
    else
        logger.info("Energy saving mode %s enabled", (hwState[0].energy_saving_enabled[0] and "is" or "is not"))
    end

    return status
end

--- `climp hw availability_type` command handler
function Climp_Handler.hwAvailabilityType(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].availability_type = ffi.new("availability_type_t[1]")

    local status = Climp_Handler.halFunc.halmplane_get_availability_type(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw avail_type", status)
    else
        if hwState[0].availability_type[0] == ffi.C.AVAILABILITY_TYPE_NORMAL then
            logger.info("Availability Type: Normal")
        elseif hwState[0].availability_type[0] == ffi.C.AVAILABILITY_TYPE_DEGRADED then
            logger.info("Availability Type: Degraded")
        elseif hwState[0].availability_type[0] == ffi.C.AVAILABILITY_TYPE_FAULTY then
            logger.info("Availability Type: Faulty")
        else
            logger.info("Availability Type: Unknown")
        end
    end

    return status
end

--- `climp hw label_content` command handler
function Climp_Handler.hwLabelContent(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].label_content = ffi.new("label_content_t[1]")
    hwState[0].label_content.model_name = ffi.new("bool[1]")
    hwState[0].label_content.serial_number = ffi.new("bool[1]")

    local status = Climp_Handler.halFunc.halmplane_get_label_content(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw label_content", status)
    else
        logger.info(
            "Model Name: %s \nSerial Number: %s",
            (hwState[0].label_content.model_name[0] and "Yes" or "No"),
            (hwState[0].label_content.serial_number[0] and "Yes" or "No")
        )
    end

    return status
end

--- `climp hw product_code` command handler
function Climp_Handler.hwProductCode(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].product_code = ""

    local status = Climp_Handler.halFunc.halmplane_get_product_code(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw prod_code", status)
    else
        logger.info("Product Code: %s", ffi.string(hwState[0].product_code))
    end

    return status
end

--- `climp hw dying_gasp_support` command handler
function Climp_Handler.hwDyingGaspSupport(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].dying_gasp_support = ffi.new("bool[1]")

    local status = Climp_Handler.halFunc.halmplane_get_dying_gasp_support(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw dying_gasp_support", status)
    else
        logger.info("Dying Gasp Support %s enabled", hwState[0].dying_gasp_support[0] and "is" or "is not")
    end

    return status
end

--- `climp hw service_date` command handler
function Climp_Handler.hwServiceDate(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].last_service_date = ""

    local status = Climp_Handler.halFunc.halmplane_get_last_service_date(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw service_date", status)
    else
        logger.info("Last Service Time: %s", ffi.string(hwState[0].last_service_date))
    end

    return status
end

--- `climp hw name` command handler
function Climp_Handler.hwOranName(args, name)
    local hwState = ffi.new("hw_component_t[1]")
    hwState[0].o_ran_name = ""

    local status = Climp_Handler.halFunc.halmplane_get_o_ran_name(hwState)

    if status ~= ffi.C.NONE then
        logErrorWithContext("hw name", status)
    else
        logger.info("O-RAN Name: %s", ffi.string(hwState[0].o_ran_name))
    end

    return status
end

--- `climp externalio` subcommand
local function addExternalioCmd(parser)
    local externalioCmd = parser:command("externalio", "Interact with the device's external I/Os")
    -- add the get command
    local externalioGetCmd = externalioCmd:command("get", "Get the value of the specified I/O port")
    externalioGetCmd:action(Climp_Handler.externalioGet)
    externalioGetCmd:argument("type", "I/O type (input or output)")
    externalioGetCmd:argument("port_name", "I/O port name")

    -- add the set command
    local externalioSetCmd = externalioCmd:command("set", "Set the output value of the specified I/O port")
    externalioSetCmd:action(Climp_Handler.externalioSet)
    externalioSetCmd:argument("port_name", "I/O port name")
    externalioSetCmd:argument("value", "Value"):convert(tonumber)
end

--- `climp fan` subcommand
local function addFanCmd(parser)
    local fanCmd = parser:command("fan", "Get information about the device's fan")
    -- add the name command
    local fanNameCmd = fanCmd:command("name", "Get the fan's name")
    fanNameCmd:action(Climp_Handler.fanName)

    -- add the is_operating command
    local fanIsOperatingCmd = fanCmd:command("is_operating", "Check if the fan is present and operating")
    fanIsOperatingCmd:action(Climp_Handler.fanIsOperating)

    -- add the location command
    local fanLocationCmd = fanCmd:command("location", "Get the fan's location")
    fanLocationCmd:action(Climp_Handler.fanLocation)

    -- add the vendor_code command
    local fanVendorCodeCmd = fanCmd:command("vendor_code", "Get the fan's vendor code")
    fanVendorCodeCmd:action(Climp_Handler.fanVendorCode)

    -- add the speed command
    local fanSpeedCmd = fanCmd:command("speed", "Get the fan's speed")
    fanSpeedCmd:action(Climp_Handler.fanSpeed)

    -- add the target_speed command
    local fanTargetSpeedCmd = fanCmd:command("target_speed", "Get the fan's target speed")
    fanTargetSpeedCmd:action(Climp_Handler.fanTargetSpeed)
end

--- `climp hw` subcommand
local function addHwCmd(parser)
    local hwCmd = parser:command("hw", "Get information about the device")
    -- add the energy_saving command
    local hwEnergySavingCmd = hwCmd:command("energy_saving", "Get energy saving details of this device")
    local hwEnergySavingStateCmd = hwEnergySavingCmd:command("state", "Get the energy saving state")
    hwEnergySavingStateCmd:action(Climp_Handler.hwEnergySavingState)
    local hwEnergySavingEnabledCmd =
        hwEnergySavingCmd:command("check_enabled", "Check if energy saving mode is enabled on the device")
    hwEnergySavingEnabledCmd:action(Climp_Handler.hwEnergySavingEnabled)

    -- add the availability_type command
    local hwAvailabilityTypeCmd = hwCmd:command("availability_type", "Get availability type of this device")
    hwAvailabilityTypeCmd:action(Climp_Handler.hwAvailabilityType)

    -- add the label_content command
    local hwLabelContentCmd = hwCmd:command("label_content", "Check if model name or serial no. is on the label")
    hwLabelContentCmd:action(Climp_Handler.hwLabelContent)

    -- add the product_code command
    local hwProductCodeCmd = hwCmd:command("product_code", "Get the product code of this device")
    hwProductCodeCmd:action(Climp_Handler.hwProductCode)

    -- add the dying_gasp_support command
    local hwDyingGaspSupportCmd =
        hwCmd:command("dying_gasp_support", "Check if the device has dying gasp support enabled")
    hwDyingGaspSupportCmd:action(Climp_Handler.hwDyingGaspSupport)

    -- add the service_date command
    local hwServiceDateCmd = hwCmd:command("service_date", "Get the date the device was last serviced")
    hwServiceDateCmd:action(Climp_Handler.hwServiceDate)

    -- add the name command
    local hwOranNameCmd = hwCmd:command("name", "Get the device's O-RAN name")
    hwOranNameCmd:action(Climp_Handler.hwOranName)
end

local function createParser()
    local parser = argparse("climp", "M-Plane Command Line Interface")

    -- Add subcommands
    addExternalioCmd(parser)
    addFanCmd(parser)
    addHwCmd(parser)

    return parser
end

local parser = createParser()

-- Check if being run as main function
if debug.getinfo(4) == nil then
    parser:parse()
else
    return parser, Climp, Climp_Handler
end
