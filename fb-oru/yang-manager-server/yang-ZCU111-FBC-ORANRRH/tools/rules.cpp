//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfAcm::addSudoRules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='sudo-rules']/name"] = "sudo-rules" ;
	dataCfg["rule-list[name='sudo-rules']/group"] = "sudo" ;

//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/name"] = "sudo-iana-hardware" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/module-name"] = "iana-hardware" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-hardware']/comment"] = "sudo iana-hardware RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-if-type']/name"] = "sudo-iana-if-type" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-if-type']/module-name"] = "iana-if-type" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-if-type']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-if-type']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-iana-if-type']/comment"] = "sudo iana-if-type R--" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-permit-write']/name"] = "sudo-ietf-dhcpv6-types-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-permit-write']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-permit-write']/comment"] = "sudo ietf-dhcpv6-types RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-deny-exec']/name"] = "sudo-ietf-dhcpv6-types-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-deny-exec']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-dhcpv6-types-deny-exec']/comment"] = "sudo ietf-dhcpv6-types RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/name"] = "sudo-ietf-hardware" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/module-name"] = "ietf-hardware" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-hardware']/comment"] = "sudo ietf-hardware RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-inet-types']/name"] = "sudo-ietf-inet-types" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-inet-types']/module-name"] = "ietf-inet-types" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-inet-types']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-inet-types']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-inet-types']/comment"] = "sudo ietf-inet-types R--" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/name"] = "sudo-ietf-interfaces-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-permit-write']/comment"] = "sudo ietf-interfaces RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/name"] = "sudo-ietf-interfaces-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-interfaces-deny-exec']/comment"] = "sudo ietf-interfaces RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/name"] = "sudo-ietf-ip-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-permit-write']/comment"] = "sudo ietf-ip RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/name"] = "sudo-ietf-ip-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-ip-deny-exec']/comment"] = "sudo ietf-ip RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm']/name"] = "sudo-ietf-netconf-acm" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm']/module-name"] = "ietf-netconf-acm" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-acm']/comment"] = "sudo ietf-netconf-acm RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-monitoring']/name"] = "sudo-ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-monitoring']/module-name"] = "ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-monitoring']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-monitoring']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-netconf-monitoring']/comment"] = "sudo ietf-netconf-monitoring RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-yang-library']/name"] = "sudo-ietf-yang-library" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-yang-library']/module-name"] = "ietf-yang-library" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-yang-library']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-yang-library']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-ietf-yang-library']/comment"] = "sudo ietf-yang-library RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/name"] = "sudo-o-ran-ald-port" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ald-port']/comment"] = "sudo o-ran-ald-port RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/name"] = "sudo-o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-antenna-calibration']/comment"] = "sudo o-ran-antenna-calibration RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-beamforming']/name"] = "sudo-o-ran-beamforming" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-beamforming']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-beamforming']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-beamforming']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-beamforming']/comment"] = "sudo o-ran-beamforming RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/name"] = "sudo-o-ran-delay-management-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-permit-write']/comment"] = "sudo o-ran-delay-management RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/name"] = "sudo-o-ran-delay-management-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-delay-management-deny-exec']/comment"] = "sudo o-ran-delay-management RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/name"] = "sudo-o-ran-dhcp" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-dhcp']/comment"] = "sudo o-ran-dhcp R--" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/name"] = "sudo-o-ran-ecpri-delay-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-permit-write']/comment"] = "sudo o-ran-ecpri-delay RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/name"] = "sudo-o-ran-ecpri-delay-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-ecpri-delay-deny-exec']/comment"] = "sudo o-ran-ecpri-delay RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/name"] = "sudo-o-ran-externalio" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-externalio']/comment"] = "sudo o-ran-externalio RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/name"] = "sudo-o-ran-fan" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-fan']/comment"] = "sudo o-ran-fan R--" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/name"] = "sudo-o-ran-interfaces" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-interfaces']/comment"] = "sudo o-ran-interfaces RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/name"] = "sudo-o-ran-laa-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-permit-write']/comment"] = "sudo o-ran-laa RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/name"] = "sudo-o-ran-laa-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-laa-deny-exec']/comment"] = "sudo o-ran-laa RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm']/name"] = "sudo-o-ran-lbm" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-lbm']/comment"] = "sudo o-ran-lbm RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap']/name"] = "sudo-o-ran-module-cap" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-module-cap']/comment"] = "sudo o-ran-module-cap R--" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/name"] = "sudo-o-ran-mplane-int-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-permit-write']/comment"] = "sudo o-ran-mplane-int RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/name"] = "sudo-o-ran-mplane-int-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-mplane-int-deny-exec']/comment"] = "sudo o-ran-mplane-int RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/name"] = "sudo-o-ran-performance-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-performance-management']/comment"] = "sudo o-ran-performance-management RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/name"] = "sudo-o-ran-processing-element-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-permit-write']/comment"] = "sudo o-ran-processing-element RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/name"] = "sudo-o-ran-processing-element-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-processing-element-deny-exec']/comment"] = "sudo o-ran-processing-element RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-software-management']/name"] = "sudo-o-ran-software-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-software-management']/module-name"] = "o-ran-software-management" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-software-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-software-management']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-software-management']/comment"] = "sudo o-ran-software-management RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-permit-write']/name"] = "sudo-o-ran-sync-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-permit-write']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-permit-write']/comment"] = "sudo o-ran-sync RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-deny-exec']/name"] = "sudo-o-ran-sync-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-deny-exec']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-sync-deny-exec']/comment"] = "sudo o-ran-sync RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/name"] = "sudo-o-ran-transceiver-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-permit-write']/comment"] = "sudo o-ran-transceiver RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/name"] = "sudo-o-ran-transceiver-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-transceiver-deny-exec']/comment"] = "sudo o-ran-transceiver RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/name"] = "sudo-o-ran-udp-echo-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-permit-write']/comment"] = "sudo o-ran-udp-echo RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/name"] = "sudo-o-ran-udp-echo-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-udp-echo-deny-exec']/comment"] = "sudo o-ran-udp-echo RW- (2/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/name"] = "sudo-o-ran-uplane-conf" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-uplane-conf']/comment"] = "sudo o-ran-uplane-conf RWX" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-permit-write']/name"] = "sudo-o-ran-usermgmt-permit-write" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-permit-write']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-permit-write']/comment"] = "sudo o-ran-usermgmt RW- (1/2)" ;
	
