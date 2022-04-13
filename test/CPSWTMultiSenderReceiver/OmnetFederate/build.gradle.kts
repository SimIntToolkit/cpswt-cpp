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

import java.io.FileReader

import org.json.JSONObject
import org.json.JSONTokener


val javaHome = System.getenv("JAVA_HOME")
val rtiHome = System.getenv("RTI_HOME")
val omnetppCpswtHome = System.getenv("OMNETPP_CPSWT_HOME")
val inetHome = System.getenv("INET_HOME")

val archivaHostId: String by project
val archivaPort: String by project

tasks.register<Exec>("run") {
    if ( omnetppCpswtHome == null || omnetppCpswtHome.isEmpty() ) {
        throw GradleException("OMNET_CPSWT_HOME environment variable not set")
    }
    val omnetFederateInfoJsonFile = File(omnetppCpswtHome, "OmnetFederateInfo.json")
    val fileReader = FileReader(omnetFederateInfoJsonFile)
    val omnetFederateInfoJson = JSONObject(JSONTokener(fileReader))

    val installedExecutableString = omnetFederateInfoJson.getString("installedExecutableString")
    val libraryDirectoryString = omnetFederateInfoJson.getString("libraryDirectoryString")

    val libraryPathList = listOf("$javaHome/jre/lib/amd64/server", libraryDirectoryString)
    environment.put(
        "LD_LIBRARY_PATH", libraryPathList.joinToString(":")
    )

    val omnet_ini_file = File(project.projectDir, "omnetpp.ini")

    val inetNedFilesDirectory = File(inetHome, "src")
    val projectNedFilesDirectory = File(project.projectDir, "NedFiles")
    val mainNedFilesDirectory = File(omnetppCpswtHome, "src/main/resources")
    val hlaNedFilesDirectory = File(omnetppCpswtHome, "src/hla/resources")

    val nedPathList = listOf(
        inetNedFilesDirectory.absolutePath,
        projectNedFilesDirectory.absolutePath,
        mainNedFilesDirectory.absolutePath,
        hlaNedFilesDirectory.absolutePath
    )

    val nedPath = nedPathList.joinToString(separator=":")
    workingDir = project.projectDir

    commandLine = listOf(
        installedExecutableString, "-f", omnet_ini_file.absolutePath, "-n", nedPath
    )
    print("command:\n" + commandLine.joinToString(separator=" "))
}

var spawnedProcess: Process? = null

fun spawnProcess() {
    val runTask = tasks.named<Exec>("run").get()

    val runTaskEnvironment = runTask.environment
    val runTaskWorkingDir = runTask.workingDir

    val runTaskCommandLine = runTask.commandLine

    val xtermCommandList = listOf(
        "xterm", "-geometry", "220x80", "-fg", "black", "-bg", "white", "-e", runTaskCommandLine.joinToString(" ")
    )

    val processBuilder = ProcessBuilder(xtermCommandList)
    processBuilder.directory(runTaskWorkingDir)

    val environment = processBuilder.environment()
    for(entry in runTaskEnvironment.entries) {
        environment.put(entry.key, entry.value.toString())
    }

    spawnedProcess = processBuilder.start()
}

tasks.register("runAsynchronous") {
    doLast {
        spawnProcess()
    }
}

tasks.register("killFederate") {
    doLast {
        spawnedProcess?.destroy()
    }
}
