#
#  Copyright (C) 2025 Texas Instruments Incorporated.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#


#########################################################################
#                               Params                                  #
#########################################################################
profile_list="debug release"
device_list="am64x am243x"


#########################################################################
#                               Log files                               #
#########################################################################
log_dir=$GITHUB_WORKSPACE/logs
build_dir=$GITHUB_WORKSPACE/mcu_plus_sdk
pr_checkout_dir=$GITHUB_WORKSPACE/pr_checkout
build_log_file=build.log
build_error_log_file=build_error.log


 #########################################################################
 #                               Functions                               #
 #########################################################################
print_time_diff() {
    local end_time=$(date +%s)
    local start_time=$1
    local deltatime=$(( end_time-start_time ))
    local hours=$(( deltatime/3600 ))
    local minutes=$(( deltatime/60 ))
    local minutes=$(( minutes%60 ))
    local seconds=$(( deltatime%60 ))
    printf "$2: %d:%02d:%02d\n" $hours $minutes $seconds
    printf " \n"
}

make_folders() {
    echo "Making required folder..."

    mkdir -p ${log_dir}
    for device in ${device_list}
    do
        mkdir -p ${log_dir}/${device}
    done
    echo "Making required folder ... Done"
    echo " "
}

proc=`nproc`
repo_init() {
    mkdir workarea 
    cd workaread
    echo "Doing repo init and sync ..."
    local start_time=`date +%s`
    sudo apt-get update
    sudo apt-get -y install repo
    
    repo init -u https://github.com/TexasInstruments/mcupsdk-manifests.git -m all/dev.xml -b main  --depth=1
    repo sync -j${proc} -q

    #Show the current branch/git status
    repo forall -c "pwd;git branch -vv | cut -d ' ' -f 1-4"

    print_time_diff $start_time "Repo Init Time"
    echo "Doing repo init and sync ... Done"
    echo " "

    #Copy the PR checkout to mcu_plus_sdk directory
    

    #List the changed files in this PR
    pushd ${build_dir}
    
    git fetch origin pull/${PR_NUMBER}/head:pr_${PR_NUMBER}
    git switch pr_${PR_NUMBER}
    git log --oneline -n5
    popd

}

download_components() {
    echo "Downloading Components ..."

    local start_time=`date +%s`

    mkdir ${HOME}/ti

    find ./mcupsdk_setup -name "*.sh" -execdir chmod u+x {} +
    ./mcupsdk_setup/am64x/download_components.sh

    print_time_diff $start_time "Download Components Time"
    echo "Downloading Components ... Done"
    echo " "
}

check_logs() {
    local device=$1

    local build_log=${log_dir}/${device}/build.log
    local build_error_log=${log_dir}/${device}/build_error.log
    if [ -e ${build_error_log} ]; then
        if [ -s ${build_error_log} ]; then
            echo "Build for SOC $device failed ...."
            echo 
            echo
            cat ${build_error_log}
            exit 1
        fi
    fi
}

build_sdk() {
    echo "Build SDK ..."
    local start_time=`date +%s`

    pushd ${build_dir}

    #Scrub build files
    for device in ${device_list}
    do
        build_log=${log_dir}/${device}/build.log
        build_error_log=${log_dir}/${device}/build_error.log
        echo "    Scrub Build Files for DEVICE:${device} ..."
        make -s ${jobs_option} scrub DEVICE=${device} 1>>${build_log} 2>>${build_error_log}
        make -s gen-buildfiles-clean DEVICE=${device} 1>>${build_log} 2>>${build_error_log}
        echo "    Scrub Build Files for DEVICE:${device} completed!!"
        check_logs $device

        echo "    Generate Build Files for DEVICE:${device} ..."
        make -s gen-buildfiles DEVICE=${device} 1>>${build_log} 2>>${build_error_log}
        echo "    Generate Build Files for DEVICE:${device} completed!!"
        check_logs $device

        for profile in ${profile_list}
        do
            echo "    Building for DEVICE:${device} PROFILE:${profile} ..."
            make -s -j${proc} all DEVICE=${device} PROFILE=${profile} 1>>${build_log} 2>>${build_error_log}
            echo "    Building for DEVICE:${device} PROFILE:${profile} completed!!"
            check_logs $device
        done
    done

    popd

    print_time_diff $start_time "Build Time"
    echo "Build SDK ... Done"
}

#########################################################################
#                           Script run                                  #
#########################################################################
make_folders
repo_init
download_components
build_sdk