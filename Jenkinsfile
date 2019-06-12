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
        stage('test backslash') {
          steps {
            sh './42shtester/42shtester.rb 42sh backslash'
          }
        }
        stage('test pipe') {
          steps {
            sh './42shtester/42shtester.rb 42sh pipe'
          }
        }
        stage('test hard') {
          steps {
            sh './42shtester/42shtester.rb 42sh hard'
          }
        }
        stage('test aggreg') {
          steps {
            sh './42shtester/42shtester.rb 42sh aggreg'
          }
        }
        stage('test cd') {
          steps {
            sh './42shtester/42shtester.rb 42sh cd'
          }
        }
        stage('test echo') {
          steps {
            sh './42shtester/42shtester.rb 42sh echo'
          }
        }
        stage('test exit') {
          steps {
            sh './42shtester/42shtester.rb 42sh exit'
          }
        }
        stage('test export') {
          steps {
            sh './42shtester/42shtester.rb 42sh export'
          }
        }
        stage('test fc ') {
          steps {
            sh './42shtester/42shtester.rb 42sh fc'
          }
        }
        stage('test hash') {
          steps {
            sh './42shtester/42shtester.rb 42sh hash'
          }
        }
        stage('test mixed_commands') {
          steps {
            sh './42shtester/42shtester.rb 42sh mixed_commands'
          }
        }
        stage('test multi_command') {
          steps {
            sh './42shtester/42shtester.rb 42sh multi_command'
          }
        }
        stage('test multiline') {
          steps {
            sh './42shtester/42shtester.rb 42sh multiline'
          }
        }
        stage('test redirection') {
          steps {
            sh './42shtester/42shtester.rb 42sh redirections'
          }
        }
        stage('test signal') {
          steps {
            sh './42shtester/42shtester.rb 42sh signal'
          }
        }
        stage('test test') {
          steps {
            sh './42shtester/42shtester.rb 42sh test'
          }
        }
      }
    }
  }
}