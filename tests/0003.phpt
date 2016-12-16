--TEST--
Test recursion involving internal function (2)
--INI--
nl.max_level = 9
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php
function f($n)
{
	echo $n, PHP_EOL;
	$tmp = array($n + 1);
	array_map('f', $tmp);
}

f(1);
?>
--EXPECTF--
1
2
3
4
5

Fatal error: Maximum function nesting level of '%d' has been reached in %s on line %d
