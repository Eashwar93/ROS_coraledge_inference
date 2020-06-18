
if(NOT "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitinfo.txt" IS_NEWER_THAN "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout "https://github.com/tensorflow/tensorflow" "tensorflow"
    WORKING_DIRECTORY "/home/eashwara/edgetpu_video_inference/build/tensorflow/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/tensorflow/tensorflow'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout d855adfc5a0195788bf5f92c3c7352e638aa1109 --
  WORKING_DIRECTORY "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'd855adfc5a0195788bf5f92c3c7352e638aa1109'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitinfo.txt"
    "/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/eashwara/edgetpu_video_inference/build/tensorflow/src/tensorflow-stamp/tensorflow-gitclone-lastrun.txt'")
endif()