//	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-deny-exec']/name"] = "sudo-o-ran-usermgmt-deny-exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-deny-exec']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='sudo-rules']/rule[name='sudo-o-ran-usermgmt-deny-exec']/comment"] = "sudo o-ran-usermgmt RW- (2/2)" ;
	
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;
	
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfAcm::addNmsRules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='nms-rules']/name"] = "nms-rules" ;
	dataCfg["rule-list[name='nms-rules']/group"] = "nms" ;

//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/name"] = "nms-iana-hardware" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/module-name"] = "iana-hardware" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-hardware']/comment"] = "nms iana-hardware RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-if-type']/name"] = "nms-iana-if-type" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-if-type']/module-name"] = "iana-if-type" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-if-type']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-if-type']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-iana-if-type']/comment"] = "nms iana-if-type R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-permit-write']/name"] = "nms-ietf-dhcpv6-types-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-permit-write']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-permit-write']/comment"] = "nms ietf-dhcpv6-types RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-deny-exec']/name"] = "nms-ietf-dhcpv6-types-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-deny-exec']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-dhcpv6-types-deny-exec']/comment"] = "nms ietf-dhcpv6-types RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/name"] = "nms-ietf-hardware" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/module-name"] = "ietf-hardware" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-hardware']/comment"] = "nms ietf-hardware RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-inet-types']/name"] = "nms-ietf-inet-types" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-inet-types']/module-name"] = "ietf-inet-types" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-inet-types']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-inet-types']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-inet-types']/comment"] = "nms ietf-inet-types R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/name"] = "nms-ietf-interfaces-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-permit-write']/comment"] = "nms ietf-interfaces RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/name"] = "nms-ietf-interfaces-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-interfaces-deny-exec']/comment"] = "nms ietf-interfaces RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/name"] = "nms-ietf-ip-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-permit-write']/comment"] = "nms ietf-ip RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/name"] = "nms-ietf-ip-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-ip-deny-exec']/comment"] = "nms ietf-ip RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/name"] = "nms-ietf-netconf-acm" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/module-name"] = "ietf-netconf-acm" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-acm']/comment"] = "nms ietf-netconf-acm R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-monitoring']/name"] = "nms-ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-monitoring']/module-name"] = "ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-monitoring']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-monitoring']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-netconf-monitoring']/comment"] = "nms ietf-netconf-monitoring RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-yang-library']/name"] = "nms-ietf-yang-library" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-yang-library']/module-name"] = "ietf-yang-library" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-yang-library']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-yang-library']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-ietf-yang-library']/comment"] = "nms ietf-yang-library RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/name"] = "nms-o-ran-ald-deny-read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-read']/comment"] = "nms o-ran-ald --- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/name"] = "nms-o-ran-ald-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-deny-exec']/comment"] = "nms o-ran-ald --- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/name"] = "nms-o-ran-ald-port" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ald-port']/comment"] = "nms o-ran-ald-port RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/name"] = "nms-o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-antenna-calibration']/comment"] = "nms o-ran-antenna-calibration R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-beamforming']/name"] = "nms-o-ran-beamforming" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-beamforming']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-beamforming']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-beamforming']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-beamforming']/comment"] = "nms o-ran-beamforming RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/name"] = "nms-o-ran-delay-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-delay-management']/comment"] = "nms o-ran-delay-management R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/name"] = "nms-o-ran-dhcp" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-dhcp']/comment"] = "nms o-ran-dhcp R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-permit-write']/name"] = "nms-o-ran-ecpri-delay-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-permit-write']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-permit-write']/comment"] = "nms o-ran-ecpri-delay RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-deny-exec']/name"] = "nms-o-ran-ecpri-delay-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-deny-exec']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-ecpri-delay-deny-exec']/comment"] = "nms o-ran-ecpri-delay RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/name"] = "nms-o-ran-externalio" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-externalio']/comment"] = "nms o-ran-externalio RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/name"] = "nms-o-ran-fan" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-fan']/comment"] = "nms o-ran-fan R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/name"] = "nms-o-ran-interfaces" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-interfaces']/comment"] = "nms o-ran-interfaces RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/name"] = "nms-o-ran-laa-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-permit-write']/comment"] = "nms o-ran-laa RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/name"] = "nms-o-ran-laa-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-deny-exec']/comment"] = "nms o-ran-laa RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/name"] = "nms-o-ran-laa-operations-deny-read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-read']/comment"] = "nms o-ran-laa-operations --- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/name"] = "nms-o-ran-laa-operations-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-laa-operations-deny-exec']/comment"] = "nms o-ran-laa-operations --- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/name"] = "nms-o-ran-lbm-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-permit-write']/comment"] = "nms o-ran-lbm RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/name"] = "nms-o-ran-lbm-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-lbm-deny-exec']/comment"] = "nms o-ran-lbm RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/name"] = "nms-o-ran-module-cap" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-module-cap']/comment"] = "nms o-ran-module-cap R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/name"] = "nms-o-ran-mplane-int-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-permit-write']/comment"] = "nms o-ran-mplane-int RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/name"] = "nms-o-ran-mplane-int-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-mplane-int-deny-exec']/comment"] = "nms o-ran-mplane-int RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations']/name"] = "nms-o-ran-operations" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations']/module-name"] = "o-ran-operations" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-operations']/comment"] = "nms o-ran-operations R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/name"] = "nms-o-ran-performance-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-performance-management']/comment"] = "nms o-ran-performance-management RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/name"] = "nms-o-ran-processing-element-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-permit-write']/comment"] = "nms o-ran-processing-element RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/name"] = "nms-o-ran-processing-element-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-processing-element-deny-exec']/comment"] = "nms o-ran-processing-element RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-software-management']/name"] = "nms-o-ran-software-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-software-management']/module-name"] = "o-ran-software-management" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-software-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-software-management']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-software-management']/comment"] = "nms o-ran-software-management RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/name"] = "nms-o-ran-supervision-deny-read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-read']/comment"] = "nms o-ran-supervision --- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/name"] = "nms-o-ran-supervision-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-supervision-deny-exec']/comment"] = "nms o-ran-supervision --- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-permit-write']/name"] = "nms-o-ran-sync-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-permit-write']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-permit-write']/comment"] = "nms o-ran-sync RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-deny-exec']/name"] = "nms-o-ran-sync-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-deny-exec']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-sync-deny-exec']/comment"] = "nms o-ran-sync RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/name"] = "nms-o-ran-transceiver-permit-write" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-permit-write']/comment"] = "nms o-ran-transceiver RW- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/name"] = "nms-o-ran-transceiver-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-transceiver-deny-exec']/comment"] = "nms o-ran-transceiver RW- (2/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/name"] = "nms-o-ran-udp-echo" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-udp-echo']/comment"] = "nms o-ran-udp-echo R--" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/name"] = "nms-o-ran-uplane-conf" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/action"] = "permit" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-uplane-conf']/comment"] = "nms o-ran-uplane-conf RWX" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/name"] = "nms-o-ran-usermgmt-deny-read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-read']/comment"] = "nms o-ran-usermgmt --- (1/2)" ;
	
