
// This code has been generated by the C2W code generator.
// Do not edit manually!

package TESDemoIntegrationModel;

import java.util.HashSet;
import java.util.Set;

import hla.rti.*;

import c2w.hla.*;

/**
* The StartReplayAttack class implements the StartReplayAttack interaction in the
* TESDemoIntegrationModel simulation.
*/
public class StartReplayAttack extends OmnetCommand {

	/**
	* Default constructor -- creates an instance of the StartReplayAttack interaction
	* class with default parameter values.
	*/
	public StartReplayAttack() { }

	
	
	private static int _dstNetworkAddress_handle;
	private static int _srcNetworkAddress_handle;
	private static int _recordingNodeFullPath_handle;
	
	
	/**
	* Returns the handle (RTI assigned) of the "dstNetworkAddress" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "dstNetworkAddress" parameter
	*/
	public static int get_dstNetworkAddress_handle() { return _dstNetworkAddress_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "srcNetworkAddress" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "srcNetworkAddress" parameter
	*/
	public static int get_srcNetworkAddress_handle() { return _srcNetworkAddress_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "recordingNodeFullPath" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "recordingNodeFullPath" parameter
	*/
	public static int get_recordingNodeFullPath_handle() { return _recordingNodeFullPath_handle; }
	
	
	
	private static boolean _isInitialized = false;

	private static int _handle;

	/**
	* Returns the handle (RTI assigned) of the StartReplayAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the handle of the class pertaining to the reference,\
	* rather than the handle of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassHandle()}.
	*/
	public static int get_handle() { return _handle; }

	/**
	* Returns the fully-qualified (dot-delimited) name of the StartReplayAttack
	* interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the name of the class pertaining to the reference,\
	* rather than the name of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassName()}.
	*/
	public static String get_class_name() { return "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack"; }

	/**
	* Returns the simple name (the last name in the dot-delimited fully-qualified
	* class name) of the StartReplayAttack interaction class.
	*/
	public static String get_simple_class_name() { return "StartReplayAttack"; }

	private static Set< String > _datamemberNames = new HashSet< String >();
	private static Set< String > _allDatamemberNames = new HashSet< String >();

	/**
	* Returns a set containing the names of all of the non-hidden parameters in the
	* StartReplayAttack interaction class.
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
	* StartReplayAttack interaction class.
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
		_classNameSet.add( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack" );
		_classNameClassMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack", StartReplayAttack.class );
		
		_datamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack", _datamemberNames );
		_allDatamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack", _allDatamemberNames );

		
		
		_datamemberNames.add( "dstNetworkAddress" );
		_datamemberNames.add( "srcNetworkAddress" );
		
		
		_datamemberNames.add( "recordingNodeFullPath" );
		
		
		
		
		
		_allDatamemberNames.add( "dstNetworkAddress" );
		_allDatamemberNames.add( "srcNetworkAddress" );
		_allDatamemberNames.add( "sourceFed" );
		_allDatamemberNames.add( "uniqueCommandID" );
		_allDatamemberNames.add( "recordingNodeFullPath" );
		_allDatamemberNames.add( "originFed" );
		_allDatamemberNames.add( "federateFilter" );
		_allDatamemberNames.add( "actualLogicalGenerationTime" );
		
		
		_datamemberTypeMap.put( "dstNetworkAddress", "String" );
		_datamemberTypeMap.put( "srcNetworkAddress", "String" );
		_datamemberTypeMap.put( "recordingNodeFullPath", "String" );
	
	

	}


	private static String initErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack:  could not initialize:  ";
	protected static void init( RTIambassador rti ) {
		if ( _isInitialized ) return;
		_isInitialized = true;
		
		OmnetCommand.init( rti );
		
		boolean isNotInitialized = true;
		while( isNotInitialized ) {
			try {
				_handle = rti.getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack" );
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

		_classNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack", get_handle() );
		_classHandleNameMap.put( get_handle(), "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack" );
		_classHandleSimpleNameMap.put( get_handle(), "StartReplayAttack" );

		
		isNotInitialized = true;
		while( isNotInitialized ) {
			try {
							
				_dstNetworkAddress_handle = rti.getParameterHandle( "dstNetworkAddress", get_handle() );			
				_srcNetworkAddress_handle = rti.getParameterHandle( "srcNetworkAddress", get_handle() );			
				_recordingNodeFullPath_handle = rti.getParameterHandle( "recordingNodeFullPath", get_handle() );
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
			
			
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack,dstNetworkAddress", get_dstNetworkAddress_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack,srcNetworkAddress", get_srcNetworkAddress_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack,recordingNodeFullPath", get_recordingNodeFullPath_handle() );
			
			
		_datamemberHandleNameMap.put( get_dstNetworkAddress_handle(), "dstNetworkAddress" );
		_datamemberHandleNameMap.put( get_srcNetworkAddress_handle(), "srcNetworkAddress" );
		_datamemberHandleNameMap.put( get_recordingNodeFullPath_handle(), "recordingNodeFullPath" );
		
	}


	private static boolean _isPublished = false;
	private static String publishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack:  could not publish:  ";

	/**
	* Publishes the StartReplayAttack interaction class for a federate.
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

	private static String unpublishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack:  could not unpublish:  ";
	/**
	* Unpublishes the StartReplayAttack interaction class for a federate.
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
	private static String subscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack:  could not subscribe:  ";
	/**
	* Subscribes a federate to the StartReplayAttack interaction class.
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

	private static String unsubscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartReplayAttack:  could not unsubscribe:  ";
	/**
	* Unsubscribes a federate from the StartReplayAttack interaction class.
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
	* (that is, the StartReplayAttack interaction class).
	*
	* @param handle handle to compare to the value of the handle (RTI assigned) of
	* this class (the StartReplayAttack interaction class).
	* @return "true" if "handle" matches the value of the handle of this class
	* (that is, the StartReplayAttack interaction class).
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
		return "StartReplayAttack("
			
			
			+ "dstNetworkAddress:" + get_dstNetworkAddress()
			+ "," + "srcNetworkAddress:" + get_srcNetworkAddress()
			+ "," + "recordingNodeFullPath:" + get_recordingNodeFullPath()
			+ ")";
	}
	



	
	
	private String _dstNetworkAddress = "";
	
	private String _srcNetworkAddress = "";
	
	private String _recordingNodeFullPath = "";

	
	
	/**
	* Set the value of the "dstNetworkAddress" parameter to "value" for this parameter.
	*
	* @param value the new value for the "dstNetworkAddress" parameter
	*/
	public void set_dstNetworkAddress( String value ) { _dstNetworkAddress = value; }
	
	/**
	* Returns the value of the "dstNetworkAddress" parameter of this interaction.
	*
	* @return the value of the "dstNetworkAddress" parameter
	*/
	public String get_dstNetworkAddress() { return _dstNetworkAddress; }
	
	
	/**
	* Set the value of the "srcNetworkAddress" parameter to "value" for this parameter.
	*
	* @param value the new value for the "srcNetworkAddress" parameter
	*/
	public void set_srcNetworkAddress( String value ) { _srcNetworkAddress = value; }
	
	/**
	* Returns the value of the "srcNetworkAddress" parameter of this interaction.
	*
	* @return the value of the "srcNetworkAddress" parameter
	*/
	public String get_srcNetworkAddress() { return _srcNetworkAddress; }
	
	
	/**
	* Set the value of the "recordingNodeFullPath" parameter to "value" for this parameter.
	*
	* @param value the new value for the "recordingNodeFullPath" parameter
	*/
	public void set_recordingNodeFullPath( String value ) { _recordingNodeFullPath = value; }
	
	/**
	* Returns the value of the "recordingNodeFullPath" parameter of this interaction.
	*
	* @return the value of the "recordingNodeFullPath" parameter
	*/
	public String get_recordingNodeFullPath() { return _recordingNodeFullPath; }
	


	protected StartReplayAttack( ReceivedInteraction datamemberMap, boolean initFlag ) {
		super( datamemberMap, false );
		if ( initFlag ) setParameters( datamemberMap );
	}
	
	protected StartReplayAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime, boolean initFlag ) {
		super( datamemberMap, logicalTime, false );
		if ( initFlag ) setParameters( datamemberMap );
	}


	/**
	* Creates an instance of the StartReplayAttack interaction class, using
	* "datamemberMap" to initialize its parameter values.
	* "datamemberMap" is usually acquired as an argument to an RTI federate
	* callback method, such as "receiveInteraction".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StartReplayAttack interaction class instance
	*/
	public StartReplayAttack( ReceivedInteraction datamemberMap ) {
		this( datamemberMap, true );
	}
	
	/**
	* Like {@link #StartReplayAttack( ReceivedInteraction datamemberMap )}, except this
	* new StartReplayAttack interaction class instance is given a timestamp of
	* "logicalTime".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StartReplayAttack interaction class instance
	* @param logicalTime timestamp for this new StartReplayAttack interaction class
	* instance
	*/
	public StartReplayAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime ) {
		this( datamemberMap, logicalTime, true );
	}

