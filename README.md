Put it somewhere in your path and run it like this:

    vooblyslpdecode slp_in.slp slp_out.slp

For automation, create a dir called "decoded", and run the following in a CMD:

    for %I in (*.slp) do vooblyslpdecode "%I" "decoded\%~nI.slp"

Compiled with:

    gcc -s -static -o vooblyslpdecode.exe vooblyslpdecode.c