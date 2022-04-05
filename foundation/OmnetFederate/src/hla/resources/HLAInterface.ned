//
// HLAInterface.ned
//

package OmnetFederate;

simple HLAInterface {

    parameters:
        string federation_json_file_name;
        string dynamic_messaging_classes_json_file_name;
        string federate_host_config_json_file_name;
        string federate_sequence_to_messaging_info_json_file_name;
        string federation_name;
        string federate_name = default( "OmnetFederate" );
        double federate_step_size = default( 0.1 );
        double federate_lookahead = default( 0.01 );

    gates:
        input	hlaOut @directIn;
}
