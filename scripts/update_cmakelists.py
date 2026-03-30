#!/usr/bin/env python3
"""
Scan kuBig2026 tree for directories that contain a CMakeLists.txt
and update the AUTO_SUBDIRS block in the root CMakeLists.txt with
add_subdirectory(relative/path) lines.

Run: python3 scripts/update_cmakelists.py
"""
import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CMAKE_FILE = ROOT / 'CMakeLists.txt'
TARGET_DIR = ROOT / 'kuBig2026'

def find_subdirs_with_cmake(base: Path):
    results = []
    for dirpath, dirnames, filenames in os.walk(base):
        if 'CMakeLists.txt' in filenames:
            p = Path(dirpath).relative_to(ROOT)
            # skip top-level kuBig2026 if it is the base project itself
            if str(p) == 'kuBig2026':
                continue
            results.append(str(p).replace('\\', '/'))
    results.sort()
    return results


def build_block(lines):
    out = ['# AUTO_SUBDIRS_BEGIN']
    for l in lines:
        out.append(f'add_subdirectory({l})')
    out.append('# AUTO_SUBDIRS_END')
    return '\n'.join(out)


def update_cmakelists():
    if not CMAKE_FILE.exists():
        print('Root CMakeLists.txt not found:', CMAKE_FILE)
        return 1
    txt = CMAKE_FILE.read_text(encoding='utf-8')
    before, marker_begin, after = None, None, None
    if '# AUTO_SUBDIRS_BEGIN' in txt and '# AUTO_SUBDIRS_END' in txt:
        pre, rest = txt.split('# AUTO_SUBDIRS_BEGIN', 1)
        _, post = rest.split('# AUTO_SUBDIRS_END', 1)
        before = pre
        after = post
    else:
        print('Markers not found in CMakeLists.txt; please ensure markers exist')
        return 1

    subdirs = find_subdirs_with_cmake(TARGET_DIR)
    block = build_block(subdirs)

    newtxt = before + block + after
    CMAKE_FILE.write_text(newtxt, encoding='utf-8')
    print('Updated', CMAKE_FILE)
    return 0

if __name__ == '__main__':
    raise SystemExit(update_cmakelists())
