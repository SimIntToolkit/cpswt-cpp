plugins {
    `cpp-library`
    `maven-publish`
    `cpp-unit-test`
}

val archivaUser: String by project
val archivaPassword: String by project
val version: String by project
val archivaHostId: String by project
val archivaPort: String by project

library {
    source.from(file("src/main/c++"))
    publicHeaders.from(file("src/main/include"))
}

unitTest {
    targetMachines.set(listOf(machines.linux.x86_64))
    source.from(file("src/test/c++"))
    privateHeaders.from(file("src/test/include"))
}

tasks.withType(LinkExecutable::class.java).configureEach {
    linkerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> listOf("-lcppunit", "-ljsoncpp")
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
            name = "corePublish"
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
