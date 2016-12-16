--TEST--
Test magic methods
--INI--
nl.max_level = 1
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

$x = new Test();
run($x);
?>
--EXPECTF--
Fatal error: Maximum function nesting level of '%d' has been reached in %s on line %d
