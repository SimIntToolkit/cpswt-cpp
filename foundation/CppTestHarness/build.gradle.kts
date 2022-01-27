plugins {
    `cpp-library`
    `maven-publish`
}

val rtiHome: String? = System.getenv("RTI_HOME")
print("RTI_HOME=\"$rtiHome\"\n")

val archivaUser: String by project
val archivaPassword: String by project
val version: String by project
val archivaHostId: String by project
val archivaPort: String by project

library {
    source.from(file("src/main/c++"))
    publicHeaders.from(file("src/main/include"))
}

publishing {
    publications {
        getByName<MavenPublication>("main") {
            group = "org.cpswt"
        }
    }
    repositories {
        maven {
            name = "cppTestHarnessPublish"
            val internalRepoUrl = "http://$archivaHostId:$archivaPort/repository/internal"
            val snapshotsRepoUrl = "http://$archivaHostId:$archivaPort/repository/snapshots"
            url = uri(if (version.toString().endsWith("SNAPSHOT")) snapshotsRepoUrl else internalRepoUrl)

            logger.info("URL = \"$url\"")
            isAllowInsecureProtocol = true
            authentication {
                create<BasicAuthentication>("basic")
            }
            credentials {
                username = archivaUser
                password = archivaPassword
            }
        }
    }
}