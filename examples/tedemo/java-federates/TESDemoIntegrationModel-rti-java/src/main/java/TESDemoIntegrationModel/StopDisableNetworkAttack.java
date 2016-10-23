
// This code has been generated by the C2W code generator.
// Do not edit manually!

package TESDemoIntegrationModel;

import java.util.HashSet;
import java.util.Set;

import hla.rti.*;

import c2w.hla.*;

/**
* The StopDisableNetworkAttack class implements the StopDisableNetworkAttack interaction in the
* TESDemoIntegrationModel simulation.
*/
public class StopDisableNetworkAttack extends OmnetCommand {

	/**
	* Default constructor -- creates an instance of the StopDisableNetworkAttack interaction
	* class with default parameter values.
	*/
	public StopDisableNetworkAttack() { }

	
	
	private static int _networkAddress_handle;
	
	
	/**
	* Returns the handle (RTI assigned) of the "networkAddress" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "networkAddress" parameter
	*/
	public static int get_networkAddress_handle() { return _networkAddress_handle; }
	
	
	
	private static boolean _isInitialized = false;

	private static int _handle;

	/**
	* Returns the handle (RTI assigned) of the StopDisableNetworkAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the handle of the class pertaining to the reference,\
	* rather than the handle of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassHandle()}.
	*/
	public static int get_handle() { return _handle; }

	/**
	* Returns the fully-qualified (dot-delimited) name of the StopDisableNetworkAttack
	* interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the name of the class pertaining to the reference,\
	* rather than the name of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassName()}.
	*/
	public static String get_class_name() { return "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack"; }

	/**
	* Returns the simple name (the last name in the dot-delimited fully-qualified
	* class name) of the StopDisableNetworkAttack interaction class.
	*/
	public static String get_simple_class_name() { return "StopDisableNetworkAttack"; }

	private static Set< String > _datamemberNames = new HashSet< String >();
	private static Set< String > _allDatamemberNames = new HashSet< String >();

	/**
	* Returns a set containing the names of all of the non-hidden parameters in the
	* StopDisableNetworkAttack interaction class.
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
	* StopDisableNetworkAttack interaction class.
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
		_classNameSet.add( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack" );
		_classNameClassMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack", StopDisableNetworkAttack.class );
		
		_datamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack", _datamemberNames );
		_allDatamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack", _allDatamemberNames );

		
		
		_datamemberNames.add( "networkAddress" );
		
		
		
		
		
		
		
		_allDatamemberNames.add( "networkAddress" );
		_allDatamemberNames.add( "sourceFed" );
		_allDatamemberNames.add( "uniqueCommandID" );
		_allDatamemberNames.add( "originFed" );
		_allDatamemberNames.add( "federateFilter" );
		_allDatamemberNames.add( "actualLogicalGenerationTime" );
		
		
		_datamemberTypeMap.put( "networkAddress", "String" );
	
	

	}


	private static String initErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack:  could not initialize:  ";
	protected static void init( RTIambassador rti ) {
		if ( _isInitialized ) return;
		_isInitialized = true;
		
		OmnetCommand.init( rti );
		
		boolean isNotInitialized = true;
		while( isNotInitialized ) {
			try {
				_handle = rti.getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack" );
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

		_classNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack", get_handle() );
		_classHandleNameMap.put( get_handle(), "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack" );
		_classHandleSimpleNameMap.put( get_handle(), "StopDisableNetworkAttack" );

		
		isNotInitialized = true;
		while( isNotInitialized ) {
			try {
							
				_networkAddress_handle = rti.getParameterHandle( "networkAddress", get_handle() );
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
			
			
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack,networkAddress", get_networkAddress_handle() );
			
			
		_datamemberHandleNameMap.put( get_networkAddress_handle(), "networkAddress" );
		
	}


	private static boolean _isPublished = false;
	private static String publishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack:  could not publish:  ";

	/**
	* Publishes the StopDisableNetworkAttack interaction class for a federate.
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

	private static String unpublishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack:  could not unpublish:  ";
	/**
	* Unpublishes the StopDisableNetworkAttack interaction class for a federate.
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
	private static String subscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack:  could not subscribe:  ";
	/**
	* Subscribes a federate to the StopDisableNetworkAttack interaction class.
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

	private static String unsubscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopDisableNetworkAttack:  could not unsubscribe:  ";
	/**
	* Unsubscribes a federate from the StopDisableNetworkAttack interaction class.
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
	* (that is, the StopDisableNetworkAttack interaction class).
	*
	* @param handle handle to compare to the value of the handle (RTI assigned) of
	* this class (the StopDisableNetworkAttack interaction class).
	* @return "true" if "handle" matches the value of the handle of this class
	* (that is, the StopDisableNetworkAttack interaction class).
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
		return "StopDisableNetworkAttack("
			
			
			+ "networkAddress:" + get_networkAddress()
			+ ")";
	}
	



	
	
	private String _networkAddress = "";

	
	
	/**
	* Set the value of the "networkAddress" parameter to "value" for this parameter.
	*
	* @param value the new value for the "networkAddress" parameter
	*/
	public void set_networkAddress( String value ) { _networkAddress = value; }
	
