--TEST--
Check that nl.max_level can be modified from userspace
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php

class Test
{
	public function __get($property)
	{
		return 42;
	}
}

function run($x)
{
	$var = $x->some_property;
	echo $var, PHP_EOL;
}

ini_set('nl.max_level', 0);
$x = new Test();
run($x);

ini_set('nl.max_level', 1);
run($x);
?>
--EXPECTF--
42

Fatal error: Maximum function nesting level of '%d' has been reached in %s on line %d
