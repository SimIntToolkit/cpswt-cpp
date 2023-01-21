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

import java.nio.file.FileVisitResult
import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.SimpleFileVisitor
import java.nio.file.attribute.BasicFileAttributes
import java.io.FileWriter
import org.json.JSONObject

import java.util.stream.Collectors


plugins {
    `cpp-application`
//    `maven-publish`
}

val inetHome: String? = System.getenv("INET_HOME")
val javaHome: String? = System.getenv("JAVA_HOME")
val rtiHome: String? = System.getenv("RTI_HOME")

val archivaUser: String by project
val archivaPassword: String by project
val version: String by project
val archivaHostId: String by project
val archivaPort: String by project

val omnetppHome: String by project

class MessageFileVisitor: SimpleFileVisitor<Path>() {
    private val messageFileSet = HashSet<File>()
    private val messageSourceFileSet = HashSet<File>()
    private val messageSourceDirectorySet = HashSet<File>()
    private val messageHeaderFileSet = HashSet<File>()

    private val messageHeaderDirectorySet = HashSet<File>()

    override fun visitFile(p0: Path?, p1: BasicFileAttributes?): FileVisitResult {
        if (p0 != null) {
            val file = p0.toFile()
            if (file.name.endsWith(".msg")) {
                messageFileSet.add(file)

                val parentDirFile = file.parentFile.absoluteFile
                val fileBaseName = file.name.substring(0, file.name.length - 4)

                val sourceFile = File(parentDirFile, "${fileBaseName}_m.cpp")
                messageSourceFileSet.add(sourceFile)
                messageSourceDirectorySet.add(parentDirFile)

                val headerFile = File(parentDirFile, "${fileBaseName}_m.h")
                messageHeaderFileSet.add(headerFile)

                messageHeaderDirectorySet.add(parentDirFile)
                messageHeaderDirectorySet.add(parentDirFile.parentFile)
            }
        }
        return FileVisitResult.CONTINUE
    }
    fun getMessageFileList(): List<File> {
        return messageFileSet.toList().sorted()
    }
    fun getMessageSourceFileList(): List<File> {
        return messageSourceFileSet.toList().sorted()
    }
    fun getMessageHeaderFileList(): List<File> {
        return messageHeaderFileSet.toList().sorted()
    }
    fun getSourceFileList(): List<File> {
        return messageSourceFileSet.toList().sorted()
    }
    fun getHeaderDirectoryList(): List<File> {
        return messageHeaderDirectorySet.toList().sorted()
    }

}

val projectPath: Path = project.projectDir.toPath()
val localMessageFileVisitor = MessageFileVisitor()
var messageFileVisitorFlag = false

fun getMessageFileVisitor(): MessageFileVisitor {
    if (!messageFileVisitorFlag) {
        Files.walkFileTree(projectPath, localMessageFileVisitor)
    }
    return localMessageFileVisitor
}

application {
    dependencies {
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="CPSWTConfig", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="rti-base-cpp", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="C2WConsoleLogger", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="core-cpp", version=version)
        implementation(group="edu.vanderbilt.vuisis.cpswt", name="SynchronizedFederate", version=version)
    }
    source.from(
        file("src/hla/c++"),
        file("src/main/c++"),
        getMessageFileVisitor().getHeaderDirectoryList()
    )
    privateHeaders.from(
        file("src/hla/include"),
        file("src/main/include"),
        file("$omnetppHome/include")
    )
    targetMachines.set(listOf(machines.linux.x86_64))
}

tasks.register("processMessageFiles") {

    val messageFileVisitor = getMessageFileVisitor()
    val messageFileList = messageFileVisitor.getMessageFileList()

    inputs.files(messageFileList)
    outputs.files(messageFileVisitor.getMessageSourceFileList())
    outputs.files(messageFileVisitor.getMessageHeaderFileList())

    doLast {
        for(file in messageFileList) {
            val processBuilder = ProcessBuilder("opp_msgc", "-s", "_m.cpp", file.absolutePath)
            val process = processBuilder.start()
            val exitStatus = process.waitFor()
            if (exitStatus != 0) {
                val errorMessage = process.getErrorStream().bufferedReader(Charsets.UTF_8).use {
                    it.lines().collect(Collectors.joining())
                }
                val exceptionMessage =
                    "\"${processBuilder.command().joinToString(" ")}\": error \"${errorMessage}\""
                throw TaskExecutionException(this, Exception(exceptionMessage))
            }
        }
    }
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
                Files.createSymbolicLink(libraryFile.toPath(), File(fileName).toPath())
            }
        }

        val executableFileString = installedExecutable.get().asFile.absolutePath

        val topLevelJSONObject = JSONObject();
        topLevelJSONObject.put("libraryDirectoryString", libraryDirectory.absolutePath);
        topLevelJSONObject.put("installedExecutableString", executableFileString);

        val jsonFile = File(project.projectDir, "OmnetFederateInfo.json")
        val fileWriter = FileWriter(jsonFile)
        fileWriter.use {
            fileWriter.write(topLevelJSONObject.toString(4))
        }
    }
}

