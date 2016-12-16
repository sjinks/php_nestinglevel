--TEST--
Recursion in user function
--INI--
nl.max_level = 10
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php
function f($n)
{
	echo $n, PHP_EOL;
	f($n+1);
}

f(1);
?>
--EXPECTF--
1
2
3
4
5
6
7
8
9
10

Fatal error: Maximum function nesting level of '10' has been reached in %s on line %d
