// Do NOT place within the pipeline block 
properties([ [ $class: 'ThrottleJobProperty',
               categories: ['ci_cpswt_build'], 
               limitOneJobWithMatchingParams: false,
               maxConcurrentPerNode: 1,
               maxConcurrentTotal: 1,
               paramsToUseForLimit: '',
               throttleEnabled: true,
               throttleOption: 'category' ] ])

pipeline {
    agent any
    triggers {
        pollSCM('*/1 * * * *') // poll the SCM every 1 minutes
    }

    stages {
        stage('Clone repository') {
            steps {
                echo 'Cloning cpswt-cpp...'
                deleteDir() // Delete workspace before cloning
                sh 'git clone git@github.com:justinyeh1995/CI_with_Jenkins.git'
            }
        }
        stage('Build cpswt-cpp image') {
            steps {
                echo 'Start a Docker Container for this experiment, which should start the experiment and a archiva server, a inet server, and a omnet++ server..'
                // sh 'if docker images | grep -q cpswt-cpp:latest; then docker rmi cpswt-cpp:latest; fi' // Remove the existing image with the name:tag cpswt-cpp:latest
                dir("CI_with_Jenkins/cpswt-cpp") {
                    sh 'docker build -t cpswt-cpp:latest -f Dockerfile --build-arg ssh_prv_key="$(cat ~/.ssh/id_rsa)" --build-arg ssh_pub_key="$(cat ~/.ssh/id_rsa.pub)" .'
                }
            }
        }
        stage('Deploy image') {
            steps {
                echo 'Run the Docker Container inside Jenkins container'
                //sh 'if docker ps -a | grep -q cpswt-cpp; then docker stop cpswt-cpp; fi' //Stop the existing container with the name cpswt-cpp
                //sh 'if docker ps -a | grep -q cpswt-cpp; then docker rm -f cpswt-cpp; fi' // Remove the existing container with the name cpswt-cpp
                sh 'docker run \
                        --name cpswt-cpp \
			-p 8082:8080 \
                        cpswt-cpp:latest'
            }
        }
        stage('Wait for cpswt-cpp container to stop') {
            options {
                timeout(time: 30, unit: 'MINUTES')
            }
            steps {
                echo 'Wait for container to stop'
                sh 'docker wait cpswt-cpp'
            }
        }
        stage('Archive loggings') {
            steps {
                echo 'Archiving cpswt-cpp results...'
                sh 'docker logs cpswt-cpp > cpswt-cpp.log'
                archiveArtifacts artifacts: 'cpswt-cpp.log', fingerprint: true
            }
        }
    }

    post {
        always {
            echo 'This will always run'
            emailext body: "${currentBuild.currentResult}: Job ${env.JOB_NAME} build ${env.BUILD_NUMBER}\n More info at: ${env.BUILD_URL}",
                    recipientProviders: [[$class: 'DevelopersRecipientProvider'], [$class: 'RequesterRecipientProvider']],
                    subject: "Jenkins Build ${currentBuild.currentResult}: Job ${env.JOB_NAME}",
                    attachLog: true,
                    attachmentsPattern: 'cpswt-cpp.log'
            // echo 'Tearing Down the image & container....'
            sh 'rm -rf cpswt-cpp'
            sh 'docker rm -f cpswt-cpp'
            sh 'docker rmi cpswt-cpp:latest'
        }
    }	
}