tasks.withType(CppCompile::class.java).configureEach {
    dependsOn("processMessageFiles")

    val messageFileVisitor = getMessageFileVisitor()

    val includeDirectoryList = listOf("$rtiHome/include/hla13", "$inetHome/src") +
            messageFileVisitor.getHeaderDirectoryList().map { it.toString() }

    compilerArgs.addAll(toolChain.map { toolChain ->
        when (toolChain) {
            is Gcc, is Clang -> includeDirectoryList.map { "-I$it" } + listOf("-Wno-deprecated")
            is VisualCpp -> includeDirectoryList.map { "/I $it" }
            else -> listOf()
        }
    })
}

tasks.withType(LinkExecutable::class.java).configureEach {

    // LINKER OPTIONS OBTAINED FROM "make -n" ON Makefile
    // THESE ARE USED AS ARBUMENTS TO THE LINKER IN THIS BUILD SCRIPT
//    val linkerArgList = listOf(
//        "-Wl,-rpath,$omnetppHome/lib",
//        "-Wl,-rpath,/lib",
//        "-Wl,-rpath,.",
//        "-Wl,--export-dynamic",
//        "-L$omnetppHome/lib",
//        "-Wl,--no-as-needed",
//        "-Wl,--whole-archive",
//        "-L$inetHome/src",
//        "-L$rtiHome/lib/gcc4",
//        "-L$javaHome/jre/lib/amd46/server",
//        "-lINET",
//        "-lRTI-NG_64",
//        "-lFedTime_64",
//        "-lboost_regex",
//        "-lboost_program_options",
//        "-Wl,-rpath,$inetHome/src",
//        "-Wl,-rpath,$rtiHome/lib/gcc64",
//        "-Wl,-rpath,$javaHome/jre/lib/amd46/server",
//        "-Wl,--no-whole-archive",
//        "-loppmain",
//        "-Wl,-u,_cmdenv_lib",
////        "-Wl,--no-as-needed",  // REPEAT -- NOT NEEDED
//        "-loppcmdenv",
//        "-loppenvir",
//        "-Wl,-u,_qtenv_lib",
////        "-Wl,--no-as-needed",  // REPEAT -- NOT NEEDED
//        "-Wl,-rpath-link=/usr/lib/x86_64-linux-gnu",
//        "-loppqtenv",
////        "-loppenvir",  // REPEAT -- NOT NEEDED
//        "-lopoplayout",
//        "-loppsim",
//        "-ldl",
//        "-lstdc++"
//    )

    val linkDirectoryList = listOf(
        "$projectDir/lib",
        "$omnetppHome/lib",
        "$inetHome/src",
        "$rtiHome/lib/gcc4",
        "$javaHome/jre/lib/amd64/server"
    )

    val rpathDirectoryList = linkDirectoryList + listOf("/lib", ".")

    val rpathLinkDirectoryList = listOf("/usr/lib/x86_64-linux-gnu")

    val forceUndefinedSymbolList = listOf("_cmdenv_lib", "_qtenv_list")

    val linkerOptionList = listOf("--export-dynamic", "--no-as-needed")

    val linkWholeLibraryList = listOf(
        "INET", "RTI-NG_64", "FedTime_64"
    )

    val linkLibraryList = listOf(
        "oppmain", "oppcmdenv", "oppenvir", "oppqtenv", "opplayout", "oppsim", "dl", "stdc++", "jvm", "jsoncpp",
        "boost_regex", "boost_program_options", "boost_log_setup", "boost_log", "boost_system",
        "boost_thread", "pthread"
    )

    val linkCompleteLibraryList = linkWholeLibraryList + linkLibraryList

    val rpathOptionDirectoryList = rpathDirectoryList.map { "-rpath,$it" }
    val rpathLinkOptionDirectoryList = rpathLinkDirectoryList.map { "-rpath-link=$it" }
    val forceUndefinedOptionSymbolList = forceUndefinedSymbolList.map { "-u,$it"}

    val gccLinkerList = rpathOptionDirectoryList + rpathLinkOptionDirectoryList + forceUndefinedOptionSymbolList +
            linkerOptionList
    val gccLinkerOptionList = gccLinkerList.map { "-Wl,$it"}

    val linkDirectoryOptionList = linkDirectoryList.map { "-L$it" }

    val linkWholeLibraryOptionList = linkWholeLibraryList.map { "-l$it" }
    val linkLibraryOptionList = linkLibraryList.map { "-l$it" }

    val gccCompleteLinkerOptionList = gccLinkerOptionList + linkDirectoryOptionList +
            listOf("-Wl,--whole-archive") + linkWholeLibraryOptionList + listOf("-Wl,--no-whole-archive") +
            linkLibraryOptionList

    val windowsLinkDirectoryOptionList = linkDirectoryOptionList.map { "/LIBPATH $it" }
    val windowsCompleteLibraryOptionList = linkCompleteLibraryList.map { "/link $it" }
    val windowsCompleteLinkerOptionList = windowsLinkDirectoryOptionList + windowsCompleteLibraryOptionList

    println(gccCompleteLinkerOptionList)

    linkerArgs.addAll(toolChain.map { toolChain ->
        when(toolChain) {
            is Gcc, is Clang -> gccCompleteLinkerOptionList
            is VisualCpp -> windowsCompleteLinkerOptionList
            else -> listOf()
        }
    })
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
//            url = uri(if (version.toString().endsWith("SNAPSHOT")) snapshotsRepoUrl else internalRepoUrl)
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
