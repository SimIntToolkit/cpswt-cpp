import java.util.regex.Pattern
import java.net.URL
import java.security.MessageDigest
import java.math.BigInteger
import java.nio.file.Files
import java.nio.file.FileVisitResult
import java.nio.file.SimpleFileVisitor
import java.nio.file.Path
import java.nio.file.attribute.BasicFileAttributes

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

val sha512Digest: MessageDigest = MessageDigest.getInstance("SHA-512")
fun getSHA512Digest(inputFile: File): String {
    val sha512BigInt = BigInteger(1, sha512Digest.digest(inputFile.readBytes()))
    val stringBuilder = StringBuilder(sha512BigInt.toString(16))
    while(stringBuilder.length < 128) {
        stringBuilder.insert(0, "0")
    }
    return stringBuilder.toString()
}

fun getLibraryFilenames(contentListUrl: String, artifactId: String): Pair<String?, String?> {

    val libraryPattern = Pattern.compile("\"($artifactId.*?\\.so)\"")
    val librarySHA512Pattern = Pattern.compile("\"($artifactId.*?\\.so\\.sha512)\"")

    var libraryFileName: String? = null
    var librarySHA512FileName: String? = null

    val contentListBufferedReader = URL(contentListUrl).openStream().bufferedReader()
    contentListBufferedReader.use {
        var line = it.readLine()
        while(line != null && (libraryFileName == null || librarySHA512FileName == null)) {
            val libraryPatternMatcher = libraryPattern.matcher(line)
            val librarySHA512PatternMatcher = librarySHA512Pattern.matcher(line)
            if (libraryFileName == null && libraryPatternMatcher.find()) {
                libraryFileName = libraryPatternMatcher.group(1)
            }
            if (librarySHA512FileName == null && librarySHA512PatternMatcher.find()) {
                librarySHA512FileName = librarySHA512PatternMatcher.group(1)
            }
            line = it.readLine()
        }
    }

    return Pair(libraryFileName, librarySHA512FileName)
}