//	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/name"] = "nms-o-ran-usermgmt-deny-exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='nms-rules']/rule[name='nms-o-ran-usermgmt-deny-exec']/comment"] = "nms o-ran-usermgmt --- (2/2)" ;
	
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;
	
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfAcm::addFmpmRules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='fm-pm-rules']/name"] = "fm-pm-rules" ;
	dataCfg["rule-list[name='fm-pm-rules']/group"] = "fm-pm" ;

//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-iana-if-type']/name"] = "fm-pm-iana-if-type" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-iana-if-type']/module-name"] = "iana-if-type" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-iana-if-type']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-iana-if-type']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-iana-if-type']/comment"] = "fm-pm iana-if-type R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-read']/name"] = "fm-pm-ietf-dhcpv6-types-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-read']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-read']/comment"] = "fm-pm ietf-dhcpv6-types --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-exec']/name"] = "fm-pm-ietf-dhcpv6-types-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-exec']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-dhcpv6-types-deny-exec']/comment"] = "fm-pm ietf-dhcpv6-types --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-inet-types']/name"] = "fm-pm-ietf-inet-types" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-inet-types']/module-name"] = "ietf-inet-types" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-inet-types']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-inet-types']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-inet-types']/comment"] = "fm-pm ietf-inet-types R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/name"] = "fm-pm-ietf-interfaces" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-interfaces']/comment"] = "fm-pm ietf-interfaces R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/name"] = "fm-pm-ietf-ip" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-ip']/comment"] = "fm-pm ietf-ip R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/name"] = "fm-pm-ietf-netconf-acm" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/module-name"] = "ietf-netconf-acm" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-acm']/comment"] = "fm-pm ietf-netconf-acm R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-monitoring']/name"] = "fm-pm-ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-monitoring']/module-name"] = "ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-monitoring']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-monitoring']/action"] = "permit" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-netconf-monitoring']/comment"] = "fm-pm ietf-netconf-monitoring RWX" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-yang-library']/name"] = "fm-pm-ietf-yang-library" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-yang-library']/module-name"] = "ietf-yang-library" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-yang-library']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-yang-library']/action"] = "permit" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-ietf-yang-library']/comment"] = "fm-pm ietf-yang-library RWX" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/name"] = "fm-pm-o-ran-ald-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-read']/comment"] = "fm-pm o-ran-ald --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/name"] = "fm-pm-o-ran-ald-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-deny-exec']/comment"] = "fm-pm o-ran-ald --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/name"] = "fm-pm-o-ran-ald-port-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-read']/comment"] = "fm-pm o-ran-ald-port --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/name"] = "fm-pm-o-ran-ald-port-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ald-port-deny-exec']/comment"] = "fm-pm o-ran-ald-port --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/name"] = "fm-pm-o-ran-antenna-calibration-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-read']/comment"] = "fm-pm o-ran-antenna-calibration --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/name"] = "fm-pm-o-ran-antenna-calibration-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-antenna-calibration-deny-exec']/comment"] = "fm-pm o-ran-antenna-calibration --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/name"] = "fm-pm-o-ran-beamforming" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-beamforming']/comment"] = "fm-pm o-ran-beamforming R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/name"] = "fm-pm-o-ran-delay-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-delay-management']/comment"] = "fm-pm o-ran-delay-management R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/name"] = "fm-pm-o-ran-dhcp" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-dhcp']/comment"] = "fm-pm o-ran-dhcp R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/name"] = "fm-pm-o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-ecpri-delay']/comment"] = "fm-pm o-ran-ecpri-delay R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/name"] = "fm-pm-o-ran-externalio-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-read']/comment"] = "fm-pm o-ran-externalio --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/name"] = "fm-pm-o-ran-externalio-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-externalio-deny-exec']/comment"] = "fm-pm o-ran-externalio --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/name"] = "fm-pm-o-ran-fan" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-fan']/comment"] = "fm-pm o-ran-fan R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/name"] = "fm-pm-o-ran-hardware-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/module-name"] = "o-ran-hardware" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-read']/comment"] = "fm-pm o-ran-hardware --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/name"] = "fm-pm-o-ran-hardware-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/module-name"] = "o-ran-hardware" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-hardware-deny-exec']/comment"] = "fm-pm o-ran-hardware --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/name"] = "fm-pm-o-ran-interfaces" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-interfaces']/comment"] = "fm-pm o-ran-interfaces R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/name"] = "fm-pm-o-ran-laa-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-read']/comment"] = "fm-pm o-ran-laa --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/name"] = "fm-pm-o-ran-laa-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-deny-exec']/comment"] = "fm-pm o-ran-laa --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/name"] = "fm-pm-o-ran-laa-operations-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-read']/comment"] = "fm-pm o-ran-laa-operations --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/name"] = "fm-pm-o-ran-laa-operations-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-laa-operations-deny-exec']/comment"] = "fm-pm o-ran-laa-operations --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/name"] = "fm-pm-o-ran-lbm" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-lbm']/comment"] = "fm-pm o-ran-lbm R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/name"] = "fm-pm-o-ran-module-cap" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-module-cap']/comment"] = "fm-pm o-ran-module-cap R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/name"] = "fm-pm-o-ran-mplane-int" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-mplane-int']/comment"] = "fm-pm o-ran-mplane-int R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/name"] = "fm-pm-o-ran-operations" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/module-name"] = "o-ran-operations" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-operations']/comment"] = "fm-pm o-ran-operations R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/name"] = "fm-pm-o-ran-performance-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/action"] = "permit" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-performance-management']/comment"] = "fm-pm o-ran-performance-management RWX" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/name"] = "fm-pm-o-ran-processing-element" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-processing-element']/comment"] = "fm-pm o-ran-processing-element R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/name"] = "fm-pm-o-ran-software-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/module-name"] = "o-ran-software-management" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-software-management']/comment"] = "fm-pm o-ran-software-management R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/name"] = "fm-pm-o-ran-supervision-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-read']/comment"] = "fm-pm o-ran-supervision --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/name"] = "fm-pm-o-ran-supervision-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-supervision-deny-exec']/comment"] = "fm-pm o-ran-supervision --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/name"] = "fm-pm-o-ran-sync" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-sync']/comment"] = "fm-pm o-ran-sync R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/name"] = "fm-pm-o-ran-transceiver" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-transceiver']/comment"] = "fm-pm o-ran-transceiver R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/name"] = "fm-pm-o-ran-udp-echo-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-read']/comment"] = "fm-pm o-ran-udp-echo --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/name"] = "fm-pm-o-ran-udp-echo-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-udp-echo-deny-exec']/comment"] = "fm-pm o-ran-udp-echo --- (2/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/name"] = "fm-pm-o-ran-uplane-conf" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-uplane-conf']/comment"] = "fm-pm o-ran-uplane-conf R--" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/name"] = "fm-pm-o-ran-usermgmt-deny-read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-read']/comment"] = "fm-pm o-ran-usermgmt --- (1/2)" ;
	
