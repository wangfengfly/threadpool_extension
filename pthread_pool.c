/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_pthread_pool.h"
#include "unistd.h"
#include "threadpool.c"

/* If you declare any globals in php_pthread_pool.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(pthread_pool)
*/

/* True global resources - no need for thread safety here */
static int le_pthread_pool;
threadpool_t* pool = NULL;
int total;

PHP_FUNCTION(threadpool_create){
	long tc, qs;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &tc, &qs) == FAILURE){
		RETURN_FALSE;
	}
	pool = threadpool_create(tc, qs, 0);
	if(pool == NULL){
		RETURN_FALSE;
	}
	total = qs;
	RETURN_TRUE;
}

PHP_FUNCTION(threadpool_add){
	zend_fcall_info  fci;
	zend_fcall_info_cache fci_cache;
	zval *retval_ptr = NULL;
	long s;
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lf*", &s, &fci, &fci_cache, &fci.params, &fci.param_count) == FAILURE) {
	        RETURN_FALSE;
	}
	fci.retval_ptr_ptr = &retval_ptr;

	int res, j;
	for(j=0; j<s; j++){
		res = threadpool_add(pool, &fci, &fci_cache, 0);
		if(res!=0){
			RETURN_FALSE;
		}
	}

	res = threadpool_destroy(pool, 1);
	if(fci.params) {
		efree(fci.params);
	}
	RETURN_TRUE;
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("pthread_pool.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_pthread_pool_globals, pthread_pool_globals)
    STD_PHP_INI_ENTRY("pthread_pool.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_pthread_pool_globals, pthread_pool_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_pthread_pool_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_pthread_pool_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "pthread_pool", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_pthread_pool_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_pthread_pool_init_globals(zend_pthread_pool_globals *pthread_pool_globals)
{
	pthread_pool_globals->global_value = 0;
	pthread_pool_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pthread_pool)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pthread_pool)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(pthread_pool)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(pthread_pool)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pthread_pool)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "pthread_pool support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ pthread_pool_functions[]
 *
 * Every user visible function must have an entry in pthread_pool_functions[].
 */
const zend_function_entry pthread_pool_functions[] = {
	PHP_FE(confirm_pthread_pool_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(threadpool_create, NULL)
	PHP_FE(threadpool_add, NULL)
	PHP_FE_END	/* Must be the last line in pthread_pool_functions[] */
};
/* }}} */

/* {{{ pthread_pool_module_entry
 */
zend_module_entry pthread_pool_module_entry = {
	STANDARD_MODULE_HEADER,
	"pthread_pool",
	pthread_pool_functions,
	PHP_MINIT(pthread_pool),
	PHP_MSHUTDOWN(pthread_pool),
	PHP_RINIT(pthread_pool),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pthread_pool),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pthread_pool),
	PHP_PTHREAD_POOL_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PTHREAD_POOL
ZEND_GET_MODULE(pthread_pool)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
