plugins {
    alias(libs.plugins.kotlin.jvm)
    alias(libs.plugins.jmh)
}

dependencies {
    implementation(project(":extra"))
    implementation("io.github.quillraven.fleks:Fleks:2.14")
}

kotlin {
    jvmToolchain(21)

    sourceSets.named("jmh") {
//        kotlin.srcDir("../extra/src/commonTest/kotlin/com/cws/extra/test")
    }
}

jmh {
    jmhVersion.set("1.37")
    warmupIterations.set(5)
    iterations.set(10)
    fork.set(2)
    timeOnIteration.set("1s")
    warmup.set("1s")
    resultFormat.set("JSON")
    resultsFile.set(layout.buildDirectory.file("results/jmh/results.json"))
    profilers.set(listOf("gc"))
}

tasks.register<JavaExec>("jmhSmoke") {
    group = "benchmark"
    description = "Runs one short fork of the ECS JMH comparison."
    dependsOn("jmhJar")

    classpath(tasks.named<Jar>("jmhJar").flatMap { it.archiveFile })
    mainClass.set("org.openjdk.jmh.Main")
    args(
        "EcsComparisonBenchmark",
        "-p", "entityCount=10000,100000",
        "-p", "operation=mixed",
        "-wi", "2",
        "-i", "3",
        "-w", "250ms",
        "-r", "250ms",
        "-f", "1",
        "-prof", "gc",
    )
}