	/**
	* Creates a new StartReplayAttack interaction class instance that is a duplicate
	* of the instance referred to by StartReplayAttack_var.
	*
	* @param StartReplayAttack_var StartReplayAttack interaction class instance of which
	* this newly created StartReplayAttack interaction class instance will be a
	* duplicate
	*/
	public StartReplayAttack( StartReplayAttack StartReplayAttack_var ) {
		super( StartReplayAttack_var );
		
		
		set_dstNetworkAddress( StartReplayAttack_var.get_dstNetworkAddress() );
		set_srcNetworkAddress( StartReplayAttack_var.get_srcNetworkAddress() );
		set_recordingNodeFullPath( StartReplayAttack_var.get_recordingNodeFullPath() );
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
		
		
		
		if (  "dstNetworkAddress".equals( datamemberName )  ) return get_dstNetworkAddress();
		else if (  "srcNetworkAddress".equals( datamemberName )  ) return get_srcNetworkAddress();
		else if (  "recordingNodeFullPath".equals( datamemberName )  ) return get_recordingNodeFullPath();
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
		
				
		
		if ( get_dstNetworkAddress_handle() == datamemberHandle ) return get_dstNetworkAddress();
		else if ( get_srcNetworkAddress_handle() == datamemberHandle ) return get_srcNetworkAddress();
		else if ( get_recordingNodeFullPath_handle() == datamemberHandle ) return get_recordingNodeFullPath();
		else return super.getParameter( datamemberHandle );
	}
	
