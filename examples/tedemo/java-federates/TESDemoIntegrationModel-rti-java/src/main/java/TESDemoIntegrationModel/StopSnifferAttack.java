
// This code has been generated by the C2W code generator.
// Do not edit manually!

package TESDemoIntegrationModel;

import java.util.HashSet;
import java.util.Set;

import hla.rti.*;

import c2w.hla.*;

/**
* The StopSnifferAttack class implements the StopSnifferAttack interaction in the
* TESDemoIntegrationModel simulation.
*/
public class StopSnifferAttack extends OmnetCommand {

	/**
	* Default constructor -- creates an instance of the StopSnifferAttack interaction
	* class with default parameter values.
	*/
	public StopSnifferAttack() { }

	
	
	private static int _listenerNodeFullPath_handle;
	private static int _listenerInterface_handle;
	private static int _nodeFullPath_handle;
	
	
	/**
	* Returns the handle (RTI assigned) of the "listenerNodeFullPath" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "listenerNodeFullPath" parameter
	*/
	public static int get_listenerNodeFullPath_handle() { return _listenerNodeFullPath_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "listenerInterface" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "listenerInterface" parameter
	*/
	public static int get_listenerInterface_handle() { return _listenerInterface_handle; }
	
	/**
	* Returns the handle (RTI assigned) of the "nodeFullPath" parameter of
	* its containing interaction class.
	*
	* @return the handle (RTI assigned) of the "nodeFullPath" parameter
	*/
	public static int get_nodeFullPath_handle() { return _nodeFullPath_handle; }
	
	
	
	private static boolean _isInitialized = false;

	private static int _handle;

	/**
	* Returns the handle (RTI assigned) of the StopSnifferAttack interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the handle of the class pertaining to the reference,\
	* rather than the handle of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassHandle()}.
	*/
	public static int get_handle() { return _handle; }

	/**
	* Returns the fully-qualified (dot-delimited) name of the StopSnifferAttack
	* interaction class.
	* Note: As this is a static method, it is NOT polymorphic, and so, if called on
	* a reference will return the name of the class pertaining to the reference,\
	* rather than the name of the class for the instance referred to by the reference.
	* For the polymorphic version of this method, use {@link #getClassName()}.
	*/
	public static String get_class_name() { return "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack"; }

	/**
	* Returns the simple name (the last name in the dot-delimited fully-qualified
	* class name) of the StopSnifferAttack interaction class.
	*/
	public static String get_simple_class_name() { return "StopSnifferAttack"; }

	private static Set< String > _datamemberNames = new HashSet< String >();
	private static Set< String > _allDatamemberNames = new HashSet< String >();

	/**
	* Returns a set containing the names of all of the non-hidden parameters in the
	* StopSnifferAttack interaction class.
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
	* StopSnifferAttack interaction class.
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
		_classNameSet.add( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack" );
		_classNameClassMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack", StopSnifferAttack.class );
		
		_datamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack", _datamemberNames );
		_allDatamemberClassNameSetMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack", _allDatamemberNames );

		
		
		_datamemberNames.add( "listenerNodeFullPath" );
		
		
		_datamemberNames.add( "listenerInterface" );
		_datamemberNames.add( "nodeFullPath" );
		
		
		
		
		
		_allDatamemberNames.add( "listenerNodeFullPath" );
		_allDatamemberNames.add( "sourceFed" );
		_allDatamemberNames.add( "uniqueCommandID" );
		_allDatamemberNames.add( "listenerInterface" );
		_allDatamemberNames.add( "nodeFullPath" );
		_allDatamemberNames.add( "originFed" );
		_allDatamemberNames.add( "federateFilter" );
		_allDatamemberNames.add( "actualLogicalGenerationTime" );
		
		
		_datamemberTypeMap.put( "listenerNodeFullPath", "String" );
		_datamemberTypeMap.put( "listenerInterface", "String" );
		_datamemberTypeMap.put( "nodeFullPath", "String" );
	
	

	}


	private static String initErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack:  could not initialize:  ";
	protected static void init( RTIambassador rti ) {
		if ( _isInitialized ) return;
		_isInitialized = true;
		
		OmnetCommand.init( rti );
		
		boolean isNotInitialized = true;
		while( isNotInitialized ) {
			try {
				_handle = rti.getInteractionClassHandle( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack" );
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

		_classNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack", get_handle() );
		_classHandleNameMap.put( get_handle(), "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack" );
		_classHandleSimpleNameMap.put( get_handle(), "StopSnifferAttack" );

		
		isNotInitialized = true;
		while( isNotInitialized ) {
			try {
							
				_listenerNodeFullPath_handle = rti.getParameterHandle( "listenerNodeFullPath", get_handle() );			
				_listenerInterface_handle = rti.getParameterHandle( "listenerInterface", get_handle() );			
				_nodeFullPath_handle = rti.getParameterHandle( "nodeFullPath", get_handle() );
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
			
			
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack,listenerNodeFullPath", get_listenerNodeFullPath_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack,listenerInterface", get_listenerInterface_handle() );
		_datamemberNameHandleMap.put( "InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack,nodeFullPath", get_nodeFullPath_handle() );
			
			
		_datamemberHandleNameMap.put( get_listenerNodeFullPath_handle(), "listenerNodeFullPath" );
		_datamemberHandleNameMap.put( get_listenerInterface_handle(), "listenerInterface" );
		_datamemberHandleNameMap.put( get_nodeFullPath_handle(), "nodeFullPath" );
		
	}


	private static boolean _isPublished = false;
	private static String publishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack:  could not publish:  ";

	/**
	* Publishes the StopSnifferAttack interaction class for a federate.
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

	private static String unpublishErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack:  could not unpublish:  ";
	/**
	* Unpublishes the StopSnifferAttack interaction class for a federate.
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
	private static String subscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack:  could not subscribe:  ";
	/**
	* Subscribes a federate to the StopSnifferAttack interaction class.
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

	private static String unsubscribeErrorMessage = "Error:  InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopSnifferAttack:  could not unsubscribe:  ";
	/**
	* Unsubscribes a federate from the StopSnifferAttack interaction class.
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
	* (that is, the StopSnifferAttack interaction class).
	*
	* @param handle handle to compare to the value of the handle (RTI assigned) of
	* this class (the StopSnifferAttack interaction class).
	* @return "true" if "handle" matches the value of the handle of this class
	* (that is, the StopSnifferAttack interaction class).
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
		return "StopSnifferAttack("
			
			
			+ "listenerNodeFullPath:" + get_listenerNodeFullPath()
			+ "," + "listenerInterface:" + get_listenerInterface()
			+ "," + "nodeFullPath:" + get_nodeFullPath()
			+ ")";
	}
	



	
	
	private String _listenerNodeFullPath = "";
	
	private String _listenerInterface = "";
	
	private String _nodeFullPath = "";

	
	
	/**
	* Set the value of the "listenerNodeFullPath" parameter to "value" for this parameter.
	*
	* @param value the new value for the "listenerNodeFullPath" parameter
	*/
	public void set_listenerNodeFullPath( String value ) { _listenerNodeFullPath = value; }
	
	/**
	* Returns the value of the "listenerNodeFullPath" parameter of this interaction.
	*
	* @return the value of the "listenerNodeFullPath" parameter
	*/
	public String get_listenerNodeFullPath() { return _listenerNodeFullPath; }
	
	
	/**
	* Set the value of the "listenerInterface" parameter to "value" for this parameter.
	*
	* @param value the new value for the "listenerInterface" parameter
	*/
	public void set_listenerInterface( String value ) { _listenerInterface = value; }
	
	/**
	* Returns the value of the "listenerInterface" parameter of this interaction.
	*
	* @return the value of the "listenerInterface" parameter
	*/
	public String get_listenerInterface() { return _listenerInterface; }
	
	
	/**
	* Set the value of the "nodeFullPath" parameter to "value" for this parameter.
	*
	* @param value the new value for the "nodeFullPath" parameter
	*/
	public void set_nodeFullPath( String value ) { _nodeFullPath = value; }
	
	/**
	* Returns the value of the "nodeFullPath" parameter of this interaction.
	*
	* @return the value of the "nodeFullPath" parameter
	*/
	public String get_nodeFullPath() { return _nodeFullPath; }
	


	protected StopSnifferAttack( ReceivedInteraction datamemberMap, boolean initFlag ) {
		super( datamemberMap, false );
		if ( initFlag ) setParameters( datamemberMap );
	}
	
	protected StopSnifferAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime, boolean initFlag ) {
		super( datamemberMap, logicalTime, false );
		if ( initFlag ) setParameters( datamemberMap );
	}


