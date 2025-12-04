#!/bin/sh
# Run 20 clients against the server
for i in 1 2 3 4 5 6 7 8 9 10 \
         11 12 13 14 15 16 17 18 19 20
do
    java ./counterclient.java localhost 9090 hello &
done
wait