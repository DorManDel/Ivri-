"""Build the Ivri++ browser demos from the repository's C++ examples."""

import argparse
import base64
import json
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
EXAMPLES = {
    "basics": (
        "01_basics.cpp",
        "הדוגמה מוסיפה מספר לווקטור, ממיינת אותו ומדפיסה את הסכום.",
    ),
    "terminal": (
        "03_hebrew_terminal.cpp",
        "המסוף מקבל פקודות בעברית, שומר מספרים ומחשב סכום וממוצע.",
    ),
}
TOKEN = re.compile(r'''//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|[^\W\d]\w*''')


def build(zig: str, output: Path) -> None:
    header = (ROOT / "include" / "ivri" / "core.hpp").read_text(encoding="utf-8")
    macros = dict(re.findall(r"^#define (\w+) ([^\n]+)$", header, re.MULTILINE))
    samples = {}
    with tempfile.TemporaryDirectory(prefix="ivri-playground-") as temporary:
        for key, (filename, description) in EXAMPLES.items():
            source = ROOT / "examples" / filename
            wasm = Path(temporary) / f"{key}.wasm"
            subprocess.run(
                [zig, "c++", "-target", "wasm32-wasi", "-std=c++17", "-O2", "-s",
                 "-fno-exceptions", "-I", str(ROOT / "include"), str(source),
                 "-o", str(wasm)],
                check=True,
            )
            hebrew = source.read_text(encoding="utf-8")
            samples[key] = {
                "file": filename,
                "summary": description,
                "hebrew": hebrew,
                "cpp": TOKEN.sub(lambda match: macros.get(match[0], match[0]), hebrew),
                "wasm": base64.b64encode(wasm.read_bytes()).decode("ascii"),
            }

    output.mkdir(parents=True, exist_ok=True)
    for asset in (HERE / "web").iterdir():
        shutil.copy2(asset, output / asset.name)
    payload = json.dumps({"keywords": macros, "examples": samples}, ensure_ascii=False)
    (output / "samples.js").write_text(f"globalThis.ivriSamples = {payload};\n", encoding="utf-8")
    print(f"Open {output / 'index.html'} in a browser.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--zig", default="zig", help="Path to Zig 0.15.2")
    parser.add_argument("--output", type=Path, default=HERE / "dist")
    args = parser.parse_args()
    build(args.zig, args.output.resolve())
