for file in $(find **/*.hpp); do
	echo "/* $file */"
	echo
	cat "$file"
done
