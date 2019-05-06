pipeline {
  agent any
  stages {
    stage('make') {
      steps {
        sh 'make'
      }
    }
    stage('pull test') {
      steps {
        sh 'rm -rf 42shtester'
        sh 'gem install --user-install diffy'
        sh 'git clone https://gitea.xanar.net/Shamoka/42shtester'
      }
    }
    stage('test simple_quote') {
      parallel {
        stage('test simple_quote') {
          steps {
            sh './42shtester/42shtester.rb 42sh simple_quote'
          }
        }
        stage('test double_quote') {
          steps {
            sh './42shtester/42shtester.rb 42sh double_quote'
          }
        }
        stage('test expand') {
          steps {
            sh './42shtester/42shtester.rb 42sh expand'
          }
        }
      }
    }
  }
}