plugins {
    java
    application
}

group = "isis.vanderbilt.edu"
version = "1.0-SNAPSHOT"

dependencies {
    implementation(group = "org.cpswt", name = "config", version = "0.6.0-SNAPSHOT")
    implementation(group = "org.cpswt", name = "base-events", version = "0.6.0-SNAPSHOT")
    implementation(group = "org.cpswt", name = "federate-base", version = "0.6.0-SNAPSHOT")

    implementation(files("/home/vagrant/portico-2.1.0/lib/portico.jar"))

    implementation(group = "org.apache.logging.log4j", name = "log4j-core", version = "2.14.1")
    implementation(group = "com.fasterxml.jackson.core", name = "jackson-annotations", version = "2.12.5")
    implementation(group = "org.apache.commons", name = "commons-lang3", version = "3.11")
    implementation(group = "commons-cli", name = "commons-cli", version = "1.4")
    implementation(group = "com.fasterxml.jackson.core", name = "jackson-core", version = "2.12.5")
    implementation(group = "com.fasterxml.jackson.core", name = "jackson-databind", version = "2.12.5")
}

application {
    mainClass.set("OmnetFederateTest")
}