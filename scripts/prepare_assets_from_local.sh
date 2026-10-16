#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ASSET_DIR="$ROOT_DIR/assets/redalert"
ALLIES_SRC=""
SOVIET_SRC=""

usage() {
  cat <<'USAGE'
Usage: scripts/prepare_assets_from_local.sh --allies DIR --soviet DIR

Copy locally provided Red Alert disc contents into the ignored assets tree.

Required:
  --allies DIR      Mounted or extracted Allies disc directory
  --soviet DIR      Mounted or extracted Soviet disc directory

Options:
  -h, --help        Show this help
USAGE
}

absolute_dir() {
  local path="$1"
  [[ -d "$path" ]] || { echo "Not a directory: $path" >&2; exit 2; }
  (cd "$path" && pwd -P)
}

validate_disc_root() {
  local name="$1"
  local source_dir="$2"

  if [[ ! -d "$source_dir/INSTALL" ]]; then
    echo "$name source does not look like a Red Alert disc root: missing INSTALL/" >&2
    exit 2
  fi

  if ! find "$source_dir" -maxdepth 3 -type f \( -iname '*.mix' -o -iname 'REDALERT.INI' \) -print -quit | grep -q .; then
    echo "$name source does not contain expected Red Alert data files" >&2
    exit 2
  fi
}

copy_disc() {
  local name="$1"
  local source_dir="$2"
  local target_dir="$ASSET_DIR/$name"

  validate_disc_root "$name" "$source_dir"
  mkdir -p "$target_dir"
  rsync -a --delete "$source_dir/" "$target_dir/"
  echo "Prepared $name assets in $target_dir"
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --allies)
      [[ $# -ge 2 ]] || { echo "--allies requires a directory" >&2; exit 2; }
      ALLIES_SRC="$(absolute_dir "$2")"
      shift 2
      ;;
    --soviet)
      [[ $# -ge 2 ]] || { echo "--soviet requires a directory" >&2; exit 2; }
      SOVIET_SRC="$(absolute_dir "$2")"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage >&2
      exit 2
      ;;
  esac
done

if [[ -z "$ALLIES_SRC" || -z "$SOVIET_SRC" ]]; then
  usage >&2
  exit 2
fi

copy_disc allies "$ALLIES_SRC"
copy_disc soviet "$SOVIET_SRC"
echo "Assets are ready under $ASSET_DIR"
