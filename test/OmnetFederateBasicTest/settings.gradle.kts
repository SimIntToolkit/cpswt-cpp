rootProject.name = "omnet-federate-manager"

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
            url = uri("https://cpswtng_archiva:8080/repository")
        }
    }
}

//includeBuild("../base-events")
//includeBuild("../config")
//includeBuild("../root")
//includeBuild("../utils")