	/**
	* Creates an instance of the StopSnifferAttack interaction class, using
	* "datamemberMap" to initialize its parameter values.
	* "datamemberMap" is usually acquired as an argument to an RTI federate
	* callback method, such as "receiveInteraction".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StopSnifferAttack interaction class instance
	*/
	public StopSnifferAttack( ReceivedInteraction datamemberMap ) {
		this( datamemberMap, true );
	}
	
	/**
	* Like {@link #StopSnifferAttack( ReceivedInteraction datamemberMap )}, except this
	* new StopSnifferAttack interaction class instance is given a timestamp of
	* "logicalTime".
	*
	* @param datamemberMap data structure containing initial values for the
	* parameters of this new StopSnifferAttack interaction class instance
	* @param logicalTime timestamp for this new StopSnifferAttack interaction class
	* instance
	*/
	public StopSnifferAttack( ReceivedInteraction datamemberMap, LogicalTime logicalTime ) {
		this( datamemberMap, logicalTime, true );
	}

	/**
	* Creates a new StopSnifferAttack interaction class instance that is a duplicate
	* of the instance referred to by StopSnifferAttack_var.
	*
	* @param StopSnifferAttack_var StopSnifferAttack interaction class instance of which
	* this newly created StopSnifferAttack interaction class instance will be a
	* duplicate
	*/
	public StopSnifferAttack( StopSnifferAttack StopSnifferAttack_var ) {
		super( StopSnifferAttack_var );
		
		
		set_listenerNodeFullPath( StopSnifferAttack_var.get_listenerNodeFullPath() );
		set_listenerInterface( StopSnifferAttack_var.get_listenerInterface() );
		set_nodeFullPath( StopSnifferAttack_var.get_nodeFullPath() );
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
		
		
		
		if (  "listenerNodeFullPath".equals( datamemberName )  ) return get_listenerNodeFullPath();
		else if (  "listenerInterface".equals( datamemberName )  ) return get_listenerInterface();
		else if (  "nodeFullPath".equals( datamemberName )  ) return get_nodeFullPath();
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
		
				
		
		if ( get_listenerNodeFullPath_handle() == datamemberHandle ) return get_listenerNodeFullPath();
		else if ( get_listenerInterface_handle() == datamemberHandle ) return get_listenerInterface();
		else if ( get_nodeFullPath_handle() == datamemberHandle ) return get_nodeFullPath();
		else return super.getParameter( datamemberHandle );
	}
	