//	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/name"] = "fm-pm-o-ran-usermgmt-deny-exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='fm-pm-rules']/rule[name='fm-pm-o-ran-usermgmt-deny-exec']/comment"] = "fm-pm o-ran-usermgmt --- (2/2)" ;
	
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;
	
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfAcm::addSwmRules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='swm-rules']/name"] = "swm-rules" ;
	dataCfg["rule-list[name='swm-rules']/group"] = "swm" ;

//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/name"] = "swm-iana-hardware-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/module-name"] = "iana-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-read']/comment"] = "swm iana-hardware --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/name"] = "swm-iana-hardware-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/module-name"] = "iana-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-hardware-deny-exec']/comment"] = "swm iana-hardware --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-if-type']/name"] = "swm-iana-if-type" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-if-type']/module-name"] = "iana-if-type" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-if-type']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-if-type']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-iana-if-type']/comment"] = "swm iana-if-type R--" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-read']/name"] = "swm-ietf-dhcpv6-types-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-read']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-read']/comment"] = "swm ietf-dhcpv6-types --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-exec']/name"] = "swm-ietf-dhcpv6-types-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-exec']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-dhcpv6-types-deny-exec']/comment"] = "swm ietf-dhcpv6-types --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/name"] = "swm-ietf-hardware-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/module-name"] = "ietf-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-read']/comment"] = "swm ietf-hardware --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/name"] = "swm-ietf-hardware-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/module-name"] = "ietf-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-hardware-deny-exec']/comment"] = "swm ietf-hardware --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-inet-types']/name"] = "swm-ietf-inet-types" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-inet-types']/module-name"] = "ietf-inet-types" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-inet-types']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-inet-types']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-inet-types']/comment"] = "swm ietf-inet-types R--" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/name"] = "swm-ietf-interfaces-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-read']/comment"] = "swm ietf-interfaces --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/name"] = "swm-ietf-interfaces-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-interfaces-deny-exec']/comment"] = "swm ietf-interfaces --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/name"] = "swm-ietf-ip-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-read']/comment"] = "swm ietf-ip --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/name"] = "swm-ietf-ip-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-ip-deny-exec']/comment"] = "swm ietf-ip --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/name"] = "swm-ietf-netconf-acm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/module-name"] = "ietf-netconf-acm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-acm']/comment"] = "swm ietf-netconf-acm R--" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-monitoring']/name"] = "swm-ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-monitoring']/module-name"] = "ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-monitoring']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-monitoring']/action"] = "permit" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-netconf-monitoring']/comment"] = "swm ietf-netconf-monitoring RWX" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-yang-library']/name"] = "swm-ietf-yang-library" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-yang-library']/module-name"] = "ietf-yang-library" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-yang-library']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-yang-library']/action"] = "permit" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-ietf-yang-library']/comment"] = "swm ietf-yang-library RWX" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/name"] = "swm-o-ran-ald-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-read']/comment"] = "swm o-ran-ald --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/name"] = "swm-o-ran-ald-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-deny-exec']/comment"] = "swm o-ran-ald --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/name"] = "swm-o-ran-ald-port-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-read']/comment"] = "swm o-ran-ald-port --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/name"] = "swm-o-ran-ald-port-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ald-port-deny-exec']/comment"] = "swm o-ran-ald-port --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/name"] = "swm-o-ran-antenna-calibration-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-read']/comment"] = "swm o-ran-antenna-calibration --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/name"] = "swm-o-ran-antenna-calibration-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-antenna-calibration-deny-exec']/comment"] = "swm o-ran-antenna-calibration --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/name"] = "swm-o-ran-beamforming-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-read']/comment"] = "swm o-ran-beamforming --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/name"] = "swm-o-ran-beamforming-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-beamforming-deny-exec']/comment"] = "swm o-ran-beamforming --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/name"] = "swm-o-ran-delay-management-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-read']/comment"] = "swm o-ran-delay-management --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/name"] = "swm-o-ran-delay-management-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-delay-management-deny-exec']/comment"] = "swm o-ran-delay-management --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/name"] = "swm-o-ran-dhcp-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-read']/comment"] = "swm o-ran-dhcp --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/name"] = "swm-o-ran-dhcp-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-dhcp-deny-exec']/comment"] = "swm o-ran-dhcp --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/name"] = "swm-o-ran-ecpri-delay-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-read']/comment"] = "swm o-ran-ecpri-delay --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/name"] = "swm-o-ran-ecpri-delay-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-ecpri-delay-deny-exec']/comment"] = "swm o-ran-ecpri-delay --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/name"] = "swm-o-ran-externalio-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-read']/comment"] = "swm o-ran-externalio --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/name"] = "swm-o-ran-externalio-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-externalio-deny-exec']/comment"] = "swm o-ran-externalio --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/name"] = "swm-o-ran-fan-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-read']/comment"] = "swm o-ran-fan --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/name"] = "swm-o-ran-fan-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fan-deny-exec']/comment"] = "swm o-ran-fan --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/name"] = "swm-o-ran-file-management-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/module-name"] = "o-ran-file-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-read']/comment"] = "swm o-ran-file-management --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/name"] = "swm-o-ran-file-management-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/module-name"] = "o-ran-file-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-file-management-deny-exec']/comment"] = "swm o-ran-file-management --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/name"] = "swm-o-ran-fm-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/module-name"] = "o-ran-fm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-read']/comment"] = "swm o-ran-fm --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/name"] = "swm-o-ran-fm-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/module-name"] = "o-ran-fm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-fm-deny-exec']/comment"] = "swm o-ran-fm --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/name"] = "swm-o-ran-hardware-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/module-name"] = "o-ran-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-read']/comment"] = "swm o-ran-hardware --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/name"] = "swm-o-ran-hardware-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/module-name"] = "o-ran-hardware" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-hardware-deny-exec']/comment"] = "swm o-ran-hardware --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/name"] = "swm-o-ran-interfaces-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-read']/comment"] = "swm o-ran-interfaces --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/name"] = "swm-o-ran-interfaces-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-interfaces-deny-exec']/comment"] = "swm o-ran-interfaces --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/name"] = "swm-o-ran-laa-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-read']/comment"] = "swm o-ran-laa --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/name"] = "swm-o-ran-laa-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-deny-exec']/comment"] = "swm o-ran-laa --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/name"] = "swm-o-ran-laa-operations-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-read']/comment"] = "swm o-ran-laa-operations --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/name"] = "swm-o-ran-laa-operations-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-laa-operations-deny-exec']/comment"] = "swm o-ran-laa-operations --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/name"] = "swm-o-ran-lbm-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-read']/comment"] = "swm o-ran-lbm --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/name"] = "swm-o-ran-lbm-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-lbm-deny-exec']/comment"] = "swm o-ran-lbm --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/name"] = "swm-o-ran-module-cap-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-read']/comment"] = "swm o-ran-module-cap --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/name"] = "swm-o-ran-module-cap-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-module-cap-deny-exec']/comment"] = "swm o-ran-module-cap --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/name"] = "swm-o-ran-mplane-int-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-read']/comment"] = "swm o-ran-mplane-int --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/name"] = "swm-o-ran-mplane-int-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-mplane-int-deny-exec']/comment"] = "swm o-ran-mplane-int --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/name"] = "swm-o-ran-operations-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/module-name"] = "o-ran-operations" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-read']/comment"] = "swm o-ran-operations --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/name"] = "swm-o-ran-operations-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/module-name"] = "o-ran-operations" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-operations-deny-exec']/comment"] = "swm o-ran-operations --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/name"] = "swm-o-ran-performance-management-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-read']/comment"] = "swm o-ran-performance-management --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/name"] = "swm-o-ran-performance-management-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-performance-management-deny-exec']/comment"] = "swm o-ran-performance-management --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/name"] = "swm-o-ran-processing-element-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-read']/comment"] = "swm o-ran-processing-element --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/name"] = "swm-o-ran-processing-element-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-processing-element-deny-exec']/comment"] = "swm o-ran-processing-element --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-software-management']/name"] = "swm-o-ran-software-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-software-management']/module-name"] = "o-ran-software-management" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-software-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-software-management']/action"] = "permit" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-software-management']/comment"] = "swm o-ran-software-management RWX" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/name"] = "swm-o-ran-supervision-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-read']/comment"] = "swm o-ran-supervision --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/name"] = "swm-o-ran-supervision-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-supervision-deny-exec']/comment"] = "swm o-ran-supervision --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/name"] = "swm-o-ran-sync-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-read']/comment"] = "swm o-ran-sync --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/name"] = "swm-o-ran-sync-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-sync-deny-exec']/comment"] = "swm o-ran-sync --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/name"] = "swm-o-ran-trace-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/module-name"] = "o-ran-trace" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-read']/comment"] = "swm o-ran-trace --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/name"] = "swm-o-ran-trace-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/module-name"] = "o-ran-trace" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-trace-deny-exec']/comment"] = "swm o-ran-trace --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/name"] = "swm-o-ran-transceiver-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-read']/comment"] = "swm o-ran-transceiver --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/name"] = "swm-o-ran-transceiver-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-transceiver-deny-exec']/comment"] = "swm o-ran-transceiver --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/name"] = "swm-o-ran-troubleshooting-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/module-name"] = "o-ran-troubleshooting" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-read']/comment"] = "swm o-ran-troubleshooting --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/name"] = "swm-o-ran-troubleshooting-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/module-name"] = "o-ran-troubleshooting" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-troubleshooting-deny-exec']/comment"] = "swm o-ran-troubleshooting --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/name"] = "swm-o-ran-udp-echo-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-read']/comment"] = "swm o-ran-udp-echo --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/name"] = "swm-o-ran-udp-echo-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-udp-echo-deny-exec']/comment"] = "swm o-ran-udp-echo --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/name"] = "swm-o-ran-uplane-conf-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-read']/comment"] = "swm o-ran-uplane-conf --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/name"] = "swm-o-ran-uplane-conf-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-uplane-conf-deny-exec']/comment"] = "swm o-ran-uplane-conf --- (2/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/name"] = "swm-o-ran-usermgmt-deny-read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/access-operations"] = "read" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-read']/comment"] = "swm o-ran-usermgmt --- (1/2)" ;
	
