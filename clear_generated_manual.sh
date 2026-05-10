#!/usr/bin/env bash

set -euo pipefail

usage() {
  cat <<'USAGE'
Usage: clear_generated_manual.sh [--dry-run] [--yes] [--doc-root PATH]

Remove generated manual documentation from misc/docs/website/*/manual.
Tutorials, resources, styles, scripts and website pages outside manual/ are not touched.

Options:
  --dry-run        Show what would be removed, but do not delete anything.
  --yes, -y        Do not ask for confirmation.
  --doc-root PATH  Use another documentation root instead of misc/docs/website.
  --help, -h       Show this help.

The script keeps manual/example.php and manual/.gitkeep when present.
USAGE
}

dry_run=0
yes=0
doc_root=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --dry-run)
      dry_run=1
      shift
      ;;
    --yes|-y)
      yes=1
      shift
      ;;
    --doc-root)
      if [ "$#" -lt 2 ]; then
        echo "error: --doc-root requires a path" >&2
        exit 2
      fi
      doc_root=$2
      shift 2
      ;;
    --help|-h)
      usage
      exit 0
      ;;
    *)
      echo "error: unknown option: $1" >&2
      usage >&2
      exit 2
      ;;
  esac
done

if [ -z "$doc_root" ]; then
  if root=$(git rev-parse --show-toplevel 2>/dev/null); then
    doc_root="$root/misc/docs/website"
  else
    doc_root="misc/docs/website"
  fi
fi

if [ ! -d "$doc_root" ]; then
  echo "error: documentation root not found: $doc_root" >&2
  exit 1
fi

manual_dirs=()
while IFS= read -r -d '' dir; do
  manual_dirs+=("$dir")
done < <(find "$doc_root" -mindepth 2 -maxdepth 2 -type d -name manual -print0 | sort -z)

if [ "${#manual_dirs[@]}" -eq 0 ]; then
  echo "No manual directory found under: $doc_root"
  exit 0
fi

targets=()
for manual in "${manual_dirs[@]}"; do
  while IFS= read -r -d '' entry; do
    targets+=("$entry")
  done < <(
    find "$manual" -mindepth 1 -maxdepth 1 \
      ! -name 'example.php' \
      ! -name '.gitkeep' \
      -print0 | sort -z
  )
done

if [ "${#targets[@]}" -eq 0 ]; then
  echo "No generated manual documentation to remove."
  exit 0
fi

echo "Manual documentation directories found: ${#manual_dirs[@]}"
printf '  %s\n' "${manual_dirs[@]}"
echo
echo "Entries to remove: ${#targets[@]}"
printf '  %s\n' "${targets[@]}"

if [ "$dry_run" -eq 1 ]; then
  echo
echo "Dry run only: nothing was removed."
  exit 0
fi

if [ "$yes" -ne 1 ]; then
  if [ -t 0 ]; then
    printf '\nRemove these generated manual entries? [y/N] '
    read -r answer
    case "$answer" in
      y|Y|yes|YES|Yes)
        ;;
      *)
        echo "Aborted."
        exit 0
        ;;
    esac
  else
    echo "Refusing to remove files without confirmation on a non-interactive input." >&2
    echo "Run again with --yes, or use --dry-run to preview." >&2
    exit 1
  fi
fi

rm -rf -- "${targets[@]}"
echo "Generated manual documentation cleared."
