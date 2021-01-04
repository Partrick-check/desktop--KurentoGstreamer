#!/bin/bash
set -o errexit -o errtrace -o pipefail -o nounset
shopt -s inherit_errexit 2>/dev/null || true

shopt -s expand_aliases
BASENAME="$(basename "$0")"
echo_and_restore() {
    echo "[${BASENAME}] $(cat -)"
    case "$flags" in (*x*) set -x; esac
}
alias log='({ flags="$-"; set +x; } 2>/dev/null; echo_and_restore) <<<'

on_exit() {
    { _RC="$?"; set +x; } 2>/dev/null
    if ((_RC)); then log "ERROR ($_RC)"; fi
}
trap on_exit EXIT

usage() { grep '^#/' "$0" | cut --characters=4-; exit 0; }
REGEX='(^|\W)(-h|--help)($|\W)'
[[ "$*" =~ $REGEX ]] && usage || true
