rootProject.name = "cpswt-cpp"
  
val archivaHostId: String by settings
val archivaPort: String by settings

pluginManagement {
    repositories {
        gradlePluginPortal()
    }
    plugins {
    }
}

dependencyResolutionManagement {
    repositories {
        mavenLocal()
        mavenCentral()

        maven {
            isAllowInsecureProtocol = true
            url = uri("http://$archivaHostId:$archivaPort/repository/snapshots")

        }
    }
}


include("foundation")


include("foundation:core")
project(":foundation:core").name = "core-cpp"

include("foundation:C2WConsoleLogger")
project(":foundation:C2WConsoleLogger").name = "C2WConsoleLogger"

include("foundation:rti-base")
project(":foundation:rti-base").name = "rti-base-cpp"

include("foundation:config")
project(":foundation:config").name = "CPSWTConfig"

include("foundation:SynchronizedFederate")
project(":foundation:SynchronizedFederate").name = "SynchronizedFederate"

include("foundation:OmnetFederate")
project(":foundation:OmnetFederate").name = "OmnetFederate"
