#! /bin/bash
echo "comparing xxx_test.xml and xxx.xml"
bash compare.sh halfadder.xml halfadder_test.xml
bash compare.sh or2.xml or2_test.xml
bash compare.sh xor2.xml xor2_test.xml
bash compare.sh and2.xml and2_test.xml

echo "rewriting xxx_test.xml into the xxx.xml"
cat and2_test.xml > and2.xml
cat or2_test.xml > or2.xml
cat xor2_test.xml > xor2.xml
cat halfadder_test.xml > halfadder.xml

echo "supressing files xxx_test.xml"
rm and2_test.xml
rm or2_test.xml
rm xor2_test.xml
rm halfadder_test.xml