	protected boolean setParameterAux( int param_handle, String val ) {
		boolean retval = true;		
		
			
		
		if ( param_handle == get_listenerNodeFullPath_handle() ) set_listenerNodeFullPath( val );
		else if ( param_handle == get_listenerInterface_handle() ) set_listenerInterface( val );
		else if ( param_handle == get_nodeFullPath_handle() ) set_nodeFullPath( val );
		else retval = super.setParameterAux( param_handle, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, String val ) {
		boolean retval = true;
		
			
		
		if (  "listenerNodeFullPath".equals( datamemberName )  ) set_listenerNodeFullPath( val );
		else if (  "listenerInterface".equals( datamemberName )  ) set_listenerInterface( val );
		else if (  "nodeFullPath".equals( datamemberName )  ) set_nodeFullPath( val );	
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}
	
	protected boolean setParameterAux( String datamemberName, Object val ) {
		boolean retval = true;
		
		
		
		if (  "listenerNodeFullPath".equals( datamemberName )  ) set_listenerNodeFullPath( (String)val );
		else if (  "listenerInterface".equals( datamemberName )  ) set_listenerInterface( (String)val );
		else if (  "nodeFullPath".equals( datamemberName )  ) set_nodeFullPath( (String)val );		
		else retval = super.setParameterAux( datamemberName, val );
		
		return retval;
	}

	protected SuppliedParameters createSuppliedDatamembers() {
		SuppliedParameters datamembers = super.createSuppliedDatamembers();

	
		
		
			datamembers.add( get_listenerNodeFullPath_handle(), get_listenerNodeFullPath().getBytes() );
		
			datamembers.add( get_listenerInterface_handle(), get_listenerInterface().getBytes() );
		
			datamembers.add( get_nodeFullPath_handle(), get_nodeFullPath().getBytes() );
		
	
		return datamembers;
	}

	
	public void copyFrom( Object object ) {
		super.copyFrom( object );
		if ( object instanceof StopSnifferAttack ) {
			StopSnifferAttack data = (StopSnifferAttack)object;
			
			
				_listenerNodeFullPath = data._listenerNodeFullPath;
				_listenerInterface = data._listenerInterface;
				_nodeFullPath = data._nodeFullPath;
			
		}
	}
}
