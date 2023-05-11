# mplane_server Implementation
The software architecture of `mplane-server` follows that of the `fb-oru`
implementation. It is useful to reference the original documentation for the
`fb-oru` software, which can be built with Doxygen following the instructions in
the top-level `fb-oru` directory.

The bulk of the M-Plane-specific functionality and features are found in
`yang-manager-server` while other modules contain supporting libraries and
services for the application.

To add support for additional YANG models the steps are generally to:
- Create a handler class for the YANG model, which is derived from
  `YangHandlerSysrepo` and placed in
  "mplane_server/yang-manager-server/yang-model-handlers/".
- Register the handler in "OranYangHandlerMgr.cpp".
- Add an element in "YangConfig.xml" for the YANG model (it can be empty).

The handler class for the YANG model needs to do the following:
- Handle initial/startup data inside the `initialise` function.
  Operational/state data and configuration data can both be read from
  "YangConfig.xml". They are handled a bit differently: State data is added into
  an `ILeafContainer` object and the `getItemsSubscribe` function registers it
  as the entity which returns state data values when a client does a `<get>`.
  Configuration data can be organized and then written into sysrepo
  configuration datastore. If appropriate, you can also read whatever config
  data is already in from the datastore and store/handle them as you wish.
- Make appropriate HAL calls. Likely to be done as part during the `initialise`
  function and/or `valueChange`. The `changeSubscribe` function does some
  plumbing so that when any configuration data gets changed, `valueChange` will
  be called with the old value and new value. (The xpath parameter is always
  empty for some reason, the actual xpath to be used for various logic can be
  found in `YangParam->name()`.)

When creating the handler class, the corresponding files in
"fb-oru/yang-manager-server/yang-ZC111-FBC-ORANRRH" can be useful as a reference
for what types of state or logic are needed in the handler class code,
especially if the behavior is complex. Some YANG models, like for processing
elements, are fairly simple and the handler class's job is primarily to handle
some startup values, and make straightforward calls to the HAL.
