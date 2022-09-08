#!/usr/bin/awk -f

{
	sub(/ *$/, "")
}

/^[a-z].*(.*);$/ {
	print ".. c:function::", $0
	next
}

/^[a-z].*;$/ {
	print ".. c:var::", $0
	next
}

/^#define/ {
	print ".. c:macro::", $2
	next
}

/^\/\*$/ {
	print ""
	next
}

/^ \* / || /^ \*$/ {
	sub(/\*/, " ")
	print
	next
}

/^ \*\/$/ {
	print ""
	next
}
