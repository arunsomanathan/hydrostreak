Import("env")

# Build, Check and Test
env.AddCustomTarget(
    name="build",
    dependencies=None,
    actions=[
        "pio run -e native",
        "pio run -e nodemcuv2",
        "pio check -e native --fail-on-defect=high --fail-on-defect=medium --fail-on-defect=low",
        "pio check -e nodemcuv2 --fail-on-defect=high --fail-on-defect=medium --fail-on-defect=low",
        "pio run -t clean",
        "pio test -e native",
        "pio run -t gcovr",
        "pio run -t clean",
        "pio run -e native",
        "valgrind --error-exitcode=1 --leak-check=full --gen-suppressions=all --suppressions=./valgrind.supp  ./.pio/build/native/program"

    ],
    title="Build",
    description="Build, Check, Test and Coverage"
)

# Check and Test
env.AddCustomTarget(
    name="check-test",
    dependencies=None,
    actions=[
        "pio check",
        "pio test",
        "pio run -t gcovr"
    ],
    title="Check & Test",
    description="Check, Test and Coverage"
)

#Clean and Test
env.AddCustomTarget(
    name="clean-test",
    dependencies=None,
    actions=[
        "pio run -t clean",
        "pio test",
        "pio run -t gcovr"
    ],
    title="Clean Test",
    description="Clean and Test and Coverage"
)

#  Test & Coverage
env.AddCustomTarget(
    name="test",
    dependencies=None,
    actions=[
        "pio test",
        "pio run -t gcovr"
    ],
    title="Test",
    description="Test and Coverage"
)

#  Memory Leak test
env.AddCustomTarget(
    name="test-memory",
    dependencies=None,
    actions=[
        "pio run -t clean",
        "pio run -e native",
        "valgrind --error-exitcode=1 --leak-check=full --gen-suppressions=all --suppressions=./valgrind.supp  ./.pio/build/native/program"
    ],
    title="Check Memory Leak",
    description="Check for memory leak using valgrind"
)
