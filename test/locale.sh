#! /bin/sh

set -e

test `whoami` != root

mkdir -p /tmp/id3-test
FILE=/tmp/id3-test/unicode
cat /dev/null > $FILE

set -v
# testing euro in latin15
export LC_CTYPE=en_US.ISO8859-15
test `./id3 -q '\u20ac' /dev/null` = '�'
# testing euro in utf8
export LC_CTYPE=en_US.UTF-8
test `./id3 -q '\u20ac' /dev/null` = '€'
echo testing higher unicode
test `./id3 -q '\U10330' /dev/null` = '𐌰' 

# storing unicode in id3v2
./id3 -2 -a '\u20ac' -t '\U010330' $FILE
test `./id3 -2 -q '%a' $FILE` = '€'
test `./id3 -2 -q '%t' $FILE` = '𐌰' 

# storing unicode in filename
rm -f /tmp/id3-test/euro*
./id3 -2 -f "euro%aeuro" $FILE
test `./id3 -2 -q '%a' /tmp/id3-test/euro€euro` = '€'
test `./id3 -2 -q '%a' /tmp/id3-test/euro*euro` = '€'
test `./id3 -2 -q '%a' "/tmp/id3-test/euro?euro"` = '€'
test `./id3 -2 -q '%1' "/tmp/id3-test/euro*euro"` = '€'

# seems fine
