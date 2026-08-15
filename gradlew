#!/bin/bash
APP_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
GRADLE_OPTS="-Xmx2048m"
export GRADLE_OPTS
java -classpath "$APP_PATH/gradle/wrapper/gradle-wrapper.jar" org.gradle.wrapper.GradleWrapperMain "$@"
