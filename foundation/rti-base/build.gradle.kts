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
    dependencies {
        implementation(group="org.cpswt", name="core-cpp", version="0.7.0-SNAPSHOT")
        implementation(group="org.cpswt", name="C2WConsoleLogger", version="0.7.0-SNAPSHOT")
    }
    source.from(file("src/main/c++"))
    publicHeaders.from(file("src/main/include"))
}

tasks.withType(CppCompile::class.java).configureEach {
    compilerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> listOf("-I$rtiHome/include/hla13")
            is VisualCpp -> listOf("/I $rtiHome/include/hla13")
            else -> listOf()
        }
    })
}

publishing {
    publications {
        getByName<MavenPublication>("main") {
            group = "org.cpswt"
        }
    }
    repositories {
        maven {
            name = "rtiBaseCppPublish"
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