	/**
	* Returns the value of the "networkAddress" parameter of this interaction.
	*
	* @return the value of the "networkAddress" parameter
	*/
	public String get_networkAddress() { return _networkAddress; }
	


	protected StopDisableNetworkAttack( ReceivedInteraction datamemberMap, boolean initFlag ) {
		super( datamemberMap, false );
		if ( initFlag ) setParameters( datamemberMap );
	}
	
	protected StopDisableNetworkAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime, boolean initFlag ) {
		super( datamemberMap, logicalTime, false );
		if ( initFlag ) setParameters( datamemberMap );
	}


	/**
	* Creates an instance of the StopDisableNetworkAttack interaction class, using
	* "datamemberMap" to initialize its parameter values.
	* "datamemberMap" is usually acquired as an argument to an RTI federate
	* callback method, such as "receiveInteraction".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StopDisableNetworkAttack interaction class instance
	*/
	public StopDisableNetworkAttack( ReceivedInteraction datamemberMap ) {
		this( datamemberMap, true );
	}
	
	/**
	* Like {@link #StopDisableNetworkAttack( ReceivedInteraction datamemberMap )}, except this
	* new StopDisableNetworkAttack interaction class instance is given a timestamp of
	* "logicalTime".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StopDisableNetworkAttack interaction class instance
	* @param logicalTime timestamp for this new StopDisableNetworkAttack interaction class
	* instance
	*/
	public StopDisableNetworkAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime ) {
		this( datamemberMap, logicalTime, true );
	}

	/**
	* Creates a new StopDisableNetworkAttack interaction class instance that is a duplicate
	* of the instance referred to by StopDisableNetworkAttack_var.
	*
	* @param StopDisableNetworkAttack_var StopDisableNetworkAttack interaction class instance of which
	* this newly created StopDisableNetworkAttack interaction class instance will be a
	* duplicate
	*/
	public StopDisableNetworkAttack( StopDisableNetworkAttack StopDisableNetworkAttack_var ) {
		super( StopDisableNetworkAttack_var );
		
		
		set_networkAddress( StopDisableNetworkAttack_var.get_networkAddress() );
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
		
		
		
		if (  "networkAddress".equals( datamemberName )  ) return get_networkAddress();
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
		
				
		
		if ( get_networkAddress_handle() == datamemberHandle ) return get_networkAddress();
		else return super.getParameter( datamemberHandle );
	}
	
	protected boolean setParameterAux( int param_handle, String val ) {
		boolean retval = true;		
		
			
		
		if ( param_handle == get_networkAddress_handle() ) set_networkAddress( val );
		else retval = super.setParameterAux( param_handle, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, String val ) {
		boolean retval = true;
		
			
		
		if (  "networkAddress".equals( datamemberName )  ) set_networkAddress( val );	
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, Object val ) {
		boolean retval = true;
		
		
		
		if (  "networkAddress".equals( datamemberName )  ) set_networkAddress( (String)val );		
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}

	protected SuppliedParameters createSuppliedDatamembers() {
		SuppliedParameters datamembers = super.createSuppliedDatamembers();

	
		
		
			datamembers.add( get_networkAddress_handle(), get_networkAddress().getBytes() );
		
	
		return datamembers;
	}

	
	public void copyFrom( Object object ) {
		super.copyFrom( object );
		if ( object instanceof StopDisableNetworkAttack ) {
			StopDisableNetworkAttack data = (StopDisableNetworkAttack)object;
			
			
				_networkAddress = data._networkAddress;
			
		}
	}
}
