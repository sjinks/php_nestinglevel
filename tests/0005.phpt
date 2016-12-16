--TEST--
Test module info
--CGI--
--INI--
nl.max_level = 5
--SKIPIF--
<?php include('skipif.inc'); ?>
--FILE--
<?php
phpinfo(INFO_MODULES);
?>
--EXPECTREGEX--
.*Function Nesting Limit\s+=>\s+enabled.*nl\.max_level\s+=>\s+5\s+=>\s+5\n.*