	protected boolean setParameterAux( int param_handle, String val ) {
		boolean retval = true;		
		
			
		
		if ( param_handle == get_dstNetworkAddress_handle() ) set_dstNetworkAddress( val );
		else if ( param_handle == get_srcNetworkAddress_handle() ) set_srcNetworkAddress( val );
		else if ( param_handle == get_recordingNodeFullPath_handle() ) set_recordingNodeFullPath( val );
		else retval = super.setParameterAux( param_handle, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, String val ) {
		boolean retval = true;
		
			
		
		if (  "dstNetworkAddress".equals( datamemberName )  ) set_dstNetworkAddress( val );
		else if (  "srcNetworkAddress".equals( datamemberName )  ) set_srcNetworkAddress( val );
		else if (  "recordingNodeFullPath".equals( datamemberName )  ) set_recordingNodeFullPath( val );	
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, Object val ) {
		boolean retval = true;
		
		
		
		if (  "dstNetworkAddress".equals( datamemberName )  ) set_dstNetworkAddress( (String)val );
		else if (  "srcNetworkAddress".equals( datamemberName )  ) set_srcNetworkAddress( (String)val );
		else if (  "recordingNodeFullPath".equals( datamemberName )  ) set_recordingNodeFullPath( (String)val );		
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}

	protected SuppliedParameters createSuppliedDatamembers() {
		SuppliedParameters datamembers = super.createSuppliedDatamembers();

	
		
		
			datamembers.add( get_dstNetworkAddress_handle(), get_dstNetworkAddress().getBytes() );
		
			datamembers.add( get_srcNetworkAddress_handle(), get_srcNetworkAddress().getBytes() );
		
			datamembers.add( get_recordingNodeFullPath_handle(), get_recordingNodeFullPath().getBytes() );
		
	
		return datamembers;
	}

	
	public void copyFrom( Object object ) {
		super.copyFrom( object );
		if ( object instanceof StartReplayAttack ) {
			StartReplayAttack data = (StartReplayAttack)object;
			
			
				_dstNetworkAddress = data._dstNetworkAddress;
				_srcNetworkAddress = data._srcNetworkAddress;
				_recordingNodeFullPath = data._recordingNodeFullPath;
			
		}
	}
}