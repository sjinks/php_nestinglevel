# php-nestinglimit

[![Build and Test](https://github.com/sjinks/php_nestinglevel/actions/workflows/test.yml/badge.svg)](https://github.com/sjinks/php_nestinglevel/actions/workflows/test.yml) [![codecov](https://codecov.io/gh/sjinks/php_nestinglevel/branch/master/graph/badge.svg)](https://codecov.io/gh/sjinks/php_nestinglevel)

PHP extension to control maximum function nesting level, and not let PHP crash with segmentation fault due to infinite recursion.

Tested with PHP 5.5, 5.6, 7.0, 7.1, 7.2, 7.3, 7.4, 8.0, 8.1, 8.2, 8.3, 8.4 nightly (currently, it's 8.5)

## Installing/Configuring

```bash
phpize
./configure
make
sudo make install
```

Then you will need to add a line like this to your `php.ini`:

```
extension=nl.so
```

or, for Windows,

```
extension=nl.dll
```

## INI settings

  * `nl.max_level`: maximum nesting level. Negative value or zero turns the extension off.
    * integer, defaults to -1 (disabled)
    * PHP_INI_ALL

### More Information

Please see [tests](https://github.com/sjinks/php_nestinglevel/tree/master/tests) for usage examples.
