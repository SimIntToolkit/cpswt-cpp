
// This code has been generated by the C2W code generator.
// Do not edit manually!

package TESDemoIntegrationModel;

import java.util.HashSet;
import java.util.Set;

import hla.rti.*;

import c2w.hla.*;

/**
* The StartDataInjectionAttack class implements the StartDataInjectionAttack interaction in the
* TESDemoIntegrationModel simulation.
*/
public class StartDataInjectionAttack extends AttacksNotYetImplemented {

	/**
	* Default constructor -- creates an instance of the StartDataInjectionAttack interaction
	* class with default parameter values.
	*/
	public StartDataInjectionAttack() { }

	
	
	private static int _packet_handle;
	private static int _toNode_handle;
	private static int _fromNode_handle;
	
	
	/**
	* Returns the handle (RTI assigned) of the "packet" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "packet" parameter
	*/
	public static int get_packet_handle() { return _packet_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "toNode" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "toNode" parameter
	*/
	public static int get_toNode_handle() { return _toNode_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "fromNode" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "fromNode" parameter
	*/
	public static int get_fromNode_handle() { return _fromNode_handle; }
	
	
	
	private static boolean _isInitialized = false;

	private static int _handle;

	/**
	* Returns the handle (RTI assigned) of the StartDataInjectionAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the handle of the class pertaining to the reference,\
	* rather than the handle of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassHandle()}.
	*/
	public static int get_handle() { return _handle; }

	/**
	* Returns the fully-qualified (dot-delimited) name of the StartDataInjectionAttack
	* interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the name of the class pertaining to the reference,\
	* rather than the name of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassName()}.
	*/
	public static String get_class_name() { return "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack"; }

	/**
	* Returns the simple name (the last name in the dot-delimited fully-qualified
	* class name) of the StartDataInjectionAttack interaction class.
	*/
	public static String get_simple_class_name() { return "StartDataInjectionAttack"; }

	private static Set< String > _datamemberNames = new HashSet< String >();
	private static Set< String > _allDatamemberNames = new HashSet< String >();

	/**
	* Returns a set containing the names of all of the non-hidden parameters in the
	* StartDataInjectionAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return a set of parameter names pertaining to the reference,\
	* rather than the parameter names of the class for the instance referred to by
	* the reference.  For the polymorphic version of this method, use
	* {@link #getParameterNames()}.
	*/
	public static Set< String > get_parameter_names() {
		return new HashSet< String >( _datamemberNames );
	}


	/**
	* Returns a set containing the names of all of the parameters in the
	* StartDataInjectionAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return a set of parameter names pertaining to the reference,\
	* rather than the parameter names of the class for the instance referred to by
	* the reference.  For the polymorphic version of this method, use
	* {@link #getParameterNames()}.
	*/
	public static Set< String > get_all_parameter_names() {
		return new HashSet< String >( _allDatamemberNames );
	}


	

	static {
		_classNameSet.add( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack" );
		_classNameClassMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack", StartDataInjectionAttack.class );
		
		_datamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack", _datamemberNames );
		_allDatamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack", _allDatamemberNames );

		
		
		
		
		
		_datamemberNames.add( "packet" );
		_datamemberNames.add( "toNode" );
		_datamemberNames.add( "fromNode" );
		
		
		
		
		_allDatamemberNames.add( "sourceFed" );
		_allDatamemberNames.add( "uniqueCommandID" );
		_allDatamemberNames.add( "originFed" );
		_allDatamemberNames.add( "packet" );
		_allDatamemberNames.add( "toNode" );
		_allDatamemberNames.add( "fromNode" );
		_allDatamemberNames.add( "federateFilter" );
		_allDatamemberNames.add( "actualLogicalGenerationTime" );
		
		
		_datamemberTypeMap.put( "packet", "String" );
		_datamemberTypeMap.put( "toNode", "String" );
		_datamemberTypeMap.put( "fromNode", "String" );
	
	

	}


	private static String initErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack:  could not initialize:  ";
	protected static void init( RTIambassador rti ) {
		if ( _isInitialized ) return;
		_isInitialized = true;
		
		AttacksNotYetImplemented.init( rti );
		
		boolean isNotInitialized = true;
		while( isNotInitialized ) {
			try {
				_handle = rti.getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack" );
				isNotInitialized = false;
			} catch ( FederateNotExecutionMember f ) {
				System.err.println( initErrorMessage + "Federate Not Execution Member" );
				f.printStackTrace();
				return;				
			} catch ( NameNotFound n ) {
				System.err.println( initErrorMessage + "Name Not Found" );
				n.printStackTrace();
				return;				
			} catch ( Exception e ) {
				e.printStackTrace();
				try { Thread.sleep( 50 ); } catch( Exception e1 ) { }					
			}
		}

		_classNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack", get_handle() );
		_classHandleNameMap.put( get_handle(), "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack" );
		_classHandleSimpleNameMap.put( get_handle(), "StartDataInjectionAttack" );

		
		isNotInitialized = true;
		while( isNotInitialized ) {
			try {
							
				_packet_handle = rti.getParameterHandle( "packet", get_handle() );			
				_toNode_handle = rti.getParameterHandle( "toNode", get_handle() );			
				_fromNode_handle = rti.getParameterHandle( "fromNode", get_handle() );
				isNotInitialized = false;
			} catch ( FederateNotExecutionMember f ) {
				System.err.println( initErrorMessage + "Federate Not Execution Member" );
				f.printStackTrace();
				return;				
			} catch ( InteractionClassNotDefined i ) {
				System.err.println( initErrorMessage + "Interaction Class Not Defined" );
				i.printStackTrace();
				return;				
			} catch ( NameNotFound n ) {
				System.err.println( initErrorMessage + "Name Not Found" );
				n.printStackTrace();
				return;				
			} catch ( Exception e ) {
				e.printStackTrace();
				try { Thread.sleep( 50 ); } catch( Exception e1 ) { }					
			}
		}
			
			
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack,packet", get_packet_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack,toNode", get_toNode_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack,fromNode", get_fromNode_handle() );
			
			
		_datamemberHandleNameMap.put( get_packet_handle(), "packet" );
		_datamemberHandleNameMap.put( get_toNode_handle(), "toNode" );
		_datamemberHandleNameMap.put( get_fromNode_handle(), "fromNode" );
		
	}


	private static boolean _isPublished = false;
	private static String publishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack:  could not publish:  ";

	/**
	* Publishes the StartDataInjectionAttack interaction class for a federate.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public static void publish( RTIambassador rti ) {
		if ( _isPublished ) return;
		
		init( rti );

	

		synchronized( rti ) {
			boolean isNotPublished = true;
			while( isNotPublished ) {
				try {
					rti.publishInteractionClass( get_handle() );
					isNotPublished = false;
				} catch ( FederateNotExecutionMember f ) {
					System.err.println( publishErrorMessage + "Federate Not Execution Member" );
					f.printStackTrace();
					return;
				} catch ( InteractionClassNotDefined i ) {
					System.err.println( publishErrorMessage + "Interaction Class Not Defined" );
					i.printStackTrace();
					return;
				} catch ( Exception e ) {
					e.printStackTrace();
					try { Thread.sleep( 50 ); } catch( Exception e1 ) { }
				}
			}
		}
		
		_isPublished = true;
	}

	private static String unpublishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack:  could not unpublish:  ";
	/**
	* Unpublishes the StartDataInjectionAttack interaction class for a federate.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public static void unpublish( RTIambassador rti ) {
		if ( !_isPublished ) return;
		
		init( rti );
		synchronized( rti ) {
			boolean isNotUnpublished = true;
			while( isNotUnpublished ) {
				try {
					rti.unpublishInteractionClass( get_handle() );
					isNotUnpublished = false;
				} catch ( FederateNotExecutionMember f ) {
					System.err.println( unpublishErrorMessage + "Federate Not Execution Member" );
					f.printStackTrace();
					return;
				} catch ( InteractionClassNotDefined i ) {
					System.err.println( unpublishErrorMessage + "Interaction Class Not Defined" );
					i.printStackTrace();
					return;
				} catch ( InteractionClassNotPublished i ) {
					System.err.println( unpublishErrorMessage + "Interaction Class Not Published" );
					i.printStackTrace();
					return;
				} catch ( Exception e ) {
					e.printStackTrace();
					try { Thread.sleep( 50 ); } catch( Exception e1 ) { }
				}
			}
		}
		
		_isPublished = false;
	}

	private static boolean _isSubscribed = false;
	private static String subscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack:  could not subscribe:  ";
	/**
	* Subscribes a federate to the StartDataInjectionAttack interaction class.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public static void subscribe( RTIambassador rti ) {
		if ( _isSubscribed ) return;
		
		init( rti );
	
		
		synchronized( rti ) {
			boolean isNotSubscribed = true;
			while( isNotSubscribed ) {
				try {
					rti.subscribeInteractionClass( get_handle() );
					isNotSubscribed = false;
				} catch ( FederateNotExecutionMember f ) {
					System.err.println( subscribeErrorMessage + "Federate Not Execution Member" );
					f.printStackTrace();
					return;
				} catch ( InteractionClassNotDefined i ) {
					System.err.println( subscribeErrorMessage + "Interaction Class Not Defined" );
					i.printStackTrace();
					return;
				} catch ( Exception e ) {
					e.printStackTrace();
					try { Thread.sleep( 50 ); } catch( Exception e1 ) { }
				}
			}
		}
		
		_isSubscribed = true;
	}

	private static String unsubscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.AttacksNotYetImplemented.StartDataInjectionAttack:  could not unsubscribe:  ";
	/**
	* Unsubscribes a federate from the StartDataInjectionAttack interaction class.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public static void unsubscribe( RTIambassador rti ) {
		if ( !_isSubscribed ) return;

		init( rti );
		synchronized( rti ) {
			boolean isNotUnsubscribed = true;
			while( isNotUnsubscribed ) {
				try {
					rti.unsubscribeInteractionClass( get_handle() );
					isNotUnsubscribed = false;
				} catch ( FederateNotExecutionMember f ) {
					System.err.println( unsubscribeErrorMessage + "Federate Not Execution Member" );
					f.printStackTrace();
					return;
				} catch ( InteractionClassNotDefined i ) {
					System.err.println( unsubscribeErrorMessage + "Interaction Class Not Defined" );
					i.printStackTrace();
					return;
				} catch ( InteractionClassNotSubscribed i ) {
					System.err.println( unsubscribeErrorMessage + "Interaction Class Not Subscribed" );
					i.printStackTrace();
					return;
				} catch ( Exception e ) {
					e.printStackTrace();
					try { Thread.sleep( 50 ); } catch( Exception e1 ) { }
				}
			}
		}
		
		_isSubscribed = false;
	}

	/**
	* Return true if "handle" is equal to the handle (RTI assigned) of this class
	* (that is, the StartDataInjectionAttack interaction class).
	*
	* @param handle handle to compare to the value of the handle (RTI assigned) of
	* this class (the StartDataInjectionAttack interaction class).
	* @return "true" if "handle" matches the value of the handle of this class
	* (that is, the StartDataInjectionAttack interaction class).
	*/
	public static boolean match( int handle ) { return handle == get_handle(); }

	/**
	* Returns the handle (RTI assigned) of this instance's interaction class .
	* 
	* @return the handle (RTI assigned) if this instance's interaction class
	*/
	public int getClassHandle() { return get_handle(); }

	/**
	* Returns the fully-qualified (dot-delimited) name of this instance's interaction class.
	* 
	* @return the fully-qualified (dot-delimited) name of this instance's interaction class
	*/
	public String getClassName() { return get_class_name(); }

	/**
	* Returns the simple name (last name in its fully-qualified dot-delimited name)
	* of this instance's interaction class.
	* 
	* @return the simple name of this instance's interaction class 
	*/
	public String getSimpleClassName() { return get_simple_class_name(); }

	/**
	* Returns a set containing the names of all of the non-hiddenparameters of an
	* interaction class instance.
	*
	* @return set containing the names of all of the parameters of an
	* interaction class instance
	*/
	public Set< String > getParameterNames() { return get_parameter_names(); }

	/**
	* Returns a set containing the names of all of the parameters of an
	* interaction class instance.
	*
	* @return set containing the names of all of the parameters of an
	* interaction class instance
	*/
	public Set< String > getAllParameterNames() { return get_all_parameter_names(); }

	/**
	* Publishes the interaction class of this instance of the class for a federate.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public void publishInteraction( RTIambassador rti ) { publish( rti ); }

	/**
	* Unpublishes the interaction class of this instance of this class for a federate.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public void unpublishInteraction( RTIambassador rti ) { unpublish( rti ); }

	/**
	* Subscribes a federate to the interaction class of this instance of this class.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public void subscribeInteraction( RTIambassador rti ) { subscribe( rti ); }

	/**
	* Unsubscribes a federate from the interaction class of this instance of this class.
	*
	* @param rti handle to the RTI, usu. obtained through the
	* {@link SynchronizedFederate#getRTI()} call
	*/
	public void unsubscribeInteraction( RTIambassador rti ) { unsubscribe( rti ); }

	

	public String toString() {
		return "StartDataInjectionAttack("
			
			
			+ "packet:" + get_packet()
			+ "," + "toNode:" + get_toNode()
			+ "," + "fromNode:" + get_fromNode()
			+ ")";
	}
	



	
	
	private String _packet = "";
	
	private String _toNode = "";
	
	private String _fromNode = "";

	
	
	/**
	* Set the value of the "packet" parameter to "value" for this parameter.
	*
	* @param value the new value for the "packet" parameter
	*/
	public void set_packet( String value ) { _packet = value; }
	
	/**
	* Returns the value of the "packet" parameter of this interaction.
	*
	* @return the value of the "packet" parameter
	*/
	public String get_packet() { return _packet; }
	
	
	/**
	* Set the value of the "toNode" parameter to "value" for this parameter.
	*
	* @param value the new value for the "toNode" parameter
	*/
	public void set_toNode( String value ) { _toNode = value; }
	
	/**
	* Returns the value of the "toNode" parameter of this interaction.
	*
	* @return the value of the "toNode" parameter
	*/
	public String get_toNode() { return _toNode; }
	
	
	/**
	* Set the value of the "fromNode" parameter to "value" for this parameter.
	*
	* @param value the new value for the "fromNode" parameter
	*/
	public void set_fromNode( String value ) { _fromNode = value; }
	
	/**
	* Returns the value of the "fromNode" parameter of this interaction.
	*
	* @return the value of the "fromNode" parameter
	*/
	public String get_fromNode() { return _fromNode; }
	


	protected StartDataInjectionAttack( ReceivedInteraction datamemberMap, boolean initFlag ) {
		super( datamemberMap, false );
		if ( initFlag ) setParameters( datamemberMap );
	}
	
	protected StartDataInjectionAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime, boolean initFlag ) {
		super( datamemberMap, logicalTime, false );
		if ( initFlag ) setParameters( datamemberMap );
	}


	/**
	* Creates an instance of the StartDataInjectionAttack interaction class, using
	* "datamemberMap" to initialize its parameter values.
	* "datamemberMap" is usually acquired as an argument to an RTI federate
	* callback method, such as "receiveInteraction".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StartDataInjectionAttack interaction class instance
	*/
	public StartDataInjectionAttack( ReceivedInteraction datamemberMap ) {
		this( datamemberMap, true );
	}
	
	/**
	* Like {@link #StartDataInjectionAttack( ReceivedInteraction datamemberMap )}, except this
	* new StartDataInjectionAttack interaction class instance is given a timestamp of
	* "logicalTime".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StartDataInjectionAttack interaction class instance
	* @param logicalTime timestamp for this new StartDataInjectionAttack interaction class
	* instance
	*/
	public StartDataInjectionAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime ) {
		this( datamemberMap, logicalTime, true );
	}

	/**
	* Creates a new StartDataInjectionAttack interaction class instance that is a duplicate
	* of the instance referred to by StartDataInjectionAttack_var.
	*
	* @param StartDataInjectionAttack_var StartDataInjectionAttack interaction class instance of which
	* this newly created StartDataInjectionAttack interaction class instance will be a
	* duplicate
	*/
	public StartDataInjectionAttack( StartDataInjectionAttack StartDataInjectionAttack_var ) {
		super( StartDataInjectionAttack_var );
		
		
		set_packet( StartDataInjectionAttack_var.get_packet() );
		set_toNode( StartDataInjectionAttack_var.get_toNode() );
		set_fromNode( StartDataInjectionAttack_var.get_fromNode() );
	}


	/**
	* Returns the value of the parameter whose name is "datamemberName"
	* for this interaction.
	*
	* @param datamemberName name of parameter whose value is to be
	* returned
	* @return value of the parameter whose name is "datamemberName"
	* for this interaction
	*/
	public Object getParameter( String datamemberName ) {
		
		
		
		if (  "packet".equals( datamemberName )  ) return get_packet();
		else if (  "toNode".equals( datamemberName )  ) return get_toNode();
		else if (  "fromNode".equals( datamemberName )  ) return get_fromNode();
		else return super.getParameter( datamemberName );
	}
	
	/**
	* Returns the value of the parameter whose handle (RTI assigned)
	* is "datamemberHandle" for this interaction.
	*
	* @param datamemberHandle handle (RTI assigned) of parameter whose
	* value is to be returned
	* @return value of the parameter whose handle (RTI assigned) is
	* "datamemberHandle" for this interaction
	*/
	public Object getParameter( int datamemberHandle ) {
		
				
		
		if ( get_packet_handle() == datamemberHandle ) return get_packet();
		else if ( get_toNode_handle() == datamemberHandle ) return get_toNode();
		else if ( get_fromNode_handle() == datamemberHandle ) return get_fromNode();
		else return super.getParameter( datamemberHandle );
	}
	
	protected boolean setParameterAux( int param_handle, String val ) {
		boolean retval = true;		
		
			
		
		if ( param_handle == get_packet_handle() ) set_packet( val );
		else if ( param_handle == get_toNode_handle() ) set_toNode( val );
		else if ( param_handle == get_fromNode_handle() ) set_fromNode( val );
		else retval = super.setParameterAux( param_handle, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, String val ) {
		boolean retval = true;
		
			
		
		if (  "packet".equals( datamemberName )  ) set_packet( val );
		else if (  "toNode".equals( datamemberName )  ) set_toNode( val );
		else if (  "fromNode".equals( datamemberName )  ) set_fromNode( val );	
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, Object val ) {
		boolean retval = true;
		
		
		
		if (  "packet".equals( datamemberName )  ) set_packet( (String)val );
		else if (  "toNode".equals( datamemberName )  ) set_toNode( (String)val );
		else if (  "fromNode".equals( datamemberName )  ) set_fromNode( (String)val );		
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}

	protected SuppliedParameters createSuppliedDatamembers() {
		SuppliedParameters datamembers = super.createSuppliedDatamembers();

	
		
		
			datamembers.add( get_packet_handle(), get_packet().getBytes() );
		
			datamembers.add( get_toNode_handle(), get_toNode().getBytes() );
		
			datamembers.add( get_fromNode_handle(), get_fromNode().getBytes() );
		
	
		return datamembers;
	}

	
	public void copyFrom( Object object ) {
		super.copyFrom( object );
		if ( object instanceof StartDataInjectionAttack ) {
			StartDataInjectionAttack data = (StartDataInjectionAttack)object;
			
			
				_packet = data._packet;
				_toNode = data._toNode;
				_fromNode = data._fromNode;
			
		}
	}
}
