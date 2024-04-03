
for i in ../examples/*; do
    echo "Testing $i"
    ../semantic/alanc < ../examples/$i
    echo
done