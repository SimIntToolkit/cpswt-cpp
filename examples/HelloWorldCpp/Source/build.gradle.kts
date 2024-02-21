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
 */

import java.io.PrintWriter
import java.nio.file.Files


plugins {
    `cpp-application`
//    `maven-publish`
}

// THE EXPLICIT TYPE OF NULLABLE-STRING (String?) IS NEEDED HERE BECAUSE KOTLIN-SCRIPT CANNOT
// DETERMINE THE RETURN TYPE OF "System.getenv()" (WHICH IS INDEED String?) THROUGH TYPE-INFERENCE
val rtiHome: String? = System.getenv("RTI_HOME")
val javaHome: String? = System.getenv("JAVA_HOME")

val archivaUser: String by project
val archivaPassword: String by project
val version: String by project
val archivaHostId: String by project
val archivaPort: String by project

application {
    dependencies {
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="core-cpp", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="C2WConsoleLogger", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="rti-base-cpp", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="CPSWTConfig", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="SynchronizedFederate", version=version)
    }
    source.from(
        file("src/main/c++"),
    )
    privateHeaders.from(
        file("src/main/include"),
    )
    targetMachines.set(listOf(machines.linux.x86_64))
}

tasks.withType(InstallExecutable::class.java).configureEach {
    doLast {
        val libraryDirectory = File(installDirectory.asFile.get(), "lib")
        val sharedObjectFileList = libraryDirectory.listFiles { file -> file.name.endsWith(".so") }!!.toList()

        val pattern = java.util.regex.Pattern.compile("(.*)_(?:debug|release)")

        for(file in sharedObjectFileList) {
            val fileName = file.name
            val matcher = pattern.matcher(fileName)
            if (matcher.find()) {
                val libName = matcher.group(1)
                val libraryFile = File(libraryDirectory, "lib${libName}.so")
                java.nio.file.Files.createSymbolicLink(libraryFile.toPath(), File(fileName).toPath())
            }
        }
    }
}

tasks.withType(CppCompile::class.java).configureEach {

    compilerArgs.addAll(toolChain.map { toolChain ->
        when (toolChain) {
            is Gcc, is Clang -> listOf("-Wno-deprecated")
            else -> listOf()
        }
    })

    val includeDirectoryList = listOf("$rtiHome/include/hla13")

    compilerArgs.addAll(toolChain.map { toolChain ->
        when (toolChain) {
            is Gcc, is Clang -> includeDirectoryList.map { "-I$it" }
            is VisualCpp -> includeDirectoryList.map { "/I $it" }
            else -> listOf()
        }
    })
}


tasks.withType(LinkExecutable::class.java).configureEach {

    val linkDirectoryList = listOf(
        "$projectDir/lib",
        "$rtiHome/lib/gcc4",
        "$javaHome/jre/lib/amd64/server",
        "$javaHome/lib/server"
    )

    val rpathDirectoryList = linkDirectoryList + listOf("/lib", ".")

    val rpathLinkDirectoryList = listOf("/usr/lib/x86_64-linux-gnu")

    val linkWholeLibraryList = listOf(
        "RTI-NG_64",
        "FedTime_64",
        "boost_regex",
        "boost_program_options",
        "jsoncpp",
        "boost_log_setup",
        "boost_log",
        "boost_system",
        "boost_thread",
        "pthread"
    )

    val linkLibraryList = listOf(
        "dl", "stdc++", "jvm"
    )

    val rpathOptionDirectoryList = rpathDirectoryList.map { "-rpath,$it" }
    val rpathLinkOptionDirectoryList = rpathLinkDirectoryList.map { "-rpath-link=$it" }

    val gccLinkerList = rpathOptionDirectoryList + rpathLinkOptionDirectoryList
    val gccLinkerOptionList = gccLinkerList.map { "-Wl,$it"}

    val linkDirectoryOptionList = linkDirectoryList.map { "-L$it" }

    val linkWholeLibraryOptionList = linkWholeLibraryList.map { "-l$it" }
    val linkLibraryOptionList = linkLibraryList.map { "-l$it" }

    val gccCompleteLinkerOptionList = gccLinkerOptionList + linkDirectoryOptionList +
            listOf("-Wl,--whole-archive") + linkWholeLibraryOptionList + listOf("-Wl,--no-whole-archive") +
            linkLibraryOptionList

    linkerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> gccCompleteLinkerOptionList
            else -> listOf()
        }
    })
}