fun getLibrary(group: String, artifactId: String, version: String) {

    println("Updating \"$group:$artifactId:$version\"")

    // MAKE SURE lib DIRECTORY EXISTS
    val libDirectoryFile = File("${projectDir}/lib")
    if (!libDirectoryFile.isDirectory) {
        if (libDirectoryFile.exists()) {
            libDirectoryFile.delete()
        }
        libDirectoryFile.mkdir()
    }

    // CONTENT LIST URL
    val groupPath = group.replace(".", "/")
    val contentListUrl = "http://$archivaHostId:$archivaPort/repository/snapshots/$groupPath/$artifactId/$version"

    // GET SHARED OBJECT FILENAME AND THE FILENAME OF ITS SHA512 HASH
    val (libraryFileName, librarySHA512FileName) = getLibraryFilenames(contentListUrl, artifactId)

    if (libraryFileName == null) {
        println("Unable to download library file for artifact \"$group:$artifactId:$version\": not in content list")
        return
    }
    if (librarySHA512FileName == null) {
        println(
            "Unable to download library SHA512 file for artifact \"$group:$artifactId:$version\": not in content list"
        )
        return
    }

    // SHOULD LIBRARY FILE BE (RE)DOWNLOADED?
    var refreshLibraryFile = false

    val libraryFile = File(libDirectoryFile, libraryFileName)

    if (libraryFile.exists() && !libraryFile.isFile) {
        libraryFile.deleteRecursively()
        println("Library file \"${libraryFile.name}\" does not exists or is not a regular file.  Will download.")
        refreshLibraryFile = true
    }

    val librarySHA512File = File(libDirectoryFile, librarySHA512FileName)

    // GET PREVIOUS SHA512 HASH
    var previousSHA16 = ""
    if (librarySHA512File.exists()) {
        if (!librarySHA512File.isFile) {
            librarySHA512File.deleteRecursively()
        } else {
            previousSHA16 = librarySHA512File.readText()
        }
    }

    val libraryUrl = "$contentListUrl/$libraryFileName"
    val librarySHA512Url = "$contentListUrl/$librarySHA512FileName"

    // GET CURRENT SHA512 HASH, COMPARE TO PREVIOUS
    val currentSHA512 = URL(librarySHA512Url).openStream().bufferedReader().readText()
    if (currentSHA512 != previousSHA16) {
        librarySHA512File.delete()
        librarySHA512File.writeText(currentSHA512)
        if (previousSHA16.isEmpty()) {
            println("No previous checksum for library file \"${libraryFile.name}\".  Will download.")
        } else {
            println("Checksums for library file \"${libraryFile.name}\" do not match.  Will (re)download.")
        }
        refreshLibraryFile = true
    }
    // (RE)DOWNLOAD SHARED LIBRARY
    if (refreshLibraryFile) {
        println("(Re)downloading \"${libraryFile.name}\".")
        libraryFile.delete()
        libraryFile.writeBytes(URL(libraryUrl).readBytes())
    }

    // MAKE SURE SHARED LIBRARY IS NOT CORRUPTED
    var calculatedSHA512 = getSHA512Digest(libraryFile)
    if (currentSHA512 != calculatedSHA512) {
        if (refreshLibraryFile) {
            println("Library file \"${libraryFile.name}\" corrupted: checksum does not match calculated checksum!")
            return
        }
        println("Library file \"${libraryFile.name}\" does not have correct calculated checksum.  Redownloading.")
        libraryFile.writeBytes(URL(libraryUrl).readBytes())
        calculatedSHA512 = getSHA512Digest(libraryFile)
        if (currentSHA512 != calculatedSHA512) {
            println("Library file \"${libraryFile.name}\" corrupted: checksum does not match calculated checksum!")
            return
        }
    }

    // CREATE SYMLINK FOR DOWNLOADED LIBRARY
    val underscorePosition = artifactId.lastIndexOf("_")
    val linkName = if (underscorePosition < 0)  artifactId else artifactId.substring(0, underscorePosition)
    val linkFile = File(libDirectoryFile, "lib$linkName.so")

    if (linkFile.exists()) {
        linkFile.deleteRecursively()
    }

    println("Symlinking \"${libraryFile.name}\" to \"${linkFile.name}\"")
    Files.createSymbolicLink(linkFile.toPath(), libraryFile.toPath().fileName)
}

application {
    dependencies {
        implementation(group="org.cpswt", name="CPSWTConfig", version="0.7.0-SNAPSHOT")
        implementation(group="org.cpswt", name="rti-base-cpp", version="0.7.0-SNAPSHOT")
        implementation(group="org.cpswt", name="C2WConsoleLogger", version="0.7.0-SNAPSHOT")
        implementation(group="org.cpswt", name="core-cpp", version="0.7.0-SNAPSHOT")
        implementation(group="org.cpswt", name="SynchronizedFederate", version="0.7.0-SNAPSHOT")
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
            process.waitFor()
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
            is Gcc, is Clang -> includeDirectoryList.map { "-I$it" }
            is VisualCpp -> includeDirectoryList.map { "/I $it" }
            else -> listOf()
        }
    })
}

val archivaLibraryArtifactList = listOf(
    "org.cpswt:C2WConsoleLogger_debug:$version",
    "org.cpswt:rti-base-cpp_debug:$version",
    "org.cpswt:SynchronizedFederate_debug:$version"
)
tasks.register("DownloadLibraries") {
    doLast {
        for (archivaLibraryArtifact in archivaLibraryArtifactList) {
            val artifactComponentList = archivaLibraryArtifact.split(":")
            getLibrary(artifactComponentList[0], artifactComponentList[1], artifactComponentList[2])
        }
    }
}

tasks.withType(LinkExecutable::class.java).configureEach {
    dependsOn("DownloadLibraries")

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
        "INET", "RTI-NG_64", "FedTime_64", "boost_regex", "boost_program_options"
    )

    val linkLibraryList = listOf(
        "oppmain", "oppcmdenv", "oppenvir", "oppqtenv", "opplayout", "oppsim", "dl", "stdc++", "jvm"
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
//            group = "org.cpswt"
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
