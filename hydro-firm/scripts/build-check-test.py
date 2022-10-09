Import("env")

# Build, Check and Test
env.AddCustomTarget(
    name="build",
    dependencies=None,
    actions=[
        "pio run",
        "pio check",
        "pio run -t clean",
        "pio test",
        "pio run -t gcovr"
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
    title="Clean Test",
    description="Clean and Test and Coverage"
)
