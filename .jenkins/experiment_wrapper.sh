# this script is used to build cpswt-core and its dependencies in the docker container 
ORIGINAL_PATH=$PATH
export JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
/opt/apache-archiva-2.2.5/bin/archiva start

# wait for archiva to start
echo "Waiting archiva to launch on 8080..."

while ! nc -z localhost 8080; do   
  sleep 0.1 # wait for 1/10 of the second before check again
done

echo "archiva launched"

# create admin user
curl --no-progress-meter -X POST -H "Content-Type: application/json" -H "Origin: http://localhost:8080" -d @- \
 http://localhost:8080/restServices/redbackServices/userService/createAdminUser <<'TERMINUS'
{
    "username": "admin",
    "password": "adminpass123",
    "email": "admin@archiva-test.org",
    "fullName": "Admin",
    "locked": false,
    "passwordChangeRequired": false,
    "permanent": false,
    "readOnly": false,
    "validated": true,
    "confirmPassword": "adminpass123"
}
TERMINUS

# disable rest.csrffilter.enabled in archiva.xml
sed -i '/<rest>/,/<\/csrffilter>/s/<enabled>true/<enabled>false/' /opt/apache-archiva-2.2.5/conf/archiva.xml
# sed -i 's/<baseUrl\/>/<baseUrl>http:\/\/129.59.107.97\/archiva-core\/<\/baseUrl>/' /opt/apache-archiva-2.2.5/conf/archiva.xml

# # restart archiva
/opt/apache-archiva-2.2.5/bin/archiva stop
/opt/apache-archiva-2.2.5/bin/archiva start

echo "Waiting archiva to launch again on 8080..."

while ! nc -z localhost 8080; do   
  sleep 0.1 # wait for 1/10 of the second before check again
done

echo "archiva launched  again"


# switch to java 17
unset JAVA_HOME
export JAVA_HOME=/usr/lib/jvm/java-1.17.0-openjdk-amd64
export PATH=$JAVA_HOME/bin:$ORIGINAL_PATH

# clone cpswt-core and build it
cd /home/cpswt
git clone https://github.com/SimIntToolkit/cpswt-core.git
cd cpswt-core/cpswt-core

gradle wrapper --gradle-version=8.0

./gradlew :utils:publish 
./gradlew :root:publish
./gradlew :base-events:publish 
./gradlew :config:publish
./gradlew :federate-base:publish 
./gradlew :coa:publish 
./gradlew :federation-manager:publish 
./gradlew :fedmanager-host:publish 

# build cpswt-cpp
cd /home/cpswt
git clone https://github.com/SimIntToolkit/cpswt-cpp.git
cd cpswt-cpp

gradle wrapper --gradle-version=8.0

./gradlew :foundation:CppTestHarness:publish
./gradlew :foundation:core-cpp:publish
./gradlew :foundation:C2WConsoleLogger:publish
./gradlew :foundation:rti-base-cpp:publish
./gradlew :foundation:CPSWTConfig:publish
./gradlew :foundation:SynchronizedFederate:publish

cd /home/cpswt/cpswt-cpp/examples/HelloWorldCpp
touch build.dummy.kts
gradle -b build.dummy.kts wrapper --gradle-version=8.0
./gradlew :Source:build
./gradlew :Sink:build
./gradlew :PingCounter:build
./gradlew :runFederationBatch
