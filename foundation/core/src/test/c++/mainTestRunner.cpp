#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include <boost/lexical_cast.hpp>
int main(void) {
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}