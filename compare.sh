#!/bin/zsh

clear
make && \
clear && \
echo ------------  std ------------ && time ./stdcontainer | tee std && \
echo ------------  ft ------------ && time ./ftcontainer  | tee ft && \
echo ------------  diff ------------  &&
diff std ft && echo "No difference found"

# echo -----------------------------
# echo -n "std:  " && cat std | wc -l
# echo -n "ft:  " && cat ft | wc -l