#!/usr/bin/env lua

-- Copyright (c) Meta Platforms, Inc. and affiliates.
--
-- This source code is licensed under the MIT license found in the
-- LICENSE file in the root directory of this source tree.

local climp = assert(loadfile("/usr/share/lua/5.1/climp.lua"))

local lu = require "luaunit"
local ffi = require "ffi"

TestMain = {}
TestInfo = setmetatable({}, {__index = TestMain})
TestExternalio = setmetatable({}, {__index = TestMain})
TestFan = setmetatable({}, {__index = TestMain})
TestHw = setmetatable({}, {__index = TestMain})

function TestMain:setUp()
  -- Mock HAL functions
  -- Store invoked functions and arguments in "invokedFns"
  self.invokedFns = {}
  self.parser, self.Climp, self.Climp_Handler = climp()
  -- mock function calls
  self.mockHal = setmetatable({}, {
    __index = function(t, k)
      self.invokedFns[k] = true
      return function()
        return ffi.C.NONE
      end
    end
  })
  self.Climp_Handler.halFunc = self.mockHal

end

--- Basic functionality checks.
function TestMain:test_BasicFunctionality()
  lu.assertStrContains(self.parser:get_usage(), "Usage:")
end

--- Test "climp externalio get" command.
function TestExternalio:test_externalioGet()
  lu.assertIsFunction(self.Climp_Handler.externalioGet)
  -- check errors
  lu.assertFalse(self.parser:pparse({"externalio", "get", "output", "heartbeat", "extra-arg"}))
  lu.assertFalse(self.parser:pparse({"externalio", "get"}))

  -- test reading valid gpio should succeed
  lu.assertTrue(self.parser:pparse({"externalio", "get", "output", "heartbeat"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_io_value)
end

--- Test "climp externalio set" command.
function TestExternalio:test_externalioSet()
  lu.assertIsFunction(self.Climp_Handler.externalioSet)
  lu.assertFalse(self.parser:pparse({"externalio", "set"}))
  lu.assertFalse(self.parser:pparse({"externalio", "set", "heartbeat", "string"}))

  -- test setting valid gpio should succeed
  lu.assertTrue(self.parser:pparse({"externalio", "set", "heartbeat",  "0"}))
  lu.assertNotNil(self.invokedFns.halmplane_set_io_value)

end

--- Test "climp fan" commands.
function TestFan:test_fanName()
  -- check function for the command exists
  lu.assertIsFunction(self.Climp_Handler.fanName)
  -- -- check all commands are valid
  lu.assertTrue(self.parser:pparse({"fan", "name"}))
  -- make sure correct function has been called by climp
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_name)
end

function TestFan:test_fanLocation()
  lu.assertIsFunction(self.Climp_Handler.fanLocation)
  lu.assertTrue(self.parser:pparse({"fan", "location"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_location)
end

function TestFan:test_fanIsOperating()
  lu.assertIsFunction(self.Climp_Handler.fanIsOperating)
  lu.assertTrue(self.parser:pparse({"fan", "is_operating"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_present_and_operating)
end

function TestFan:test_fanVendorCode()
  lu.assertIsFunction(self.Climp_Handler.fanVendorCode)
  lu.assertTrue(self.parser:pparse({"fan", "vendor_code"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_vendor_code)
end

function TestFan:test_fanTargetSpeed()
  lu.assertIsFunction(self.Climp_Handler.fanTargetSpeed)
  lu.assertTrue(self.parser:pparse({"fan", "target_speed"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_target_speed)
end

function TestFan:test_fanSpeed()
  lu.assertIsFunction(self.Climp_Handler.fanSpeed)
  lu.assertTrue(self.parser:pparse({"fan", "speed"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_fan_speed)
end

-- Test `climp hw` commands
function TestHw:test_hwEnergySavingState()
  lu.assertIsFunction(self.Climp_Handler.hwEnergySavingState)
  lu.assertTrue(self.parser:pparse({"hw", "energy_saving", "state"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_energysaving_state)
end

function TestHw:test_hwEnergySavingEnabled()
  lu.assertIsFunction(self.Climp_Handler.hwEnergySavingEnabled)
  lu.assertTrue(self.parser:pparse({"hw", "energy_saving", "check_enabled"}))
  lu.assertNotNil(self.invokedFns.halmplane_is_energy_saving_enabled)
end

function TestHw:test_hwLabelContent()
  lu.assertIsFunction(self.Climp_Handler.hwLabelContent)
  lu.assertTrue(self.parser:pparse({"hw", "label_content"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_label_content)
end

function TestHw:test_hwAvailabilityType()
  lu.assertIsFunction(self.Climp_Handler.hwAvailabilityType)
  lu.assertTrue(self.parser:pparse({"hw", "availability_type"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_availability_type)
end

function TestHw:test_hwProductCode()
  lu.assertIsFunction(self.Climp_Handler.hwProductCode)
  lu.assertTrue(self.parser:pparse({"hw", "product_code"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_product_code)
end

function TestHw:test_hwDyingGaspSupport()
  lu.assertIsFunction(self.Climp_Handler.hwDyingGaspSupport)
  lu.assertTrue(self.parser:pparse({"hw", "dying_gasp_support"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_dying_gasp_support)
end

function TestHw:test_hwServiceDate()
  lu.assertIsFunction(self.Climp_Handler.hwServiceDate)
  lu.assertTrue(self.parser:pparse({"hw", "service_date"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_last_service_date)
end

function TestHw:test_hwOranName()
  lu.assertIsFunction(self.Climp_Handler.hwOranName)
  lu.assertTrue(self.parser:pparse({"hw", "name"}))
  lu.assertNotNil(self.invokedFns.halmplane_get_o_ran_name)
end



-- Test "climp" command errors.
function TestInfo:test_Error()
  lu.assertFalse(self.parser:pparse({"info"}))
  lu.assertFalse(self.parser:pparse({"info", "test"}))
end

os.exit(lu.LuaUnit.run("-v"))
