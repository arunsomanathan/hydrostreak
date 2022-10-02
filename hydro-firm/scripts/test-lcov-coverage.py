import os

Import("env")


def generateCoverageInfo(source, target, env):
    for file in os.listdir("test"):
        os.system(".pio/build/native/program test/"+file)
    os.makedirs(".pio/build/native/coverage", exist_ok=True)
    os.system(
        "lcov -d .pio/build/native/ -c -o .pio/build/native/coverage/lcov.info")
    os.system(
        "lcov --remove .pio/build/native/coverage/lcov.info '*/googlemock/*' '*/test/*' '/usr/include/*' '*/gtest/*' '*/gtest*' -o .pio/build/native/coverage/filtered_lcov.info")
    os.system(
        "genhtml -o .pio/build/native/coverage/report --demangle-cpp .pio/build/native/coverage/filtered_lcov.info")


env.AddPostAction(".pio/build/native/program", generateCoverageInfo)