//	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/name"] = "swm-o-ran-usermgmt-deny-exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/access-operations"] = "exec" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/action"] = "deny" ;
	dataCfg["rule-list[name='swm-rules']/rule[name='swm-o-ran-usermgmt-deny-exec']/comment"] = "swm o-ran-usermgmt --- (2/2)" ;
	
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;
	
	return true ;
}


//-------------------------------------------------------------------------------------------------------------
bool Zcu111FbcOranrrhHandlerIetfNetconfAcm::addRootRules()
{
	std::map<std::string, std::string> dataCfg;

	dataCfg["rule-list[name='root-rules']/name"] = "root-rules" ;
	dataCfg["rule-list[name='root-rules']/group"] = "root" ;

//	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/name"] = "root-iana-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/module-name"] = "iana-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-hardware']/comment"] = "root iana-hardware RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-if-type']/name"] = "root-iana-if-type" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-if-type']/module-name"] = "iana-if-type" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-if-type']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-if-type']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-iana-if-type']/comment"] = "root iana-if-type RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-dhcpv6-types']/name"] = "root-ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-dhcpv6-types']/module-name"] = "ietf-dhcpv6-types" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-dhcpv6-types']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-dhcpv6-types']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-dhcpv6-types']/comment"] = "root ietf-dhcpv6-types RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/name"] = "root-ietf-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/module-name"] = "ietf-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-hardware']/comment"] = "root ietf-hardware RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-inet-types']/name"] = "root-ietf-inet-types" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-inet-types']/module-name"] = "ietf-inet-types" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-inet-types']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-inet-types']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-inet-types']/comment"] = "root ietf-inet-types RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/name"] = "root-ietf-interfaces" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/module-name"] = "ietf-interfaces" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-interfaces']/comment"] = "root ietf-interfaces RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/name"] = "root-ietf-ip" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/module-name"] = "ietf-ip" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-ip']/comment"] = "root ietf-ip RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/name"] = "root-ietf-netconf-acm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/module-name"] = "ietf-netconf-acm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-acm']/comment"] = "root ietf-netconf-acm RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/name"] = "root-ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/module-name"] = "ietf-netconf-monitoring" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-netconf-monitoring']/comment"] = "root ietf-netconf-monitoring RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/name"] = "root-ietf-yang-library" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/module-name"] = "ietf-yang-library" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-ietf-yang-library']/comment"] = "root ietf-yang-library RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/name"] = "root-o-ran-ald" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/module-name"] = "o-ran-ald" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald']/comment"] = "root o-ran-ald RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/name"] = "root-o-ran-ald-port" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/module-name"] = "o-ran-ald-port" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ald-port']/comment"] = "root o-ran-ald-port RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/name"] = "root-o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/module-name"] = "o-ran-antenna-calibration" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-antenna-calibration']/comment"] = "root o-ran-antenna-calibration RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/name"] = "root-o-ran-beamforming" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/module-name"] = "o-ran-beamforming" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-beamforming']/comment"] = "root o-ran-beamforming RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/name"] = "root-o-ran-delay-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/module-name"] = "o-ran-delay-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-delay-management']/comment"] = "root o-ran-delay-management RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/name"] = "root-o-ran-dhcp" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/module-name"] = "o-ran-dhcp" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-dhcp']/comment"] = "root o-ran-dhcp RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/name"] = "root-o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/module-name"] = "o-ran-ecpri-delay" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-ecpri-delay']/comment"] = "root o-ran-ecpri-delay RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/name"] = "root-o-ran-externalio" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/module-name"] = "o-ran-externalio" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-externalio']/comment"] = "root o-ran-externalio RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/name"] = "root-o-ran-fan" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/module-name"] = "o-ran-fan" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fan']/comment"] = "root o-ran-fan RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/name"] = "root-o-ran-file-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/module-name"] = "o-ran-file-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-file-management']/comment"] = "root o-ran-file-management RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/name"] = "root-o-ran-fm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/module-name"] = "o-ran-fm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-fm']/comment"] = "root o-ran-fm RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/name"] = "root-o-ran-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/module-name"] = "o-ran-hardware" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-hardware']/comment"] = "root o-ran-hardware RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/name"] = "root-o-ran-interfaces" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/module-name"] = "o-ran-interfaces" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-interfaces']/comment"] = "root o-ran-interfaces RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/name"] = "root-o-ran-laa" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/module-name"] = "o-ran-laa" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa']/comment"] = "root o-ran-laa RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/name"] = "root-o-ran-laa-operations" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/module-name"] = "o-ran-laa-operations" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-laa-operations']/comment"] = "root o-ran-laa-operations RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/name"] = "root-o-ran-lbm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/module-name"] = "o-ran-lbm" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-lbm']/comment"] = "root o-ran-lbm RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/name"] = "root-o-ran-module-cap" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/module-name"] = "o-ran-module-cap" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-module-cap']/comment"] = "root o-ran-module-cap RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/name"] = "root-o-ran-mplane-int" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/module-name"] = "o-ran-mplane-int" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-mplane-int']/comment"] = "root o-ran-mplane-int RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/name"] = "root-o-ran-operations" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/module-name"] = "o-ran-operations" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-operations']/comment"] = "root o-ran-operations RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/name"] = "root-o-ran-performance-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/module-name"] = "o-ran-performance-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-performance-management']/comment"] = "root o-ran-performance-management RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/name"] = "root-o-ran-processing-element" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/module-name"] = "o-ran-processing-element" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-processing-element']/comment"] = "root o-ran-processing-element RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/name"] = "root-o-ran-software-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/module-name"] = "o-ran-software-management" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-software-management']/comment"] = "root o-ran-software-management RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/name"] = "root-o-ran-supervision" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/module-name"] = "o-ran-supervision" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-supervision']/comment"] = "root o-ran-supervision RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/name"] = "root-o-ran-sync" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/module-name"] = "o-ran-sync" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-sync']/comment"] = "root o-ran-sync RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/name"] = "root-o-ran-trace" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/module-name"] = "o-ran-trace" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-trace']/comment"] = "root o-ran-trace RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/name"] = "root-o-ran-transceiver" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/module-name"] = "o-ran-transceiver" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-transceiver']/comment"] = "root o-ran-transceiver RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/name"] = "root-o-ran-troubleshooting" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/module-name"] = "o-ran-troubleshooting" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-troubleshooting']/comment"] = "root o-ran-troubleshooting RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/name"] = "root-o-ran-udp-echo" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/module-name"] = "o-ran-udp-echo" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-udp-echo']/comment"] = "root o-ran-udp-echo RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/name"] = "root-o-ran-uplane-conf" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/module-name"] = "o-ran-uplane-conf" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-uplane-conf']/comment"] = "root o-ran-uplane-conf RWX" ;
	
//	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/name"] = "root-o-ran-usermgmt" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/module-name"] = "o-ran-usermgmt" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/access-operations"] = "create update delete" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/action"] = "permit" ;
	dataCfg["rule-list[name='root-rules']/rule[name='root-o-ran-usermgmt']/comment"] = "root o-ran-usermgmt RWX" ;
	
	if (createListEntry(path("nacm"), dataCfg) != YangResult_E::OK)
		return false ;
	
	return true ;
}


