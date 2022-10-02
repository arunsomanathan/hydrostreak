import os
Import("env")


def gcovr_generate_html(*arg, **kwargs):
    print("Generating Coverage HTML reports")
    os.makedirs(".pio/build/native/coverage/reports/", exist_ok=True)
    return env.Execute(
        "gcovr --add-tracefile .pio/build/native/coverage/*.json --html-details .pio/build/native/coverage/reports/coverage.html")


env.AddCustomTarget(
    "gcovr-html",
    None,
    gcovr_generate_html,
    title="gcovr-html",
    description="Generate gcovr html report")


def gcovr_generate_json(source, target, env):
    print("Generating Coverage JSON")
    os.makedirs(".pio/build/native/coverage/", exist_ok=True)
    return env.Execute(
        "gcovr -e 'test/' -e '.pio/libdeps/' --json .pio/build/native/coverage/test_coverage.json")


env.AddCustomTarget(
    "gcovr-json",
    None,
    gcovr_generate_json,
    title="gcovr-json",
    description="Generte gcovr json file")


def gcovr_check(source, target, env):
    print("Check Coverage")
    return env.Execute(
        "gcovr --add-tracefile .pio/build/native/coverage/*.json --fail-under-line 100 --fail-under-branch 85")


env.AddCustomTarget(
    "gcovr-check",
    None,
    gcovr_check,
    title="gcovr-check",
    description="Verify code coverage")
