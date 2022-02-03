
/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 *
 * @author Harmon Nine
 */

import java.nio.file.Files
import java.util.regex.Pattern

plugins {
    `cpp-library`
    `maven-publish`
    `cpp-unit-test`
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

        testImplementation(project(":foundation:CppTestHarness"))
    }
    source.from(file("src/main/c++"))
    publicHeaders.from(file("src/main/include"))
}

unitTest {
    targetMachines.set(listOf(machines.linux.x86_64))
    source.from(file("src/test/c++"))
    privateHeaders.from(file("src/test/include"))
}


tasks.withType(CppCompile::class.java).configureEach {
    compilerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> listOf("-I$rtiHome/include/hla13", "-Wno-deprecated")
            is VisualCpp -> listOf("/I $rtiHome/include/hla13")
            else -> listOf()
        }
    })
}

tasks.withType(LinkExecutable::class.java).configureEach {

    val linkLibraryList = listOf(
        "cppunit", "jsoncpp", "boost_log_setup", "boost_log", "boost_system", "boost_thread", "pthread"
    )

    val linkLibraryOptionList = linkLibraryList.map { "-l$it" }

    linkerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> linkLibraryOptionList
            else -> listOf()
        }
    })
}

tasks.withType(InstallExecutable::class.java).configureEach {
    doLast {
        val libraryDirectory = File(installDirectory.asFile.get(), "lib")
        val sharedObjectFileList = libraryDirectory.listFiles { file -> file.name.endsWith(".so") }!!.toList()

        val pattern = Pattern.compile("(.*)_(?:debug|release)")

        for(file in sharedObjectFileList) {
            val fileName = file.name
            val matcher = pattern.matcher(fileName)
            if (matcher.find()) {
                val libName = matcher.group(1);
                val libraryFile = File(libraryDirectory, "lib${libName}.so")
                Files.createSymbolicLink(libraryFile.toPath(), File(fileName).toPath())
            }
        }
    }
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