tasks.register<Exec>("run") {
    val installDebugTask = tasks.withType(InstallExecutable::class.java).filter {
        it.name.lowercase().contains("debug")
    }.get(0)

    val installDirectory = File(installDebugTask.installDirectory.get().asFile, "lib").absolutePath
    val libraryPathList = listOf("$javaHome/jre/lib/amd64/server", "$javaHome/lib/server", installDirectory)
    environment["LD_LIBRARY_PATH"] = libraryPathList.joinToString(":")

    workingDir = project.projectDir

    val executableFileString = installDebugTask.installedExecutable.get().asFile.absolutePath
    commandLine = listOf(executableFileString, "--configFile", "conf/Source.json")
}

fun getCommandList(): List<String> {
    val runTask = tasks.named<Exec>("run").get()

    return runTask.commandLine
}

fun getXTermCommandList(): List<String> {
    val commandList = getCommandList()

    return listOf(
            "xterm", "-geometry", "220x80", "-fg", "black", "-bg", "white", "-e", commandList.joinToString(" ")
    )
}

lateinit var spawnedProcess: Process

fun configureProcessBuilder(processBuilder: ProcessBuilder) {
    val runTask = tasks.named<Exec>("run").get()

    processBuilder.directory(projectDir)

    val environment = processBuilder.environment()
    runTask.environment.forEach { entry ->
        environment[entry.key] = entry.value.toString()
    }
}

fun spawnProcess() {
    val xtermCommandList = getXTermCommandList()

    val processBuilder = ProcessBuilder(xtermCommandList)
    configureProcessBuilder(processBuilder)

    spawnedProcess = processBuilder.start()
}

fun spawnProcessBatch() {
    val commandList = getCommandList()

    val processBuilder = ProcessBuilder(commandList)
    configureProcessBuilder(processBuilder)

    val statusDirectory = File(projectDir, "StatusDirectory")
    if (!statusDirectory.exists()) {
        Files.createDirectory(statusDirectory.toPath())
    }
    val stdoutFile = File(statusDirectory, "stdout")
    val stderrFile = File(statusDirectory, "stderr")

    processBuilder.redirectOutput(stdoutFile)
    processBuilder.redirectError(stderrFile)

    spawnedProcess = processBuilder.start()

    val pid = spawnedProcess.pid()

    PrintWriter(File(statusDirectory, "pid")).use {
        it.println(pid)
    }
}

tasks.register("runAsynchronous") {
    dependsOn("build")
    doLast {
        spawnProcess()
    }
}

val runAsynchronousBatch = tasks.register("runAsynchronousBatch") {
    dependsOn("build")
    doLast {
        spawnProcessBatch()
    }
}

tasks.register("waitForFederate") {
    doLast {
        spawnedProcess.waitFor()
    }
}

tasks.register("killFederate") {
    doLast {
        spawnedProcess.destroy()
    }
}

//publishing {
//    publications {
//        getByName<MavenPublication>("main") {
//            group = "edu.vanderbilt.vuisis.cpswt"
//        }
//    }
//    repositories {
//        maven {
//            name = "rtiBaseCppPublish"
//            val internalRepoUrl = "http://$archivaHostId:$archivaPort/repository/internal"
//            val snapshotsRepoUrl = "http://$archivaHostId:$archivaPort/repository/snapshots"
//            url = uri(if (version.endsWith("SNAPSHOT")) snapshotsRepoUrl else internalRepoUrl)
//
//            logger.info("URL = \"$url\"")
//            isAllowInsecureProtocol = true
//            authentication {
//                create<BasicAuthentication>("basic")
//            }
//            credentials {
//                username = archivaUser
//                password = archivaPassword
//            }
//        }
//    }
//}
