cmake_minimum_required(VERSION 3.22)

project(redalert_ios LANGUAGES C CXX OBJC)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
    message(FATAL_ERROR "Configure the iOS target with -DCMAKE_SYSTEM_NAME=iOS, or use scripts/build_ios_debug.sh.")
endif()

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "16.0" CACHE STRING "" FORCE)
endif()

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE)

set(RA95_IOS_BUNDLED_ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}/../assets/redalert" CACHE PATH "Local Red Alert assets to bundle into the iOS debug app.")

if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/third_party/SDL/CMakeLists.txt")
    message(FATAL_ERROR "Missing SDL2 sources at ios/third_party/SDL. Run scripts/build_ios_debug.sh to fetch them.")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/third_party/SDL" "${CMAKE_BINARY_DIR}/SDL2")

include("${CMAKE_CURRENT_LIST_DIR}/../cmake/ra95_common.cmake")

set(RA95_IOS_ASSETS_CATALOG "${CMAKE_CURRENT_LIST_DIR}/Assets.xcassets")
set_source_files_properties(${RA95_IOS_ASSETS_CATALOG} PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources
)

add_executable(redalert_ios MACOSX_BUNDLE
    "${RA95_REPO_ROOT}/PORT/IOS/src/ios_app_delegate.m"
    "${RA95_REPO_ROOT}/PORT/IOS/src/ios_main.cpp"
    ${RA95_PLATFORM_SDL_SOURCES}
    ${RA95_SOURCES}
    ${RA95_SUPPORT_SOURCES}
    ${RA95_IOS_ASSETS_CATALOG}
)

ra95_configure_target(redalert_ios)

target_compile_definitions(redalert_ios PRIVATE
    RA_IOS
    RA_MOBILE_TOUCH
)

target_include_directories(redalert_ios PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/third_party/SDL/src/video/uikit"
)

if(TARGET SDL2::SDL2main)
    set(RA95_SDLMAIN_TARGET SDL2::SDL2main)
elseif(TARGET SDL2main)
    set(RA95_SDLMAIN_TARGET SDL2main)
else()
    message(FATAL_ERROR "SDL2main CMake target was not created")
endif()

if(TARGET SDL2::SDL2-static)
    set(RA95_SDL_TARGET SDL2::SDL2-static)
elseif(TARGET SDL2-static)
    set(RA95_SDL_TARGET SDL2-static)
elseif(TARGET SDL2::SDL2)
    set(RA95_SDL_TARGET SDL2::SDL2)
elseif(TARGET SDL2)
    set(RA95_SDL_TARGET SDL2)
else()
    message(FATAL_ERROR "SDL2 CMake target was not created")
endif()

target_link_libraries(redalert_ios PRIVATE
    ${RA95_SDLMAIN_TARGET}
    ${RA95_SDL_TARGET}
)

if(TARGET SDL2main)
    set_target_properties(SDL2main PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    )
endif()

if(TARGET SDL2-static)
    set_target_properties(SDL2-static PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    )
endif()

if(NOT DEFINED RA_IOS_BUNDLE_IDENTIFIER)
    if(DEFINED ENV{RA_IOS_BUNDLE_IDENTIFIER})
        set(RA_IOS_BUNDLE_IDENTIFIER "$ENV{RA_IOS_BUNDLE_IDENTIFIER}" CACHE STRING "Bundle identifier")
    else()
        set(RA_IOS_BUNDLE_IDENTIFIER "com.raport.redalert" CACHE STRING "Bundle identifier")
    endif()
endif()

set_target_properties(redalert_ios PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/Info.plist.in"
    XCODE_ATTRIBUTE_CODE_SIGN_STYLE "Automatic"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${RA_IOS_BUNDLE_IDENTIFIER}"
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
)

if(DEFINED ENV{RA_IOS_DEVELOPMENT_TEAM} AND NOT DEFINED RA_IOS_DEVELOPMENT_TEAM)
    set(RA_IOS_DEVELOPMENT_TEAM "$ENV{RA_IOS_DEVELOPMENT_TEAM}" CACHE STRING "Development team")
endif()

if(RA_IOS_DEVELOPMENT_TEAM)
    set_target_properties(redalert_ios PROPERTIES
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${RA_IOS_DEVELOPMENT_TEAM}"
    )
endif()

add_custom_command(TARGET redalert_ios POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "$<TARGET_BUNDLE_DIR:redalert_ios>/assets"
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${RA95_IOS_BUNDLED_ASSETS_DIR}" "$<TARGET_BUNDLE_DIR:redalert_ios>/assets/redalert"
    COMMENT "Copying local Red Alert assets into the iOS debug bundle"
)
